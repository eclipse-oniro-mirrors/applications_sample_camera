// 首页逻辑：路由跳转控制
import router from '@system.router';

export default {
  // 导航到指定测试页面
  navigateTo(page) {
    // 鸿蒙Lite路由跳转，目标页面对应 pages/页面名/页面名 结构
    router.replace({ uri: 'pages/' + 'lightGraphics/' + 'rm' + page + '/index' + page });
  },

  goBack() {
    // 返回首页
    router.replace({ uri: 'pages/index/index'});
  }
};
