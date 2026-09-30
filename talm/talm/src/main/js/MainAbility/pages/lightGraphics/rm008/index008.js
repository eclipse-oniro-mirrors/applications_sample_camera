// RM.008 入口页逻辑：跳转到各用例分类页
import router from '@system.router';

export default {
  // 跳转到指定分类页
  navigateTo(page) {
    // 边界约束和异常场景直接跳转到具体用例页，跳过二级导航
    const target = (page === 'boundary') ? 'boundary_path' :
                   (page === 'exception') ? 'exception_path' : page;
    router.replace({ uri: 'pages/lightGraphics/rm008/' + target + '/' + target });
  },

  goBack() {
    // 返回轻图形入口页
    router.replace({ uri: 'pages/lightGraphics/lightGraphics' });
  }
};
