import router from '@system.router';

// Keyed by the engine's animation.type string, which reaches this page through the router
// params (js_page_state_machine.cpp: RegisterUriAndParamsToPage). The keys are quoted on
// purpose: they are API values rather than variable names, and the engine spells the slide
// types in snake case, which the camelcase naming check would otherwise flag.
const TYPE_MAP = {
  'fade': { title: 'Fade 淡入淡出动效', bgColor: '#e67e22', animated: true },
  'scale': { title: 'Scale 缩放动效', bgColor: '#2ecc71', animated: true },
  'slide_left': { title: 'Slide Left 左滑入', bgColor: '#3498db', animated: true },
  'slide_right': { title: 'Slide Right 右滑入', bgColor: '#9b59b6', animated: true },
  'slide_up': { title: 'Slide Up 上滑入', bgColor: '#1abc9c', animated: true },
  'slide_down': { title: 'Slide Down 下滑入', bgColor: '#f39c12', animated: true },
  'slide_over_left': { title: 'Slide Over Left 覆盖左滑', bgColor: '#e74c3c', animated: true },
  'slide_over_right': { title: 'Slide Over Right 覆盖右滑', bgColor: '#34495e', animated: true },
  'slide_over_up': { title: 'Slide Over Up 覆盖上滑', bgColor: '#16a085', animated: true },
  'slide_over_down': { title: 'Slide Over Down 覆盖下滑', bgColor: '#8e44ad', animated: true },
  'none': { title: '无动效目标页 (baseline)', bgColor: '#7f8c8d', animated: false },
  'invalid': { title: '无效 type 已降级', bgColor: '#95a5a6', animated: false }
};

// Aligned with the engine's router_module.cpp: duration is clamped to [0, 5000]
// (TRANSITION_DURATION_MAX), so a button that sets 10000ms actually plays for 5000ms - which is
// exactly the difference this page is meant to expose.
const ANIM_DURATION_MAX = 5000;
// Polling parameters: JS timers are deferred by frame rendering during a transition, so the
// first check is placed after the expected end plus a margin, followed by bounded retries.
// Checking earlier would only waste attempts.
const FIRST_CHECK_MARGIN = 120;
const RETRY_INTERVAL = 200;
const MAX_ATTEMPTS = 20;
const TEXT_MEASURING = '测量中…';
const TEXT_NO_ANIM = '-- (无动效)';
const TEXT_TIMEOUT = '未测到';

function appData() {
  return getApp().data;
}

// Settle the measured duration; returns true once this run is over (settled, or no animation),
// so the caller stops polling.
function settle(page, seq) {
  const d = appData();
  if (d.animEndSeq !== seq) {
    return false; // the source page's onHide has not written its end timestamp yet
  }
  if (d.animEndMs < d.animStartMs) {
    // End before start: when StartPageTransition() fails the engine falls back to no animation
    // (js_router.cpp), and the source page's onHide then precedes this page's onShow, leaving no
    // animation interval to measure.
    page.actualText = TEXT_NO_ANIM;
    return true;
  }
  const actual = d.animEndMs - d.animStartMs;
  page.actualText = actual + 'ms';
  console.info('[measure] actual=' + actual + 'ms set=' + page.duration + 'ms type=' + page.type +
    ' start=' + d.animStartMs + ' end=' + d.animEndMs);
  return true;
}

export default {
  data: {
    type: 'none',
    duration: 0,
    title: '',
    bgColor: '#7f8c8d',
    from: '',
    // Measured-duration display: measuring / 1234ms / '-- (no animation)' / not measured
    actualText: '--',
    // Whether this page instance has already started a measurement (onShow fires again when the
    // app returns to the foreground; this keeps the timer from restarting)
    measured: false
  },
  onInit() {
    console.info('page_animation/target onInit');
    const t = this.type || 'none';
    const cfg = TYPE_MAP[t] || TYPE_MAP.none;
    this.type = t;
    this.title = cfg.title;
    this.bgColor = cfg.bgColor;
  },
  onShow() {
    if (this.measured) {
      return; // onShow fired again after a resume from background; do not restart
    }
    this.measured = true;

    const d = appData();
    const seq = d.animSeq;
    // This page's onShow marks the animation start: in js_router.cpp's
    // ReplaceSyncWithTransition() StartPageTransition() has already applied the first frame and
    // started the Animator, and the following ChangeState(SHOW_STATE) triggers this callback
    // while no animation frame has run yet.
    d.animStartMs = Date.now();
    d.animTargetSeq = seq;

    const t = this.type || 'none';
    const cfg = TYPE_MAP[t] || TYPE_MAP.none;
    // The engine copies duration into the page data as is (RegisterUriAndParamsToPage in
    // js_page_state_machine.cpp only calls jerry_set_property, with no string conversion), so it
    // is normally a number; it is still coerced defensively here so that a type mismatch cannot
    // silently degrade to "no animation" and be misread.
    const rawDur = (typeof this.duration === 'number') ? this.duration : Number(this.duration);
    const setMs = (rawDur > 0) ? rawDur : 0; // NaN > 0 is false, so invalid values become 0
    if (!cfg.animated || setMs <= 0) {
      // The engine treats this as no animation (invalid type / duration<=0): nothing to measure
      this.actualText = TEXT_NO_ANIM;
      console.info('[measure] no animation: type=' + t + ' duration=' + this.duration);
      return;
    }
    this.actualText = TEXT_MEASURING;
    // Printed unconditionally so the serial log confirms which build is actually running on the
    // board (useful when a stale hap is suspected)
    console.info('[measure] target onShow seq=' + seq + ' type=' + t + ' set=' + setMs + 'ms, measuring');

    const expectedMs = (setMs > ANIM_DURATION_MAX) ? ANIM_DURATION_MAX : setMs;
    // `this` inside a setTimeout callback is not the page object (timer_module.cpp passes the
    // global object), so the page reference must be captured in a closure; otherwise
    // self.actualText silently fails to reach the page and nothing is reported.
    const self = this;
    let attempts = 0;
    const tick = function () {
      attempts++;
      const cur = appData();
      if (cur.animTargetSeq !== seq) {
        return; // this page was replaced or a new switch started; abandon this run
      }
      if (settle(self, seq)) {
        return;
      }
      if (attempts >= MAX_ATTEMPTS) {
        self.actualText = TEXT_TIMEOUT;
        console.info('[measure] timeout waiting source onHide, seq=' + seq);
        return;
      }
      setTimeout(tick, RETRY_INTERVAL);
    };
    setTimeout(tick, expectedMs + FIRST_CHECK_MARGIN);
  },
  onHide() {
    // This page is being replaced (including tapping back during a transition): void the pending
    // run so an expired timer cannot write into a released page
    appData().animTargetSeq = 0;
  },
  goBack() {
    // Go back to the originating group page when arriving from one, otherwise back to the menu
    if (this.from) {
      router.replace({ uri: this.from });
    } else {
      router.replace({ uri: 'pages/page_animation/page_animation' });
    }
  }
};
