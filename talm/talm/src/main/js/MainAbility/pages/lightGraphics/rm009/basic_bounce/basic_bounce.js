// RM.009 基础用例-弹跳插值动画页逻辑
// 注意：Lite 端无 this.setData，数据更新一律用直接赋值 this.key = value
import router from '@system.router';

export default {
  data: {
    // 动画播放状态：true=挂载动画块（挂载即启动），false=挂载静态起始态块
    playing: false,
    // 元素挂载状态：用于结束动画时卸载重挂载强制复位
    rendered: true
  },

  // 开始/结束切换
  toggle() {
    if (this.playing) {
      this.rendered = false;
      this.playing = false;
      setTimeout(() => { this.rendered = true }, 50);
    } else {
      this.playing = true;
      this.rendered = true;
    }
  },

  goBack() {
    router.replace({ uri: 'pages/lightGraphics/rm009/basic/basic' });
  }
};
