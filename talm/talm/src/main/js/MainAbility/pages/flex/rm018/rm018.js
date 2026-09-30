import router from '@system.router';

const baseData = {
    // Flex容器配置
    flexDirection: 'row',
    justifyContent: 'flex-start',
    alignItems: 'flex-start',
    flexWrap: 'nowrap',
    alignContent: undefined,
    boxOverflow: 'visible',
};

const itemData = {
    // Flex子项配置（红色item1生效）
    itemAlignSelf: 'auto',
    itemGrow: 0,
    itemShrink: 0,
    itemBasis: undefined,
    item2Grow: 0,
    item2Shrink: 0,
    item2Basis: undefined,
    item3Grow: 0,
    item3Shrink: 0,
    item3Basis: undefined,

    itemWidth: '50px',
    itemHeight: '50px',
    itemDisplay: 'flex',
    itemDisplay4to6: 'flex',
    itemDisplay2to3: 'flex',

    // 容器显示控制
    flex2Display: 'flex',
    flex3Display: 'flex',

    // 无高/无宽容器中 item1 的宽高
    itemNoHeight: undefined,
    itemNoWidth: undefined,
};

const stateData = {
    // 高频切换选中状态
    isAutoWrap: false,
    isAutoDir: false,
    isAutoAlignContent: false,

    // 高频切换定时器
    timerWrap: null,
    timerDir: null,
    timerAlignContent: null,

    // 每行独立选中索引（-1 表示无选中）
    idxOverflow: -1,
    idxAlignContent: -1,
    idxWrap: -1,
    idxDir: -1,
    idxCross: -1,
    idxAlignSelf: -1,
    idxItemWidth: -1,
    idxItemHeight: -1,
    idxFlexGrow: -1,
    idxFlexShrink: -1,
    idxFlexBasis: -1,
    idxItemDisplay: -1,
    idxItemDisplay4to6: -1,
    idxItemDisplay2to3: -1,
    idxNoHeight1: -1,
    idxNoWidth1: -1,

    // 容器显示控制索引
    idxFlex2Display: -1,
    idxFlex3Display: -1,
};

