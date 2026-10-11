// RM.006 基础用例分类页逻辑
// talm lite 路由：replace + uri（replaceUrl/url 会跳转失败）
import router from '@system.router';

export default {
  // 跳转到指定特性测试页
  navigateTo(page) {
    router.replace({ uri: 'pages/lightGraphics/rm006/' + page + '/' + page });
  },

  goBack() {
    // 返回 RM.006 入口页
    router.replace({ uri: 'pages/lightGraphics/rm006/index006' });
  }
};
