import router from '@system.router';

const baseData = {
    // Flex容器配置
    flexDirection: 'row',
    alignItems: 'flex-start',
    flexWrap: 'nowrap',
    boxOverflow: 'visible',
};

const itemData = {
    // Flex子项配置（红色item1生效）
    itemGrow: 0,
    itemShrink: 0,

    itemWidth: '50px',
    itemHeight: '50px',
    itemDisplay: 'flex',
    itemDisplay4to6: 'flex',
    c2ItemDisplay4to11: 'flex',
    c2BoxDisplay: 'flex',
};

const constraintData = {
    // 尺寸约束
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

    // 容器2高频测试变量
    c2Item1MinWidth: undefined,
    c2Item1Shrink: 0,
    c2Item2MaxWidth: undefined,
    c2Item2Grow: 0,
    c2Item3MinHeight: undefined,
};

const stateData = {
    // 高频切换选中状态
    isAutoMinWidthShrink: false,
    isAutoMaxWidthGrow: false,
    isAutoMinHeight: false,

    // 高频切换定时器
    timerMinWidthShrink: null,
    timerMaxWidthGrow: null,
    timerMinHeight: null,

    // 每行独立选中索引（-1 表示无选中）
    idxOverflow: -1,
    idxWrap: -1,
    idxDir: -1,
    idxItemWidth: -1,
    idxItemHeight: -1,
    idxFlexGrow: -1,
    idxFlexShrink: -1,
    idxItemDisplay: -1,
    idxItemDisplay4to6: -1,
    idxC2ItemDisplay4to11: -1,
    idxC2BoxDisplay: -1,
    idxSizeConstraint: -1,
};

