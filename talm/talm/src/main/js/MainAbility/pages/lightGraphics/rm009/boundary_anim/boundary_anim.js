// RM.009 边界约束用例-动画边界页逻辑
// 注意：Lite 端无 this.setData，数据更新一律用直接赋值 this.key = value
import router from '@system.router';

export default {
  data: {
    p014: false,
    p015: false,
    rendered014: true,
    rendered015: true
  },

  toggle014() {
    if (this.p014) {
      this.rendered014 = false;
      this.p014 = false;
      setTimeout(() => { this.rendered014 = true }, 50);
    } else {
      this.p014 = true;
      this.rendered014 = true;
    }
  },

  toggle015() {
    if (this.p015) {
      this.rendered015 = false;
      this.p015 = false;
      setTimeout(() => { this.rendered015 = true }, 50);
    } else {
      this.p015 = true;
      this.rendered015 = true;
    }
  },

  goBack() {
    router.replace({ uri: 'pages/lightGraphics/rm009/index009' });
  }
};
