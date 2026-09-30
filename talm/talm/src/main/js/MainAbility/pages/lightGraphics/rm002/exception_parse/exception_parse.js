// RM.002 异常场景-非法内容容错页逻辑
import router from '@system.router';

export default {
  goBack() {
    // 返回 rm002 入口页
    router.replace({ uri: 'pages/lightGraphics/rm002/index002' });
  }
};
