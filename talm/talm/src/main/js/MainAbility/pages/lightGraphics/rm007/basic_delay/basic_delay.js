// RM.007 延迟转场页逻辑 — 008，参考 demo 写法：去掉 show，先 startTransition 再改状态
// Lite 端无 this.setData，数据更新一律用直接赋值 this.key = value
import router from '@system.router';

export default {
  data: {
    delayShow: 'a'
  },

  switchDelay() {
    const next = (this.delayShow === 'a') ? 'b' : 'a';
    this.$refs.delayStage.startTransition(this.$refs[next === 'a' ? 'delayA' : 'delayB']);
    this.delayShow = next;
  },

  goBack() {
    router.replace({ uri: 'pages/lightGraphics/rm007/basic/basic' });
  }
};
