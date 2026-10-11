// RM.007 异常场景用例-非法转场容错页逻辑 — 013~016，参考 demo 写法：去掉 show，先 startTransition 再改状态
// Lite 端无 this.setData，数据更新一律用直接赋值 this.key = value
import router from '@system.router';

export default {
  data: {
    s013: 'a',
    s014: 'a',
    s015: 'a',
    s016: 'a'
  },

  switch013() {
    const next = (this.s013 === 'a') ? 'b' : 'a';
    this.$refs.st013.startTransition(this.$refs[next === 'a' ? 'a013' : 'b013']);
    this.s013 = next;
  },

  switch014() {
    const next = (this.s014 === 'a') ? 'b' : 'a';
    this.$refs.st014.startTransition(this.$refs[next === 'a' ? 'a014' : 'b014']);
    this.s014 = next;
  },

  switch015() {
    const next = (this.s015 === 'a') ? 'b' : 'a';
    this.$refs.st015.startTransition(this.$refs[next === 'a' ? 'a015' : 'b015']);
    this.s015 = next;
  },

  switch016() {
    const next = (this.s016 === 'a') ? 'b' : 'a';
    this.$refs.st016.startTransition(this.$refs[next === 'a' ? 'a016' : 'b016']);
    this.s016 = next;
  },

  goBack() {
    router.replace({ uri: 'pages/lightGraphics/rm007/index007' });
  }
};
