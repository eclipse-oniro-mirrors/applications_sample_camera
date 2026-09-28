export default {
  // ---- Cross-page channel for the measured transition duration ----
  // ace-loader bundles every page into a self-contained bundle (one entry per page), so local
  // modules cannot share state across pages; getApp().data is the only reliable cross-page
  // store. Sequence: the source page bumps animSeq and sets animPending before replace(); the
  // target page's onShow (animation start) writes animStartMs/animTargetSeq; the source page's
  // onHide (animation end) writes animEndMs/animEndSeq; the target page settles once both ends
  // of this seq are present.
  data: {
    animSeq: 0, // switch sequence number, incremented per switch
    animPending: false, // this page just started a switch towards the target page
    animTargetSeq: 0, // seq the target page is observing; 0 means none
    animStartMs: 0, // animation start timestamp (written by the target page's onShow)
    animEndSeq: -1, // seq whose end timestamp is written; -1 avoids matching the first seq=0
    animEndMs: 0, // animation end timestamp (written by the source page's onHide)
    animFrom: '' // uri of the source page of this switch, for logging only
  },
  onCreate() {
    console.info('Talm app onCreate');
  },
  onDestroy() {
    console.info('Talm app onDestroy');
  }
};
