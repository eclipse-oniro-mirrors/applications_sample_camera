// RM.002 基础用例分类页逻辑
import router from '@system.router';

export default {
  // 跳转到指定特性测试页
  navigateTo(page) {
    router.replace({ uri: 'pages/lightGraphics/rm002/' + page + '/' + page });
  },

  goBack() {
    // 返回 rm002 入口页
    router.replace({ uri: 'pages/lightGraphics/rm002/index002' });
  }
};
