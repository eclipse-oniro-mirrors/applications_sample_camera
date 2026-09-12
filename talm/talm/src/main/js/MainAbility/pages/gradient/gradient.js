import router from '@system.router';

export default {
  onInit() {
    console.info('gradient onInit');
  },
  goBack() {
    router.replace({ uri: 'pages/index/index'});
  }
};
