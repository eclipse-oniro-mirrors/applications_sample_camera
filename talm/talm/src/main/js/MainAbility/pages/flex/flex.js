import router from '@system.router';

export default {
  onInit() {
    console.info('flex onInit');
  },
  goBack() {
    router.replace({ uri: 'pages/index/index'});
  }
};
