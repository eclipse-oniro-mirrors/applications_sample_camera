import router from '@system.router';
import app from '@system.app';

export default {
  data: {
  },
  onInit() {
    console.info('index onInit');
  },

  goBack() {
    app.terminate();
  },
  goFlex() {
    router.replace({ uri: 'pages/flex/flex'});
  },
  goLightGraphics() {
    router.replace({ uri: 'pages/lightGraphics/lightGraphics'});
  },
  goPageAnimation() {
    router.replace({ uri: 'pages/page_animation/page_animation'});
  }
};
