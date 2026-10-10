import router from '@system.router';

export default {
    data() {
        return {
            // Flex容器配置
            flexDirection: 'row',
            alignItems: 'flex-start',
            flexWrap: 'nowrap',
            boxOverflow: 'visible',

            // Flex子项配置（红色item1生效）
            itemWidth: '50px',
            itemHeight: '50px',
            itemDisplay: 'flex',
            itemDisplay4to6: 'flex',
            flex2Display: 'flex',

            // 尺寸约束
            item1Width: undefined,
            item1Height: undefined,
            item2Width: undefined,
            item2Height: undefined,
            item1MinWidth: undefined,
            item2MinWidth: undefined,
            item3MinWidth: undefined,
            item4MinWidth: undefined,
            item5MinWidth: undefined,
            item1MaxWidth: undefined,
            item2MaxWidth: undefined,
            item3MaxWidth: undefined,
            item4MaxWidth: undefined,
            item5MaxWidth: undefined,
            item1MinHeight: undefined,
            item2MinHeight: undefined,
            item3MinHeight: undefined,
            item4MinHeight: undefined,
            item5MinHeight: undefined,
            item3Width: undefined,
            item3Height: undefined,
            itemAspectRatio: undefined,

            // 高频切换选中状态
            isAutoItemWidth: false,
            isAutoItemHeight: false,
            isAutoAspect: false,

            // 高频切换定时器
            timerItemWidth: null,
            timerItemHeight: null,
            timerAspect: null,

            // 每行独立选中索引（-1 表示无选中）
            idxOverflow: -1,
            idxWrap: -1,
            idxDir: -1,
            idxItemDisplay: -1,
            idxItemDisplay4to6: -1,
            idxFlex2Display: -1,
            idxSizeConstraintW: -1,
            idxSizeConstraintH: -1,
            idxSizeConstraintAspect: -1,
        };
    },
    onShow() {
        // 页面进来默认每行选中第一个
        this.idxOverflow = 0;
        this.idxWrap = 0;
        this.idxDir = 0;
    },
    // 所有按钮共用同一个函数
    changeSelect(key, index) {
        this[key] = index;
    },
    setPropAndSelect(key, index, prop, val) {
        if (prop === 'overflow') { this.setOverflow(val) }
        else if (prop === 'wrap') { this.setWrap(val) }
        else if (prop === 'dir') { this.setDir(val) }
        else if (prop === 'constraint') { this.setSizeConstraint(val) }
        else if (prop === 'constraintW') { this.setSizeConstraintW(val) }
        else if (prop === 'constraintH') { this.setSizeConstraintH(val) }
        else if (prop === 'itemDisplay') { this.setItemDisplay(val) }
        else if (prop === 'itemDisplay4to6') { this.setItemDisplay4to6(val) }
        else if (prop === 'flex2Display') { this.setFlex2Display(val) }
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
    setItemDisplay(val) {
        this.itemDisplay = val;
    },
    setItemDisplay4to6(val) {
        this.itemDisplay4to6 = val;
    },
    setFlex2Display(val) {
        this.flex2Display = val;
    },
    setWrap(val) {
        this.flexWrap = val;
    },
    // 主轴方向
    setSizeConstraintW(val) {
        // 清空宽相关约束
        this.item1Width = undefined;
        this.item2Width = undefined;
        this.item3Width = undefined;
        this.item1MinWidth = undefined;
        this.item2MinWidth = undefined;
        this.item3MinWidth = undefined;
        this.item4MinWidth = undefined;
        this.item5MinWidth = undefined;
        this.item1MaxWidth = undefined;
        this.item2MaxWidth = undefined;
        this.item3MaxWidth = undefined;
        this.item4MaxWidth = undefined;
        this.item5MaxWidth = undefined;

        if (val === 'fixed') {
            this.item1Width = '100px';
        } else if (val === 'percent') {
            this.item1Width = '50%';
        } else if (val === 'zero') {
            this.item1Width = '0';
        } else if (val === 'huge') {
            this.item1Width = '1000px';
        } else if (val === 'negative') {
            this.item1Width = '-50px';
        } else if (val === 'w80') {
            this.item1Width = '80px';
            this.item2Width = '90px';
            this.item3Width = '100px';
        } else if (val === 'reset') {
            this.item1Width = '50px';
            this.item2Width = '50px';
            this.item3Width = '50px';
        }
    },
    setSizeConstraintH(val) {
        // 清空高相关约束
        this.item1Height = undefined;
        this.item2Height = undefined;
        this.item3Height = undefined;
        this.item1MinHeight = undefined;
        this.item2MinHeight = undefined;
        this.item3MinHeight = undefined;
        this.item4MinHeight = undefined;
        this.item5MinHeight = undefined;

        if (val === 'fixed') {
            this.item1Height = '100px';
        } else if (val === 'percent') {
            this.item1Height = '50%';
        } else if (val === 'zero') {
            this.item1Height = '0';
        } else if (val === 'huge') {
            this.item1Height = '1000px';
        } else if (val === 'negative') {
            this.item1Height = '-50px';
        } else if (val === 'h60') {
            this.item1Height = '60px';
            this.item2Height = '70px';
            this.item3Height = '80px';
        } else if (val === 'reset') {
            this.item1Height = '50px';
            this.item2Height = '50px';
            this.item3Height = '50px';
        }
    },
    setSizeConstraint(val) {
        // 清空最大/最小/比例约束
        this.item1MinWidth = undefined;
        this.item2MinWidth = undefined;
        this.item3MinWidth = undefined;
        this.item4MinWidth = undefined;
        this.item5MinWidth = undefined;
        this.item1MaxWidth = undefined;
        this.item2MaxWidth = undefined;
        this.item3MaxWidth = undefined;
        this.item4MaxWidth = undefined;
        this.item5MaxWidth = undefined;
        this.item1MinHeight = undefined;
        this.item2MinHeight = undefined;
        this.item3MinHeight = undefined;
        this.item4MinHeight = undefined;
        this.item5MinHeight = undefined;
        this.item3Width = undefined;
        this.itemAspectRatio = undefined;

        if (val === 'aspect2') {
            this.itemAspectRatio = '2';
        } else if (val === 'aspect') {
            this.itemAspectRatio = '1.5';
        } else if (val === 'aspect0_65') {
            this.itemAspectRatio = '0.65';
        } else if (val === 'aspect0') {
            this.itemAspectRatio = '0';
        } else if (val === 'aspectNeg1') {
            this.itemAspectRatio = '-1';
        } else if (val === 'aspect999999') {
            this.itemAspectRatio = '999999';
        }
    },
    // 主轴方向
    setDir(val) {
        this.flexDirection = val;
    },
    // 自动测试
    autoFlexItemWidth() {
        if (this.isAutoItemWidth) {
            this.stopAutoItemWidth();
            return;
        }
        const values = ['100px', '150px', '200px', '250px', '350px'];
        let idx = 0;
        let count = 0;
        this.isAutoItemWidth = true;
        const timer = setInterval(() => {
            this.item1Width = values[idx % values.length];
            idx++;
            count++;
            if (count >= 50) {
                clearInterval(timer);
                this.timerItemWidth = null;
                this.isAutoItemWidth = false;
            }
        }, 100);
        this.timerItemWidth = timer;
    },
    stopAutoItemWidth() {
        if (this.timerItemWidth) {
            clearInterval(this.timerItemWidth);
            this.timerItemWidth = null;
        }
        this.isAutoItemWidth = false;
    },
    autoFlexItemHeight() {
        if (this.isAutoItemHeight) {
            this.stopAutoItemHeight();
            return;
        }
        const values = ['80px', '100px', '140px', '160px', '200px'];
        let idx = 0;
        let count = 0;
        this.isAutoItemHeight = true;
        const timer = setInterval(() => {
            this.item1Height = values[idx % values.length];
            idx++;
            count++;
            if (count >= 50) {
                clearInterval(timer);
                this.timerItemHeight = null;
                this.isAutoItemHeight = false;
            }
        }, 100);
        this.timerItemHeight = timer;
    },
    stopAutoItemHeight() {
        if (this.timerItemHeight) {
            clearInterval(this.timerItemHeight);
            this.timerItemHeight = null;
        }
        this.isAutoItemHeight = false;
    },
    autoFlexAspect() {
        if (this.isAutoAspect) {
            this.stopAutoAspect();
            return;
        }
        const values = ['2', '1.5', '0.65'];
        let idx = 0;
        let count = 0;
        this.isAutoAspect = true;
        const timer = setInterval(() => {
            this.itemAspectRatio = values[idx % values.length];
            idx++;
            count++;
            if (count >= 50) {
                clearInterval(timer);
                this.timerAspect = null;
                this.isAutoAspect = false;
            }
        }, 100);
        this.timerAspect = timer;
    },
    stopAutoAspect() {
        if (this.timerAspect) {
            clearInterval(this.timerAspect);
            this.timerAspect = null;
        }
        this.isAutoAspect = false;
    },
    stopAutoTest() {
        this.stopAutoItemWidth();
        this.stopAutoItemHeight();
        this.stopAutoAspect();
    },
    // 全部重置
    resetAll() {
        this.stopAutoTest();
        this.flexDirection = 'row';
        this.alignItems = 'flex-start';
        this.flexWrap = 'nowrap';
        this.boxOverflow = 'visible';

        // Flex子项配置
        this.itemWidth = '50px';
        this.itemHeight = '50px';
        this.itemDisplay = 'flex';
        this.itemDisplay4to6 = 'flex';
        this.flex2Display = 'flex';

        // 尺寸约束
        this.item1Width = '50px';
        this.item1Height = '50px';
        this.item2Width = '50px';
        this.item2Height = '50px';
        this.item1MinWidth = undefined;
        this.item2MinWidth = undefined;
        this.item3MinWidth = undefined;
        this.item4MinWidth = undefined;
        this.item5MinWidth = undefined;
        this.item1MaxWidth = undefined;
        this.item2MaxWidth = undefined;
        this.item3MaxWidth = undefined;
        this.item4MaxWidth = undefined;
        this.item5MaxWidth = undefined;
        this.item1MinHeight = undefined;
        this.item2MinHeight = undefined;
        this.item3MinHeight = undefined;
        this.item4MinHeight = undefined;
        this.item5MinHeight = undefined;
        this.item3Width = '50px';
        this.item3Height = '50px';
        this.itemAspectRatio = undefined;

        // 每行独立选中索引（-1 表示无选中）
        this.idxOverflow = -1;
        this.idxWrap = -1;
        this.idxDir = -1;
        this.idxItemDisplay = -1;
        this.idxItemDisplay4to6 = -1;
        this.idxFlex2Display = -1;
        this.idxSizeConstraintW = -1;
        this.idxSizeConstraintH = -1;
        this.idxSizeConstraintAspect = -1;
    },
};
