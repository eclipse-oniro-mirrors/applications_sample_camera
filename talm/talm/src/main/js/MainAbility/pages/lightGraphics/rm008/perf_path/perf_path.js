// RM.008 性能用例-批量路径动画页逻辑
// 注意：Lite 端无 this.setData，数据更新一律用直接赋值 this.key = value
import router from '@system.router';

export default {
  data: {
    // 用例播放状态：p1=016 批量路径动画
    p1: false,
    // 生成 12 个占位对象，用于 for 循环渲染 12 个路径动画单元格
    blocks: [
      {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}
    ]
  },

  // 单用例开始/结束切换（挂载/卸载动画块即触发/复位）
  toggle(key) {
    this[key] = !this[key];
  },

  goBack() {
    // 返回性能用例分类页
    router.replace({ uri: 'pages/lightGraphics/rm008/performance/performance' });
  }
};
