// RM.008 基础用例-沿指定路径移动页逻辑
// 注意：Lite 端无 this.setData，数据更新一律用直接赋值 this.key = value
import router from '@system.router';

export default {
  data: {
    // 各用例播放状态：p1=001 直线，p2=002 折线，p3=003 沿路径旋转，p4=004 循环，p5=005 折线90度旋转
    p1: false,
    p2: false,
    p3: false,
    p4: false,
    p5: false
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
