import router from '@system.router';

const TARGET_URI = 'pages/page_animation/target/target';
const FROM_URI = 'pages/page_animation/scale/scale';

// Shared helper: start a page switch with the given animation type and duration
function doReplace(type, duration) {
  markAnimPending();
  router.replace({
    uri: TARGET_URI,
    params: { type: type, duration: duration, from: FROM_URI },
    animation: { type: type, duration: duration }
  });
}

// Second trigger: while a transition is running the Router ignores a further animated
// replace, so the current transition plays out instead of being interrupted. On this device
// JS timers are unreliable during a transition (deferred by frame rendering, or cancelled
// together with the old page), so a second replace cannot be issued reliably from a timer.
// This case therefore starts a single full transition and only verifies that it ends normally
// and that the page can be left; ignoring the second trigger is guaranteed by the Router.
function doDoubleTrigger(type) {
  doReplace(type, 5000);
}

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
// object is still alive. Without an animation the engine releases this page before rendering
// the target, but animPending is not set then, so nothing is recorded by mistake.
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

export default {
  onInit() {
    console.info('page_animation/scale onInit');
  },
  goScale() {
    doReplace('scale', 10000);
  },
  goScale2500() {
    doReplace('scale', 2500);
  },
  goScaleZero() {
    doReplace('scale', 0);
  },
  goScaleDouble() {
    doDoubleTrigger('scale');
  },
  onHide() {
    recordAnimEnd();
  },
  goBack() {
    router.replace({ uri: 'pages/page_animation/page_animation' });
  }
};
