// RM.001 入口页逻辑：跳转到各用例分类页
import router from '@system.router';

export default {
  // 跳转到指定分类页
  navigateTo(page) {
    router.replace({ uri: 'pages/lightGraphics/rm001/' + page + '/' + page });
  },

  goBack() {
    // 返回轻图形入口页
    router.replace({ uri: 'pages/lightGraphics/lightGraphics' });
  }
};
