// 首页逻辑：路由跳转控制
import router from '@system.router';

export default {
    // 导航到指定测试页面
    navigateTo(page) {
        // 鸿蒙Lite路由跳转，目标页面对应 pages/页面名/页面名 结构
        console.log('xyb: ' + page);
        router.replace({ uri: 'pages/flex/' + page + '/' + page });

    },

    goBack() {
        // 返回首页
        router.replace({ uri: 'pages/index/index'});
    },
    goRM017Display() {
        router.replace({ uri: 'pages/flex/rm017/rm017'});
    }

};
