// RM.009 入口页逻辑：跳转到各用例分类页
// talm lite 路由：replace + uri（replaceUrl/url 会跳转失败）
import router from '@system.router';

export default {
  // 跳转到指定分类页
  navigateTo(page) {
    if (page === 'boundary') {
      router.replace({ uri: 'pages/lightGraphics/rm009/boundary_anim/boundary_anim' });
    } else if (page === 'exception') {
      router.replace({ uri: 'pages/lightGraphics/rm009/exception_anim/exception_anim' });
    } else {
      router.replace({ uri: 'pages/lightGraphics/rm009/' + page + '/' + page });
    }
  },

  goBack() {
    // 返回轻图形入口页
    router.replace({ uri: 'pages/lightGraphics/lightGraphics' });
  }
};
