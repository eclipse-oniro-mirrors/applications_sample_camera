import router from '@system.router';

export default {
    data() {
        return {
            flexDirection: 'row',
            justifyContent: 'flex-start',
            alignItems: 'flex-start',
            flexWrap: 'nowrap',
            boxOverflow: 'visible',
            itemWidth: '50px',
            itemHeight: '50px',
            itemMarginLeft: '0px',
            itemDisplay: 'flex',
            itemDisplay4to6: 'flex',
            displayFlex2: 'flex',
            displayFlex3: 'flex',

            // 高频切换选中状态
            isAutoOverflow: false,
            isAutoMargin: false,
            isAutoWrap: false,
            isAutoDir: false,
            isAutoMain: false,
            isAutoCross: false,

            // 高频切换定时器
            timerOverflow: null,
            timerMargin: null,
            timerWrap: null,
            timerDir: null,
            timerMain: null,
            timerCross: null,

            // 无高/无宽容器中 item1 的宽高
            itemNoHeight: undefined,
            itemNoWidth: undefined,

            // 每行独立选中索引（-1 表示无选中）
            idxOverflow: -1,
            idxMargin: -1,
            idxMarginPct: -1,
            idxWrap: -1,
            idxDir: -1,
            idxMain: -1,
            idxCross: -1,
            idxItemWidth: -1,
            idxItemHeight: -1,
            idxItemDisplay: -1,
            idxItemDisplay4to6: -1,
            idxNoHeight1: -1,
            idxNoWidth1: -1,
            idxDisplayFlex2: -1,
            idxDisplayFlex3: -1,
        };
    },
    onShow() {
        // 页面进来默认每行选中第一个
        this.idxOverflow = 0;
        this.idxMargin = 1;
        this.idxMarginPct = 1;
        this.idxWrap = 0;
        this.idxDir = 0;
        this.idxMain = 0;
        this.idxCross = 0;
        this.idxDisplayFlex2 = 0;
        this.idxDisplayFlex3 = 0;
    },
    // 所有按钮共用同一个函数
    changeSelect(key, index) {
        this[key] = index;
    },
    setPropAndSelect(key, index, prop, val) {
        if (prop === 'overflow') { this.setOverflow(val) }
        else if (prop === 'margin') { this.setMarginLeft(val) }
        else if (prop === 'wrap') { this.setWrap(val) }
        else if (prop === 'dir') { this.setDir(val) }
        else if (prop === 'main') { this.setMain(val) }
        else if (prop === 'cross') { this.setCross(val) }
        else if (prop === 'width') { this.setItemWidth(val) }
        else if (prop === 'height') { this.setItemHeight(val) }
        else if (prop === 'noHeight') { this.setItemNoHeight(val) }
        else if (prop === 'noWidth') { this.setItemNoWidth(val) }
        else if (prop === 'itemDisplay') { this.setItemDisplay(val) }
        else if (prop === 'itemDisplay4to6') { this.setItemDisplay4to6(val) }
        else if (prop === 'displayFlex2') { this.setDisplayFlex2(val) }
        else if (prop === 'displayFlex3') { this.setDisplayFlex3(val) }
        this.changeSelect(key, index);
    },
    onInit() {
        console.info('flex onInit');
    },
    goBack() {
        router.replace({ uri: 'pages/flex/flex' });
    },
    // 容器溢出
    setOverflow(val) {
        this.boxOverflow = val;
    },
    setItemWidth(val) {
        this.itemWidth = val;
    },
    setItemHeight(val) {
        this.itemHeight = val;
    },
    setItemNoHeight(val) {
        this.itemNoHeight = val || undefined;
    },
    setItemNoWidth(val) {
        this.itemNoWidth = val || undefined;
    },
    setItemDisplay(val) {
        this.itemDisplay = val;
    },
    setItemDisplay4to6(val) {
        this.itemDisplay4to6 = val;
    },
    setDisplayFlex2(val) {
        this.displayFlex2 = val;
    },
    setDisplayFlex3(val) {
        this.displayFlex3 = val;
    },
    // 是否换行
    setWrap(val) {
        this.flexWrap = val;
    },
    setMarginLeft(val) {
        this.itemMarginLeft = val;
    },
    // 主轴方向
    setDir(val) {
        this.flexDirection = val;
    },
    // 主轴对齐
    setMain(val) {
        this.justifyContent = val;
    },
    // 交叉轴对齐
    setCross(val) {
        this.alignItems = val;
    },
    // 自动测试
    autoToggleOverflow() {
        if (this.isAutoOverflow) {
            this.stopAutoOverflow();
            return;
        }
        let count = 0;
        this.isAutoOverflow = true;
        const timer = setInterval(() => {
            this.boxOverflow = (this.boxOverflow === 'visible') ? 'hidden' : 'visible';
            count++;
            if (count >= 50) {
                clearInterval(timer);
                this.timerOverflow = null;
                this.isAutoOverflow = false;
            }
        }, 100);
        this.timerOverflow = timer;
    },
    stopAutoOverflow() {
        if (this.timerOverflow) {
            clearInterval(this.timerOverflow);
            this.timerOverflow = null;
        }
        this.isAutoOverflow = false;
    },
    autoToggleMargin() {
        if (this.isAutoMargin) {
            this.stopAutoMargin();
            return;
        }
        const values = ['0px', '50px', '20%', 'auto', '-50px'];
        let idx = 0;
        let count = 0;
        this.isAutoMargin = true;
        const timer = setInterval(() => {
            this.itemMarginLeft = values[idx % values.length];
            idx++;
            count++;
            if (count >= 50) {
                clearInterval(timer);
                this.timerMargin = null;
                this.isAutoMargin = false;
            }
        }, 100);
        this.timerMargin = timer;
    },
    stopAutoMargin() {
        if (this.timerMargin) {
            clearInterval(this.timerMargin);
            this.timerMargin = null;
        }
        this.isAutoMargin = false;
    },
    autoFlexWrap() {
        if (this.isAutoWrap) {
            this.stopAutoWrap();
            return;
        }
        const values = ['wrap', 'nowrap'];
        let idx = 0;
        let count = 0;
        this.isAutoWrap = true;
        const timer = setInterval(() => {
            this.flexWrap = values[idx % values.length];
            idx++;
            count++;
            if (count >= 50) {
                clearInterval(timer);
                this.timerWrap = null;
                this.isAutoWrap = false;
            }
        }, 100);
        this.timerWrap = timer;
    },
    stopAutoWrap() {
        if (this.timerWrap) {
            clearInterval(this.timerWrap);
            this.timerWrap = null;
        }
        this.isAutoWrap = false;
    },
    autoFlexDir() {
        if (this.isAutoDir) {
            this.stopAutoDir();
            return;
        }
        const values = ['column', 'row'];
        let idx = 0;
        let count = 0;
        this.isAutoDir = true;
        const timer = setInterval(() => {
            this.flexDirection = values[idx % values.length];
            idx++;
            count++;
            if (count >= 50) {
                clearInterval(timer);
                this.timerDir = null;
                this.isAutoDir = false;
            }
        }, 100);
        this.timerDir = timer;
    },
    stopAutoDir() {
        if (this.timerDir) {
            clearInterval(this.timerDir);
            this.timerDir = null;
        }
        this.isAutoDir = false;
    },
    autoJustifyContent() {
        if (this.isAutoMain) {
            this.stopAutoMain();
            return;
        }
        const values = ['flex-start', 'center', 'flex-end', 'space-between', 'space-around', 'space-evenly'];
        let idx = 0;
        let count = 0;
        this.isAutoMain = true;
        const timer = setInterval(() => {
            this.justifyContent = values[idx % values.length];
            idx++;
            count++;
            if (count >= 50) {
                clearInterval(timer);
                this.timerMain = null;
                this.isAutoMain = false;
            }
        }, 100);
        this.timerMain = timer;
    },
    stopAutoMain() {
        if (this.timerMain) {
            clearInterval(this.timerMain);
            this.timerMain = null;
        }
        this.isAutoMain = false;
    },
    autoAlignItems() {
        if (this.isAutoCross) {
            this.stopAutoCross();
            return;
        }
        const values = ['flex-start', 'center', 'flex-end'];
        let idx = 0;
        let count = 0;
        this.isAutoCross = true;
        const timer = setInterval(() => {
            this.alignItems = values[idx % values.length];
            idx++;
            count++;
            if (count >= 50) {
                clearInterval(timer);
                this.timerCross = null;
                this.isAutoCross = false;
            }
        }, 100);
        this.timerCross = timer;
    },
    stopAutoCross() {
        if (this.timerCross) {
            clearInterval(this.timerCross);
            this.timerCross = null;
        }
        this.isAutoCross = false;
    },
    stopAutoTest() {
        this.stopAutoOverflow();
        this.stopAutoMargin();
        this.stopAutoWrap();
        this.stopAutoDir();
        this.stopAutoMain();
        this.stopAutoCross();
    },
    // 全部重置
    resetAll() {
        this.stopAutoTest();
        this.flexDirection = 'row';
        this.justifyContent = 'flex-start';
        this.alignItems = 'flex-start';
        this.flexWrap = 'nowrap';
        this.boxOverflow = 'visible';

        this.itemWidth = '50px';
        this.itemHeight = '50px';
        this.itemMarginLeft = '0px';
        this.itemDisplay = 'flex';
        this.itemDisplay4to6 = 'flex';
        this.displayFlex2 = 'flex';
        this.displayFlex3 = 'flex';

        this.setItemNoHeight('undefined');
        this.setItemNoWidth('undefined');

        // 每行独立选中索引（-1 表示无选中）
        this.idxOverflow = -1;
        this.idxMargin = -1;
        this.idxMarginPct = -1;
        this.idxWrap = -1;
        this.idxDir = -1;
        this.idxMain = -1;
        this.idxCross = -1;
        this.idxItemWidth = -1;
        this.idxItemHeight = -1;
        this.idxItemDisplay = -1;
        this.idxItemDisplay4to6 = -1;
        this.idxNoHeight1 = -1;
        this.idxNoWidth1 = -1;
        this.idxDisplayFlex2 = -1;
        this.idxDisplayFlex3 = -1;
    },
};
