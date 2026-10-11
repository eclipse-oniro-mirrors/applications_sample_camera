// RM.007 共享元素转场页逻辑 — 007，参考 demo 写法：去掉 show，先 startTransition 再改状态
// Lite 端无 this.setData，数据更新一律用直接赋值 this.key = value
import router from '@system.router';

export default {
  data: {
    sharedShow: 'a'
  },

  // 007 共享元素转场：星星从左上 (30,30,40×40) 移动到中心偏右下 (200,70,80×80)，背景红绿切换
  switchShared() {
    const rectA = { x: 30, y: 30, w: 40, h: 40 };
    const rectB = { x: 200, y: 70, w: 80, h: 80 };
    const toB = (this.sharedShow === 'a');

    this.$refs.sharedStage.startTransition({
      incoming: this.$refs[toB ? 'sharedB' : 'sharedA'],
      sharedElement: this.$refs.sharedStar,
      sharedStartRect: toB ? rectA : rectB,
      sharedEndRect: toB ? rectB : rectA
    });
    this.sharedShow = toB ? 'b' : 'a';
  },

  goBack() {
    router.replace({ uri: 'pages/lightGraphics/rm007/basic/basic' });
  }
};
