// RM.009 基础用例-串行/并行动画页逻辑
// 注意：Lite 端无 this.setData，数据更新一律用直接赋值 this.key = value
import router from '@system.router';

export default {
  data: {
    p010: false,
    p011: false,
    p012: false,
    rendered010: true,
    rendered011: true,
    rendered012: true
  },

  toggle010() {
    if (this.p010) {
      this.rendered010 = false;
      this.p010 = false;
      setTimeout(() => { this.rendered010 = true }, 100);
    } else {
      this.p010 = true;
      this.rendered010 = true;
    }
  },

  toggle011() {
    if (this.p011) {
      this.rendered011 = false;
      this.p011 = false;
      setTimeout(() => { this.rendered011 = true }, 100);
    } else {
      this.p011 = true;
      this.rendered011 = true;
    }
  },

  toggle012() {
    if (this.p012) {
      this.rendered012 = false;
      this.p012 = false;
      setTimeout(() => { this.rendered012 = true }, 100);
    } else {
      this.p012 = true;
      this.rendered012 = true;
    }
  },

  goBack() {
    router.replace({ uri: 'pages/lightGraphics/rm009/basic/basic' });
  }
};
