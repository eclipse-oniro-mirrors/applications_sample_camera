// RM.007 基础用例分类页逻辑
import router from '@system.router';

export default {
  // 跳转到指定特性测试页
  navigateTo(page) {
    // talm lite 路由：replace + uri（replaceUrl/url 会跳转失败）
    router.replace({ uri: 'pages/lightGraphics/rm007/' + page + '/' + page });
  },

  goBack() {
    // 返回 RM.007 入口页
    router.replace({ uri: 'pages/lightGraphics/rm007/index007' });
  }
};
