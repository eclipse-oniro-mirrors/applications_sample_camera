// RM.002 基础用例-SVG变换页逻辑
// 点击按钮切换变换/恢复状态，再次点击可重新变换
import router from '@system.router';

export default {
  data: {
    applied7: false,
    applied8: false,
    applied9: false,
    applied10: false,
    applied11: false,
    applied12: false,
    applied13: false
  },

  // 变换/恢复切换：key 为对应卡片的状态字段名
  toggle(key) {
    this[key] = !this[key];
  },

  goBack() {
    // 返回基础用例分类页
    router.replace({ uri: 'pages/lightGraphics/rm002/basic/basic' });
  }
};
