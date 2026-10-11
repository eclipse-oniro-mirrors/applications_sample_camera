// RM.003 基础用例-SVG路径绘制页逻辑
import router from '@system.router';

export default {
  goBack() {
    // 返回基础用例分类页
    router.replace({ uri: 'pages/lightGraphics/rm003/basic/basic' });
  }
};
