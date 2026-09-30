// RM.008 边界约束用例-路径边界页逻辑
// 注意：Lite 端无 this.setData，数据更新一律用直接赋值 this.key = value
import router from '@system.router';

export default {
  data: {
    // 各用例播放状态：p1=009 零长度，p2=010 超长时长，p3=011 负数duration，p4=012 0ms duration
    p1: false,
    p2: false,
    p3: false,
    p4: false
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