export default {
    data() {
        return Object.assign({}, baseData, itemData, constraintData, stateData);
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
        else if (prop === 'width') { this.setItemWidth(val) }
        else if (prop === 'height') { this.setItemHeight(val) }
        else if (prop === 'grow') { this.setFlexGrow(val) }
        else if (prop === 'shrink') { this.setFlexShrink(val) }
        else if (prop === 'constraint') { this.setSizeConstraint(val) }
        else if (prop === 'itemDisplay') { this.setItemDisplay(val) }
        else if (prop === 'itemDisplay4to6') { this.setItemDisplay4to6(val) }
        else if (prop === 'c2ItemDisplay4to11') { this.setC2ItemDisplay4to11(val) }
        else if (prop === 'c2BoxDisplay') { this.setC2BoxDisplay(val) }
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
    setItemDisplay(val) {
        this.itemDisplay = val;
    },
    setItemDisplay4to6(val) {
        this.itemDisplay4to6 = val;
    },
    setC2ItemDisplay4to11(val) {
        this.c2ItemDisplay4to11 = val;
    },
    setC2BoxDisplay(val) {
        this.c2BoxDisplay = val;
    },
    // 是否换行
    setWrap(val) {
        this.flexWrap = val;
    },
    setFlexGrow(val) {
        this.itemGrow = parseInt(val);
    },
    setFlexShrink(val) {
        this.itemShrink = parseInt(val);
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

        if (val === 'minWidth') {
            this.item1MinWidth = '10px';
            this.item2MinWidth = '20px';
            this.item3MinWidth = '30px';
            this.item4MinWidth = '-20px';
            this.item5MinWidth = '0px';
        } else if (val === 'maxWidth') {
            this.item1MaxWidth = '100px';
            this.item2MaxWidth = '100px';
            this.item3MaxWidth = '100px';
            this.item4MaxWidth = '-20px';
            this.item5MaxWidth = '0px';
        } else if (val === 'minHeight') {
            this.item1MinHeight = '10px';
            this.item2MinHeight = '20px';
            this.item3MinHeight = '100px';
            this.item4MinHeight = '-20px';
            this.item5MinHeight = '0px';
        } else if (val === 'item5All50') {
            this.item5MinWidth = '50px';
            this.item5MaxWidth = '50px';
            this.item5MinHeight = '50px';
        }
    },
    // 主轴方向
    setDir(val) {
        this.flexDirection = val;
    },
    // 自动测试
    autoMinWidthShrink() {
        if (this.isAutoMinWidthShrink) {
            this.stopAutoMinWidthShrink();
            return;
        }
        const values = ['10px', '20px', '30px'];
        let idx = 0;
        let count = 0;
        this.isAutoMinWidthShrink = true;
        this.c2Item1Shrink = 1;
        const timer = setInterval(() => {
            this.c2Item1MinWidth = values[idx % values.length];
            idx++;
            count++;
            if (count >= 50) {
                clearInterval(timer);
                this.timerMinWidthShrink = null;
                this.isAutoMinWidthShrink = false;
                this.c2Item1Shrink = 0;
                this.c2Item1MinWidth = '50px';
            }
        }, 100);
        this.timerMinWidthShrink = timer;
    },
    stopAutoMinWidthShrink() {
        if (this.timerMinWidthShrink) {
            clearInterval(this.timerMinWidthShrink);
            this.timerMinWidthShrink = null;
        }
        this.isAutoMinWidthShrink = false;
        this.c2Item1Shrink = 0;
    },
    autoMaxWidthGrow() {
        if (this.isAutoMaxWidthGrow) {
            this.stopAutoMaxWidthGrow();
            return;
        }
        const values = ['100px', '150px', '200px', '250px', '300px'];
        let idx = 0;
        let count = 0;
        this.isAutoMaxWidthGrow = true;
        this.c2Item2Grow = 1;
        const timer = setInterval(() => {
            this.c2Item2MaxWidth = values[idx % values.length];
            idx++;
            count++;
            if (count >= 50) {
                clearInterval(timer);
                this.timerMaxWidthGrow = null;
                this.isAutoMaxWidthGrow = false;
                this.c2Item2Grow = 0;
                this.c2Item2MaxWidth = '50px';
            }
        }, 100);
        this.timerMaxWidthGrow = timer;
    },
    stopAutoMaxWidthGrow() {
        if (this.timerMaxWidthGrow) {
            clearInterval(this.timerMaxWidthGrow);
            this.timerMaxWidthGrow = null;
        }
        this.isAutoMaxWidthGrow = false;
        this.c2Item2Grow = 0;
    },
    autoMinHeight() {
        if (this.isAutoMinHeight) {
            this.stopAutoMinHeight();
            return;
        }
        const values = ['100px', '150px', '200px'];
        let idx = 0;
        let count = 0;
        this.isAutoMinHeight = true;
        const timer = setInterval(() => {
            this.c2Item3MinHeight = values[idx % values.length];
            idx++;
            count++;
            if (count >= 50) {
                clearInterval(timer);
                this.timerMinHeight = null;
                this.isAutoMinHeight = false;
                this.c2Item3MinHeight = '50px';
            }
        }, 100);
        this.timerMinHeight = timer;
    },
    stopAutoMinHeight() {
        if (this.timerMinHeight) {
            clearInterval(this.timerMinHeight);
            this.timerMinHeight = null;
        }
        this.isAutoMinHeight = false;
    },
    stopAutoTest() {
        this.stopAutoMinWidthShrink();
        this.stopAutoMaxWidthGrow();
        this.stopAutoMinHeight();
    },
    // 全部重置
    resetAll() {
        this.stopAutoTest();
        this.resetFlexContainer();
        this.resetFlexItems();
        this.resetSizeConstraints();
        this.resetC2Container();
        this.resetIndexes();
        this.resetAutoFlags();
    },
    resetFlexContainer() {
        this.flexDirection = 'row';
        this.alignItems = 'flex-start';
        this.flexWrap = 'nowrap';
        this.boxOverflow = 'visible';
    },
    resetFlexItems() {
        this.itemGrow = 0;
        this.itemShrink = 0;
        // this.itemOrder = 0
        this.itemWidth = '50px';
        this.itemHeight = '50px';
        this.itemDisplay = 'flex';
        this.itemDisplay4to6 = 'flex';
        this.c2ItemDisplay4to11 = 'flex';
        this.c2BoxDisplay = 'flex';
    },
    resetSizeConstraints() {
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
    },
    resetC2Container() {
        this.c2Item1MinWidth = undefined;
        this.c2Item1Shrink = 0;
        this.c2Item2MaxWidth = undefined;
        this.c2Item2Grow = 0;
        this.c2Item3MinHeight = undefined;
    },
    resetIndexes() {
        this.idxOverflow = -1;
        this.idxWrap = -1;
        this.idxDir = -1;
        this.idxItemWidth = -1;
        this.idxItemHeight = -1;
        this.idxFlexGrow = -1;
        this.idxFlexShrink = -1;
        this.idxItemDisplay = -1;
        this.idxItemDisplay4to6 = -1;
        this.idxC2ItemDisplay4to11 = -1;
        this.idxC2BoxDisplay = -1;
        this.idxSizeConstraint = -1;
    },
    resetAutoFlags() {
        this.isAutoMinWidthShrink = false;
        this.timerMinWidthShrink = null;
        this.isAutoMaxWidthGrow = false;
        this.timerMaxWidthGrow = null;
        this.isAutoMinHeight = false;
        this.timerMinHeight = null;
    },
};
