"use strict";
var __classPrivateFieldGet = (this && this.__classPrivateFieldGet) || function (receiver, state, kind, f) {
    if (kind === "a" && !f) throw new TypeError("Private accessor was defined without a getter");
    if (typeof state === "function" ? receiver !== state || !f : !state.has(receiver)) throw new TypeError("Cannot read private member from an object whose class did not declare it");
    return kind === "m" ? f : kind === "a" ? f.call(receiver) : f ? f.value : state.get(receiver);
};
var __classPrivateFieldSet = (this && this.__classPrivateFieldSet) || function (receiver, state, value, kind, f) {
    if (kind === "m") throw new TypeError("Private method is not writable");
    if (kind === "a" && !f) throw new TypeError("Private accessor was defined without a setter");
    if (typeof state === "function" ? receiver !== state || !f : !state.has(receiver)) throw new TypeError("Cannot write private member to an object whose class did not declare it");
    return (kind === "a" ? f.call(receiver, value) : f ? f.value = value : state.set(receiver, value)), value;
};
var _hmc_win32_instances, _hmc_win32_thenConsole, _hmc_win32_window_get, _hmc_win32_watch_get, _hmc_win32_shell_get, _hmc_win32_usb_get, _hmc_win32_clipboard_get, _hmc_win32_process_get, _hmc_win32_auto_get;
Object.defineProperty(exports, "__esModule", { value: true });
exports.native = exports.hmc = exports.HWND = exports.RECT2Rect = exports.pointInRect = exports.RectInRect = void 0;
const path = require("path");
const native_1 = require("./native");
Object.defineProperty(exports, "native", { enumerable: true, get: function () { return native_1.native; } });
const child_process_1 = require("child_process");
const net = require("net");
let chcpList = {
    37: "IBM037",
    437: "IBM437",
    500: "IBM500",
    708: "ASMO-708",
    720: "DOS-720",
    737: "ibm737",
    775: "ibm775",
    850: "ibm850",
    852: "ibm852",
    855: "IBM855",
    857: "ibm857",
    858: "IBM00858",
    860: "IBM860",
    861: "ibm861",
    862: "DOS-862",
    863: "IBM863",
    864: "IBM864",
    865: "IBM865",
    866: "cp866",
    869: "ibm869",
    870: "IBM870",
    874: "windows-874",
    875: "cp875",
    932: "shift_jis",
    936: "gb2312",
    949: "ks_c_5601-1987",
    950: "big5",
    1026: "IBM1026",
    1047: "IBM01047",
    1140: "IBM01140",
    1141: "IBM01141",
    1142: "IBM01142",
    1143: "IBM01143",
    1144: "IBM01144",
    1145: "IBM01145",
    1146: "IBM01146",
    1147: "IBM01147",
    1148: "IBM01148",
    1149: "IBM01149",
    1200: "utf-16",
    1201: "unicodeFFFE",
    1250: "windows-1250",
    1251: "windows-1251",
    1252: "windows-1252",
    1253: "windows-1253",
    1254: "windows-1254",
    1255: "windows-1255",
    1256: "windows-1256",
    1257: "windows-1257",
    1258: "windows-1258",
    1361: "Johab",
    10000: "macintosh",
    10001: "x-mac-japanese",
    10002: "x-mac-chinesetrad",
    10003: "x-mac-korean",
    10004: "x-mac-arabic",
    10005: "x-mac-hebrew",
    10006: "x-mac-greek",
    10007: "x-mac-cyrillic",
    10008: "x-mac-chinesesimp",
    10010: "x-mac-romanian",
    10017: "x-mac-ukrainian",
    10021: "x-mac-thai",
    10029: "x-mac-ce",
    10079: "x-mac-icelandic",
    10081: "x-mac-turkish",
    10082: "x-mac-croatian",
    12000: "utf-32",
    12001: "utf-32BE",
    20000: "x-Chinese_CNS",
    20001: "x-cp20001",
    20002: "x_Chinese-Eten",
    20003: "x-cp20003",
    20004: "x-cp20004",
    20005: "x-cp20005",
    20105: "x-IA5",
    20106: "x-IA5-German",
    20107: "x-IA5-Swedish",
    20108: "x-IA5-Norwegian",
    20127: "us-ascii",
    20261: "x-cp20261",
    20269: "x-cp20269",
    20273: "IBM273",
    20277: "IBM277",
    20278: "IBM278",
    20280: "IBM280",
    20284: "IBM284",
    20285: "IBM285",
    20290: "IBM290",
    20297: "IBM297",
    20420: "IBM420",
    20423: "IBM423",
    20424: "IBM424",
    20833: "x-EBCDIC-KoreanExtended",
    20838: "IBM-Thai",
    20866: "koi8-r",
    20871: "IBM871",
    20880: "IBM880",
    20905: "IBM905",
    20924: "IBM00924",
    20932: "EUC-JP",
    20936: "x-cp20936",
    20949: "x-cp20949",
    21025: "cp1025",
    21866: "koi8-u",
    28591: "iso-8859-1",
    28592: "iso-8859-2",
    28593: "iso-8859-3",
    28594: "iso-8859-4",
    28595: "iso-8859-5",
    28596: "iso-8859-6",
    28597: "iso-8859-7",
    28598: "iso-8859-8",
    28599: "iso-8859-9",
    28603: "iso-8859-13",
    28605: "iso-8859-15",
    29001: "x-Europa",
    38598: "iso-8859-8-i",
    50220: "iso-2022-jp",
    50221: "csISO2022JP",
    50222: "iso-2022-jp",
    50225: "iso-2022-kr",
    50227: "x-cp50227",
    51932: "euc-jp",
    51936: "EUC-CN",
    51949: "euc-kr",
    52936: "hz-gb-2312",
    54936: "GB18030",
    57002: "x-iscii-de",
    57003: "x-iscii-be",
    57004: "x-iscii-ta",
    57005: "x-iscii-te",
    57006: "x-iscii-as",
    57007: "x-iscii-or",
    57008: "x-iscii-ka",
    57009: "x-iscii-ma",
    57010: "x-iscii-gu",
    57011: "x-iscii-pa",
    65000: "utf-7",
    65001: "utf-8"
};
function systemChcp() {
    let result = { code: 437, chcp: chcpList[437] };
    return new Promise(resolve => {
        (0, child_process_1.execFile)("chcp", function (err, data) {
            if (!data || err)
                return resolve(result);
            let sy_Chcp = data.match(/^.+?(\d+)[\r\n]+$/);
            if (sy_Chcp && chcpList[Number(sy_Chcp[1])]) {
                result.chcp = chcpList[Number(sy_Chcp[1])];
                result.code = Number(sy_Chcp[1]);
                resolve(result);
            }
            resolve(result);
        });
    });
}
function iscRECT(cRECT) {
    return typeof cRECT.left == "number" && typeof cRECT.right == "number" && typeof cRECT.bottom == "number" && typeof cRECT.top == "number";
}
function iscPOINT(cPOINT) {
    return typeof cPOINT.x == "number" && typeof cPOINT.y == "number" && typeof cPOINT.height == "undefined" && typeof cPOINT.width == "undefined";
}
/**
 * 矩形是否在矩形范围中
 * @param inRect
 * @param mian
 * @returns
 */
function RectInRect(mian, InRect) {
    if (iscRECT(mian)) {
        mian = RECT2Rect(mian);
    }
    if (iscRECT(InRect)) {
        InRect = RECT2Rect(InRect);
    }
    if (iscPOINT(InRect)) {
        return pointInRect(InRect, mian);
    }
    let inRect = InRect;
    let isInRet = true;
    // 得出对比传入的边界
    let in_x = inRect.x;
    let in_y = inRect.y;
    let in_xw = inRect.x + inRect.width;
    let in_hy = inRect.y + inRect.height;
    if (!inRect.x)
        in_x = 1;
    if (!inRect.y)
        in_y = 1;
    // 得出mian的边界
    let mian_x = mian.x;
    let mian_y = mian.y;
    let mian_xw = mian.x + mian.width;
    let mian_hy = mian.y + mian.height;
    isInRet = (((in_x >= mian_x && in_x < mian_xw) || (mian_x >= in_x && mian_x <= in_xw)) &&
        ((in_y >= mian_y && in_y < mian_hy) || (mian_y >= in_y && mian_y <= in_hy)))
        ? false
        : true;
    if (isInRet == false) {
        if (mian.x > inRect.x && mian.y > inRect.y &&
            mian.x + mian.width < inRect.x + inRect.width &&
            mian.y + mian.height < inRect.x + inRect.height) {
            return true;
        }
        return false;
    }
    return false;
}
exports.RectInRect = RectInRect;
/**
 * 点是否在矩形范围中
 * @param pt
 * @param rect
 * @returns
 */
function pointInRect(pt, rect) {
    if ((pt.x > rect.x) && (pt.y > rect.y) && (pt.x < (rect.x + rect.width)) && (pt.y < (rect.y + rect.height))) {
        return true;
    }
    return false;
}
exports.pointInRect = pointInRect;
function RECT2Rect(inputRect) {
    return {
        height: inputRect.top - inputRect.bottom,
        width: inputRect.right - inputRect.left,
        x: inputRect.left,
        y: inputRect.top
    };
}
exports.RECT2Rect = RECT2Rect;
/**
 * 句柄 可以视为是一个数字也可以视为是一个功能 {0}
 * 继承了 Number 的构建类
 */
