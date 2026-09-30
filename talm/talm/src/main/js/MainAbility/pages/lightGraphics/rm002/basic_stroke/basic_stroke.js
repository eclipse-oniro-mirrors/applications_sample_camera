// RM.002 基础用例-SVG描边样式页逻辑
import router from '@system.router';

export default {
  data: {
    ringPlaying: false,
  },
  goBack() {
    // 先停掉动画再返回，防止 SMIL 未清理导致 crash
    this.ringPlaying = false;
    // 返回基础用例分类页
    router.replace({ uri: 'pages/lightGraphics/rm002/basic/basic' });
  },
  toggleRing() {
    this.ringPlaying = !this.ringPlaying;
  },
};