export default {
    data() {
        return Object.assign({}, baseData, itemData, stateData);
    },
    onShow() {
        // 页面进来默认每行选中第一个
        this.idxOverflow = 0;
        this.idxWrap = 0;
        this.idxDir = 0;
        this.idxCross = -1;
        this.idxAlignContent = -1;
    },
    onInit() {
        console.info('flex onInit');
    },
    goBack() {
        router.replace({ uri: 'pages/flex/flex' });
    },
    onHide() {
        this.stopAutoTest();
    },
    onDestroy() {
        this.stopAutoTest();
    },
    // 所有按钮共用同一个函数
    setPropAndSelect(key, index, prop, val) {
        this.applyProp(prop, val);
        this[key] = index;
    },
    applyProp(prop, val) {
        if (prop === 'overflow') { this.boxOverflow = val }
        if (prop === 'alignContent') { this.alignContent = val }
        if (prop === 'wrap') { this.flexWrap = val }
        if (prop === 'dir') { this.flexDirection = val }
        if (prop === 'cross') { this.alignItems = val }
        if (prop === 'width') { this.itemWidth = val }
        if (prop === 'height') { this.itemHeight = val }
        if (prop === 'noHeight') { this.itemNoHeight = val || undefined }
        if (prop === 'noWidth') { this.itemNoWidth = val || undefined }
        if (prop === 'alignSelf') { this.itemAlignSelf = val }
        if (prop === 'grow') { this.applyGrow(val) }
        if (prop === 'shrink') { this.applyShrink(val) }
        if (prop === 'basis') { this.applyBasis(val) }
        if (prop === 'itemDisplay') { this.itemDisplay = val }
        if (prop === 'itemDisplay4to6') { this.itemDisplay4to6 = val }
        if (prop === 'itemDisplay2to3') { this.itemDisplay2to3 = val }
        if (prop === 'flex2Display') { this.flex2Display = val }
        if (prop === 'flex3Display') { this.flex3Display = val }
    },
    applyGrow(val) {
        if (val === '1/2/1') {
            this.itemGrow = 1;
            this.item2Grow = 2;
            this.item3Grow = 1;
        } else {
            const numVal = parseInt(val);
            this.itemGrow = numVal;
            this.item2Grow = numVal;
            this.item3Grow = numVal;
        }
    },
    applyShrink(val) {
        const numVal = parseInt(val);
        this.itemShrink = numVal;
        this.item2Shrink = numVal;
        this.item3Shrink = numVal;
    },
    applyBasis(val) {
        this.itemBasis = val;
        this.item2Basis = val;
        this.item3Basis = val;
    },
    // 通用自动切换
    autoToggle(config) {
        if (this[config.flag]) {
            this.stopToggle(config);
            return;
        }
        const values = config.values;
        let idx = 0;
        let count = 0;
        this[config.flag] = true;
        const timer = setInterval(() => {
            this[config.prop] = values[idx % values.length];
            idx++;
            count++;
            if (count >= 50) {
                clearInterval(timer);
                this[config.timerKey] = null;
                this[config.flag] = false;
            }
        }, 100);
        this[config.timerKey] = timer;
    },
    stopToggle(config) {
        if (this[config.timerKey]) {
            clearInterval(this[config.timerKey]);
            this[config.timerKey] = null;
        }
        this[config.flag] = false;
    },
    // 自动测试
    autoFlexWrap() {
        this.autoToggle({
            flag: 'isAutoWrap',
            timerKey: 'timerWrap',
            prop: 'flexWrap',
            values: ['wrap', 'nowrap']
        });
    },
    stopAutoWrap() {
        this.stopToggle({ flag: 'isAutoWrap', timerKey: 'timerWrap' });
    },
    autoFlexDir() {
        this.autoToggle({
            flag: 'isAutoDir',
            timerKey: 'timerDir',
            prop: 'flexDirection',
            values: ['column', 'row']
        });
    },
    stopAutoDir() {
        this.stopToggle({ flag: 'isAutoDir', timerKey: 'timerDir' });
    },
    autoAlignContent() {
        this.autoToggle({
            flag: 'isAutoAlignContent',
            timerKey: 'timerAlignContent',
            prop: 'alignContent',
            values: ['flex-start', 'center', 'flex-end', 'space-between', 'stretch']
        });
    },
    stopAutoAlignContent() {
        this.stopToggle({ flag: 'isAutoAlignContent', timerKey: 'timerAlignContent' });
    },
    stopAutoTest() {
        this.stopAutoWrap();
        this.stopAutoDir();
        this.stopAutoAlignContent();
    },
    // 全部重置
    resetAll() {
        this.stopAutoTest();
        this.flexDirection = 'row';
        this.justifyContent = 'flex-start';
        this.alignItems = 'flex-start';
        this.flexWrap = 'nowrap';
        this.alignContent = undefined;
        this.boxOverflow = 'visible';

        // Flex子项配置
        this.itemAlignSelf = 'auto';
        this.itemGrow = 0;
        this.itemShrink = 0;
        this.itemBasis = undefined;
        this.item2Grow = 0;
        this.item2Shrink = 0;
        this.item2Basis = undefined;
        this.item3Grow = 0;
        this.item3Shrink = 0;
        this.item3Basis = undefined;
        // this.itemOrder = 0
        this.itemWidth = '50px';
        this.itemHeight = '50px';
        this.itemDisplay = 'flex';
        this.itemDisplay4to6 = 'flex';
        this.itemDisplay2to3 = 'flex';

        // 容器显示控制重置
        this.flex2Display = 'flex';
        this.flex3Display = 'flex';

        this.setItemNoHeight('undefined');
        this.setItemNoWidth('undefined');

        // 每行独立选中索引（-1 表示无选中）
        this.idxOverflow = -1;
        this.idxAlignContent = -1;
        this.idxWrap = -1;
        this.idxDir = -1;
        this.idxCross = -1;
        this.idxAlignSelf = -1;
        this.idxItemWidth = -1;
        this.idxItemHeight = -1;
        this.idxFlexGrow = -1;
        this.idxFlexShrink = -1;
        this.idxFlexBasis = -1;
        this.idxItemDisplay = -1;
        this.idxItemDisplay4to6 = -1;
        this.idxItemDisplay2to3 = -1;
        this.idxNoHeight1 = -1;
        this.idxNoWidth1 = -1;

        // 容器显示控制索引重置
        this.idxFlex2Display = -1;
        this.idxFlex3Display = -1;
    },
};
