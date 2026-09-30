// RM.002 基础用例-SVG星形路径页逻辑
import router from '@system.router';

export default {
  goBack() {
    // 返回基础用例分类页
    router.replace({ uri: 'pages/lightGraphics/rm002/basic/basic' });
  }
};
