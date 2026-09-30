// RM.008 异常场景用例-非法路径值容错页逻辑
// 注意：Lite 端无 this.setData，数据更新一律用直接赋值 this.key = value
import router from '@system.router';

export default {
  data: {
    // 各用例播放状态：p1=013 非法offset-path，p2=014 非法offset-rotate，p3=015 非法duration
    p1: false,
    p2: false,
    p3: false,
    // 非法 animation-duration 值，编译期写 CSS 会报错，改为运行时通过内联 style 注入
    badDur: 'abc'
  },

  // 单用例开始/结束切换（挂载/卸载动画块即触发/复位）
  toggle(key) {
    this[key] = !this[key];
  },

  goBack() {
    // 返回 RM.008 入口页
    router.replace({ uri: 'pages/lightGraphics/rm008/index008' });
  }
};
