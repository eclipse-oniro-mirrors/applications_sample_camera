// RM.001 异常场景-属性异常值专项测试页逻辑
import router from '@system.router';

export default {
  data: {
    // 各卡片动画播放状态：true=挂载动画版SVG播放，false=卸载并显示静态帧
    play31: false
  },

  // 播放/停止切换：key 为对应卡片的状态字段名
  togglePlay(key) {
    this[key] = !this[key];
  },

  goBack() {
    // 先停掉动画再返回，防止 SMIL 未清理导致 crash
    this.play31 = false;
    // 返回 rm001 入口页
    router.replace({ uri: 'pages/lightGraphics/rm001/index001' });
  }
};
