import router from '@system.router';

const TARGET_URI = 'pages/page_animation/target/target';
const FROM_URI = 'pages/page_animation/edge/edge';

// Register the measurement window (cross-page channel, see app.js). Must be called before
// router.replace(): the target page's onShow reads animSeq right away as this run's id.
function markAnimPending() {
  const app = getApp();
  if (app && app.data) {
    app.data.animSeq = (app.data.animSeq || 0) + 1;
    app.data.animFrom = FROM_URI;
    app.data.animPending = true;
  }
}

// End of the animation: on normal completion Router::FinishTransition() releases the old
// page, and ~StateMachine -> ChangeState(BACKGROUND_STATE) -> onHide fires while this JS
// object is still alive. The omitted-duration case below really does animate, so its onHide
// lands after the transition, exactly as on the regular pages. The other two cases do not
// animate (no animation argument / an invalid type degrades to none): the engine then releases
// this page before rendering the target, so onHide precedes the target's onShow and animPending
// is set without an animation to measure.
function recordAnimEnd() {
  const app = getApp();
  if (!app || !app.data || !app.data.animPending) {
    return; // this page did not just start an animated switch (e.g. the back-to-menu button)
  }
  app.data.animPending = false;
  app.data.animEndMs = Date.now();
  app.data.animEndSeq = app.data.animSeq;
  console.info('[measure] source onHide end=' + app.data.animEndMs + ' seq=' + app.data.animEndSeq);
}

// Edge cases: three non-redundant ones - no animation (animation argument omitted), an invalid
// type (degrades to no animation) and an omitted duration (the engine falls back to its
// default). duration=0, duration>5000 truncation and transition interruption were removed as
// redundant; the duration semantics and the ignore-second-trigger behaviour are covered by the
// engine.
export default {
  onInit() {
    console.info('page_animation/edge onInit');
  },
  goBaseline() {
    markAnimPending();
    router.replace({ uri: TARGET_URI, params: { type: 'none', from: FROM_URI } });
  },
  goInvalidType() {
    markAnimPending();
    router.replace({
      uri: TARGET_URI,
      params: { type: 'invalid', duration: 10000, from: FROM_URI },
      animation: { type: 'invalid', duration: 10000 }
    });
  },
  // duration omitted from animation: the engine falls back to TRANSITION_DURATION_DEFAULT
  // (300ms, router_module.cpp). params still carries 300 so the target page can display the
  // expected value and compare it with the measurement - if the engine's default ever changed,
  // the measured duration would drift away from the displayed one and the mismatch would show.
  // scale is used because it is the heaviest type, which is where such a drift shows first.
  goDefaultDuration() {
    markAnimPending();
    router.replace({
      uri: TARGET_URI,
      params: { type: 'scale', duration: 300, from: FROM_URI },
      animation: { type: 'scale' }
    });
  },
  onHide() {
    recordAnimEnd();
  },
  goBack() {
    router.replace({ uri: 'pages/page_animation/page_animation' });
  }
};
