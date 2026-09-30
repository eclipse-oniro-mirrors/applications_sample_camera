// RM.001 基础用例分类页逻辑
import router from '@system.router';

export default {
  // 跳转到指定特性测试页
  navigateTo(page) {
    router.replace({ uri: 'pages/lightGraphics/rm001/' + page + '/' + page });
  },

  goBack() {
    // 返回 rm001 入口页
    router.replace({ uri: 'pages/lightGraphics/rm001/index001' });
  }
};
