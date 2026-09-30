// RM.006 基础用例-颜色渐变页逻辑
// talm lite 路由：replace + uri（replaceUrl/url 会跳转失败）
import router from '@system.router';

export default {
  goBack() {
    // 返回基础用例分类页
    router.replace({ uri: 'pages/lightGraphics/rm006/basic/basic' });
  }
};