class HWND extends Number {
    constructor(hWnd) {
        super(hWnd);
        this.HWND = hWnd;
    }
    /**
     * 强制关闭窗口不发送被关闭的消息给窗口
     */
    closed() {
        if (!this.exists)
            return false;
        return native_1.native.closedHandle(this.HWND);
    }
    /**
     * 向窗口发送关闭的消息
     */
    close() {
        if (!this.exists)
            return false;
        return native_1.native.lookHandleCloseWindow(this.HWND);
    }
    /**
     * 窗口位置
     */
    get rect() {
        if (!this.exists)
            return null;
        return native_1.native.getWindowRect(this.HWND);
    }
    /**
     * 窗口名称
     */
    get title() {
        return native_1.native.lookHandleGetTitle(this.HWND) || "";
    }
    /**
     * 设置窗口的标题
     * @param Title 标题
     * @returns
     */
    setTitle(Title) {
        if (typeof Title !== "string" || !this.exists) {
            return false;
        }
        return native_1.native.lookHandleSetTitle(this.HWND, Title);
    }
    /**句柄是否有效 */
    get exists() {
        if (!this.HWND)
            return false;
        return native_1.native.isHandle(this.HWND);
    }
    /**句柄是否有效 */
    get isHandle() {
        return this.exists;
    }
    /**
     * 当前句柄的pid
     */
    get pid() {
        if (!this.exists)
            return 0;
        return native_1.native.getHandleProcessID(this.HWND);
    }
    /**
     * 获取主窗口的pid
     */
    get MianPid() {
        if (!this.exists)
            return 0;
        return native_1.native.getHandleProcessID(this.MainHandle);
    }
    get MainHandle() {
        return native_1.native.getMainWindow(this.HWND) || 0;
    }
    /**
     * 判断窗口是否可见
     * @returns
     */
    isVisible() {
        if (!this.HWND)
            return false;
        return native_1.native.isHandleWindowVisible(this.HWND);
    }
    /**
     * 结束该进程
     * @returns
     */
    kill() {
        let processid = this.MianPid;
        if (!processid)
            return false;
        return native_1.native.killProcess(processid);
    }
    /**
     * 隐藏窗口
     * @returns
     */
    hide() {
        if (!this.HWND)
            return false;
        return native_1.native.lookHandleShowWindow(this.HWND, 0);
    }
    /**
     * 显示窗口
     * @returns
     */
    show() {
        if (!this.HWND)
            return false;
        return native_1.native.lookHandleShowWindow(this.HWND, 5);
    }
    /**
     * 窗口最小化
     * @returns
     */
    setMin() {
        if (!this.HWND)
            return false;
        return native_1.native.lookHandleShowWindow(this.HWND, 7);
    }
    /**
     * 窗口最大化
     * @returns
     */
    setMax() {
        if (!this.HWND)
            return false;
        return native_1.native.lookHandleShowWindow(this.HWND, 3);
    }
    /**
     * 恢复最近的状态
     * @returns
     */
    setRestore() {
        if (!this.HWND)
            return false;
        return native_1.native.lookHandleShowWindow(this.HWND, 9);
    }
    /**
     * 聚焦该窗口
     * @returns
     */
    setFocus() {
        if (!this.HWND)
            return false;
        return native_1.native.setWindowFocus(this.HWND);
    }
    /**
     * 禁用窗口
     * @param enabled
     * @returns
     */
    setEnabled(enabled) {
        if (!this.HWND)
            return false;
        return native_1.native.setWindowEnabled(this.HWND, enabled);
    }
    /**
     * 是否被禁用
     * @returns
     */
    isEnabled() {
        if (!this.HWND)
            return false;
        return native_1.native.isEnabled(this.HWND);
    }
    /**
     * 窗口抖动
     * @returns
     */
    setJitter() {
        if (!this.HWND)
            return false;
        return native_1.native.windowJitter(this.HWND);
    }
    /**
     * 判断窗口是否被顶设
     * @returns
     */
    isTop() {
        if (!this.HWND)
            return false;
        return native_1.native.hasWindowTop(this.HWND);
    }
    /**
     * 设置窗口顶设或者取消
     * @returns
     */
    setTopOrCancel() {
        if (!this.HWND)
            return false;
        return native_1.native.setWindowTop(this.HWND);
    }
    /**
     * 设置窗口不透明度
     * @param opacity 0-100 or 0.0 - 1.0
     */
    setOpacity(opacity) {
        if (typeof opacity !== "number" || opacity > 100 || isNaN(opacity))
            throw new Error("fun <setOpacity> arg:<Opacity> is only allowed from 0.0 to 1.0 or  0 to 255");
        if (opacity < 1) {
            return this.setTransparent(Math.trunc(255 * opacity));
        }
        opacity = (255 / 100) * opacity;
        if (!isNaN(opacity)) {
            return this.setTransparent(Math.trunc(255 * opacity));
        }
        return false;
    }
    /**
     * 设置窗口不透明度
     * @param opacity -1 - 255
     */
    setTransparent(opacity) {
        if (opacity > -1 || opacity < 255) {
            throw new Error("fun <setTransparent> arg:<Opacity> is only allowed from -1 to 255");
        }
        if (!this.HWND)
            return false;
        return native_1.native.setHandleTransparent(this.HWND, opacity);
    }
}
exports.HWND = HWND;
/**注册表根目录 */
const Hkey = {
    /**用作默认用户首选设置，也作为单个用户的首选设置 */
    HKEY_CURRENT_CONFIG: "HKEY_CURRENT_CONFIG",
    /**用作默认用户首选设置，也作为单个用户的首选设置 */
    HKEY_USERS: "HKEY_USERS",
    /**是与文档类型和 OLE\COM 相关的信息的支持键。这个键是 */
    HKEY_CLASSES_ROOT: "HKEY_CLASSES_ROOT",
    /**包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息 */
    HKEY_LOCAL_MACHINE: "HKEY_LOCAL_MACHINE",
    /**管理系统当前的用户信息 */
    HKEY_CURRENT_USER: "HKEY_CURRENT_USER",
};
/**
 * 直达路径解析
 * @param Path 全路径(直达路径)
 * @param atkey 是否将最后一个值解释为键
 * @returns
 */
function analysisDirectPath(Path, atkey) {
    let directPath = [];
    directPath.push(...Path.split(new RegExp(Object.keys(Hkey).join("|"))));
    if (directPath.length < 2) {
        return [];
    }
    directPath[1] = directPath[1].replace(/[\\\/]+/g, "\\");
    if (atkey) {
        let paths = directPath[1].split(/[\\]/g);
        if (paths.length) {
            let popData = paths.pop();
            popData && directPath.push(popData);
            directPath.unshift(...paths);
        }
    }
    return directPath;
}
/**
 * 是否是 HKEY
 */
