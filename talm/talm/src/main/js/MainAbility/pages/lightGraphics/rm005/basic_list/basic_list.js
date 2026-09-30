// RM.005 基础用例-List 方向渐变页逻辑
import router from '@system.router';

export default {
  goBack() {
    // 返回基础用例分类页
    // talm lite 路由：replace + uri（replaceUrl/url 会跳转失败）
    router.replace({ uri: 'pages/lightGraphics/rm005/basic/basic' });
  }
};
