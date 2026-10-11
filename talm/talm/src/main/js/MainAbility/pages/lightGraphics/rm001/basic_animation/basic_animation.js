// RM.001 基础用例-SVG动画页逻辑
// 注意：Lite 端无 this.setData，数据更新一律用直接赋值 this.key = value
import router from '@system.router';

export default {
  data: {
    // 各卡片动画播放状态：true=挂载动画版SVG播放，false=卸载并显示静态帧
    play13: false,
    play14: false,
    play15: false,
    play16: false,
    play17: false,
    play18: false,
    play19: false,
    play20: false,
    play21: false
  },

  // 播放/停止切换：key 为对应卡片的状态字段名
  togglePlay(key) {
    this[key] = !this[key];
  },

  goBack() {
    // 先停掉所有动画，防止页面替换时 SMIL 未清理导致 crash
    this.play13 = false;
    this.play14 = false;
    this.play15 = false;
    this.play16 = false;
    this.play17 = false;
    this.play18 = false;
    this.play19 = false;
    this.play20 = false;
    this.play21 = false;
    router.replace({ uri: 'pages/lightGraphics/rm001/basic/basic' });
  }
};
