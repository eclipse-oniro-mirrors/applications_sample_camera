// RM.009 基础用例-基础动画页逻辑
// 注意：Lite 端无 this.setData，数据更新一律用直接赋值 this.key = value
import router from '@system.router';

export default {
  data: {
    p001: false,
    p002: false,
    p003: false,
    p004: false,
    p005: false,
    p006: false,
    p007: false,
    p008: false,
    rendered001: true,
    rendered002: true,
    rendered003: true,
    rendered004: true,
    rendered005: true,
    rendered006: true,
    rendered007: true,
    rendered008: true,
    p013: false,
    rendered013: true
  },

  toggle001() {
    if (this.p001) {
      this.rendered001 = false;
      this.p001 = false;
      setTimeout(() => { this.rendered001 = true }, 50);
    } else {
      this.p001 = true;
      this.rendered001 = true;
    }
  },
  toggle002() {
    if (this.p002) {
      this.rendered002 = false;
      this.p002 = false;
      setTimeout(() => { this.rendered002 = true }, 50);
    } else {
      this.p002 = true;
      this.rendered002 = true;
    }
  },
  toggle003() {
    if (this.p003) {
      this.rendered003 = false;
      this.p003 = false;
      setTimeout(() => { this.rendered003 = true }, 50);
    } else {
      this.p003 = true;
      this.rendered003 = true;
    }
  },
  toggle004() {
    if (this.p004) {
      this.rendered004 = false;
      this.p004 = false;
      setTimeout(() => { this.rendered004 = true }, 50);
    } else {
      this.p004 = true;
      this.rendered004 = true;
    }
  },
  toggle005() {
    if (this.p005) {
      this.rendered005 = false;
      this.p005 = false;
      setTimeout(() => { this.rendered005 = true }, 50);
    } else {
      this.p005 = true;
      this.rendered005 = true;
    }
  },
  toggle006() {
    if (this.p006) {
      this.rendered006 = false;
      this.p006 = false;
      setTimeout(() => { this.rendered006 = true }, 50);
    } else {
      this.p006 = true;
      this.rendered006 = true;
    }
  },
  toggle007() {
    if (this.p007) {
      this.rendered007 = false;
      this.p007 = false;
      setTimeout(() => { this.rendered007 = true }, 50);
    } else {
      this.p007 = true;
      this.rendered007 = true;
    }
  },
  toggle008() {
    if (this.p008) {
      this.rendered008 = false;
      this.p008 = false;
      setTimeout(() => { this.rendered008 = true }, 50);
    } else {
      this.p008 = true;
      this.rendered008 = true;
    }
  },

  toggle013() {
    if (this.p013) {
      this.rendered013 = false;
      this.p013 = false;
      setTimeout(() => { this.rendered013 = true }, 50);
    } else {
      this.p013 = true;
      this.rendered013 = true;
    }
  },

  goBack() {
    router.replace({ uri: 'pages/lightGraphics/rm009/basic/basic' });
  }
};
