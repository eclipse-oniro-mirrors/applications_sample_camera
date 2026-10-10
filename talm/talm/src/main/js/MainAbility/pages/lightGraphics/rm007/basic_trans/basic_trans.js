// RM.007 基础转场页逻辑 — 001~006，参考 demo 写法：去掉 show，先 startTransition 再改状态
// Lite 端无 this.setData，数据更新一律用直接赋值 this.key = value
import router from '@system.router';

export default {
  data: {
    s001: 'a',
    s002: 'a',
    s003: 'a',
    s004: 'a',
    s005: 'a',
    s006: 'a'
  },

  switch001() {
    const next = (this.s001 === 'a') ? 'b' : 'a';
    this.$refs.st001.startTransition(this.$refs[next === 'a' ? 'a001' : 'b001']);
    this.s001 = next;
  },

  switch002() {
    const next = (this.s002 === 'a') ? 'b' : 'a';
    this.$refs.st002.startTransition(this.$refs[next === 'a' ? 'a002' : 'b002']);
    this.s002 = next;
  },

  switch003() {
    const next = (this.s003 === 'a') ? 'b' : 'a';
    this.$refs.st003.startTransition(this.$refs[next === 'a' ? 'a003' : 'b003']);
    this.s003 = next;
  },

  switch004() {
    const next = (this.s004 === 'a') ? 'b' : 'a';
    this.$refs.st004.startTransition(this.$refs[next === 'a' ? 'a004' : 'b004']);
    this.s004 = next;
  },

  switch005() {
    const next = (this.s005 === 'a') ? 'b' : 'a';
    this.$refs.st005.startTransition(this.$refs[next === 'a' ? 'a005' : 'b005']);
    this.s005 = next;
  },

  switch006() {
    const next = (this.s006 === 'a') ? 'b' : 'a';
    this.$refs.st006.startTransition(this.$refs[next === 'a' ? 'a006' : 'b006']);
    this.s006 = next;
  },

  goBack() {
    router.replace({ uri: 'pages/lightGraphics/rm007/basic/basic' });
  }
};
