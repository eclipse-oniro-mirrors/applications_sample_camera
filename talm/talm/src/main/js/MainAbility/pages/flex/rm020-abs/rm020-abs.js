import router from '@system.router';

export default {
    data() {
        return {
            isAutoTopLeft: false,
            timerTopLeft: null,
            isAutoBottomRight: false,
            timerBottomRight: null,

            c2Item1Top: '0px',
            c2Item1Left: '0px',
            c2Item1Right: '10%',
            c2Item1Bottom: '10%',

            c2Item2Right: '0px',
            c2Item2Bottom: '0px',

            isC2Item1Both: false,

            idxC2Item1TopLeft: -1,
            idxC2Item1BottomRight: -1,
            idxC2Item1Center: -1,
        };
    },
    onShow() {
        // 延迟触发一次定位重排，等页面根视图挂到 UIScrollView 后再计算初始容器块
        setTimeout(() => {
            this.c2Item2Right = '1px';
            this.c2Item2Bottom = '1px';
            setTimeout(() => {
                this.c2Item2Right = '0px';
                this.c2Item2Bottom = '0px';
            }, 10);
        }, 100);
    },
    onInit() {
        console.info('absolute positioning onInit');
    },
    goBack() {
        router.replace({ uri: 'pages/flex/flex' });
    },
    setC2Item1TopLeft(top, left, idx) {
        this.c2Item1Top = top;
        this.c2Item1Left = left;
        this.c2Item1Right = '10%';
        this.c2Item1Bottom = '10%';
        this.c2Item2Right = undefined;
        this.c2Item2Bottom = undefined;
        this.isC2Item1Both = false;
        this.idxC2Item1TopLeft = idx;
        this.idxC2Item1BottomRight = -1;
        this.idxC2Item1Center = -1;
    },
    setC2Item1BottomRight(bottom, right, idx) {
        this.c2Item2Bottom = bottom;
        this.c2Item2Right = right;
        this.c2Item1Top = '0px';
        this.c2Item1Left = '0px';
        this.c2Item1Right = '10%';
        this.c2Item1Bottom = '10%';
        this.isC2Item1Both = false;
        this.idxC2Item1BottomRight = idx;
        this.idxC2Item1TopLeft = -1;
        this.idxC2Item1Center = -1;
    },
    setC2Item1Center() {
        this.c2Item1Top = '50%';
        this.c2Item1Left = '50%';
        this.c2Item1Right = '10%';
        this.c2Item1Bottom = '10%';
        this.c2Item2Right = undefined;
        this.c2Item2Bottom = undefined;
        this.isC2Item1Both = false;
        this.idxC2Item1Center = 0;
        this.idxC2Item1TopLeft = -1;
        this.idxC2Item1BottomRight = -1;
    },
    setC2Item1Origin() {
        this.c2Item1Top = '0px';
        this.c2Item1Left = '0px';
        this.c2Item1Right = '10%';
        this.c2Item1Bottom = '10%';
        this.c2Item2Right = '0px';
        this.c2Item2Bottom = '0px';
        this.isC2Item1Both = false;
        this.idxC2Item1Center = -1;
        this.idxC2Item1TopLeft = -1;
        this.idxC2Item1BottomRight = -1;
    },
    setC2Item1Both() {
        this.c2Item1Top = '10%';
        this.c2Item1Left = '10%';
        this.c2Item1Right = '10%';
        this.c2Item1Bottom = '10%';
        this.c2Item2Right = undefined;
        this.c2Item2Bottom = undefined;
        this.isC2Item1Both = true;
        this.idxC2Item1Center = -1;
        this.idxC2Item1TopLeft = -1;
        this.idxC2Item1BottomRight = -1;
    },
    // top+left 高频自动测试（基于初始容器块）
    autoTopLeft() {
        if (this.isAutoTopLeft) {
            this.stopAutoTopLeft();
            return;
        }
        const values = [
            { top: '-25px', left: '-25px' },
            { top: '0px', left: '0px' },
            { top: '25%', left: '25%' },
            { top: '50%', left: '50%' },
            { top: '75%', left: '75%' }
        ];
        let idx = 0;
        let count = 0;
        this.isAutoTopLeft = true;
        const timer = setInterval(() => {
            const v = values[idx % values.length];
            this.c2Item1Top = v.top;
            this.c2Item1Left = v.left;
            this.c2Item1Right = '10%';
            this.c2Item1Bottom = '10%';
            this.c2Item2Right = undefined;
            this.c2Item2Bottom = undefined;
            this.isC2Item1Both = false;
            idx++;
            count++;
            if (count >= 50) {
                clearInterval(timer);
                this.timerTopLeft = null;
                this.isAutoTopLeft = false;
                this.c2Item1Top = '0px';
                this.c2Item1Left = '0px';
            }
        }, 100);
        this.timerTopLeft = timer;
    },
    stopAutoTopLeft() {
        if (this.timerTopLeft) {
            clearInterval(this.timerTopLeft);
            this.timerTopLeft = null;
        }
        this.isAutoTopLeft = false;
    },
    // right+bottom 高频自动测试（基于初始容器块）
    autoBottomRight() {
        if (this.isAutoBottomRight) {
            this.stopAutoBottomRight();
            return;
        }
        const values = [
            { bottom: '-25px', right: '-25px' },
            { bottom: '0px', right: '0px' },
            { bottom: '25%', right: '25%' },
            { bottom: '50%', right: '50%' },
            { bottom: '75%', right: '75%' }
        ];
        let idx = 0;
        let count = 0;
        this.isAutoBottomRight = true;
        const timer = setInterval(() => {
            const v = values[idx % values.length];
            this.c2Item1Top = '0px';
            this.c2Item1Left = '0px';
            this.c2Item1Right = '10%';
            this.c2Item1Bottom = '10%';
            this.c2Item2Bottom = v.bottom;
            this.c2Item2Right = v.right;
            this.isC2Item1Both = false;
            idx++;
            count++;
            if (count >= 50) {
                clearInterval(timer);
                this.timerBottomRight = null;
                this.isAutoBottomRight = false;
                this.c2Item2Bottom = '0px';
                this.c2Item2Right = '0px';
            }
        }, 100);
        this.timerBottomRight = timer;
    },
    stopAutoBottomRight() {
        if (this.timerBottomRight) {
            clearInterval(this.timerBottomRight);
            this.timerBottomRight = null;
        }
        this.isAutoBottomRight = false;
    },
    stopAutoTest() {
        this.stopAutoTopLeft();
        this.stopAutoBottomRight();
    },
    // 全部重置
    resetAll() {
        this.isAutoTopLeft = false;
        this.timerTopLeft = null;
        this.isAutoBottomRight = false;
        this.timerBottomRight = null;

        this.c2Item1Top = '0px';
        this.c2Item1Left = '0px';
        this.c2Item1Right = '10%';
        this.c2Item1Bottom = '10%';

        this.c2Item2Right = '0px';
        this.c2Item2Bottom = '0px';

        this.isC2Item1Both = false;

        this.idxC2Item1TopLeft = -1;
        this.idxC2Item1BottomRight = -1;
        this.idxC2Item1Center = -1;
    },
};
