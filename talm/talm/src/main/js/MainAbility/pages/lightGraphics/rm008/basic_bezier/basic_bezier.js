// RM.008 基础用例-贝塞尔曲线路径动画页逻辑
// 注意：Lite 端无 this.setData，数据更新一律用直接赋值 this.key = value
import router from '@system.router';

export default {
  data: {
    // 各用例播放状态：p1=006 二次贝塞尔，p2=007 三次贝塞尔，p3=008 贝塞尔长方形自动旋转
    p1: false,
    p2: false,
    p3: false
  },

  // 单用例开始/结束切换（挂载/卸载动画块即触发/复位）
  toggle(key) {
    this[key] = !this[key];
  },

  goBack() {
    // 返回基础用例分类页
    router.replace({ uri: 'pages/lightGraphics/rm008/basic/basic' });
  }
};
