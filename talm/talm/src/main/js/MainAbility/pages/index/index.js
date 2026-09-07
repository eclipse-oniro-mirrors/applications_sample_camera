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
  goSvg() {
    router.replace({ uri: 'pages/svg/svg'});
  },
  goAnimation() {
    router.replace({ uri: 'pages/animation/animation'});
  },
  goGradient() {
    router.replace({ uri: 'pages/gradient/gradient'});
  }
};
