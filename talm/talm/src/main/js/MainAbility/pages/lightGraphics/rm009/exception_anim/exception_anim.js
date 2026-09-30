// RM.009 异常场景用例-非法动画容错页逻辑
// 多组异常值经数据绑定内联注入，绕开编译期校验，专测运行时容错降级
import router from '@system.router';

export default {
  data: {
    // 016 状态
    p016: false,
    rendered016: true,
    // 017 状态
    p017: false,
    rendered017: true,
    // 018 状态
    p018: false,
    rendered018: true,
    // 019 状态
    p019: false,
    rendered019: true,
    // 020 状态
    p020: false,
    rendered020: true,
    // 021 状态
    p021: false,
    rendered021: true,
    // 022 状态
    p022: false,
    rendered022: true,
    // 023 状态
    p023: false,
    rendered023: true,
    // 016 复合非法动画属性
    badDuration: 'abc',
    badTiming: 'notatype',
    // 017 负数动画时长
    negativeDuration: '-1000ms',
    // 018 极大动画时长
    hugeDuration: '99999999ms',
    // 019 负数迭代次数
    negativeIter: '-1',
    // 020 超界透明度
    hugeOpacity: '2'
  },

  toggle016() {
    if (this.p016) {
      this.rendered016 = false;
      this.p016 = false;
      setTimeout(() => { this.rendered016 = true }, 50);
    } else {
      this.p016 = true;
      this.rendered016 = true;
    }
  },

  toggle017() {
    if (this.p017) {
      this.rendered017 = false;
      this.p017 = false;
      setTimeout(() => { this.rendered017 = true }, 50);
    } else {
      this.p017 = true;
      this.rendered017 = true;
    }
  },

  toggle018() {
    if (this.p018) {
      this.rendered018 = false;
      this.p018 = false;
      setTimeout(() => { this.rendered018 = true }, 50);
    } else {
      this.p018 = true;
      this.rendered018 = true;
    }
  },

  toggle019() {
    if (this.p019) {
      this.rendered019 = false;
      this.p019 = false;
      setTimeout(() => { this.rendered019 = true }, 50);
    } else {
      this.p019 = true;
      this.rendered019 = true;
    }
  },

  toggle020() {
    if (this.p020) {
      this.rendered020 = false;
      this.p020 = false;
      setTimeout(() => { this.rendered020 = true }, 50);
    } else {
      this.p020 = true;
      this.rendered020 = true;
    }
  },

  toggle021() {
    if (this.p021) {
      this.rendered021 = false;
      this.p021 = false;
      setTimeout(() => { this.rendered021 = true }, 50);
    } else {
      this.p021 = true;
      this.rendered021 = true;
    }
  },

  toggle022() {
    if (this.p022) {
      this.rendered022 = false;
      this.p022 = false;
      setTimeout(() => { this.rendered022 = true }, 50);
    } else {
      this.p022 = true;
      this.rendered022 = true;
    }
  },

  toggle023() {
    if (this.p023) {
      this.rendered023 = false;
      this.p023 = false;
      setTimeout(() => { this.rendered023 = true }, 50);
    } else {
      this.p023 = true;
      this.rendered023 = true;
    }
  },

  goBack() {
    router.replace({ uri: 'pages/lightGraphics/rm009/index009' });
  }
};