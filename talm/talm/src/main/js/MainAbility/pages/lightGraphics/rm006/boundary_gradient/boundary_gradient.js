// RM.006 边界约束-渐变边界页逻辑
// talm lite 路由：replace + uri（replaceUrl/url 会跳转失败）
import router from '@system.router';

export default {
  goBack() {
    // 返回 RM.006 入口页
    router.replace({ uri: 'pages/lightGraphics/rm006/index006' });
  }
};
