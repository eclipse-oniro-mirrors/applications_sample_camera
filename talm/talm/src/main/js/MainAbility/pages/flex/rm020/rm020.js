import router from '@system.router';

export default {
    data() {
        return {
            // Flex容器配置
            flexDirection: 'row',
            flexWrap: 'nowrap',
            boxOverflow: 'visible',

            itemDisplay: 'flex',
            itemDisplay4to6: 'flex',

            flex1Display: 'flex',

            gapValue: undefined,
            columnGapValue: undefined,
            rowGapValue: undefined,

            isAutoGap: false,
            timerGap: null,

            isAutoColumnGap: false,
            timerColumnGap: null,
            isAutoRowGap: false,
            timerRowGap: null,
            savedFlexWrap: 'nowrap',

            // 每行独立选中索引（-1 表示无选中）
            idxOverflow: -1,
            idxWrap: -1,
            idxDir: -1,
            idxItemDisplay: -1,
            idxItemDisplay4to6: -1,
            idxFlex1Display: -1,
            idxGap: -1,
            idxColumnGap: -1,
            idxRowGap: -1,
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
        else if (prop === 'itemDisplay') { this.setItemDisplay(val) }
        else if (prop === 'itemDisplay4to6') { this.setItemDisplay4to6(val) }
        else if (prop === 'flex1Display') { this.setFlex1Display(val) }
        else if (prop === 'gap') { this.setGap(val) }
        else if (prop === 'columnGap') { this.setColumnGap(val) }
        else if (prop === 'rowGap') { this.setRowGap(val) }
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
    setItemDisplay(val) {
        this.itemDisplay = val;
    },
    setItemDisplay4to6(val) {
        this.itemDisplay4to6 = val;
    },
    setFlex1Display(val) {
        this.flex1Display = val;
    },
    setGap(val) {
        this.gapValue = val;
    },
    setColumnGap(val) {
        this.columnGapValue = val;
    },
    setRowGap(val) {
        this.rowGapValue = val;
    },
    // gap 高频自动测试
    autoGap() {
        if (this.isAutoGap) {
            this.stopAutoGap();
            return;
        }
        const values = ['0px', '10px', '20px 20px'];
        let idx = 0;
        let count = 0;
        this.isAutoGap = true;
        const timer = setInterval(() => {
            this.gapValue = values[idx % values.length];
            idx++;
            count++;
            if (count >= 50) {
                clearInterval(timer);
                this.timerGap = null;
                this.isAutoGap = false;
                this.gapValue = undefined;
            }
        }, 100);
        this.timerGap = timer;
    },
    stopAutoGap() {
        if (this.timerGap) {
            clearInterval(this.timerGap);
            this.timerGap = null;
        }
        this.isAutoGap = false;
    },
    // column-gap 高频自动测试
    autoColumnGap() {
        if (this.isAutoColumnGap) {
            this.stopAutoColumnGap();
            return;
        }
        const values = ['0px', '15px', '25px'];
        let idx = 0;
        let count = 0;
        this.isAutoColumnGap = true;
        const timer = setInterval(() => {
            this.columnGapValue = values[idx % values.length];
            idx++;
            count++;
            if (count >= 50) {
                clearInterval(timer);
                this.timerColumnGap = null;
                this.isAutoColumnGap = false;
                this.columnGapValue = undefined;
            }
        }, 100);
        this.timerColumnGap = timer;
    },
    stopAutoColumnGap() {
        if (this.timerColumnGap) {
            clearInterval(this.timerColumnGap);
            this.timerColumnGap = null;
        }
        this.isAutoColumnGap = false;
    },
    // row-gap 高频自动测试
    autoRowGap() {
        if (this.isAutoRowGap) {
            this.stopAutoRowGap();
            return;
        }
        const values = ['0px', '15px', '25px'];
        let idx = 0;
        let count = 0;
        this.isAutoRowGap = true;
        this.savedFlexWrap = this.flexWrap;
        this.flexWrap = 'wrap';
        const timer = setInterval(() => {
            this.rowGapValue = values[idx % values.length];
            idx++;
            count++;
            if (count >= 50) {
                clearInterval(timer);
                this.timerRowGap = null;
                this.isAutoRowGap = false;
                this.rowGapValue = undefined;
                this.flexWrap = this.savedFlexWrap;
            }
        }, 100);
        this.timerRowGap = timer;
    },
    stopAutoRowGap() {
        if (this.timerRowGap) {
            clearInterval(this.timerRowGap);
            this.timerRowGap = null;
        }
        this.isAutoRowGap = false;
        this.flexWrap = this.savedFlexWrap;
    },
    stopAutoTest() {
        this.stopAutoGap();
        this.stopAutoColumnGap();
        this.stopAutoRowGap();
    },
    // 是否换行
    setWrap(val) {
        this.flexWrap = val;
    },
    // 主轴方向
    setDir(val) {
        this.flexDirection = val;
    },
    // 全部重置
    resetAll() {
        this.flexDirection = 'row';
        this.flexWrap = 'nowrap';
        this.boxOverflow = 'visible';

        this.itemDisplay = 'flex';
        this.itemDisplay4to6 = 'flex';

        this.flex1Display = 'flex';

        this.gapValue = '0px';
        this.columnGapValue = '0px';
        this.rowGapValue = '0px';

        this.isAutoGap = false;
        this.timerGap = null;

        this.isAutoColumnGap = false;
        this.timerColumnGap = null;
        this.isAutoRowGap = false;
        this.timerRowGap = null;
        this.savedFlexWrap = 'nowrap';

        // 每行独立选中索引（-1 表示无选中）
        this.idxOverflow = -1;
        this.idxWrap = -1;
        this.idxDir = -1;
        this.idxItemDisplay = -1;
        this.idxItemDisplay4to6 = -1;
        this.idxFlex1Display = -1;
        this.idxGap = -1;
        this.idxColumnGap = -1;
        this.idxRowGap = -1;
    },
};
