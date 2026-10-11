import router from '@system.router';

export default {
  onInit() {
    console.info('animation onInit');
  },
  goBack() {
    router.replace({ uri: 'pages/index/index'});
  }
};
