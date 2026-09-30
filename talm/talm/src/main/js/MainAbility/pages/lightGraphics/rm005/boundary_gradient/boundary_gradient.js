// RM.005 边界约束-渐变边界页逻辑
import router from '@system.router';

export default {
  goBack() {
    // 返回 RM.005 入口页
    // talm lite 路由：replace + uri（replaceUrl/url 会跳转失败）
    router.replace({ uri: 'pages/lightGraphics/rm005/index005' });
  }
};
