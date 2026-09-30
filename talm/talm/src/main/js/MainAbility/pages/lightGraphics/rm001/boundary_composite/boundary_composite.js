// RM.001 边界测试合集页逻辑
import router from '@system.router';

export default {
  data: {
    play22: false,
    play23: false
  },

  togglePlay(key) {
    this[key] = !this[key];
  },

  goBack() {
    // 先停掉动画再返回，防止 SMIL 未清理导致 crash
    this.play22 = false;
    this.play23 = false;
    router.replace({ uri: 'pages/lightGraphics/rm001/index001' });
  }
};
