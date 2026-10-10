import router from '@system.router';

export default {
  onInit() {
    console.info('page_animation menu onInit');
  },
  goFade() {
    router.replace({ uri: 'pages/page_animation/fade/fade' });
  },
  goScale() {
    router.replace({ uri: 'pages/page_animation/scale/scale' });
  },
  goSlide() {
    router.replace({ uri: 'pages/page_animation/slide/slide' });
  },
  goOver() {
    router.replace({ uri: 'pages/page_animation/over/over' });
  },
  goEdge() {
    router.replace({ uri: 'pages/page_animation/edge/edge' });
  },
  goBack() {
    router.replace({ uri: 'pages/index/index' });
  }
};