function hasHKEY(HKEY) {
    if (typeof HKEY !== "string")
        return false;
    return new RegExp(`^${Object.keys(Hkey).join("|")}$`).exec(HKEY);
}
/**
 * 判断输入的注册表路径是否合法
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 */
function hasregArgs(HKEY, Path, funName) {
    if (!hasHKEY(HKEY) || !Path) {
        throw new Error(`
      <fun> ${funName}  
      argument size 2 or 3
      HKEY : ${Object.keys(Hkey)}
      Path : string
      key ?: string  or "" or undefined
      `);
    }
}
class hmc_win32 {
    constructor() {
        _hmc_win32_instances.add(this);
        /**原生HMC */
        this.native = native_1.native;
        /**一个可以快速操作的句柄类对象 */
        this.HWND = HWND;
        /**版本号 */
        this.version = native_1.native.version;
        /**功能介绍 */
        this.desc = native_1.native.desc;
        /**当前二进制适用系统平台 */
        this.platform = native_1.native.platform;
        this.ref = {
            /**
            * 将内容格式化为文本路径
            * @param Str
            * @returns
            */
            path(Str) {
                return path.resolve(String(Str || "")).replace(/([\0\n\r]+)?$/, '\0');
            },
            /**
             * 格式化为bool
             * @param bool
             * @returns
             */
            bool(bool) {
                return bool ? true : false;
            },
            /**
             * 将内容格式化为文本
             * @param Str
             * @returns
             */
            string(Str) {
                return String(Str || "");
            },
            /**
             * 格式化数字为int(强制)
             * @param Num
             * @returns
             */
            int(Num) {
                if (!Num)
                    return 0;
                if (typeof Num == "object" && Num instanceof Number) {
                    Num = Num === null || Num === void 0 ? void 0 : Num.valueOf();
                }
                // 取整
                Num = Math.trunc(Num + 0);
                if (typeof Num == "number" && !isNaN(Num))
                    return Num;
                // true == 1
                if (Num && typeof Num == "boolean")
                    Num = 1;
                // false = 0;
                if (!Num && typeof Num == "boolean")
                    Num = 0;
                if (Num >= Infinity) {
                    Num = 999999999999999;
                }
                if (Num <= -Infinity) {
                    Num = -999999999999999;
                }
                return Num;
            },
            HKEY: Hkey,
            /**
             * 拼合buff片段
             * @param buffList
             * @returns
             */
            concatBuff(buffList) {
                let buffSize = 0;
                for (let index = 0; index < buffList.length; index++) {
                    const buff = buffList[index];
                    buffSize = buffSize + buff.byteLength;
                }
                let ResponseData = Buffer.concat([...buffList], buffSize);
                return ResponseData;
            }
        };
        /**
         * 获取所有窗口的信息
         * ! @time 28.283203125 ms
         * @deprecated 该功能有概率使进程奔溃 请使用 getAllWindowsHandle 代替该功能
         **/
        this.getAllWindows = native_1.native.getAllWindows;
        /**
         * 注册表编辑
         */
        this.registr = {
            /**
             * 直达路径解析
             * @param Path 全路径(直达路径)
             * @param atkey 是否将最后一个值解释为键
             * @returns
             */
            analysisDirectPath: analysisDirectPath,
            /**
             * 判断注册表中是否有该键值
             * @param HKEY 根路径
             * @param Path 路径
             * @param key 键
             * @time 0.06591796875 ms
             * @returns
             */
            has: (HKEY, Path, key) => {
                return this.hasRegistrKey(HKEY, Path, key);
            },
            /**
             * 获取内容(文本)
             * @param HKEY 根路径
             * @param Path 路径
             * @param key 键
             * @time 0.108ms
             * @returns
             */
            get: (HKEY, Path, key) => {
                return this.getStringRegKey(HKEY, Path, key);
            },
            /**
             * 设置键值对
             * @param HKEY 根路径
             * @param Path 路径
             * @param key 键
             * @param Value 数据
             * @time 2.02392578125 ms
             * @returns
             */
            set: (HKEY, Path, key, value) => {
                return this.setRegistrKey(HKEY, Path, key, value);
            },
            /**
             * 删除数据
             * @param HKEY 根路径
             * @param Path 路径
             * @param key 键
             * @time 0.076904296875 ms
             * @returns
             */
            remove: (HKEY, Path, key) => {
                return this.removeStringRegKey(HKEY, Path, key);
            },
            /**
             * 枚举键值
             * @param HKEY 根路径
             * @param Path 路径
             * @time 0.06689453125 ms
             * @returns
             */
            keys: (HKEY, Path) => {
                return this.enumRegistrKey(HKEY, Path);
            },
            /**
             * 将当前的路径的注册表值转表
             * @param HKEY
             * @param Path
             */
            list: (HKEY, Path) => {
                return this.listRegistrPath(HKEY, Path);
            },
            /**
             * 创建新的路径
             * @param HKEY 根路径
             * @param Path 路径
             * @time 2.02392578125 ms
             * @returns
             */
            create: (HKEY, Path, key) => {
                return this.createPathRegistr(HKEY, Path);
            },
            /**
             * 打开一个注册表路径并返回一些实用方法
             * @param HKEY 根路径
             * @param Path 路径
             * @param key 键
             * @returns
             */ open: (HKEY, Path, key) => {
                return this.openRegKey(HKEY, Path, key);
            },
            /**
             * 判断注册表中是否有该键值
             * @param HKEY 根路径
             * @param Path 路径
             * @param key 键
             * @time 0.06591796875 ms
             * @returns
             */
            get hasRegistrKey() {
                return this.has;
            },
            /**
             * 将当前的路径的注册表值转表
             * @param HKEY
             * @param Path
             */
            get listRegistrPath() {
                return this.list;
            },
            /**
             * 枚举键值
             * @param HKEY 根路径
             * @param Path 路径
             * @time 0.06689453125 ms
             * @returns
             */
            get enumRegistrKey() {
                return this.keys;
            },
            /**
             * 删除数据
             * @param HKEY 根路径
             * @param Path 路径
             * @param key 键
             * @time 0.076904296875 ms
             * @returns
             */
            get removeStringRegKey() {
                return this.remove;
            },
            /**
             * 设置键值对
             * @param HKEY 根路径
             * @param Path 路径
             * @param key 键
             * @param Value 数据
             * @time 2.02392578125 ms
             * @returns
             */
            get setRegistrKey() {
                return this.set;
            },
            /**
             * 获取内容(文本)
             * @param HKEY 根路径
             * @param Path 路径
             * @param key 键
             * @time 0.108ms
             * @returns
             */
            get getStringRegKey() {
                return this.get;
            },
            /**
             * 获取内容(数字)
             * @param HKEY 根路径
             * @param Path 路径
             * @param key 键
             * @time 0.10888671875 ms
             * @returns
             */
            getNumberRegKey: (HKEY, Path, key) => {
                return this.getNumberRegKey(HKEY, Path, key);
            },
            /**
             * 创建新的路径
             * @param HKEY 根路径
             * @param Path 路径
             * @time 2.02392578125 ms
             * @returns
             */
            get createPathRegistr() {
                return this.create;
            },
            /**
             * 获取内容(二进制 Buffer)
             * @param HKEY 根路径
             * @param Path 路径
             * @param key 键
             * @time 0.06787109375 ms
             * @returns
             */
            getRegistrBuffValue: (HKEY, Path, key) => {
                return this.getRegistrBuffValue(HKEY, Path, key);
            },
            /**
             * 打开一个注册表路径并返回一些实用方法
             * @param HKEY 根路径
             * @param Path 路径
             * @param key 键
             * @returns
             */
            get openRegKey() {
                return this.open;
            },
        };
        // /**
        //  * PowerShell
        //  * @param args 
        //  * @param options 
        //  * @param CallBack 
        //  * @returns 
        //  */
        // PowerShell(args: readonly string[] | string, options?: SpawnOptionsWithoutStdio | undefined | ((err: Buffer | null, data: Buffer | null, spawn: ChildProcessWithoutNullStreams) => void), CallBack?: ((err: Buffer | null, data: Buffer | null, spawn: ChildProcessWithoutNullStreams) => void)) {
        //   let _: undefined | ChildProcessWithoutNullStreams = undefined;
        //   let dataList: Buffer[] = [];
        //   let errDataList: Buffer[] = [];
        //   let PowerShell: any = new Promise<{ data: Buffer, err: Buffer }>(async(resolve, reject) => {
        //     let cmd: string[] = []
        //     let spawnSeting = Object.assign({
        //       "cwd": path.resolve(process.cwd()),
        //       "windowsHide": true,
        //     }, options || {});
        //     let SetConsoleEncoding = "$OutputEncoding = [console]::InputEncoding = [console]::OutputEncoding = New-Object System.Text.UTF8Encoding;";
        //     let sinLineSetConsoleEncoding = "-Encoding utf8";
        //     if (args) {
        //       if (Array.isArray(args)) {
        //         for (let index = 0; index < args.length; index++) {
        //           const arg = args[index];
        //           cmd.push(arg);
        //         }
        //       }
        //       else if (typeof args == "string") {
        //         cmd.push(args);
        //       }
        //     }
        //     let isSystemChcpNotEN = (await this.systemChcp()).code!=437;
        //     let HKEY:HKEY = "HKEY_CURRENT_USER";
        //     let oidCodePage:null|number = null; 
        //     let patsAllSystem32 ="Console\\%SystemRoot%_System32_WindowsPowerShell_v1.0_powershell.exe";
        //     let patsAllSysWOW64 ="Console\\%SystemRoot%_SysWOW64_WindowsPowerShell_v1.0_powershell.exe";
        //     let isdel = false;
        //     // if(isSystemChcpNotEN){
        //     //   if(!this.hasRegistrKey(HKEY,patsAllSystem32,"CodePage")){
        //     //     this.setRegistrDword(HKEY,patsAllSystem32,"CodePage",65001);
        //     //     this.setRegistrDword(HKEY,patsAllSysWOW64,"CodePage",65001);
        //     //   }else{
        //     //     oidCodePage = this.getRegistrDword(HKEY,patsAllSystem32,"CodePage")||0;
        //     //     this.setRegistrDword(HKEY,patsAllSystem32,"CodePage",65001);
        //     //     this.setRegistrDword(HKEY,patsAllSysWOW64,"CodePage",65001);
        //     //   }
        //     // }
        //     let removeChcp = ()=> {
        //       // if(isdel)return;
        //       // if(oidCodePage){
        //       //   this.setRegistrDword(HKEY,patsAllSystem32,"CodePage",oidCodePage);
        //       //   this.setRegistrDword(HKEY,patsAllSysWOW64,"CodePage",oidCodePage);
        //       //   isdel=true;
        //       // }else{
        //       //   this.removeStringRegValue(HKEY,patsAllSystem32,"CodePage");
        //       //   this.removeStringRegValue(HKEY,patsAllSysWOW64,"CodePage");
        //       //   isdel=true;
        //       // }
        //     }
        //     _ = spawn("PowerShell",
        //     // [`'$OutputEncoding = [console]::InputEncoding = [console]::OutputEncoding = New-Object System.Text.UTF8Encoding' + [Environment]::Newline + (Get-Content -Raw $PROFILE -ErrorAction SilentlyContinue) | Set-Content -Encoding utf8 $PROFILE\r\n`,...cmd]
        //     cmd
        //     ,spawnSeting);
        //     // _.stdout.setEncoding("utf8");
        //     // _.stderr.setEncoding("utf8");
        //     _.once("spawn",()=>{
        //     })
        //     _.once("close", (d) => {
        //       resolve({
        //         err: this.ref.concatBuff(errDataList),
        //         data: this.ref.concatBuff(dataList)
        //       });
        //       removeChcp();
        //     });
        //     let CallBacks = typeof options == "function" ? options : typeof CallBack == "function" ? CallBack : null
        //     _.stdout.on('data', (_data) => {
        //       dataList.push(_data);
        //       if (_) CallBacks && CallBacks(null, _data, _);
        //       removeChcp();
        //     });
        //     _.stderr.on('data', (_data) => {
        //       errDataList.push(_data);
        //       if (_) CallBacks && CallBacks(null, _data, _);
        //       removeChcp();
        //     });
        //   });
        //   PowerShell.spawn = _;
        //   PowerShell.errDataList = errDataList;
        //   PowerShell.dataList = dataList;
        //   return PowerShell as Promise<{ data: Buffer, err: Buffer }> & {
        //     spawn?: ChildProcessWithoutNullStreams,
        //     errDataList?: Buffer[],
        //     dataList?: Buffer[],
        //   };
        // }
        /**
         * 获取系统shell默认编码
         * @returns
         */
        this.systemChcp = systemChcp;
        _hmc_win32_thenConsole.set(this, void 0);
        /**
         * 所有窗口操作方法的归类合集 (拥有统一化名称)
         */
        this.window = __classPrivateFieldGet(this, _hmc_win32_instances, "a", _hmc_win32_window_get);
        /**
        * 所有监听函数的合集 (拥有统一化名称)
        */
        this.watch = __classPrivateFieldGet(this, _hmc_win32_instances, "a", _hmc_win32_watch_get);
        /**剪贴板工具集  (拥有统一化名称) */
        this.clipboard = __classPrivateFieldGet(this, _hmc_win32_instances, "a", _hmc_win32_clipboard_get);
        /**自动化工具集   (拥有统一化名称) */
        this.auto = __classPrivateFieldGet(this, _hmc_win32_instances, "a", _hmc_win32_auto_get);
        /**USB 控制的归档   (拥有统一化名称) */
        this.usb = __classPrivateFieldGet(this, _hmc_win32_instances, "a", _hmc_win32_usb_get);
        /**实用工具集   (拥有统一化名称)*/
        this.shell = __classPrivateFieldGet(this, _hmc_win32_instances, "a", _hmc_win32_shell_get);
        /**进程操作合集   (拥有统一化名称) */
        this.process = __classPrivateFieldGet(this, _hmc_win32_instances, "a", _hmc_win32_process_get);
    }
    get hmc() { return this; }
    get default() { return this; }
    /**
     * 设置窗口位置大小
     * @param Handle 句柄
     * @param x (right) 从屏幕右边到所在位置得像素数
     * @param y (top) 从屏幕顶部边到所在位置得像素数
     * @param width 窗口宽度
     * @param height 窗口高度
     * @time 0.0068359375 ms
     * @returns 布尔
     */
    setWindowMode(HWND, x, y, width, height) {
        if (!this.ref.int(HWND))
            return false;
        if (x && typeof x == "object") {
            let SetWindowRect = x;
            SetWindowRect.y = SetWindowRect.top
                ? SetWindowRect.top
                : SetWindowRect.y || 0;
            SetWindowRect.x = SetWindowRect.right
                ? SetWindowRect.right
                : SetWindowRect.x || 0;
            if (SetWindowRect.x)
                x = SetWindowRect.x;
            if (SetWindowRect.y)
                y = SetWindowRect.y;
            if (SetWindowRect.width)
                width = SetWindowRect.width;
            if (SetWindowRect.height)
                height = SetWindowRect.height;
        }
        if (!x)
            x = 0;
        if (!y)
            x = 0;
        if (!width)
            width = 0;
        if (!height)
            height = 0;
        return native_1.native.setWindowMode(this.ref.int(HWND), this.ref.int(x), this.ref.int(y), this.ref.int(width), this.ref.int(height));
    }
    /**
     * 判断注册表中是否有该键值
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.06591796875 ms
     * @returns
     */
    hasRegistrKey(HKEY, Path, key) {
        if (!key)
            key = "";
        hasregArgs(HKEY, Path, "hasRegistrKey");
        return native_1.native.hasRegistrKey(HKEY, this.ref.string(Path)
            .split(/[\\\/]+/g)
            .join("\\"), this.ref.string(key));
    }
    /**
     * 设置键值对内容(64位数字)
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @param Qword (64位数字)
     * @returns
     */
    setRegistrQword(HKEY, Path, key, Qword) {
        if (!key)
            key = "";
        hasregArgs(HKEY, Path, "hasRegistrKey");
        if (!Qword)
            Qword = BigInt(0);
        return native_1.native.setRegistrQword(HKEY, this.ref.string(Path), this.ref.string(key), BigInt(Qword));
    }
    /**
     * 设置键值对内容(32位数字)
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @param Qword (32位数字)
     * @returns
     */
    setRegistrDword(HKEY, Path, key, Dword) {
        if (!key)
            key = "";
        hasregArgs(HKEY, Path, "hasRegistrKey");
        return native_1.native.setRegistrDword(HKEY, this.ref.string(Path), this.ref.string(key), this.ref.int(Dword));
    }
    /**
     * 获取内容(64位数字)
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.06787109375 ms
     * @returns
     */
    getRegistrQword(HKEY, Path, key) {
        if (!key)
            key = "";
        hasregArgs(HKEY, Path, "getRegistrQword");
        return native_1.native.getRegistrQword(HKEY, this.ref
            .string(Path)
            .split(/[\\\/]+/g)
            .join("\\"), this.ref.string(key));
    }
    /**
     * 获取内容(64位数字)
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.06787109375 ms
     * @returns
     */
    getRegistrDword(HKEY, Path, key) {
        if (!key)
            key = "";
        hasregArgs(HKEY, Path, "getRegistrDword");
        return native_1.native.getRegistrDword(HKEY, this.ref
            .string(Path)
            .split(/[\\\/]+/g)
            .join("\\"), this.ref.string(key));
    }
    /**
     * 获取内容(二进制 Buffer)
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.06787109375 ms
     * @returns
     */
    getRegistrBuffValue(HKEY, Path, key) {
        if (!key)
            key = "";
        hasregArgs(HKEY, Path, "getRegistrBuffValue");
        return native_1.native.getRegistrBuffValue(HKEY, this.ref
            .string(Path)
            .split(/[\\\/]+/g)
            .join("\\"), this.ref.string(key));
    }
    /**
     * 枚举键值
     * @param HKEY 根路径
     * @param Path 路径
     * @time 0.06689453125 ms
     * @returns
     */
    enumRegistrKey(HKEY, Path) {
        hasregArgs(HKEY, Path, "createPathRegistr");
        let enumKeyList = new Set();
        let NatenumKey = native_1.native.enumRegistrKey(HKEY, this.ref
            .string(Path)
            .split(/[\\\/]+/g)
            .join("\\"));
        for (let index = 0; index < NatenumKey.length; index++) {
            const key = NatenumKey[index];
            enumKeyList.add(key);
        }
        return [...enumKeyList];
    }
    /**
     * 将当前的路径的注册表值转表
     * @param HKEY
     * @param Path
     */
    listRegistrPath(HKEY, Path) {
        let enumRegistrKey = this.enumRegistrKey(HKEY, Path);
        enumRegistrKey.unshift("");
        let data = {
            "": "",
        };
        for (let i = 0; i < enumRegistrKey.length; i++) {
            data[enumRegistrKey[i]] = this.getStringRegKey(HKEY, Path, enumRegistrKey[i]);
        }
        return data;
    }
    /**
     * 判断该键值是否存在子项
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     */
    isRegistrTreeKey(HKEY, Path, key) {
        return !!this.enumRegistrKey(HKEY, Path + (!key ? "" : "\\" + key)).length;
    }
    /**
     * 获取内容(文本)
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.108ms
     * @returns
     */
    getStringRegKey(HKEY, Path, key) {
        if (!key)
            key = "";
        hasregArgs(HKEY, Path, "getStringRegKey");
        return native_1.native.getStringRegKey(HKEY, this.ref
            .string(Path)
            .split(/[\\\/]+/g)
            .join("\\"), this.ref.string(key));
    }
    /**
     * 打开一个注册表路径并返回一些实用方法
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @returns
     */
    openRegKey(HKEY, Path, key) {
        let _this = this;
        if (!key)
            key = "";
        hasregArgs(HKEY, Path, "openRegKey");
        return {
            /**
             * 获取全路径
             */
            get path() {
                return HKEY.concat("\\", Path, "\\", key || "");
            },
            /**
             * 设置一个值
             * @param data 数据
             */
            set(data) {
                return native_1.native.setRegistrKey(HKEY, Path, key || "", data);
            },
            /**
             * 获取内容
             * @returns
             */
            get() {
                return native_1.native.getStringRegKey(HKEY, Path, key || "");
            },
            /**
             * 获取该内容并将其视为二进制缓冲区
             * @returns 二进制缓冲区
             */
            getBuff() {
                return (native_1.native.getRegistrBuffValue(HKEY, Path, key || "") || Buffer.alloc(0));
            },
            /**
             * 获取该内容并将其视为数字
             * @returns 数字
             */
            getNumber() {
                return Number(native_1.native.getStringRegKey(HKEY, Path, key || ""));
            },
            /**
             * 枚举当前路径下的键
             * @returns 键 数组
             */
            keys() {
                return _this.enumRegistrKey(HKEY, Path);
            },
            /**
             * 将当前目录转为对象
             */
            list() {
                return _this.listRegistrPath(HKEY, Path);
            },
        };
    }
    /**
     * 获取内容(数字)
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.10888671875 ms
     * @returns
     */
    getNumberRegKey(HKEY, Path, key) {
        if (!key)
            key = "";
        hasregArgs(HKEY, Path, "getNumberRegKey");
        return this.ref.int(native_1.native.getStringRegKey(HKEY, this.ref
            .string(Path)
            .split(/[\\\/]+/g)
            .join("\\"), this.ref.string(key)));
    }
    /**
     * 删除键 (文件夹)
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.076904296875 ms
     * @returns
     */
    removeStringRegKey(HKEY, Path, key) {
        if (!key)
            key = "";
        hasregArgs(HKEY, Path, "removeStringRegKey");
        return native_1.native.removeStringRegKey(HKEY, this.ref
            .string(Path)
            .split(/[\\\/]+/g)
            .join("\\"), this.ref.string(key));
    }
    /**
     * 删除该目录下的所有内容（树遍历）
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @returns
     */
    removeStringRegKeyWalk(HKEY, Path, key) {
        if (!key) {
            let paths = this.ref
                .string(Path)
                .split(/[\\\/]/g);
            key = paths.pop();
            if (!key)
                throw new Error("Invalid key because it is empty");
            Path = paths.join("\\");
        }
        hasregArgs(HKEY, Path, "removeStringRegKeyWalk");
        return native_1.native.removeStringRegKeyWalk(HKEY, this.ref
            .string(Path)
            .split(/[\\\/]+/g)
            .join("\\"), this.ref.string(key));
    }
    /**
   * 删除该目录下的所有内容（树遍历）
   * @param HKEY 根路径
   * @param Path 路径
   * @param key 键
   * @returns
   */
    removeStringTree(HKEY, Path, key) {
        return this.removeStringRegKeyWalk(HKEY, Path, key);
    }
    /**
     * 删除该键值
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @returns
     */
    removeStringRegValue(HKEY, Path, key) {
        if (!key)
            key = "";
        hasregArgs(HKEY, Path, "removeStringRegValue");
        return native_1.native.removeStringRegValue(HKEY, this.ref
            .string(Path)
            .split(/[\\\/]/g)
            .join("\\"), this.ref.string(key));
    }
    /**
     * 设置键值对
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @param Value 数据
     * @time 2.02392578125 ms
     * @returns
     */
    setRegistrKey(HKEY, Path, key, Value) {
        if (!key)
            key = "";
        hasregArgs(HKEY, Path, "setRegistrKey");
        return native_1.native.setRegistrKey(HKEY, this.ref
            .string(Path)
            .split(/[\\\/]/g)
            .join("\\"), this.ref.string(key), this.ref.string(Value));
    }
    /**
     * 创建新的路径
     * @param HKEY 根路径
     * @param Path 路径
     * @time 2.02392578125 ms
     * @returns
     */
    createPathRegistr(HKEY, Path) {
        hasregArgs(HKEY, Path, "createPathRegistr");
        return native_1.native.createPathRegistr(HKEY, this.ref
            .string(Path)
            .split(/[\\\/]/g)
            .join("\\"));
    }
    /**
     * 方法用于显示带有一条指定消息和一个 确认 按钮的警告框
     * @param Message 消息
     * @param Title 标题
     * @time any ms
     * @returns
     */
    alert(Message, Title) {
        return native_1.native.alert(Message, typeof Title != "string" ? getDefaultTitele() : Title);
    }
    /**
     * 方法用于显示带有一条指定消息和 确认 和取消  的按钮的消息框
     * @param Message 消息
     * @param Title 标题
     * @time any ms
     * @returns
     */
    confirm(Message, Title) {
        return native_1.native.confirm(Message, typeof Title != "string" ? getDefaultTitele() : Title);
    }
    /**
     * 方法用于显示带有一条指定消息和一个 确认 按钮的和❌（X）的消息框。
     * @param Message 消息
     * @param Title 标题
     * @time any ms
     * @returns
     */
    MessageStop(Message, Title) {
        return native_1.native.MessageStop(Message, typeof Title != "string" ? getDefaultTitele() : Title);
    }
    /**
     * 方法用于显示带有一条指定消息和一个 确认 按钮的错误框 附带有❗ 感叹号。
     * @param Message 消息
     * @param Title 标题
     * @time any ms
     * @returns
     */
    MessageError(Message, Title) {
        return native_1.native.MessageError(Message, typeof Title != "string" ? getDefaultTitele() : Title);
    }
    /**
     * 获取所有窗口句柄并返回一个快速操作的句柄类 可以快速操作窗口
     * @time 0.657958984375 ms
     * @example ```javascript
     * const getAllWindows = hmc.getAllWindowsHandle();
     * console.log({
     * title:getAllWindows[0].title,
     * handle : getAllWindows[0]+0,
     * rect:getAllWindows[0].rect,
     * })
    //  log=>
    //  {
    //   "title": "Program Manager",
    //   "handle": 65826,
    //   "rect": {
    //       "top": 0,
    //       "bottom": 1080,
    //       "left": 0,
    //       "right": 1920,
    //       "y": 0,
    //       "x": 0,
    //       "width": 1920,
    //       "height": 1080
    //   }
    //  }
     *  ```
     * @returns
     */
    getAllWindowsHandle() {
        let data = [];
        let AllWindowsHandle = native_1.native.getAllWindowsHandle();
        for (let index = 0; index < AllWindowsHandle.length; index++) {
            const element = AllWindowsHandle[index];
            // const mydata = {
            //   _Handle:null as null | HWND ,
            //   Handle:element,
            //   get handle(){
            //     if(!mydata._Handle) mydata._Handle=new HWND(mydata.Handle);
            //     return mydata._Handle
            //   }
            // }
            // data.push(mydata);
            data.push(new HWND(element));
        }
        return data;
    }
    /**
     * 进程监听 当该进程被关闭的时候执行回调
     * @param ProcessID 进程id
     * @param callback 回调函数
     * @param awaitMs 每次执行的延迟事件
     * @default awaitMs 500
     * @example ```javascript
     * hmc_win32.processWatchdog(4836,()=>console.log("进程已经退出。。。"));
     * hmc_win32.sleep(2836);
     * hmc_win32.killProcess(4836);
     * ```
     * @returns 包含一个quit函数(结束监听)的异步或对象
     */
    processWatchdog(ProcessID, callback, awaitMs) {
        let quit = false;
        if (!callback) {
            let Prom = new Promise(async (resolve, reject) => {
                while (true) {
                    if (quit)
                        break;
                    await this.Sleep(awaitMs || 500);
                    if (!this.hasProcess(this.ref.int(ProcessID))) {
                        resolve(void 0);
                        break;
                    }
                }
            });
            Prom.quit = function () {
                quit = true;
            };
            return Prom;
        }
        (async () => {
            while (true) {
                await this.Sleep(awaitMs || 500);
                if (!this.hasProcess(this.ref.int(ProcessID))) {
                    typeof callback == "function" && callback();
                    break;
                }
            }
        })();
        return {
            quit: function () {
                quit = true;
            },
        };
    }
    /**
     * 监听鼠标所在的窗口的句柄
     * @param callback 回调函数
     * @param awaitMs 每次延迟的事件
     * @default awaitMs 350
     * @example ```javascript
     * let WatchPoint = hmc_win32.WatchWindowPoint(function(newPoint,oidPoint,HWND){
      console.log(newPoint,oidPoint,HWND,HWND.title)
      // quit 结束
      WatchPoint.quit();
      });
     * ```
     * @returns 一个可以控制结束和延迟事件的对象
     */
    WatchWindowPoint(callback, awaitMs) {
        let quit = false;
        let oidPoint = native_1.native.getPointWindow() || 0;
        (async () => {
            if (typeof callback !== "function")
                return;
            while (true) {
                if (quit)
                    return;
                let newPoint = native_1.native.getPointWindow() || 0;
                if (newPoint)
                    if (newPoint != oidPoint) {
                        if (callback) {
                            callback(this.ref.int(newPoint), this.ref.int(oidPoint) || 0, new this.HWND(this.ref.int(newPoint)));
                            oidPoint = newPoint;
                        }
                    }
                await this.Sleep(awaitMs || 350);
            }
        })();
        return {
            /**结束监听 */
            quit: function () {
                quit = true;
            },
            /**设置每次延迟事件 */
            setAwaitMs(ms) {
                awaitMs = ms;
            },
        };
    }
    /**
    * 监听焦点窗口变化并返回句柄
    * @param callback 回调函数
    * @param awaitMs 每次延迟的事件
    * @default awaitMs 350
    * @example ```javascript
    * let WatchForeg = hmc_win32.WatchWindowForeground(function(newForeg,oidForeg,HWND){
      console.log(newForeg,oidForeg,HWND,HWND.title)
      // quit 结束
      WatchForeg.quit();
      });
     * ```
    * @returns 一个可以控制结束和延迟事件的对象
    */
    WatchWindowForeground(callback, awaitMs) {
        let quit = false;
        let oidForeg = this.getForegroundWindow();
        (async () => {
            if (typeof callback !== "function")
                return;
            while (true) {
                if (quit)
                    return;
                let newForeg = this.getForegroundWindow();
                if (newForeg)
                    if (this.ref.int(newForeg) != this.ref.int(oidForeg)) {
                        if (callback) {
                            callback(this.ref.int(newForeg), this.ref.int(oidForeg) || 0, new this.HWND(this.ref.int(newForeg)));
                            oidForeg = newForeg;
                        }
                    }
                await this.Sleep(awaitMs || 350);
            }
        })();
        return {
            /**结束监听 */
            quit: function () {
                quit = true;
            },
            /**设置每次延迟事件 */
            setAwaitMs(ms) {
                awaitMs = ms;
            },
        };
    }
    /**
     * 打开一个程序
     * @param AppPath 程序路径
     * @param Command 命令行
     * @param cwd 工作路径
     * @param hide 隐藏窗口
     * @param UAC 提升到管理员权限
     * @default
     * - Command ""
     * - cwd AppPath DirPath
     * - hide false
     * - UAC false
     * @returns
     */
    openApp(AppPath, Command, cwd, hide, UAC) {
        return native_1.native.openApp(this.ref.string(AppPath), this.ref.string(Array.isArray(Command)
            ? `${Command.map((data) => String(data)
                .replace(/(["]+)$/, '"')
                .replace(/^"+/, '"')).join(" ")}`
            : Command) || "", this.ref.string(cwd || path.parse(AppPath || "").dir || process.cwd()), this.ref.bool(hide || false), this.ref.bool(UAC || false));
    }
    /**
     * 获取该名称 /正则匹配的进程列表
     * @param Name
     * @returns
     */
    getProcessNameList(...Name) {
        let resultList = [];
        let ProcessList = native_1.native.getProcessList();
        for (let index = 0; index < ProcessList.length; index++) {
            const Process = ProcessList[index];
            const { pid, name } = Process;
            for (let NextNameIndex = 0; NextNameIndex < Name.length; NextNameIndex++) {
                const NextName = Name[NextNameIndex];
                if (typeof NextName === "string") {
                    if (Process.name == NextName) {
                        resultList.push({ pid, name });
                    }
                }
                if (NextName instanceof RegExp && NextName.test(name)) {
                    resultList.push({ pid, name });
                }
            }
        }
        return resultList;
    }
    /**
    * 获取该名称 /正则匹配的进程列表 带执行文件路径 慢20ms
    * @param Name
    * @returns
    */
    getDetailsProcessNameList(...Name) {
        let resultList = [];
        let ProcessList = native_1.native.getDetailsProcessList();
        for (let index = 0; index < ProcessList.length; index++) {
            const Process = ProcessList[index];
            const { pid, name, path } = Process;
            for (let NextNameIndex = 0; NextNameIndex < Name.length; NextNameIndex++) {
                const NextName = Name[NextNameIndex];
                if (typeof NextName === "string") {
                    if (Process.name == NextName) {
                        resultList.push({ pid, name, path });
                    }
                }
                if (NextName instanceof RegExp && NextName.test(name)) {
                    resultList.push({ pid, name, path });
                }
            }
        }
        return resultList;
    }
    /**
     * 结束该名称的进程
     * @param Name
     */
    killProcessName(...Name) {
        let _this = this;
        let resultList = [];
        let ProcessList = this.getProcessList();
        for (let index = 0; index < ProcessList.length; index++) {
            const Process = ProcessList[index];
            const { pid, name } = Process;
            for (let NextNameIndex = 0; NextNameIndex < Name.length; NextNameIndex++) {
                const NextName = Name[NextNameIndex];
                if (typeof NextName === "string") {
                    if (Process.name == NextName) {
                        this.killProcess(Process.pid);
                        resultList.push({
                            pid,
                            name,
                            get kill() {
                                return _this.hasProcess(pid);
                            },
                        });
                    }
                }
                if (NextName instanceof RegExp && NextName.test(name)) {
                    this.killProcess(Process.pid);
                    resultList.push({
                        pid,
                        name,
                        get kill() {
                            return _this.hasProcess(pid);
                        },
                    });
                }
            }
        }
        return resultList;
    }
    /**
     * 获取当前的焦点窗口
     * @returns 一个可以操作的伪数字类
     */
    getForegroundWindow() {
        let Handle = native_1.native.getForegroundWindow();
        return Handle ? new this.HWND(Handle) : null;
    }
    /**
     * 获取句柄的主窗口
     * @returns 一个可以操作的伪数字类
     */
    getMainWindow(Handle) {
        let Handles = native_1.native.getMainWindow(this.ref.int(Handle));
        return Handles ? new this.HWND(Handles) : null;
    }
    /**
     * 获取鼠标所在的窗口
     * @returns 一个可以操作的伪数字类
     */
    getPointWindow() {
        let Handle = native_1.native.getPointWindow();
        return Handle ? new this.HWND(Handle) : null;
    }
    /**
     * 获取鼠标所在的窗口的主窗口
     * @returns 一个可以操作的伪数字类
     */
    getPointWindowMain() {
        let Handle = native_1.native.getPointWindowMain();
        return Handle ? new this.HWND(Handle) : null;
    }
    /**
     * 获取进程的句柄
     * @param ProcessID
     * @returns
     */
    getProcessHandle(ProcessID) {
        let Handles = native_1.native.getProcessHandle(this.ref.int(ProcessID));
        return Handles ? new this.HWND(Handles) : null;
    }
    /**
     * 阻止键盘和鼠标输入事件到达应用程序。
     */
    SetBlockInput(Block) {
        return native_1.native.SetBlockInput(this.ref.bool(Block));
    }
    /**
     * 设置该窗口图标在状态栏可见性 (注意：XP 下激活窗口了会失效(但是有没有一种可能 xp运行不了node和electron))
     * @param Handle 句柄
     * @param Visible 可见性
     * @returns
     */
    SetWindowInTaskbarVisible(Handle, Visible) {
        return native_1.native.SetWindowInTaskbarVisible(this.ref.int(Handle), this.ref.bool(Visible));
    }
    /**
     * 获取句柄对应的进程id
     * @param Handle 句柄
     * @returns
     */
    getHandleProcessID(Handle) {
        return native_1.native.getHandleProcessID(this.ref.int(Handle));
    }
    /** 获取窗口位置大小
     *  - 高，宽，坐标大于一万以上都是不可见的
     * **/
    getWindowRect(Handle) {
        return native_1.native.getWindowRect(this.ref.int(Handle));
    }
    /**
     * 判断窗口是否禁用响应事件(鼠标键盘点击)
     * @param Handle
     * @returns
     */
    isEnabled(Handle) {
        return native_1.native.isEnabled(this.ref.int(Handle));
    }
    /**
     * 判断句柄是否有效
     * @param Handle
     * @returns
     */
    isHandle(Handle) {
        return native_1.native.isHandle(this.ref.int(Handle));
    }
    /**
     * 判断此句柄是否是正在活动中的窗口
     * @param Handle
     * @returns
     */
    isHandleWindowVisible(Handle) {
        return native_1.native.isHandleWindowVisible(this.ref.int(Handle));
    }
    /**
     * 关闭此句柄对应的窗口
     * @param Handle
     * @returns
     */
    lookHandleCloseWindow(Handle) {
        return native_1.native.lookHandleCloseWindow(this.ref.int(Handle));
    }
    /**
     * 获取此句柄的标题
     * @param Handle
     * @returns
     */
    lookHandleGetTitle(Handle) {
        return native_1.native.lookHandleGetTitle(this.ref.int(Handle));
    }
    /**
     * 设置此句柄的标题
     * @param Handle
     * @param title
     * @returns
     */
    lookHandleSetTitle(Handle, title) {
        return native_1.native.lookHandleSetTitle(this.ref.int(Handle), this.ref.string(title));
    }
    /**
     * 通过句柄设置窗口显示状态  https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-showwindow
     * @param Handle 窗口句柄
     * @param nCmdShow 操作内容
     *  - "SW_HIDE" ： 0 隐藏窗口并激活另一个窗口。
     *  - "SW_SHOWNORMAL" ： 1 激活并显示一个窗口。如果窗口被最小化或最大化，系统会将其恢复到原来的大小和位置。应用程序应在第一次显示窗口时指定此标志
     *  - "SW_SHOWMINIMIZED" ：2 激活窗口并将其显示为最小化窗口
     *  - "SW_SHOWMAXIMIZED" | "SW_MAXIMIZE" ： 3 激活窗口并将其显示为最大化窗口
     *  - "SW_SHOWNOACTIVATE" ： 4 以最近的大小和位置显示窗口。这个值类似于SW_SHOWNORMAL，除了窗口没有被激活
     *  - "SW_SHOW" ：5  激活窗口并以其当前大小和位置显示它
     *  - "SW_MINIMIZE" ：6 最小化指定窗口并激活 Z 顺序中的下一个顶级窗口
     *  - "SW_SHOWMINNOACTIVE" ： 7 将窗口显示为最小化窗口。这个值类似于SW_SHOWMINIMIZED，除了窗口没有被激活
     *  - "SW_SHOWNA" ： 8 以当前大小和位置显示窗口。这个值类似于SW_SHOW，除了窗口没有被激活
     *  - "SW_RESTORE" ： 9 激活并显示窗口。如果窗口被最小化或最大化，系统会将其恢复到原来的大小和位置。应用程序在恢复最小化窗口时应指定此标志
     *  - "SW_SHOWDEFAULT" ： 10 据启动应用程序的程序传递给CreateProcess函数的STARTUPINFO结构中指定的SW_值设置显示状态。
     *  - "SW_FORCEMINIMIZE" ： 11 最小化一个窗口，即使拥有该窗口的线程没有响应。只有在最小化来自不同线程的窗口时才应使用此标志
     * @returns
     */
    lookHandleShowWindow(Handle, SetShowType) {
        return native_1.native.lookHandleShowWindow(this.ref.int(Handle), this.ref.int(typeof SetShowType == "number" ? this.ref.int(SetShowType) : 5));
    }
    /**
     * 设置窗口不透明度 0-255
     * @param Handle
     * @param Transparent 0-255
     * @returns
     */
    setHandleTransparent(Handle, Transparent) {
        return native_1.native.setHandleTransparent(this.ref.int(Handle), this.ref.int(Transparent || 255));
    }
    /**
     * 设置窗口是否支持响应事件(鼠标键盘点击)
     * @param Handle
     * @param Enabled
     * @returns
     */
    setWindowEnabled(Handle, Enabled) {
        return native_1.native.setWindowEnabled(this.ref.int(Handle), this.ref.bool(Enabled));
    }
    /**
     * 设置窗口焦点
     * @param Handle
     * @returns
     */
    setWindowFocus(Handle) {
        return native_1.native.setWindowFocus(this.ref.int(Handle));
    }
    /**
     * 设置窗口顶设
     * @param Handle
     * @returns
     */
    setWindowTop(Handle) {
        return native_1.native.setWindowTop(this.ref.int(Handle));
    }
    /**
     * 刷新该窗口
     * @param Handle
     * @returns
     */
    updateWindow(Handle) {
        return native_1.native.updateWindow(this.ref.int(Handle));
    }
    /**
     * 窗口抖动
     * @param Handle
     * @returns
     */
    windowJitter(Handle) {
        return native_1.native.windowJitter(this.ref.int(Handle));
    }
    /**
     * 判断窗口是否被顶设
     * @param Handle
     * @returns
     */
    hasWindowTop(Handle) {
        return native_1.native.hasWindowTop(this.ref.int(Handle));
    }
    /**
     * 关闭该句柄窗口(可关闭托盘)(发送关闭消息)
     */
    closedHandle(Handle) {
        return native_1.native.closedHandle(this.ref.int(Handle));
    }
    /**
     * 获取所有HidUsb设备（仅限HID设备)
     * @returns HidUsb设备数组
     */
    getHidUsbList() {
        return native_1.native.getHidUsbList();
    }
    /**
     * 获取鼠标所在位置
     * @returns 鼠标所在位置
     */
    getMetrics() {
        return native_1.native.getMetrics();
    }
    /**
     * 获取鼠标之前64个位置
     * @returns 之前64个位置
     */
    getMouseMovePoints() {
        return native_1.native.getMouseMovePoints();
    }
    /**
     * 获取屏幕大小
     */
    getDeviceCaps() {
        return native_1.native.getDeviceCaps();
    }
    /**禁用/启用系统键盘鼠标钩子
      * @param HOOK 是否启用系统键盘鼠标钩子
      !注意该功能很危险 主要用于自动化防止误操作 用户锁屏  禁止用于非法用途
      *手动解锁方式 Ctrl+Alt+Del   => esc
      !请注意 你需要确保你的解锁代码  运行没有任何错误或者有定时解锁
      否则有可能导致用户无法正常使用
      **/
    SetSystemHOOK(HOOK) {
        return native_1.native.SetSystemHOOK(this.ref.bool(HOOK));
    }
    /**
     * 获取四大按钮(`alt`  `ctrl`  `win`  `shift` )是否按下
     * @returns
     */
    getBasicKeys() {
        return native_1.native.getBasicKeys();
    }
    /**
     * 获取剪贴板文本
     * @returns 剪贴板文本
     */
    getClipboardText() {
        return native_1.native.getClipboardText();
    }
    /**
     * 设置剪贴板文本
     * @param text 文本
     * @returns
     */
    setClipboardText(text) {
        return native_1.native.setClipboardText(this.ref.string(text));
    }
    /**
     * 清空剪贴版
     * @returns 处理结果
     */
    clearClipboard() {
        return native_1.native.clearClipboard();
    }
    /** 获取详细进程列表（慢20ms）**/
    getDetailsProcessList() {
        return native_1.native.getDetailsProcessList();
    }
    /** 获取进程列表**/
    getProcessList() {
        return native_1.native.getProcessList();
    }
    /**获取活动窗口的进程id */
    getForegroundWindowProcessID() {
        return native_1.native.getForegroundWindowProcessID();
    }
    /**获取鼠标所在窗口的进程名 */
    getPointWindowName() {
        return native_1.native.getPointWindowName();
    }
    /**获取鼠标所在窗口的进程id */
    getPointWindowProcessId() {
        return native_1.native.getPointWindowProcessId();
    }
    /**
     * 获取进程名
     * @param ProcessID 进程id
     * @returns
     */
    getProcessName(ProcessID) {
        return native_1.native.getProcessName(this.ref.int(ProcessID));
    }
    /**
     * 获取进程可执行文件位置
     * @param ProcessName 进程名
     * @returns 进程id
     */
    getProcessidFilePath(ProcessID) {
        return native_1.native.getProcessidFilePath(this.ref.int(ProcessID));
    }
    /**
     * 获取快捷方式的信息
     * @param LnkPath 快捷方式路径
     * @returns
     */
    getShortcutLink(LnkPath) {
        return native_1.native.getShortcutLink(this.ref.string(LnkPath));
    }
    /**系统空闲时间 */
    getSystemIdleTime() {
        return native_1.native.getSystemIdleTime();
    }
    /**
     * 设置系统右键菜单 例如win自带的系统菜单就很丑还不能禁用  使用这个禁用
     * @param Handle 句柄
     * @param boolean 是否禁用
     * @returns
     */
    getSystemMenu(Handle, boolean) {
        return native_1.native.getSystemMenu(this.ref.int(Handle), this.ref.bool(boolean));
    }
    /**获取托盘图标列表 */
    getTrayList() {
        return native_1.native.getTrayList();
    }
    /**判断该按键是否被按下  https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-getkeystate **/
    hasKeyActivate(KeysEvent) {
        return native_1.native.hasKeyActivate;
    }
    /**
     * 判断进程id 是否存在
     * @param ProcessID 进程id
     * @returns
     */
    hasProcess(ProcessID) {
        return native_1.native.isProcess(this.ref.int(ProcessID));
    }
    /**
     * 当前程序是否拥有管理员权限
     * @returns
     */
    isAdmin() {
        return native_1.native.isAdmin();
    }
    /**
     * 判断进程id 是否存在
     * @param ProcessID 进程id
     * @returns
     */
    isProcess(ProcessID) {
        return native_1.native.isProcess(this.ref.int(ProcessID));
    }
    /**判断当前系统是否是64位 */
    isSystemX64() {
        return native_1.native.isSystemX64();
    }
    /**
     * 结束该进程
     * @param ProcessID
     * @returns
     */
    killProcess(ProcessID) {
        if (typeof ProcessID == "string") {
            return this.killProcessName(ProcessID);
        }
        return native_1.native.killProcess(this.ref.int(ProcessID));
    }
    /**
     * 左键点击
     * @param ms 延迟
     * @returns
     */
    leftClick(ms) {
        return native_1.native.leftClick(ms);
    }
    /**
     * 消息窗口(调用 win-api)
     * @param message 消息内容
     * @param title 标题
     * @param UINT_String 显示窗口类型 https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-messageboxa
     * @description 衍生api(已预设): `confirm`  `alert` `MessageError` `MessageStop`
     * @returns
     */
    messageBox(message, title, UINT_String) {
        return native_1.native.messageBox(this.ref.string(message), this.ref.string(title), this.ref.string(UINT_String));
    }
    /**自定义鼠标事件 https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-mouse_event **/
    mouse(mouse_event, ms) {
        if (typeof mouse_event == "number") {
            mouse_event = this.ref.int(mouse_event);
        }
        else {
            mouse_event = this.ref.string(mouse_event);
        }
        return native_1.native.mouse.apply(undefined, ms ? [mouse_event] : [mouse_event, ms]);
    }
    /**
     * 在资源管理器中显示并选中该文件
     * @param Path 路径
     * @returns
     */
    openExternal(Path) {
        return native_1.native.openExternal(Path);
    }
    /**
     * 用默认应用打开该 （文件/文件夹）
     * @param Path 文件路径
     * @returns
     */
    openPath(Path) {
        return native_1.native.openPath(Path);
    }
    /**
     * 用默认浏览器打开这条url
     * @param URL url
     * @returns
     */
    openURL(URL) {
        return native_1.native.openURL(this.ref.string(URL));
    }
    /**
     * 电源控制
     */
    get powerControl() {
        function _PowerControl(Set) {
            native_1.native.powerControl(Set);
        }
        /**关机 */
        _PowerControl[1001] = () => { native_1.native.powerControl(1001); };
        /**重启 */
        _PowerControl[1002] = () => { native_1.native.powerControl(1002); };
        /**注销 */
        _PowerControl[1003] = () => { native_1.native.powerControl(1003); };
        /**锁定 */
        _PowerControl[1005] = () => { native_1.native.powerControl(1005); };
        /**关机 */
        _PowerControl.shutDown = () => { native_1.native.powerControl(1001); };
        /**重启 */
        _PowerControl.restart = () => { native_1.native.powerControl(1002); };
        /**注销 */
        _PowerControl.cancellation = () => { native_1.native.powerControl(1003); };
        /**锁定 */
        _PowerControl.lock = () => { native_1.native.powerControl(1005); };
        return _PowerControl;
    }
    /**
     * 右键点击
     * @param ms 延迟
     * @returns
     */
    rightClick(ms) {
        return native_1.native.rightClick(ms);
    }
    /**
     * 设置鼠标位置
     * @param x 左边开始的像素数坐标
     * @param y 上方到下方的像素数坐标
     * @returns
     */
    setCursorPos(x, y) {
        return native_1.native.setCursorPos(this.ref.int(x), this.ref.int(y));
    }
    /**
     * 创建快捷方式
     * @param LnkPath 快捷方式位置
     * @param FilePath 关联的文件
     * @param work_dir 工作目录
     * @param desc 简介
     * @param args 启动命令
     * @param iShowCmd 显示方式
     * @param icon 使用的图标如dll,exe,icon
     * @param iconIndex 图标索引
     */
    setShortcutLink(...args) {
        if (args.length < 2)
            throw new Error("not LnkPath and FilePath arguments");
        // LnkPath
        args[0] = this.ref.string(args[0] || "");
        // FilePath
        args[1] = this.ref.string(args[1] || "");
        // work_dir
        args[2] = this.ref.string(args[2] || "");
        // desc
        args[3] = this.ref.string(args[3] || "");
        // args
        if (Array.isArray(args[4])) {
            args[4] = args[4].map(itme => `"${itme ? itme === null || itme === void 0 ? void 0 : itme.replace(/\"/g, "\\\"") : ""}"`).join(" ");
        }
        args[4] = this.ref.string(args[4] || "");
        // iShowCmd
        if (args.length > 5) {
            args[5] = this.ref.int(args[5] || 0);
        }
        // icon
        if (args.length > 6) {
            args[6] = this.ref.string(args[6] || "");
        }
        // iconIndex
        if (args.length > 7) {
            args[7] = this.ref.int(args[7] || 0);
        }
        return native_1.native.setShortcutLink(...args);
    }
    /**
     * 创建文件软链接
     * @param LinkPath 创建的位置
     * @param sourcePath 原文件链接
     * @returns
     */
    createSymlink(LinkPath, sourcePath) {
        return native_1.native.createSymlink(this.ref.string(LinkPath), this.ref.string(sourcePath));
    }
    /**
     * 创建文件夹软链接
     * @param LinkPath 创建的位置
     * @param sourcePath 原文件链接
     * @returns
     */
    createDirSymlink(LinkPath, sourcePath) {
        return native_1.native.createSymlink(this.ref.string(LinkPath), this.ref.string(sourcePath));
    }
    /**
     * 创建文件硬链接
     * @param LinkPath 创建的位置
     * @param sourcePath 原文件链接
     * @returns
     */
    createHardLink(LinkPath, sourcePath) {
        return native_1.native.createSymlink(this.ref.string(LinkPath), this.ref.string(sourcePath));
    }
    /**打开显示器 */
    showMonitors(show) {
        if (typeof show == "boolean") {
            return show ? native_1.native.showMonitors() : native_1.native.shutMonitors();
        }
        return native_1.native.showMonitors();
    }
    /**关闭显示器 */
    shutMonitors(show) {
        if (typeof show == "boolean") {
            return show ? native_1.native.showMonitors() : native_1.native.shutMonitors();
        }
        return native_1.native.shutMonitors();
    }
    /**
     * `Sync` 同步阻塞(进程)
     * @param awaitTime
     * @returns
     */
    sleep(awaitTime) {
        return native_1.native.sleep(this.ref.int(awaitTime));
    }
    /**
     * `async` 异步阻塞(进程)
     * @param awaitTime
     * @returns
     */
    async Sleep(awaitTime, Sync) {
        if (Sync) {
            return this.sleep(this.ref.int(awaitTime));
        }
        return new Promise((resolve) => setTimeout(resolve, this.ref.int(awaitTime)));
    }
    /**
     * 系统启动到现在的时间(毫秒)
     * @returns
     */
    systemStartTime() {
        return native_1.native.systemStartTime();
    }
    /**
     * 同 C++/C 的system
     * @returns 程序退出代码
     */
    system(str) {
        return native_1.native.system(this.ref.string(str));
    }
    /**
     * 空闲的随机端口号
     * @returns
     */
    freePort() {
        return new Promise((resolve, reject) => {
            let sock = net.createServer(function () { });
            sock.listen(0, () => {
                var _a;
                // @ts-expect-error
                resolve(Number((_a = sock === null || sock === void 0 ? void 0 : sock.address()) === null || _a === void 0 ? void 0 : _a.port));
                sock.close();
            });
        });
    }
    /**
     * 获取剪贴板中的文件列表
     * @returns
     */
    getClipboardFilePaths(at) {
        let paths = native_1.native.getClipboardFilePaths();
        if (typeof at === 'number') {
            if (at < 0) {
                return paths[paths.length + at];
            }
            return paths[at];
        }
        return paths;
    }
    /**
     * 向剪贴板写入文件列表
     * @param FilePaths
     */
    setClipboardFilePaths(...FilePaths) {
        let filePaths = [];
        for (let index = 0; index < FilePaths.length; index++) {
            const FilePath = FilePaths[index];
            if (typeof FilePath !== "string") {
                for (let indexc = 0; indexc < FilePaths.length; indexc++) {
                    filePaths.push(this.ref.string(FilePaths[indexc]));
                }
            }
            else {
                filePaths.push(this.ref.string(FilePath));
            }
        }
        return native_1.native.setClipboardFilePaths(filePaths);
    }
    /**
     * 获取所有usb驱动器(不包含HUD)
     * @returns
     */
    getUsbDevsInfo() {
        return native_1.native.getUsbDevsInfo();
    }
    /**
     * 枚举句柄的子窗口
     * @param Handle 句柄
     * @returns
     */
    enumChildWindows(Handle) {
        return native_1.native.enumChildWindows(this.ref.int(Handle));
    }
    /**
     * 隐藏当前控制台窗口(node)
     */
    hideConsole() {
        var _a;
        if (!__classPrivateFieldGet(this, _hmc_win32_thenConsole, "f")) {
            __classPrivateFieldSet(this, _hmc_win32_thenConsole, this.getProcessHandle(process.pid), "f");
        }
        if (!__classPrivateFieldGet(this, _hmc_win32_thenConsole, "f"))
            return false;
        return ((_a = __classPrivateFieldGet(this, _hmc_win32_thenConsole, "f")) === null || _a === void 0 ? void 0 : _a.hide()) || false;
    }
    /**
     * 显示当前控制台窗口(node)
     */
    showConsole() {
        var _a;
        if (!__classPrivateFieldGet(this, _hmc_win32_thenConsole, "f")) {
            __classPrivateFieldSet(this, _hmc_win32_thenConsole, this.getProcessHandle(process.pid), "f");
        }
        if (!__classPrivateFieldGet(this, _hmc_win32_thenConsole, "f"))
            return false;
        return ((_a = __classPrivateFieldGet(this, _hmc_win32_thenConsole, "f")) === null || _a === void 0 ? void 0 : _a.show()) || false;
    }
    /**
     * 获取当前控制台窗口的句柄(node)
     * @returns
     */
    getConsoleHandle() {
        if (!__classPrivateFieldGet(this, _hmc_win32_thenConsole, "f")) {
            __classPrivateFieldSet(this, _hmc_win32_thenConsole, this.getProcessHandle(process.pid), "f");
        }
        return __classPrivateFieldGet(this, _hmc_win32_thenConsole, "f");
    }
    /**
    * 将文件/文件夹  移除到系统回收站中
    * @param Path 处理的路径(\n结尾)
    * @param Recycle 是否保留撤销权(回收站)
    * @param isShow 是否显示确认窗口
    * @returns 返回操作状态 请参考：
    * @link https://learn.microsoft.com/zh-CN/windows/win32/api/shellapi/nf-shellapi-shfileoperationa
    * @default 默认配置
    * * Recycle true
    * * isShow false
    */
    deleteFile(Path, Recycle, isShow) {
        return native_1.native.deleteFile(this.ref.path(Path), typeof Recycle == "boolean" ? this.ref.bool(Recycle) : true, typeof isShow == "boolean" ? this.ref.bool(isShow) : false);
    }
    /**
    * 将文件/文件夹  移除到系统回收站中
    * @param Path 处理的路径(\n结尾)
    * @param Recycle 是否保留撤销权(回收站)
    * @param isShow 是否显示确认窗口
    * @returns 返回操作状态 请参考：
    * @link https://learn.microsoft.com/zh-CN/windows/win32/api/shellapi/nf-shellapi-shfileoperationa
    * @default 默认配置
    * * Recycle true
    * * isShow false
    */
    get trash() {
        return this.deleteFile;
    }
    /**
     * 获取当前剪贴板内容的id(如果被重新写入了该id会变动)
     * @returns
     */
    getClipboardSequenceNumber() {
        return native_1.native.getClipboardSequenceNumber();
    }
    /**
     * 当剪贴板内容变更后发生回调
     * @param CallBack 回调函数
     * @param nextAwaitMs 每次判断内容变化用时 默认 `150` ms
     * @returns
     */
    watchClipboard(CallBack, nextAwaitMs) {
        let _this = this;
        let NextAwaitMs = nextAwaitMs || 150;
        let Next = true;
        let oidClipboardSequenceNumber = this.getClipboardSequenceNumber();
        (async function () {
            while (Next) {
                await _this.Sleep(NextAwaitMs);
                let clipboardSequenceNumber = _this.getClipboardSequenceNumber();
                if (oidClipboardSequenceNumber !== clipboardSequenceNumber) {
                    if (CallBack)
                        CallBack();
                }
                oidClipboardSequenceNumber = clipboardSequenceNumber;
            }
        })();
        return {
            /**
             * 取消继续监听
             */
            unwatcher() {
                Next = false;
            },
            /**
             * 每次判断内容变化用时 默认 `150` ms
             * @param nextAwaitMs
             */
            setNextAwaitMs(nextAwaitMs) {
                NextAwaitMs = _this.ref.int(nextAwaitMs) || 150;
            }
        };
    }
    /**
      * 当驱动器添加或者移除后发生回调
      * @param CallBack 回调函数
      * @param nextAwaitMs 每次判断内容变化用时 默认 `800` ms
      * @param watchType 监听的设备类型 默认 `["HUB","drive"]`
      * @returns
      */
    watchUSB(CallBack, nextAwaitMs, watchType) {
        let _this = this;
        let NextAwaitMs = nextAwaitMs || 800;
        let Next = true;
        let OID_ID_LIST = new Set();
        let start = true;
        if (typeof watchType == "string")
            watchType = [watchType];
        (async function () {
            while (Next) {
                await _this.Sleep(NextAwaitMs);
                let GET_ID_List = new Set(watchType ? [
                    ...(watchType.includes("hub") ? native_1.native.getHidUsbIdList() : []),
                    ...(watchType.includes("drive") ? native_1.native.getUsbDevsInfo() : []),
                ] : [...native_1.native.getHidUsbIdList(), ...native_1.native.getUsbDevsInfo()]);
                if (start) {
                    for (const NEW_ID of GET_ID_List) {
                        OID_ID_LIST.add(NEW_ID);
                        CallBack && CallBack("start", NEW_ID);
                    }
                    start = false;
                }
                let GET_ID_List_NEW = [...GET_ID_List];
                for (const OID_ID of OID_ID_LIST) {
                    if (!GET_ID_List.has(OID_ID)) {
                        CallBack && CallBack("remove", OID_ID);
                    }
                }
                for (const NEW_ID of GET_ID_List) {
                    if (!OID_ID_LIST.has(NEW_ID)) {
                        CallBack && CallBack("add", NEW_ID);
                    }
                }
                OID_ID_LIST.clear();
                for (let index = 0; index < GET_ID_List_NEW.length; index++) {
                    const GET_ID = GET_ID_List_NEW[index];
                    OID_ID_LIST.add(GET_ID);
                }
            }
        })();
        return {
            get idList() {
                return OID_ID_LIST;
            },
            /**
             * 取消继续监听
             */
            unwatcher() {
                Next = false;
            },
            /**
             * 每次判断内容变化用时 默认 `800` ms
             * @param nextAwaitMs
             */
            setNextAwaitMs(nextAwaitMs) {
                NextAwaitMs = _this.ref.int(nextAwaitMs) || 800;
            }
        };
    }
    /**
     * 获取所有屏幕
     * @returns
     */
    getDeviceCapsAll() {
        return native_1.native.getDeviceCapsAll();
    }
    /**
     * 判断句柄的窗口是否在所有窗口的范围中(无论他是否被其他窗口挡住)
     * @param Handle
     */
    isInMonitorWindow(Handle) {
        return native_1.native.isInMonitorWindow(this.ref.int(Handle));
    }
    /**
     * 判断句柄的窗口是否在鼠标所在的窗口
     * @param Handle
     */
    isMouseMonitorWindow(Handle) {
        return native_1.native.isMouseMonitorWindow(this.ref.int(Handle));
    }
    /**
     * 获取鼠标所在的屏幕信息
     */
    getCurrentMonitorRect() {
        return native_1.native.getCurrentMonitorRect();
    }
    /**
     * 当前电脑存在几个屏幕
     */
    getSystemMetricsLen() {
        return native_1.native.getSystemMetricsLen();
    }
}
_hmc_win32_thenConsole = new WeakMap(), _hmc_win32_instances = new WeakSet(), _hmc_win32_window_get = function _hmc_win32_window_get() {
    return (() => {
        return {
            isInMonitor: this.isInMonitorWindow,
            isMouseMonitor: this.isMouseMonitorWindow,
            HWND: this.HWND,
            setMode: this.setWindowMode,
            getAllWindows: this.getAllWindows,
            getAllHandle: this.getAllWindowsHandle,
            watchPoint: this.WatchWindowPoint,
            watchtFocus: this.WatchWindowForeground,
            getFocus: this.getForegroundWindow,
            getMain: this.getMainWindow,
            getPoint: this.getPointWindow,
            getProcessHandle: this.getProcessHandle,
            getPointMain: this.getPointWindowMain,
            setTaskbarVisible: this.SetWindowInTaskbarVisible,
            getProcessID: this.getHandleProcessID,
            getRect: this.getWindowRect,
            isEnabled: this.isEnabled,
            isHandle: this.isHandle,
            hasHandle: this.isHandle,
            isVisible: this.isHandleWindowVisible,
            close: this.lookHandleCloseWindow,
            getTitle: this.lookHandleGetTitle,
            setTitle: this.lookHandleSetTitle,
            setShowWindow: this.lookHandleShowWindow,
            setTransparent: this.setHandleTransparent,
            setEnabled: this.setWindowEnabled,
            setFocus: this.setWindowFocus,
            setTop: this.setWindowTop,
            update: this.updateWindow,
            jitter: this.windowJitter,
            hasTop: this.hasWindowTop,
            closed: this.closedHandle,
            getFocusProcessID: this.getForegroundWindowProcessID,
            getPointName: this.getPointWindowName,
            getPointProcessId: this.getPointWindowProcessId,
            enumChild: this.enumChildWindows,
            console: {
                hide: this.hideConsole,
                show: this.showConsole,
                get: this.getConsoleHandle,
                blockInput: this.SetBlockInput,
            }
        };
    })();
}, _hmc_win32_watch_get = function _hmc_win32_watch_get() {
    return (() => {
        return {
            clipboard: this.watchClipboard,
            usb: this.watchUSB,
            windowFocus: this.WatchWindowForeground,
            windowPoint: this.WatchWindowPoint,
            process: this.processWatchdog
        };
    })();
}, _hmc_win32_shell_get = function _hmc_win32_shell_get() {
    return (() => {
        return {
            trash: this.deleteFile,
            delete: this.deleteFile,
            openApp: this.openApp,
            getShortcutLink: this.getShortcutLink,
            setShortcutLink: this.setShortcutLink,
            freePort: this.freePort,
            createSymlink: this.createSymlink,
            createDirSymlink: this.createDirSymlink,
            createHardLink: this.createHardLink,
        };
    })();
}, _hmc_win32_usb_get = function _hmc_win32_usb_get() {
    return (() => {
        return {
            getHub: this.getHidUsbList,
            getDevsInfo: this.getUsbDevsInfo,
            watch: this.watchUSB,
        };
    })();
}, _hmc_win32_clipboard_get = function _hmc_win32_clipboard_get() {
    return (() => {
        return {
            clear: this.clearClipboard,
            readText: this.getClipboardText,
            readFilePaths: this.getClipboardFilePaths,
            writeText: this.setClipboardText,
            writeFilePaths: this.setClipboardFilePaths,
            sequence: this.getClipboardSequenceNumber,
            watch: this.watchClipboard,
        };
    })();
}, _hmc_win32_process_get = function _hmc_win32_process_get() {
    return (() => {
        return {
            watch: this.processWatchdog,
            kill: this.killProcess,
            killMatch: this.killProcessName,
            getList: this.getProcessList,
            getHandle: this.getProcessHandle,
            getName: this.getProcessName,
            getPath: this.getProcessidFilePath,
            getFocus: this.getForegroundWindowProcessID,
            has: this.hasProcess,
            match: this.getProcessNameList,
            matchDetails: this.getDetailsProcessNameList,
            getDetailsList: this.getDetailsProcessList,
        };
    })();
}, _hmc_win32_auto_get = function _hmc_win32_auto_get() {
    return (() => {
        return {};
    })();
};
/**
 * 获取窗口的标题
 * @returns
 */
function getDefaultTitele() {
    try {
        // @ts-expect-error
        return exports.window.document.title;
    }
    catch (error) {
        return (native_1.native.lookHandleGetTitle(native_1.native.getProcessHandle(process.pid) || 0) ||
            native_1.native.getProcessName(process.pid) ||
            process.title);
    }
}
exports.hmc = new hmc_win32();
exports.default = exports.hmc;
module.exports = exports.hmc;
