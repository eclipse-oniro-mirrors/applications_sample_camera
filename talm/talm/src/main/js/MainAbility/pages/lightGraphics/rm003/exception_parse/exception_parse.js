// RM.003 异常场景-SVG解析非法内容容错页逻辑
import router from '@system.router';

export default {
  goBack() {
    // 返回 rm003 入口页
    router.replace({ uri: 'pages/lightGraphics/rm003/index003' });
  }
};
