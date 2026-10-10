// RM.007 边界约束用例-转场时长边界页逻辑 — 009~012，参考 demo 写法：去掉 show，先 startTransition 再改状态
// Lite 端无 this.setData，数据更新一律用直接赋值 this.key = value
import router from '@system.router';

export default {
  data: {
    s009: 'a',
    s010: 'a',
    s011: 'a',
    s012: 'a'
  },

  switch009() {
    const next = (this.s009 === 'a') ? 'b' : 'a';
    this.$refs.st009.startTransition(this.$refs[next === 'a' ? 'a009' : 'b009']);
    this.s009 = next;
  },

  switch010() {
    const next = (this.s010 === 'a') ? 'b' : 'a';
    this.$refs.st010.startTransition(this.$refs[next === 'a' ? 'a010' : 'b010']);
    this.s010 = next;
  },

  switch011() {
    const next = (this.s011 === 'a') ? 'b' : 'a';
    this.$refs.st011.startTransition(this.$refs[next === 'a' ? 'a011' : 'b011']);
    this.s011 = next;
  },

  switch012() {
    const next = (this.s012 === 'a') ? 'b' : 'a';
    this.$refs.st012.startTransition(this.$refs[next === 'a' ? 'a012' : 'b012']);
    this.s012 = next;
  },

  goBack() {
    router.replace({ uri: 'pages/lightGraphics/rm007/index007' });
  }
};
