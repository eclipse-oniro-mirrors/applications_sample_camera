import router from '@system.router';

export default {
  onInit() {
    console.info('svg onInit');
  },
  goBack() {
    router.replace({ uri: 'pages/index/index'});
  }
};
