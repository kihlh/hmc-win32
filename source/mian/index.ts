import path = require("path");
import { Native, chcpList } from "./native";
const native: Native = require("./HMC.node");
import { spawn, execFileSync, SpawnOptionsWithoutStdio, ChildProcessWithoutNullStreams, execFile } from "child_process";
import net = require("net");
let chcpList: { [key: string | number]: SystemDecoder } = {
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
  let result = { code: 437 as SystemDecoderKey, chcp: chcpList[437] as SystemDecoder };
  return new Promise<{
    chcp: SystemDecoder,
    code: SystemDecoderKey
  }>(resolve => {
    execFile("chcp", function (err, data) {
      if (!data || err) return resolve(result);
      let sy_Chcp = data.match(/^.+?(\d+)[\r\n]+$/)
      if (sy_Chcp && chcpList[Number(sy_Chcp[1])]) {
        result.chcp = chcpList[Number(sy_Chcp[1])];
        result.code = Number(sy_Chcp[1]) as SystemDecoderKey;
        resolve(result);
      }
      resolve(result);
    });
  });
}
/**
 * C++中的坐标
 */
export type cPOINT = {
  x: number;
  y: number;
}

/**
 * C++ 中的 位置定义
 */
export type cRECT = {
  left: number;
  top: number;
  right: number;
  bottom: number;
}

/**
 * C++中的位置定义
 */
export interface cRect {
  x: number;
  y: number;
  height: number;
  width: number;
}
function iscRECT(cRECT: any): cRECT is cRECT {
  return typeof cRECT.left == "number" && typeof cRECT.right == "number" && typeof cRECT.bottom == "number" && typeof cRECT.top == "number"
}
function iscPOINT(cPOINT: any): cPOINT is cPOINT {
  return typeof cPOINT.x == "number" && typeof cPOINT.y == "number" && typeof cPOINT.height == "undefined" && typeof cPOINT.width == "undefined"
}
/**
 * 矩形是否在矩形范围中
 * @param inRect 
 * @param mian 
 * @returns 
 */
export function RectInRect(mian: cRect | cRECT, InRect: cRect | cRECT | cPOINT) {

  if (iscRECT(mian)) {
    mian = RECT2Rect(mian);
  }
  if (iscRECT(InRect)) {
    InRect = RECT2Rect(InRect);
  }
  if (iscPOINT(InRect)) {
    return pointInRect(InRect, mian);
  }

  let inRect: cRect = InRect;
  let isInRet = true;
  // 得出对比传入的边界
  let in_x = inRect.x;
  let in_y = inRect.y;
  let in_xw = inRect.x + inRect.width;
  let in_hy = inRect.y + inRect.height;
  if (!inRect.x) in_x = 1;
  if (!inRect.y) in_y = 1;

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
/**
 * 点是否在矩形范围中
 * @param pt 
 * @param rect 
 * @returns 
 */
export function pointInRect(pt: cPOINT, rect: cRect) {
  if ((pt.x > rect.x) && (pt.y > rect.y) && (pt.x < (rect.x + rect.width)) && (pt.y < (rect.y + rect.height))) {
    return true;
  }
  return false;
}

export function RECT2Rect(inputRect: cRECT): cRect {
  return {
    height: inputRect.top - inputRect.bottom,
    width: inputRect.right - inputRect.left,
    x: inputRect.left,
    y: inputRect.top
  } as Rect;
}


/**
 * 句柄 可以视为是一个数字也可以视为是一个功能 {0}
 * 继承了 Number 的构建类
 */
export class HWND extends Number {
  constructor(hWnd: number) {
    super(hWnd);
    this.HWND = hWnd;
  }

  HWND: number;
  /**
   * 强制关闭窗口不发送被关闭的消息给窗口
   */
  closed() {
    if (!this.exists) return false;
    return native.closedHandle(this.HWND);
  }
  /**
   * 向窗口发送关闭的消息
   */
  close() {
    if (!this.exists) return false;
    return native.lookHandleCloseWindow(this.HWND);
  }
  /**
   * 窗口位置
   */
  get rect(): Rect | null {
    if (!this.exists) return null;
    return native.getWindowRect(this.HWND);
  }
  /**
   * 窗口名称
   */
  get title(): string {
    return native.lookHandleGetTitle(this.HWND) || "";
  }
  /**
   * 设置窗口的标题
   * @param Title 标题
   * @returns
   */
  setTitle(Title: string) {
    if (typeof Title !== "string" || !this.exists) {
      return false;
    }
    return native.lookHandleSetTitle(this.HWND, Title);
  }
  /**句柄是否有效 */
  get exists() {
    if (!this.HWND) return false;
    return native.isHandle(this.HWND);
  }
  /**句柄是否有效 */
  get isHandle() {
    return this.exists;
  }
  /**
   * 当前句柄的pid
   */
  get pid() {
    if (!this.exists) return 0;
    return native.getHandleProcessID(this.HWND);
  }
  /**
   * 获取主窗口的pid
   */
  get MianPid(): ProcessID | null {
    if (!this.exists) return 0;
    return native.getHandleProcessID(this.MainHandle);
  }
  get MainHandle(): number {
    return native.getMainWindow(this.HWND) || 0;
  }
  /**
   * 判断窗口是否可见
   * @returns
   */
  isVisible() {
    if (!this.HWND) return false;
    return native.isHandleWindowVisible(this.HWND);
  }
  /**
   * 结束该进程
   * @returns
   */
  kill() {
    let processid = this.MianPid;
    if (!processid) return false;
    return native.killProcess(processid);
  }
  /**
   * 隐藏窗口
   * @returns
   */
  hide() {
    if (!this.HWND) return false;
    return native.lookHandleShowWindow(this.HWND, 0);
  }
  /**
   * 显示窗口
   * @returns
   */
  show() {
    if (!this.HWND) return false;

    return native.lookHandleShowWindow(this.HWND, 5);
  }
  /**
   * 窗口最小化
   * @returns
   */
  setMin() {
    if (!this.HWND) return false;

    return native.lookHandleShowWindow(this.HWND, 7);
  }
  /**
   * 窗口最大化
   * @returns
   */
  setMax() {
    if (!this.HWND) return false;

    return native.lookHandleShowWindow(this.HWND, 3);
  }
  /**
   * 恢复最近的状态
   * @returns
   */
  setRestore() {
    if (!this.HWND) return false;

    return native.lookHandleShowWindow(this.HWND, 9);
  }
  /**
   * 聚焦该窗口
   * @returns
   */
  setFocus() {
    if (!this.HWND) return false;

    return native.setWindowFocus(this.HWND);
  }
  /**
   * 禁用窗口
   * @param enabled
   * @returns
   */
  setEnabled(enabled: boolean) {
    if (!this.HWND) return false;

    return native.setWindowEnabled(this.HWND, enabled);
  }
  /**
   * 是否被禁用
   * @returns
   */
  isEnabled() {
    if (!this.HWND) return false;

    return native.isEnabled(this.HWND);
  }
  /**
   * 窗口抖动
   * @returns
   */
  setJitter() {
    if (!this.HWND) return false;
    return native.windowJitter(this.HWND);
  }
  /**
   * 判断窗口是否被顶设
   * @returns
   */
  isTop() {
    if (!this.HWND) return false;

    return native.hasWindowTop(this.HWND);
  }
  /**
   * 设置窗口顶设或者取消
   * @returns
   */
  setTopOrCancel() {
    if (!this.HWND) return false;

    return native.setWindowTop(this.HWND);
  }
  /**
   * 设置窗口不透明度
   * @param opacity 0-100 or 0.0 - 1.0
   */
  setOpacity(opacity: number) {
    if (typeof opacity !== "number" || opacity > 100 || isNaN(opacity))
      throw new Error(
        "fun <setOpacity> arg:<Opacity> is only allowed from 0.0 to 1.0 or  0 to 255"
      );
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
  setTransparent(opacity: number) {
    if (opacity > -1 || opacity < 255) {
      throw new Error(
        "fun <setTransparent> arg:<Opacity> is only allowed from -1 to 255"
      );
    }
    if (!this.HWND) return false;
    return native.setHandleTransparent(this.HWND, opacity as HandleTransparent);
  }
}
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
function analysisDirectPath(Path: string, atkey?: boolean): string[] {
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
function hasHKEY(HKEY: any) {
  if (typeof HKEY !== "string") return false;
  return new RegExp(`^${Object.keys(Hkey).join("|")}$`).exec(HKEY);
}
/**
 * 判断输入的注册表路径是否合法
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 */
function hasregArgs(HKEY: HKEY, Path: string, funName: string) {
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

  get hmc() { return this }
  get default() { return this; }
  /**原生HMC */
  native = native;
  /**一个可以快速操作的句柄类对象 */
  HWND = HWND;
  /**版本号 */
  version: string = native.version;
  /**功能介绍 */
  desc: string = native.desc;
  /**当前二进制适用系统平台 */
  platform: string = native.platform;
  ref = {
    /**
    * 将内容格式化为文本路径
    * @param Str
    * @returns
    */
    path(Str: any) {
      return path.resolve(String(Str || "")).replace(/([\0\n\r]+)?$/, '\0');
    },
    /**
     * 格式化为bool
     * @param bool
     * @returns
     */
    bool(bool: any) {
      return bool ? true : false;
    },
    /**
     * 将内容格式化为文本
     * @param Str
     * @returns
     */
    string(Str: any) {
      return String(Str || "");
    },
    /**
     * 格式化数字为int(强制)
     * @param Num
     * @returns
     */
    int(Num: any): number {
      if (!Num) return 0;
      if (typeof Num == "object" && Num instanceof Number) {
        Num = Num?.valueOf();
      }
      // 取整
      Num = Math.trunc(Num + 0);
      if (typeof Num == "number" && !isNaN(Num)) return Num;
      // true == 1
      if (Num && typeof Num == "boolean") Num = 1;
      // false = 0;
      if (!Num && typeof Num == "boolean") Num = 0;
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
    concatBuff(buffList: Buffer[]): Buffer {
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
   * 设置窗口位置大小
   * @param Handle 句柄
   * @param x (right) 从屏幕右边到所在位置得像素数
   * @param y (top) 从屏幕顶部边到所在位置得像素数
   * @param width 窗口宽度
   * @param height 窗口高度
   * @time 0.0068359375 ms
   * @returns 布尔
   */
  setWindowMode(
    HWND: HWND | number,
    x: number | null | 0 | SetWindowRect,
    y?: number | null | 0,
    width?: number | null | 0,
    height?: number | null | 0
  ): boolean {
    if (!this.ref.int(HWND)) return false;
    if (x && typeof x == "object") {
      let SetWindowRect = x;
      SetWindowRect.y = SetWindowRect.top
        ? SetWindowRect.top
        : SetWindowRect.y || 0;
      SetWindowRect.x = SetWindowRect.right
        ? SetWindowRect.right
        : SetWindowRect.x || 0;
      if (SetWindowRect.x) x = SetWindowRect.x;
      if (SetWindowRect.y) y = SetWindowRect.y;
      if (SetWindowRect.width) width = SetWindowRect.width;
      if (SetWindowRect.height) height = SetWindowRect.height;
    }
    if (!x) x = 0;
    if (!y) x = 0;
    if (!width) width = 0;
    if (!height) height = 0;
    return native.setWindowMode(
      this.ref.int(HWND),
      this.ref.int(x),
      this.ref.int(y),
      this.ref.int(width),
      this.ref.int(height)
    );
  }
  /**
   * 判断注册表中是否有该键值
   * @param HKEY 根路径
   * @param Path 路径
   * @param key 键
   * @time 0.06591796875 ms
   * @returns
   */
  hasRegistrKey(HKEY: HKEY, Path: string, key: string): boolean {
    if (!key) key = "";
    hasregArgs(HKEY, Path, "hasRegistrKey");
    return native.hasRegistrKey(
      HKEY,
      this.ref.string(Path)
        .split(/[\\\/]+/g)
        .join("\\"),
      this.ref.string(key)
    );
  }
  /**
   * 设置键值对内容(64位数字)
   * @param HKEY 根路径
   * @param Path 路径
   * @param key 键
   * @param Qword (64位数字)
   * @returns 
   */
  setRegistrQword(HKEY: HKEY, Path: string, key: string, Qword: bigint | number): boolean {
    if (!key) key = "";
    hasregArgs(HKEY, Path, "hasRegistrKey");
    if (!Qword) Qword = BigInt(0);
    return native.setRegistrQword(HKEY, this.ref.string(Path), this.ref.string(key), BigInt(Qword));
  }
  /**
   * 设置键值对内容(32位数字)
   * @param HKEY 根路径
   * @param Path 路径
   * @param key 键
   * @param Qword (32位数字)
   * @returns 
   */
  setRegistrDword(HKEY: HKEY, Path: string, key: string, Dword: number): boolean {
    if (!key) key = "";
    hasregArgs(HKEY, Path, "hasRegistrKey");
    return native.setRegistrDword(HKEY, this.ref.string(Path), this.ref.string(key), this.ref.int(Dword));
  }
  /**
   * 获取内容(64位数字)
   * @param HKEY 根路径
   * @param Path 路径
   * @param key 键
   * @time 0.06787109375 ms
   * @returns
   */
  getRegistrQword(HKEY: HKEY, Path: string, key: string) {
    if (!key) key = "";
    hasregArgs(HKEY, Path, "getRegistrQword");
    return native.getRegistrQword(
      HKEY,
      this.ref
        .string(Path)
        .split(/[\\\/]+/g)
        .join("\\"),
      this.ref.string(key)
    );
  }
  /**
   * 获取内容(64位数字)
   * @param HKEY 根路径
   * @param Path 路径
   * @param key 键
   * @time 0.06787109375 ms
   * @returns
   */
  getRegistrDword(HKEY: HKEY, Path: string, key: string) {
    if (!key) key = "";
    hasregArgs(HKEY, Path, "getRegistrDword");
    return native.getRegistrDword(
      HKEY,
      this.ref
        .string(Path)
        .split(/[\\\/]+/g)
        .join("\\"),
      this.ref.string(key)
    );
  }
  /**
   * 获取内容(二进制 Buffer)
   * @param HKEY 根路径
   * @param Path 路径
   * @param key 键
   * @time 0.06787109375 ms
   * @returns
   */
  getRegistrBuffValue(HKEY: HKEY, Path: string, key: string) {
    if (!key) key = "";
    hasregArgs(HKEY, Path, "getRegistrBuffValue");
    return native.getRegistrBuffValue(
      HKEY,
      this.ref
        .string(Path)
        .split(/[\\\/]+/g)
        .join("\\"),
      this.ref.string(key)
    );
  }
  /**
   * 枚举键值
   * @param HKEY 根路径
   * @param Path 路径
   * @time 0.06689453125 ms
   * @returns
   */
  enumRegistrKey(HKEY: HKEY, Path: string) {
    hasregArgs(HKEY, Path, "createPathRegistr");
    let enumKeyList: Set<string> = new Set();
    let NatenumKey = native.enumRegistrKey(
      HKEY,
      this.ref
        .string(Path)
        .split(/[\\\/]+/g)
        .join("\\")
    );
    for (let index = 0; index < NatenumKey.length; index++) {
      const key = NatenumKey[index];
      enumKeyList.add(key)
    }
    return [...enumKeyList];
  }
  /**
   * 将当前的路径的注册表值转表
   * @param HKEY
   * @param Path
   */
  listRegistrPath(HKEY: HKEY, Path: string) {
    let enumRegistrKey = this.enumRegistrKey(HKEY, Path);
    enumRegistrKey.unshift("");
    let data: { "": string | Buffer;[key: string]: string | Buffer } = {
      "": "",
    };
    for (let i = 0; i < enumRegistrKey.length; i++) {
      data[enumRegistrKey[i]] = this.getStringRegKey(
        HKEY,
        Path,
        enumRegistrKey[i]
      );
    }
    return data;
  }

  /**
   * 判断该键值是否存在子项
   * @param HKEY 根路径
   * @param Path 路径
   * @param key 键
   */
  isRegistrTreeKey(HKEY: HKEY, Path: string, key?: string) {
    return !!this.enumRegistrKey(HKEY, Path + (!key ? "" : "\\" + key)).length
  }
  /**
   * 获取内容(文本)
   * @param HKEY 根路径
   * @param Path 路径
   * @param key 键
   * @time 0.108ms
   * @returns
   */
  getStringRegKey(HKEY: HKEY, Path: string, key?: string) {
    if (!key) key = "";
    hasregArgs(HKEY, Path, "getStringRegKey");
    return native.getStringRegKey(
      HKEY,
      this.ref
        .string(Path)
        .split(/[\\\/]+/g)
        .join("\\"),
      this.ref.string(key)
    );
  }
  /**
   * 打开一个注册表路径并返回一些实用方法
   * @param HKEY 根路径
   * @param Path 路径
   * @param key 键
   * @returns
   */
  openRegKey(HKEY: HKEY, Path: string, key?: string) {
    let _this = this;
    if (!key) key = "";
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
      set(data: string) {
        return native.setRegistrKey(HKEY, Path, key || "", data);
      },
      /**
       * 获取内容
       * @returns
       */
      get() {
        return native.getStringRegKey(HKEY, Path, key || "");
      },
      /**
       * 获取该内容并将其视为二进制缓冲区
       * @returns 二进制缓冲区
       */
      getBuff(): Buffer {
        return (
          native.getRegistrBuffValue(HKEY, Path, key || "") || Buffer.alloc(0)
        );
      },
      /**
       * 获取该内容并将其视为数字
       * @returns 数字
       */
      getNumber(): number {
        return Number(native.getStringRegKey(HKEY, Path, key || ""));
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
  getNumberRegKey(HKEY: HKEY, Path: string, key?: string): number {
    if (!key) key = "";
    hasregArgs(HKEY, Path, "getNumberRegKey");
    return this.ref.int(
      native.getStringRegKey(
        HKEY,
        this.ref
          .string(Path)
          .split(/[\\\/]+/g)
          .join("\\"),
        this.ref.string(key)
      )
    );
  }
  /**
   * 删除键 (文件夹)
   * @param HKEY 根路径
   * @param Path 路径
   * @param key 键
   * @time 0.076904296875 ms
   * @returns
   */
  removeStringRegKey(HKEY: HKEY, Path: string, key?: string) {
    if (!key) key = "";
    hasregArgs(HKEY, Path, "removeStringRegKey");
    return native.removeStringRegKey(
      HKEY,
      this.ref
        .string(Path)
        .split(/[\\\/]+/g)
        .join("\\"),
      this.ref.string(key)
    );
  }
  /**
   * 删除该目录下的所有内容（树遍历）
   * @param HKEY 根路径
   * @param Path 路径
   * @param key 键
   * @returns 
   */
  removeStringRegKeyWalk(HKEY: HKEY, Path: string, key?: string) {
    if (!key) {
      let paths = this.ref
        .string(Path)
        .split(/[\\\/]/g);
      key = paths.pop();
      if (!key) throw new Error("Invalid key because it is empty");
      Path = paths.join("\\");
    }
    hasregArgs(HKEY, Path, "removeStringRegKeyWalk");
    return native.removeStringRegKeyWalk(
      HKEY,
      this.ref
        .string(Path)
        .split(/[\\\/]+/g)
        .join("\\"),
      this.ref.string(key)
    );
  }
  /**
 * 删除该目录下的所有内容（树遍历）
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @returns 
 */
  removeStringTree(HKEY: HKEY, Path: string, key: string) {
    return this.removeStringRegKeyWalk(HKEY, Path, key);
  }
  /**
   * 删除该键值
   * @param HKEY 根路径
   * @param Path 路径
   * @param key 键
   * @returns 
   */
  removeStringRegValue(HKEY: HKEY, Path: string, key?: string) {
    if (!key) key = "";
    hasregArgs(HKEY, Path, "removeStringRegValue");
    return native.removeStringRegValue(
      HKEY,
      this.ref
        .string(Path)
        .split(/[\\\/]/g)
        .join("\\"),
      this.ref.string(key)
    );
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
  setRegistrKey(HKEY: HKEY, Path: string, key: string, Value: string) {
    if (!key) key = "";
    hasregArgs(HKEY, Path, "setRegistrKey");
    return native.setRegistrKey(
      HKEY,
      this.ref
        .string(Path)
        .split(/[\\\/]/g)
        .join("\\"),
      this.ref.string(key),
      this.ref.string(Value)
    );
  }
  /**
   * 创建新的路径
   * @param HKEY 根路径
   * @param Path 路径
   * @time 2.02392578125 ms
   * @returns
   */
  createPathRegistr(HKEY: HKEY, Path: string) {
    hasregArgs(HKEY, Path, "createPathRegistr");
    return native.createPathRegistr(
      HKEY,
      this.ref
        .string(Path)
        .split(/[\\\/]/g)
        .join("\\")
    );
  }
  /**
   * 方法用于显示带有一条指定消息和一个 确认 按钮的警告框
   * @param Message 消息
   * @param Title 标题
   * @time any ms
   * @returns
   */
  alert(Message: string, Title?: string) {
    return native.alert(
      Message,
      typeof Title != "string" ? getDefaultTitele() : Title
    );
  }
  /**
   * 方法用于显示带有一条指定消息和 确认 和取消  的按钮的消息框
   * @param Message 消息
   * @param Title 标题
   * @time any ms
   * @returns
   */
  confirm(Message: string, Title?: string) {
    return native.confirm(
      Message,
      typeof Title != "string" ? getDefaultTitele() : Title
    );
  }
  /**
   * 方法用于显示带有一条指定消息和一个 确认 按钮的和❌（X）的消息框。
   * @param Message 消息
   * @param Title 标题
   * @time any ms
   * @returns
   */
  MessageStop(Message: string, Title?: string) {
    return native.MessageStop(
      Message,
      typeof Title != "string" ? getDefaultTitele() : Title
    );
  }
  /**
   * 方法用于显示带有一条指定消息和一个 确认 按钮的错误框 附带有❗ 感叹号。
   * @param Message 消息
   * @param Title 标题
   * @time any ms
   * @returns
   */
  MessageError(Message: string, Title?: string) {
    return native.MessageError(
      Message,
      typeof Title != "string" ? getDefaultTitele() : Title
    );
  }
  /**
   * 获取所有窗口的信息
   * ! @time 28.283203125 ms
   * @deprecated 该功能有概率使进程奔溃 请使用 getAllWindowsHandle 代替该功能
   **/
  getAllWindows = native.getAllWindows;
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
    let AllWindowsHandle = native.getAllWindowsHandle();
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
  processWatchdog(ProcessID: number, callback?: (() => void) | number, awaitMs?: number) {
    let quit = false;
    if (!callback) {
      let Prom: Promise<void> & { quit: () => void } = new Promise(
        async (resolve, reject) => {
          while (true) {
            if (quit) break;
            await this.Sleep(awaitMs || 500);
            if (!this.hasProcess(this.ref.int(ProcessID))) {
              resolve(void 0);
              break;
            }
          }
        }
      ) as Promise<void> & { quit: () => void };
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
  WatchWindowPoint(callback: (newPoint: number, oidPoint: number, HWND: HWND) => void, awaitMs?: number) {
    let quit = false;
    let oidPoint = native.getPointWindow() || 0;
    (async () => {
      if (typeof callback !== "function") return;
      while (true) {
        if (quit) return;
        let newPoint = native.getPointWindow() || 0;
        if (newPoint)
          if (newPoint != oidPoint) {
            if (callback) {
              callback(
                this.ref.int(newPoint),
                this.ref.int(oidPoint) || 0,
                new this.HWND(this.ref.int(newPoint))
              );
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
      setAwaitMs(ms: number) {
        awaitMs = ms;
      },
    };
  }
  pointInRect = pointInRect;
  RectInRect = RectInRect;
  RECT2Rect = RECT2Rect;
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
  WatchWindowForeground(
    callback: (newForeg: number, oidForeg: number, HWND: HWND) => void,
    awaitMs?: number
  ) {
    let quit = false;
    let oidForeg = this.getForegroundWindow();
    (async () => {
      if (typeof callback !== "function") return;
      while (true) {
        if (quit) return;
        let newForeg = this.getForegroundWindow();
        if (newForeg)
          if (this.ref.int(newForeg) != this.ref.int(oidForeg)) {
            if (callback) {
              callback(
                this.ref.int(newForeg),
                this.ref.int(oidForeg) || 0,
                new this.HWND(this.ref.int(newForeg))
              );
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
      setAwaitMs(ms: number) {
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
  openApp(
    AppPath: string,
    Command?: string | string[],
    cwd?: string,
    hide?: boolean,
    UAC?: boolean
  ) {
    return native.openApp(
      this.ref.string(AppPath),
      this.ref.string(
        Array.isArray(Command)
          ? `${Command.map((data) =>
            String(data)
              .replace(/(["]+)$/, '"')
              .replace(/^"+/, '"')
          ).join(" ")}`
          : Command
      ) || "",
      this.ref.string(cwd || path.parse(AppPath || "").dir || process.cwd()),
      this.ref.bool(hide || false),
      this.ref.bool(UAC || false)
    );
  }
  /**
   * 获取该名称 /正则匹配的进程列表
   * @param Name 
   * @returns 
   */
  getProcessNameList(...Name: Array<string | RegExp>) {
    let resultList: { pid: number; name: string }[] = [];
    let ProcessList = native.getProcessList();
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
  getDetailsProcessNameList(...Name: Array<string | RegExp>) {
    let resultList: { pid: number; name: string, path: string }[] = [];
    let ProcessList = native.getDetailsProcessList();
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
  killProcessName(...Name: Array<string | RegExp>) {
    let _this = this;
    let resultList: { pid: number; kill: boolean; name: string }[] = [];
    let ProcessList = this.getProcessList();
    for (let index = 0; index < ProcessList.length; index++) {
      const Process = ProcessList[index];
      const { pid, name } = Process;
      for (
        let NextNameIndex = 0;
        NextNameIndex < Name.length;
        NextNameIndex++
      ) {
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
    let Handle = native.getForegroundWindow();
    return Handle ? new this.HWND(Handle) : null;
  }

  /**
   * 获取句柄的主窗口
   * @returns 一个可以操作的伪数字类
   */
  getMainWindow(Handle: number | HWND) {
    let Handles = native.getMainWindow(this.ref.int(Handle));
    return Handles ? new this.HWND(Handles) : null;
  }

  /**
   * 获取鼠标所在的窗口
   * @returns 一个可以操作的伪数字类
   */
  getPointWindow() {
    let Handle = native.getPointWindow();
    return Handle ? new this.HWND(Handle) : null;
  }
  /**
   * 获取鼠标所在的窗口的主窗口
   * @returns 一个可以操作的伪数字类
   */
  getPointWindowMain() {
    let Handle = native.getPointWindowMain();
    return Handle ? new this.HWND(Handle) : null;
  }
  /**
   * 获取进程的句柄
   * @param ProcessID
   * @returns
   */
  getProcessHandle(ProcessID: number) {
    let Handles = native.getProcessHandle(this.ref.int(ProcessID));
    return Handles ? new this.HWND(Handles) : null;
  }
  /**
   * 阻止键盘和鼠标输入事件到达应用程序。
   */
  SetBlockInput(Block: boolean) {
    return native.SetBlockInput(this.ref.bool(Block));
  }
  /**
   * 设置该窗口图标在状态栏可见性 (注意：XP 下激活窗口了会失效(但是有没有一种可能 xp运行不了node和electron))
   * @param Handle 句柄
   * @param Visible 可见性
   * @returns
   */
  SetWindowInTaskbarVisible(Handle: number | HWND, Visible: boolean) {
    return native.SetWindowInTaskbarVisible(
      this.ref.int(Handle),
      this.ref.bool(Visible)
    );
  }
  /**
   * 获取句柄对应的进程id
   * @param Handle 句柄
   * @returns
   */
  getHandleProcessID(Handle: number | HWND) {
    return native.getHandleProcessID(this.ref.int(Handle));
  }
  /** 获取窗口位置大小
   *  - 高，宽，坐标大于一万以上都是不可见的
   * **/
  getWindowRect(Handle: number | HWND) {
    return native.getWindowRect(this.ref.int(Handle));
  }
  /**
   * 判断窗口是否禁用响应事件(鼠标键盘点击)
   * @param Handle
   * @returns
   */
  isEnabled(Handle: number | HWND) {
    return native.isEnabled(this.ref.int(Handle));
  }
  /**
   * 判断句柄是否有效
   * @param Handle
   * @returns
   */
  isHandle(Handle: number | HWND) {
    return native.isHandle(this.ref.int(Handle));
  }
  /**
   * 判断此句柄是否是正在活动中的窗口
   * @param Handle
   * @returns
   */
  isHandleWindowVisible(Handle: number | HWND) {
    return native.isHandleWindowVisible(this.ref.int(Handle));
  }
  /**
   * 关闭此句柄对应的窗口
   * @param Handle
   * @returns
   */
  lookHandleCloseWindow(Handle: number | HWND) {
    return native.lookHandleCloseWindow(this.ref.int(Handle));
  }
  /**
   * 获取此句柄的标题
   * @param Handle
   * @returns
   */
  lookHandleGetTitle(Handle: number | HWND) {
    return native.lookHandleGetTitle(this.ref.int(Handle));
  }
  /**
   * 设置此句柄的标题
   * @param Handle
   * @param title
   * @returns
   */
  lookHandleSetTitle(Handle: number | HWND, title: string) {
    return native.lookHandleSetTitle(
      this.ref.int(Handle),
      this.ref.string(title)
    );
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
  lookHandleShowWindow(
    Handle: number | HWND,
    SetShowType: 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11
  ) {
    return native.lookHandleShowWindow(
      this.ref.int(Handle),
      this.ref.int(
        typeof SetShowType == "number" ? this.ref.int(SetShowType) : 5
      ) as 0
    );
  }
  /**
   * 设置窗口不透明度 0-255
   * @param Handle
   * @param Transparent 0-255
   * @returns
   */
  setHandleTransparent(Handle: number | HWND, Transparent: number) {
    return native.setHandleTransparent(
      this.ref.int(Handle),
      this.ref.int(Transparent || 255)
    );
  }
  /**
   * 设置窗口是否支持响应事件(鼠标键盘点击)
   * @param Handle
   * @param Enabled
   * @returns
   */
  setWindowEnabled(Handle: number | HWND, Enabled: boolean) {
    return native.setWindowEnabled(
      this.ref.int(Handle),
      this.ref.bool(Enabled)
    );
  }
  /**
   * 设置窗口焦点
   * @param Handle
   * @returns
   */
  setWindowFocus(Handle: number | HWND) {
    return native.setWindowFocus(this.ref.int(Handle));
  }
  /**
   * 设置窗口顶设
   * @param Handle
   * @returns
   */
  setWindowTop(Handle: number | HWND) {
    return native.setWindowTop(this.ref.int(Handle));
  }
  /**
   * 刷新该窗口
   * @param Handle
   * @returns
   */
  updateWindow(Handle: number | HWND) {
    return native.updateWindow(this.ref.int(Handle));
  }
  /**
   * 窗口抖动
   * @param Handle
   * @returns
   */
  windowJitter(Handle: number | HWND) {
    return native.windowJitter(this.ref.int(Handle));
  }
  /**
   * 判断窗口是否被顶设
   * @param Handle
   * @returns
   */
  hasWindowTop(Handle: number | HWND) {
    return native.hasWindowTop(this.ref.int(Handle));
  }
  /**
   * 关闭该句柄窗口(可关闭托盘)(发送关闭消息)
   */
  closedHandle(Handle: number | HWND) {
    return native.closedHandle(this.ref.int(Handle));
  }
  /**
   * 获取所有HidUsb设备（仅限HID设备)
   * @returns HidUsb设备数组
   */
  getHidUsbList() {
    return native.getHidUsbList();
  }
  /**
   * 获取鼠标所在位置
   * @returns 鼠标所在位置
   */
  getMetrics() {
    return native.getMetrics();
  }
  /**
   * 获取鼠标之前64个位置
   * @returns 之前64个位置
   */
  getMouseMovePoints() {
    return native.getMouseMovePoints();
  }
  /**
   * 获取屏幕大小
   */
  getDeviceCaps() {
    return native.getDeviceCaps();
  }
  /**禁用/启用系统键盘鼠标钩子
    * @param HOOK 是否启用系统键盘鼠标钩子
    !注意该功能很危险 主要用于自动化防止误操作 用户锁屏  禁止用于非法用途
    *手动解锁方式 Ctrl+Alt+Del   => esc
    !请注意 你需要确保你的解锁代码  运行没有任何错误或者有定时解锁
    否则有可能导致用户无法正常使用
    **/
  SetSystemHOOK(HOOK: boolean) {
    return native.SetSystemHOOK(this.ref.bool(HOOK));
  }
  /**
   * 获取四大按钮(`alt`  `ctrl`  `win`  `shift` )是否按下
   * @returns
   */
  getBasicKeys() {
    return native.getBasicKeys();
  }
  /**
   * 获取剪贴板文本
   * @returns 剪贴板文本
   */
  getClipboardText() {
    return native.getClipboardText();
  }
  /**
   * 设置剪贴板文本
   * @param text 文本
   * @returns
   */
  setClipboardText(text: string) {
    return native.setClipboardText(this.ref.string(text));
  }
  /**
   * 清空剪贴版
   * @returns 处理结果
   */
  clearClipboard() {
    return native.clearClipboard();
  }
  /** 获取详细进程列表（慢20ms）**/
  getDetailsProcessList() {
    return native.getDetailsProcessList();
  }
  /** 获取进程列表**/
  getProcessList() {
    return native.getProcessList();
  }
  /**获取活动窗口的进程id */
  getForegroundWindowProcessID() {
    return native.getForegroundWindowProcessID();
  }
  /**获取鼠标所在窗口的进程名 */
  getPointWindowName() {
    return native.getPointWindowName();
  }
  /**获取鼠标所在窗口的进程id */
  getPointWindowProcessId() {
    return native.getPointWindowProcessId();
  }
  /**
   * 获取进程名
   * @param ProcessID 进程id
   * @returns
   */
  getProcessName(ProcessID: number) {
    return native.getProcessName(this.ref.int(ProcessID));
  }
  /**
   * 获取进程可执行文件位置
   * @param ProcessName 进程名
   * @returns 进程id
   */
  getProcessidFilePath(ProcessID: number) {
    return native.getProcessidFilePath(this.ref.int(ProcessID));
  }
  /**
   * 获取快捷方式的信息
   * @param LnkPath 快捷方式路径
   * @returns
   */
  getShortcutLink(LnkPath: string) {
    return native.getShortcutLink(this.ref.string(LnkPath));
  }
  /**系统空闲时间 */
  getSystemIdleTime() {
    return native.getSystemIdleTime();
  }
  /**
   * 设置系统右键菜单 例如win自带的系统菜单就很丑还不能禁用  使用这个禁用
   * @param Handle 句柄
   * @param boolean 是否禁用
   * @returns
   */
  getSystemMenu(Handle: number | HWND, boolean: boolean) {
    return native.getSystemMenu(this.ref.int(Handle), this.ref.bool(boolean));
  }
  /**获取托盘图标列表 */
  getTrayList() {
    return native.getTrayList();
  }
  /**判断该按键是否被按下  https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-getkeystate **/
  hasKeyActivate(KeysEvent: number) {
    return native.hasKeyActivate;
  }
  /**
   * 判断进程id 是否存在
   * @param ProcessID 进程id
   * @returns
   */
  hasProcess(ProcessID: number) {
    return native.isProcess(this.ref.int(ProcessID));
  }
  /**
   * 当前程序是否拥有管理员权限
   * @returns
   */
  isAdmin() {
    return native.isAdmin();
  }
  /**
   * 判断进程id 是否存在
   * @param ProcessID 进程id
   * @returns
   */
  isProcess(ProcessID: number) {
    return native.isProcess(this.ref.int(ProcessID));
  }
  /**判断当前系统是否是64位 */
  isSystemX64() {
    return native.isSystemX64();
  }
  killProcess(ProcessID: number): boolean;
  killProcess(ProcessID: string): {
    pid: number;
    kill: boolean;
    name: string;
  }[];
  /**
   * 结束该进程
   * @param ProcessID 
   * @returns 
   */
  killProcess(ProcessID: number | string) {
    if (typeof ProcessID == "string") {
      return this.killProcessName(ProcessID)
    }
    return native.killProcess(this.ref.int(ProcessID));
  }
  /**
   * 左键点击
   * @param ms 延迟
   * @returns 
   */
  leftClick(ms?: number) {
    return native.leftClick(ms);
  }
  /**
   * 消息窗口(调用 win-api)
   * @param message 消息内容
   * @param title 标题
   * @param UINT_String 显示窗口类型 https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-messageboxa
   * @description 衍生api(已预设): `confirm`  `alert` `MessageError` `MessageStop`
   * @returns 
   */
  messageBox(message: string, title: string, UINT_String: UINT) {
    return native.messageBox(this.ref.string(message), this.ref.string(title), this.ref.string(UINT_String) as UINT);
  }
  /**自定义鼠标事件 https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-mouse_event **/
  mouse(mouse_event: mouse_event, ms?: number) {
    if (typeof mouse_event == "number") {
      mouse_event = this.ref.int(mouse_event) as 1;
    } else {
      mouse_event = this.ref.string(mouse_event) as 'MOUSEEVENTF_RIGHTDOWN';
    }
    return native.mouse.apply(undefined, ms ? [mouse_event] : [mouse_event, ms]);
  }
  /**
   * 在资源管理器中显示并选中该文件
   * @param Path 路径
   * @returns 
   */
  openExternal(Path: string) {
    return native.openExternal(Path);
  }
  /**
   * 用默认应用打开该 （文件/文件夹）
   * @param Path 文件路径
   * @returns 
   */
  openPath(Path: string) {
    return native.openPath(Path);
  }
  /**
   * 用默认浏览器打开这条url
   * @param URL url
   * @returns 
   */
  openURL(URL: string) {
    return native.openURL(this.ref.string(URL));
  }
  /**
   * 电源控制
   */
  get powerControl() {
    function _PowerControl(Set:
      /**关机 */
      1001 |
      /**重启 */
      1002 |
      /**注销 */
      1003 |
      /**锁定 */
      1005) {
      native.powerControl(Set)
    }
    /**关机 */
    _PowerControl[1001] = () => { native.powerControl(1001) }
    /**重启 */
    _PowerControl[1002] = () => { native.powerControl(1002) }
    /**注销 */
    _PowerControl[1003] = () => { native.powerControl(1003) }
    /**锁定 */
    _PowerControl[1005] = () => { native.powerControl(1005) }
    /**关机 */
    _PowerControl.shutDown = () => { native.powerControl(1001) }
    /**重启 */
    _PowerControl.restart = () => { native.powerControl(1002) }
    /**注销 */
    _PowerControl.cancellation = () => { native.powerControl(1003) }
    /**锁定 */
    _PowerControl.lock = () => { native.powerControl(1005) }

    return _PowerControl;
  }
  /**
   * 右键点击
   * @param ms 延迟
   * @returns 
   */
  rightClick(ms?: number) {
    return native.rightClick(ms);
  }
  /**
   * 设置鼠标位置
   * @param x 左边开始的像素数坐标
   * @param y 上方到下方的像素数坐标
   * @returns 
   */
  setCursorPos(x: number, y: number) {
    return native.setCursorPos(this.ref.int(x), this.ref.int(y));
  }
  setShortcutLink(LnkPath: string, FilePath: string, work_dir: string, desc: string, args: string | string[], iShowCmd: number, icon: string, iconIndex: number): boolean;
  setShortcutLink(LnkPath: string, FilePath: string, work_dir?: string, desc?: string, args?: string | string[], iShowCmd?: number): boolean;
  setShortcutLink(LnkPath: string, FilePath: string): boolean;
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
  setShortcutLink(...args: unknown[]): boolean {
    if (args.length < 2) throw new Error("not LnkPath and FilePath arguments");
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
      args[4] = args[4].map(itme => `"${itme ? itme?.replace(/\"/g, "\\\"") : ""}"`).join(" ");
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
    return native.setShortcutLink(...args as [string, string, string]);
  }
  /**
   * 创建文件软链接
   * @param LinkPath 创建的位置
   * @param sourcePath 原文件链接
   * @returns 
   */
  createSymlink(LinkPath: string, sourcePath: string) {
    return native.createSymlink(this.ref.string(LinkPath), this.ref.string(sourcePath))
  }
  /**
   * 创建文件夹软链接
   * @param LinkPath 创建的位置
   * @param sourcePath 原文件链接
   * @returns 
   */
  createDirSymlink(LinkPath: string, sourcePath: string) {
    return native.createSymlink(this.ref.string(LinkPath), this.ref.string(sourcePath))
  }
  /**
   * 创建文件硬链接
   * @param LinkPath 创建的位置
   * @param sourcePath 原文件链接
   * @returns 
   */
  createHardLink(LinkPath: string, sourcePath: string) {
    return native.createSymlink(this.ref.string(LinkPath), this.ref.string(sourcePath))
  }

  /**打开显示器 */
  showMonitors(show?: boolean) {
    if (typeof show == "boolean") {
      return show ? native.showMonitors() : native.shutMonitors()
    }
    return native.showMonitors();
  }
  /**关闭显示器 */
  shutMonitors(show?: boolean) {
    if (typeof show == "boolean") {
      return show ? native.showMonitors() : native.shutMonitors()
    }
    return native.shutMonitors();
  }
  /**
   * `Sync` 同步阻塞(进程)
   * @param awaitTime
   * @returns
   */
  sleep(awaitTime: number) {
    return native.sleep(this.ref.int(awaitTime));
  }
  /**
   * `async` 异步阻塞(进程)
   * @param awaitTime
   * @returns
   */
  async Sleep(awaitTime: number, Sync?: boolean) {
    if (Sync) {
      return this.sleep(this.ref.int(awaitTime));
    }
    return new Promise((resolve) =>
      setTimeout(resolve, this.ref.int(awaitTime))
    );
  }
  /**
   * 系统启动到现在的时间(毫秒)
   * @returns
   */
  systemStartTime() {
    return native.systemStartTime();
  }
  /**
   * 注册表编辑
   */
  registr = {
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
    has: (HKEY: HKEY, Path: string, key: string) => {
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
    get: (HKEY: HKEY, Path: string, key: string) => {
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

    set: (HKEY: HKEY, Path: string, key: string, value: string) => {
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

    remove: (HKEY: HKEY, Path: string, key: string) => {
      return this.removeStringRegKey(HKEY, Path, key);
    },
    /**
     * 枚举键值
     * @param HKEY 根路径
     * @param Path 路径
     * @time 0.06689453125 ms
     * @returns
     */

    keys: (HKEY: HKEY, Path: string) => {
      return this.enumRegistrKey(HKEY, Path);
    },
    /**
     * 将当前的路径的注册表值转表
     * @param HKEY
     * @param Path
     */

    list: (HKEY: HKEY, Path: string) => {
      return this.listRegistrPath(HKEY, Path);
    },
    /**
     * 创建新的路径
     * @param HKEY 根路径
     * @param Path 路径
     * @time 2.02392578125 ms
     * @returns
     */

    create: (HKEY: HKEY, Path: string, key: string) => {
      return this.createPathRegistr(HKEY, Path);
    },
    /**
     * 打开一个注册表路径并返回一些实用方法
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @returns
     */ open: (HKEY: HKEY, Path: string, key: string) => {
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

    getNumberRegKey: (HKEY: HKEY, Path: string, key: string) => {
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

    getRegistrBuffValue: (HKEY: HKEY, Path: string, key: string) => {
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
  /**
   * 同 C++/C 的system
   * @returns 程序退出代码
   */
  system(str: string) {
    return native.system(this.ref.string(str));
  }
  /**
   * 空闲的随机端口号
   * @returns 
   */
  freePort(): Promise<number> {
    return new Promise((resolve, reject) => {
      let sock = net.createServer(function () { });
      sock.listen(0, () => {
        // @ts-expect-error
        resolve(Number(sock?.address()?.port as string));
        sock.close();
      });
    });
  }
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
  systemChcp = systemChcp;
  getClipboardFilePaths(): string[];
  getClipboardFilePaths(at: number): string | undefined;
  /**
   * 获取剪贴板中的文件列表
   * @returns 
   */
  getClipboardFilePaths(at?: number): unknown {
    let paths = native.getClipboardFilePaths();
    if (typeof at === 'number') {
      if (at < 0) {
        return paths[paths.length + at];
      }
      return paths[at];
    }
    return paths
  }
  /**
   * 向剪贴板写入文件列表
   * @param FilePaths 
   */
  setClipboardFilePaths(...FilePaths: string[] | [string[]]) {
    let filePaths: string[] = [];
    for (let index = 0; index < FilePaths.length; index++) {
      const FilePath = FilePaths[index];
      if (typeof FilePath !== "string") {
        for (let indexc = 0; indexc < FilePaths.length; indexc++) {
          filePaths.push(this.ref.string(FilePaths[indexc]));
        }
      } else {
        filePaths.push(this.ref.string(FilePath));
      }
    }
    return native.setClipboardFilePaths(filePaths);
  }
  /**
   * 获取所有usb驱动器(不包含HUD)
   * @returns 
   */
  getUsbDevsInfo() {
    return native.getUsbDevsInfo();
  }
  /**
   * 枚举句柄的子窗口
   * @param Handle 句柄
   * @returns 
   */
  enumChildWindows(Handle: number | HWND) {
    return native.enumChildWindows(this.ref.int(Handle));
  }
  #thenConsole: HWND | undefined | null;
  /**
   * 隐藏当前控制台窗口(node)
   */
  hideConsole() {
    if (!this.#thenConsole) {
      this.#thenConsole = this.getProcessHandle(process.pid);
    }
    if (!this.#thenConsole) return false;
    return this.#thenConsole?.hide() || false;
  }
  /**
   * 显示当前控制台窗口(node)
   */
  showConsole() {
    if (!this.#thenConsole) {
      this.#thenConsole = this.getProcessHandle(process.pid);
    }
    if (!this.#thenConsole) return false;
    return this.#thenConsole?.show() || false;
  }
  /**
   * 获取当前控制台窗口的句柄(node)
   * @returns 
   */
  getConsoleHandle() {
    if (!this.#thenConsole) {
      this.#thenConsole = this.getProcessHandle(process.pid);
    }
    return this.#thenConsole;
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
  deleteFile(Path: string, Recycle?: boolean, isShow?: boolean) {
    return native.deleteFile(this.ref.path(Path),
      typeof Recycle == "boolean" ? this.ref.bool(Recycle) : true,
      typeof isShow == "boolean" ? this.ref.bool(isShow) : false,
    )
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
    return this.deleteFile
  }

  /**
   * 获取当前剪贴板内容的id(如果被重新写入了该id会变动)
   * @returns 
   */
  getClipboardSequenceNumber(): number {
    return native.getClipboardSequenceNumber()
  }
  /**
   * 当剪贴板内容变更后发生回调
   * @param CallBack 回调函数
   * @param nextAwaitMs 每次判断内容变化用时 默认 `150` ms
   * @returns 
   */
  watchClipboard(CallBack: () => void, nextAwaitMs?: number) {
    let _this = this;
    let NextAwaitMs = nextAwaitMs || 150;
    let Next = true;
    let oidClipboardSequenceNumber = this.getClipboardSequenceNumber();
    (async function () {
      while (Next) {
        await _this.Sleep(NextAwaitMs);
        let clipboardSequenceNumber = _this.getClipboardSequenceNumber();
        if (oidClipboardSequenceNumber !== clipboardSequenceNumber) {
          if (CallBack) CallBack();
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
      setNextAwaitMs(nextAwaitMs: number) {
        NextAwaitMs = _this.ref.int(nextAwaitMs) || 150;
      }
    }
  }
  /**
    * 当驱动器添加或者移除后发生回调
    * @param CallBack 回调函数
    * @param nextAwaitMs 每次判断内容变化用时 默认 `800` ms
    * @param watchType 监听的设备类型 默认 `["HUB","drive"]`
    * @returns 
    */
  watchUSB(CallBack: (env: "add" | "remove" | "start", id: string) => void, nextAwaitMs?: number, watchType?: "hub" | "drive" | Array<"hub" | "drive">) {
    let _this = this;
    let NextAwaitMs = nextAwaitMs || 800;
    let Next = true;
    let OID_ID_LIST: Set<string> = new Set();
    let start = true;
    if (typeof watchType == "string") watchType = [watchType];
    (async function () {
      while (Next) {
        await _this.Sleep(NextAwaitMs);
        let GET_ID_List = new Set(watchType ? [
          ...(watchType.includes("hub") ? native.getHidUsbIdList() : []),
          ...(watchType.includes("drive") ? native.getUsbDevsInfo() : []),
        ] : [...native.getHidUsbIdList(), ...native.getUsbDevsInfo()]);
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
        return OID_ID_LIST
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
      setNextAwaitMs(nextAwaitMs: number) {
        NextAwaitMs = _this.ref.int(nextAwaitMs) || 800;
      }
    }
  }
  /**
   * 获取所有屏幕
   * @returns 
   */
  getDeviceCapsAll(): cRECT[] {
    return native.getDeviceCapsAll();
  }
  /**
   * 判断句柄的窗口是否在所有窗口的范围中(无论他是否被其他窗口挡住)
   * @param Handle 
   */
  isInMonitorWindow(Handle: number | HWND): boolean {
    return native.isInMonitorWindow(this.ref.int(Handle));
  }
  /**
   * 判断句柄的窗口是否在鼠标所在的窗口
   * @param Handle 
   */
  isMouseMonitorWindow(Handle: number): boolean {
    return native.isMouseMonitorWindow(this.ref.int(Handle));
  }
  /**
   * 获取鼠标所在的屏幕信息
   */
  getCurrentMonitorRect(): cRECT {
    return native.getCurrentMonitorRect();
  }
  /**
   * 当前电脑存在几个屏幕
   */
  getSystemMetricsLen(): number {
    return native.getSystemMetricsLen();
  }
  /**
   * 由于编写时间过长，想法不同，模块过于庞大复杂 名称混乱 重新对模块进行分类 分配统一化的名称
   */
  get #window() {
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
          blockInput:this.SetBlockInput,
        }
      }
    })();
  }
  /**
   * 所有窗口操作方法的归类合集 (拥有统一化名称) 
   */
  window = this.#window;
  get #watch() {
    return (() => {
      return {
        clipboard: this.watchClipboard,
        usb: this.watchUSB,
        windowFocus: this.WatchWindowForeground,
        windowPoint: this.WatchWindowPoint,
        process: this.processWatchdog
      }
    })();
  }
  /**
  * 所有监听函数的合集 (拥有统一化名称) 
  */
  watch = this.#watch;
  get #shell(){
    return (() => {
      return {
        trash:this.deleteFile,
        delete:this.deleteFile,
        openApp:this.openApp,
        getShortcutLink:this.getShortcutLink,
        setShortcutLink:this.setShortcutLink,
        freePort:this.freePort,
        createSymlink:this.createSymlink,
        createDirSymlink:this.createDirSymlink,
        createHardLink:this.createHardLink,
        
      }
    })();
  }
  get #usb(){
    return (() => {
      return {
        getHub:this.getHidUsbList,
        getDevsInfo:this.getUsbDevsInfo,
        watch:this.watchUSB,
        
      }
    })();
  }
  get #clipboard(){
    return (() => {
      return {
        clear:this.clearClipboard,
        readText:this.getClipboardText,
        readFilePaths:this.getClipboardFilePaths,
        writeText:this.setClipboardText,
        writeFilePaths:this.setClipboardFilePaths,
        sequence:this.getClipboardSequenceNumber,
        watch:this.watchClipboard,
      }
    })();
  }
  get #process(){
    return (() => {
      return {
        watch:this.processWatchdog,
        kill:this.killProcess,
        killMatch:this.killProcessName,
        getList:this.getProcessList,
        getHandle:this.getProcessHandle,
        getName:this.getProcessName,
        getPath:this.getProcessidFilePath,
        getFocus:this.getForegroundWindowProcessID,
        has:this.hasProcess,
        match:this.getProcessNameList,
        matchDetails:this.getDetailsProcessNameList ,
        getDetailsList:this.getDetailsProcessList,
        
      }
    })();
  }
  get #auto(){
    return (() => {
      return {
     
      }
    })();
  }
  /**剪贴板工具集  (拥有统一化名称) */ 
  clipboard=this.#clipboard;
  /**自动化工具集   (拥有统一化名称) */
  auto=this.#auto;
  /**USB 控制的归档   (拥有统一化名称) */
  usb=this.#usb;
  /**实用工具集   (拥有统一化名称)*/
  shell=this.#shell;
  /**进程操作合集   (拥有统一化名称) */
  process=this.#process;

}
/**
 * 获取窗口的标题
 * @returns
 */
function getDefaultTitele(): string {
  try {
    // @ts-expect-error
    return window.document.title;
  } catch (error) {
    return (
      native.lookHandleGetTitle(native.getProcessHandle(process.pid) || 0) ||
      native.getProcessName(process.pid) ||
      process.title
    );
  }

}

export const hmc = new hmc_win32();



export declare interface Rect {
  /**
   * (x)从屏幕左边到所在位置得像素数
   */
  right?: number;
  /**
   * 底部到当前位置
   */
  bottom: number;
  /**
   * 右边到当前位置
   */
  left: number;
  /**
   * 宽度
   */
  width: number;
  /**
   * 高度
   */
  height: number;
  /**
   * (right) 从屏幕右边到所在位置得像素数
   */
  x: number;
  /**
   * (top)从屏幕顶部边到所在位置得像素数
   */
  y: number;

  /**
   * (y)从屏幕顶部边到所在位置得像素数
   */
  top: number;
}

export declare let UINT: {
  /**消息框包含三个按钮：终止、重试和忽略。 */
  MB_ABORTRETRYIGNORE: string;
  /**消息框包含三个按钮：取消、重试、继续。使用此消息框类型而不是 MB_ABORTRETRYIGNORE。 */
  MB_CANCELTRYCONTINUE: string;
  /**向消息框 添加帮助按钮。当用户单击帮助按钮或按 F1 时，系统会向所有者 发送WM_HELP消息。 */
  MB_HELP: string;
  /**消息框包含一个按钮：确定。这是默认设置。 */
  MB_OK: string;
  /**消息框包含两个按钮：确定和取消。 */
  MB_YESNOCANCEL: string;
  /**消息框包含两个按钮：是和否。 */
  MB_YESNO: string;
  /**消息框包含两个按钮：OK和Cancel。 */
  MB_OKCANCEL: string;
  /**消息框包含两个按钮：OK和Cancel。 */
  MB_RETRYCANCEL: string;
  /**
   * 消息框包含三个按钮：Yes、No和Cancel。
   * *一个停止标志图标出现在消息框中。
   */
  MB_ICONERROR: string;
  /**一个停止标志图标出现在消息框中。 */
  MB_ICONSTOP: string;
  /**问号图标出现在消息框中。不再推荐使用问号消息图标，因为它不能清楚地表示特定类型的消息，并且作为问题的消息措辞可能适用于任何消息类型。此外，用户可能会将消息符号问号与帮助信息混淆。因此，请勿在消息框中使用此问号消息符号。系统继续支持它的包含只是为了向后兼容。 */
  MB_ICONQUESTION: string;
  /**一个由圆圈中的小写字母i组成的图标出现在消息框中。 */
  MB_ICONASTERISK: string;
  MB_ICONINFORMATION: string;
  /**消息框中会出现一个感叹号图标。 */
  MB_ICONEXCLAMATION: string;
  /** 消息框中会出现一个感叹号图标。 */
  MB_ICONWARNING: string;
  /**以下也是被支持的具体请查看 https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-messageboxa
   *消息框成为前台窗口 **/
  MB_TOPMOST: string;
  MB_SETFOREGROUND: string;
  MB_RTLREADING: string;
  MB_RIGHT: string;
  MB_DEFAULT_DESKTOP_ONLY: string;
  MB_TASKMODAL: string;
  MB_SYSTEMMODAL: string;
  MB_APPLMODAL: string;
  MB_DEFBUTTON4: string;
  MB_DEFBUTTON3: string;
  MB_DEFBUTTON2: string;
  MB_ICONHAND: string;
  MB_DEFBUTTON1: string;
};

export declare type UINT = keyof typeof UINT;
/**进程名称**/
export declare type ProcessID = number;
/**win窗口允许的不透明度 */
export declare type HandleTransparent = number;
export declare type HidUsb = {
  /**类型**/
  type: "hid" | "keyboard" | "mouse";
  /**本次枚举中的索引/
  "index": number,
  /**设备名称**/
  name: string;
  /**供应商 ID */
  dwVendorId: number;
  /**产品 ID */
  dwProductId: number;
  /**版本号 */
  dwVersionNumber: number;
  /**开发人员提供有关控制测量内容的信息 */
  usUsage: number;
  /**设备供应商对其设备的控制或者设备控制组的特定用途建议 */
  usUsagePage: number;
};
export declare type HKEY = keyof typeof Hkey;
export declare type mouse_event = keyof typeof mouse_event_list;
export declare let mouse_event_list: {
  /**不支持的属性 请使用 setCursorPos 方法设置位置*/
  32768: string;
  /**左键按下 */
  2: string;
  /**左边的按钮是向上的 */
  4: string;
  /**中间的按钮是向下的 */
  32: string;
  /**中间的按钮是向上的 */
  64: string;
  /**鼠标移动和按钮点击 */
  1: string;
  /**鼠标右键按下 */
  8: string;
  /**鼠标右键弹起 */
  16: string;
  /**滚轮按钮被旋转 */
  2048: string;
  /**按下了 X 按钮 */
  128: string;
  /**X 按钮被释放 */
  256: string;
  /**滚轮按钮倾斜*/
  4096: string;
  /**不支持的属性 请使用 setCursorPos 方法设置位置*/
  MOUSEEVENTF_ABSOLUTE: number;
  /**左键按下 */
  MOUSEEVENTF_LEFTDOWN: number;
  /**左边的按钮是向上的 */
  MOUSEEVENTF_LEFTUP: number;
  /**中间的按钮是向下的 */
  MOUSEEVENTF_MIDDLEDOWN: number;
  /**中间的按钮是向上的 */
  MOUSEEVENTF_MIDDLEUP: number;
  /**鼠标移动和按钮点击 */
  MOUSEEVENTF_MOVE: number;
  /**鼠标右键按下 */
  MOUSEEVENTF_RIGHTDOWN: number;
  /**鼠标右键弹起 */
  MOUSEEVENTF_RIGHTUP: number;
  /**滚轮按钮被旋转 */
  MOUSEEVENTF_WHEEL: number;
  /**按下了 X 按钮 */
  MOUSEEVENTF_XDOWN: number;
  /**X 按钮被释放 */
  MOUSEEVENTF_XUP: number;
  /**滚轮按钮倾斜*/
  MOUSEEVENTF_HWHEEL: number;
};
/**
 * 设置窗口坐标
 */
export type SetWindowRect = {
  /**
   * (right) 从屏幕右边到所在位置得像素数
   */
  x?: number;
  /**
   * (top)从屏幕顶部边到所在位置得像素数
   */
  y?: number;
  /**
   * 宽度
   */
  width?: number;
  /**
   * 高度
   */
  height?: number;
  /**
   * (x)从屏幕左边到所在位置得像素数
   */
  right?: number;
  /**
   * (y)从屏幕顶部边到所在位置得像素数
   */
  top?: number;
};
/**功能介绍 */
export declare const desc: hmc_win32['desc'];
/**
 * 获取所有窗口的信息
 * ! @time 28.283203125 ms
 * @deprecated 该功能有概率使进程奔溃 请使用 getAllWindowsHandle 代替该功能
 **/

export declare const getAllWindows: hmc_win32['getAllWindows'];
/**当前二进制适用系统平台 */
export declare const platform: hmc_win32['platform'];
export declare const ref: hmc_win32['ref'];
/**注册表编辑 */
export declare const registr: hmc_win32['registr'];
/**版本号 */
export declare const version: hmc_win32['version'];
/**版本号 */
export declare const powerControl: hmc_win32['powerControl'];
/**
  * 方法用于显示带有一条指定消息和一个 确认 按钮的错误框 附带有❗ 感叹号。
  * @param Message 消息
  * @param Title 标题
  * @time any ms
  * @returns
  */

export declare const MessageError: hmc_win32['MessageError'];
/**
   * 方法用于显示带有一条指定消息和一个 确认 按钮的和❌（X）的消息框。
   * @param Message 消息
   * @param Title 标题
   * @time any ms
   * @returns
   */

export declare const MessageStop: hmc_win32['MessageStop'];
/**阻止键盘和鼠标输入事件到达应用程序。 */
export declare const SetBlockInput: hmc_win32['SetBlockInput'];
/**禁用/启用系统键盘鼠标钩子
    * @param HOOK 是否启用系统键盘鼠标钩子
    !注意该功能很危险 主要用于自动化防止误操作 用户锁屏  禁止用于非法用途
    *手动解锁方式 Ctrl+Alt+Del   => esc
    !请注意 你需要确保你的解锁代码  运行没有任何错误或者有定时解锁
    否则有可能导致用户无法正常使用
    **/

export declare const SetSystemHOOK: hmc_win32['SetSystemHOOK'];
/**
   * 设置该窗口图标在状态栏可见性 (注意：XP 下激活窗口了会失效(但是有没有一种可能 xp运行不了node和electron))
   * @param Handle 句柄
   * @param Visible 可见性
   * @returns
   */

export declare const SetWindowInTaskbarVisible: hmc_win32['SetWindowInTaskbarVisible'];
/**
   * `async` 异步阻塞(进程)
   * @param awaitTime
   * @returns
   */

export declare const Sleep: hmc_win32['Sleep'];
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

export declare const WatchWindowForeground: hmc_win32['WatchWindowForeground'];
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

export declare const WatchWindowPoint: hmc_win32['WatchWindowPoint'];
/**
  * 方法用于显示带有一条指定消息和一个 确认 按钮的警告框
  * @param Message 消息
  * @param Title 标题
  * @time any ms
  * @returns
  */

export declare const alert: hmc_win32['alert'];
/**
 * 清空剪贴版
 * @returns 处理结果
 */
export declare const clearClipboard: hmc_win32['clearClipboard'];
/**
 * 关闭该句柄窗口(可关闭托盘)(发送关闭消息)
 */
export declare const closedHandle: hmc_win32['closedHandle'];
/**
 * 方法用于显示带有一条指定消息和 确认 和取消  的按钮的消息框
 * @param Message 消息
 * @param Title 标题
 * @time any ms
 * @returns
 */
export declare const confirm: hmc_win32['confirm'];
/**
 * 创建新的路径
 * @param HKEY 根路径
 * @param Path 路径
 * @time 2.02392578125 ms
 * @returns
 */
export declare const createPathRegistr: hmc_win32['createPathRegistr'];
/**
 * 枚举键值
 * @param HKEY 根路径
 * @param Path 路径
 * @time 0.06689453125 ms
 * @returns
 */
export declare const enumRegistrKey: hmc_win32['enumRegistrKey'];
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
export declare const getAllWindowsHandle: hmc_win32['getAllWindowsHandle'];
/**
 * 获取四大按钮(`alt`  `ctrl`  `win`  `shift` )是否按下
 * @returns
 */
export declare const getBasicKeys: hmc_win32['getBasicKeys'];
/**
 * 获取剪贴板文本
 * @returns 剪贴板文本
 */
export declare const getClipboardText: hmc_win32['getClipboardText'];
/** 获取详细进程列表（慢20ms）**/
export declare const getDetailsProcessList: hmc_win32['getDetailsProcessList'];
/**
 * 获取屏幕大小
 */
export declare const getDeviceCaps: hmc_win32['getDeviceCaps'];
/**
 * 获取当前的焦点窗口
 * @returns 一个可以操作的伪数字类
 */
export declare const getForegroundWindow: hmc_win32['getForegroundWindow'];
/**获取活动窗口的进程id */
export declare const getForegroundWindowProcessID: hmc_win32['getForegroundWindowProcessID'];
/**
 * 获取句柄对应的进程id
 * @param Handle 句柄
 * @returns
 */
export declare const getHandleProcessID: hmc_win32['getHandleProcessID'];
/**
 * 获取所有HidUsb设备（仅限HID设备)
 * @returns HidUsb设备数组
 */
export declare const getHidUsbList: hmc_win32['getHidUsbList'];
/**
 * 获取句柄的主窗口
 * @returns 一个可以操作的伪数字类
 */
export declare const getMainWindow: hmc_win32['getMainWindow'];
/**
 * 获取鼠标所在位置
 * @returns 鼠标所在位置
 */
export declare const getMetrics: hmc_win32['getMetrics'];
/**
 * 获取鼠标之前64个位置
 * @returns 之前64个位置
 */
export declare const getMouseMovePoints: hmc_win32['getMouseMovePoints'];
/**
 * 获取内容(数字)
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @time 0.10888671875 ms
 * @returns
 */
export declare const getNumberRegKey: hmc_win32['getNumberRegKey'];
/**
 * 获取鼠标所在的窗口
 * @returns 一个可以操作的伪数字类
 */
export declare const getPointWindow: hmc_win32['getPointWindow'];
/**
 * 获取鼠标所在的窗口的主窗口
 * @returns 一个可以操作的伪数字类
 */
export declare const getPointWindowMain: hmc_win32['getPointWindowMain'];
/**获取鼠标所在窗口的进程名 */
export declare const getPointWindowName: hmc_win32['getPointWindowName'];
/**获取鼠标所在窗口的进程id */
export declare const getPointWindowProcessId: hmc_win32['getPointWindowProcessId'];
/**
 * 获取进程的句柄
 * @param ProcessID
 * @returns
 */
export declare const getProcessHandle: hmc_win32['getProcessHandle'];
/** 获取进程列表**/
export declare const getProcessList: hmc_win32['getProcessList'];
/**
 * 获取进程名
 * @param ProcessID 进程id
 * @returns
 */
export declare const getProcessName: hmc_win32['getProcessName'];
/**
 * 获取进程可执行文件位置
 * @param ProcessName 进程名
 * @returns 进程id
 */
export declare const getProcessidFilePath: hmc_win32['getProcessidFilePath'];
/**
 * 获取内容(二进制 Buffer)
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @time 0.06787109375 ms
 * @returns
 */
export declare const getRegistrBuffValue: hmc_win32['getRegistrBuffValue'];
/**
  * 获取快捷方式的信息
  * @param LnkPath 快捷方式路径
  * @returns
  */
export declare const getShortcutLink: hmc_win32['getShortcutLink'];
/**
 * 获取内容(文本)
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @time 0.108ms
 * @returns
 */
export declare const getStringRegKey: hmc_win32['getStringRegKey'];
/**系统空闲时间 */
export declare const getSystemIdleTime: hmc_win32['getSystemIdleTime'];
/**
 * 设置系统右键菜单 例如win自带的系统菜单就很丑还不能禁用  使用这个禁用
 * @param Handle 句柄
 * @param boolean 是否禁用
 * @returns
 */
export declare const getSystemMenu: hmc_win32['getSystemMenu'];
/**获取托盘图标列表 */
export declare const getTrayList: hmc_win32['getTrayList'];
/** 获取窗口位置大小
 *  - 高，宽，坐标大于一万以上都是不可见的
 * **/
export declare const getWindowRect: hmc_win32['getWindowRect'];
/**判断该按键是否被按下  https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-getkeystate **/
export declare const hasKeyActivate: hmc_win32['hasKeyActivate'];
/**
 * 判断进程id 是否存在
 * @param ProcessID 进程id
 * @returns
 */
export declare const hasProcess: hmc_win32['hasProcess'];
/**
 * 判断注册表中是否有该键值
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @time 0.06591796875 ms
 * @returns
 */
export declare const hasRegistrKey: hmc_win32['hasRegistrKey'];
/**
 * 判断窗口是否被顶设
 * @param Handle
 * @returns
 */
export declare const hasWindowTop: hmc_win32['hasWindowTop'];
/**
 * 当前程序是否拥有管理员权限
 * @returns
 */
export declare const isAdmin: hmc_win32['isAdmin'];
/**
 * 判断窗口是否禁用响应事件(鼠标键盘点击)
 * @param Handle
 * @returns
 */
export declare const isEnabled: hmc_win32['isEnabled'];
/**
 * 判断句柄是否有效
 * @param Handle
 * @returns
 */
export declare const isHandle: hmc_win32['isHandle'];
/**
 * 判断此句柄是否是正在活动中的窗口
 * @param Handle
 * @returns
 */
export declare const isHandleWindowVisible: hmc_win32['isHandleWindowVisible'];
/**
 * 判断进程id 是否存在
 * @param ProcessID 进程id
 * @returns
 */
export declare const isProcess: hmc_win32['isProcess'];
/**判断当前系统是否是64位 */
export declare const isSystemX64: hmc_win32['isSystemX64'];
/**
 * 结束该进程
 * @param ProcessID 
 * @returns 
 */
export declare const killProcess: hmc_win32['killProcess'];
/**
 * 结束该名称的进程
 * @param Name
 */
export declare const killProcessName: hmc_win32['killProcessName'];
/**
 * 左键点击
 * @param ms 延迟
 * @returns 
 */
export declare const leftClick: hmc_win32['leftClick'];
/**
 * 将当前的路径的注册表值转表
 * @param HKEY
 * @param Path
 */
export declare const listRegistrPath: hmc_win32['listRegistrPath'];
/**
 * 关闭此句柄对应的窗口
 * @param Handle
 * @returns
 */
export declare const lookHandleCloseWindow: hmc_win32['lookHandleCloseWindow'];
/**
 * 获取此句柄的标题
 * @param Handle
 * @returns
 */
export declare const lookHandleGetTitle: hmc_win32['lookHandleGetTitle'];
/**
 * 设置此句柄的标题
 * @param Handle
 * @param title
 * @returns
 */
export declare const lookHandleSetTitle: hmc_win32['lookHandleSetTitle'];
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
export declare const lookHandleShowWindow: hmc_win32['lookHandleShowWindow'];
/**
 * 消息窗口(调用 win-api)
 * @param message 消息内容
 * @param title 标题
 * @param UINT_String 显示窗口类型 https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-messageboxa
 * @description 衍生api(已预设): `confirm`  `alert` `MessageError` `MessageStop`
 * @returns 
 */
export declare const messageBox: hmc_win32['messageBox'];
/**自定义鼠标事件 https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-mouse_event **/
export declare const mouse: hmc_win32['mouse'];
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
export declare const openApp: hmc_win32['openApp'];
/**
 * 在资源管理器中显示并选中该文件
 * @param Path 路径
 * @returns 
 */
export declare const openExternal: hmc_win32['openExternal'];
/**
 * 用默认应用打开该 （文件/文件夹）
 * @param Path 文件路径
 * @returns 
 */
export declare const openPath: hmc_win32['openPath'];
/**
 * 打开一个注册表路径并返回一些实用方法
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @returns
 */
export declare const openRegKey: hmc_win32['openRegKey'];
/**
 * 用默认浏览器打开这条url
 * @param URL url
 * @returns 
 */
export declare const openURL: hmc_win32['openURL'];
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
export declare const processWatchdog: hmc_win32['processWatchdog'];
/**
 * 删除数据
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @time 0.076904296875 ms
 * @returns
 */
export declare const removeStringRegKey: hmc_win32['removeStringRegKey'];
/**
 * 右键点击
 * @param ms 延迟
 * @returns 
 */
export declare const rightClick: hmc_win32['rightClick'];
/**
 * 设置剪贴板文本
 * @param text 文本
 * @returns
 */
export declare const setClipboardText: hmc_win32['setClipboardText'];
/**
* 设置鼠标位置
* @param x 左边开始的像素数坐标
* @param y 上方到下方的像素数坐标
* @returns 
*/
export declare const setCursorPos: hmc_win32['setCursorPos'];
/**
 * 设置窗口不透明度 0-255
 * @param Handle
 * @param Transparent 0-255
 * @returns
 */
export declare const setHandleTransparent: hmc_win32['setHandleTransparent'];
/**
 * 设置键值对
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @param Value 数据
 * @time 2.02392578125 ms
 * @returns
 */
export declare const setRegistrKey: hmc_win32['setRegistrKey'];
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
export declare const setShortcutLink: hmc_win32['setShortcutLink'];
/**
 * 设置窗口是否支持响应事件(鼠标键盘点击)
 * @param Handle
 * @param Enabled
 * @returns
 */
export declare const setWindowEnabled: hmc_win32['setWindowEnabled'];
/**
 * 设置窗口焦点
 * @param Handle
 * @returns
 */
export declare const setWindowFocus: hmc_win32['setWindowFocus'];
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
export declare const setWindowMode: hmc_win32['setWindowMode'];
/**
 * 设置窗口顶设
 * @param Handle
 * @returns
 */
export declare const setWindowTop: hmc_win32['setWindowTop'];
/**打开显示器 */
export declare const showMonitors: hmc_win32['showMonitors'];
/**关闭显示器 */
export declare const shutMonitors: hmc_win32['shutMonitors'];
/**
   * `Sync` 同步阻塞(进程)
   * @param awaitTime
   * @returns
   */

export declare const sleep: hmc_win32['sleep'];
/**
   * 同 C++/C 的system
   * @returns 程序退出代码
   */

export declare const system: hmc_win32['system'];
/**
  * 系统启动到现在的时间(毫秒)
  * @returns
  */

export declare const systemStartTime: hmc_win32['systemStartTime'];
/**
   * 刷新该窗口
   * @param Handle
   * @returns
   */

export declare const updateWindow: hmc_win32['updateWindow'];
/**
   * 窗口抖动
   * @param Handle
   * @returns
   */

export declare const windowJitter: hmc_win32['windowJitter'];
/**
   * 获取该名称 /正则匹配的进程列表
   * @param Name 
   * @returns 
   */

export declare const getProcessNameList: hmc_win32['getProcessNameList'];
/**
* 获取该名称 /正则匹配的进程列表 带执行文件路径 慢20ms
* @param Name 
* @returns 
*/
export declare const getDetailsProcessNameList: hmc_win32['getDetailsProcessNameList'];
/**
 * 删除该目录下的所有内容（树遍历）
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @returns 
 */
export declare const removeStringRegKeyWalk: hmc_win32['removeStringRegKeyWalk'];
/**
 * 删除该键值
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @returns 
 */
export declare const removeStringRegValue: hmc_win32["removeStringRegValue"];
/**
 * 设置键值对内容(32位数字)
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @param Qword (32位数字)
 * @returns 
 */
export declare const setRegistrDword: hmc_win32["setRegistrDword"];
/**
 * 设置键值对内容(64位数字)
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @param Qword (64位数字)
 * @returns 
 */
export declare const setRegistrQword: hmc_win32["setRegistrQword"];
/**
 * 获取内容(64位数字)
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @returns
 */
export declare const getRegistrQword: hmc_win32["getRegistrQword"];
/**
 * 获取内容(64位数字)
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @returns
 */
export declare const getRegistrDword: hmc_win32["getRegistrDword"];
/**
 * 枚举句柄的子窗口
 * @param Handle 句柄
 * @returns 
 */
export declare const enumChildWindows: hmc_win32["enumChildWindows"];
/**
 * 获取所有usb驱动器(不包含HUD)
 * @returns 
 */
export declare const getUsbDevsInfo: hmc_win32["getUsbDevsInfo"];
/**
  * 获取剪贴板中的文件列表
  * @returns 
  */
export declare const getClipboardFilePaths: hmc_win32["getClipboardFilePaths"];
/**
 * 创建文件夹软链接
 * @param LinkPath 创建的位置
 * @param sourcePath 原文件链接
 * @returns 
 */
export declare const createDirSymlink: hmc_win32["createDirSymlink"];

/**
 * 创建文件软链接
 * @param LinkPath 创建的位置
 * @param sourcePath 原文件链接
 * @returns 
 */
export declare const createSymlink: hmc_win32["createSymlink"];
/**
 * 创建文件硬链接
 * @param LinkPath 创建的位置
 * @param sourcePath 原文件链接
 * @returns 
 */
export declare const createHardLink: hmc_win32["createHardLink"];
/**
 * 空闲的随机端口号
 * @returns 
 */
export declare const freePort: hmc_win32["freePort"];

/**
 * 获取当前控制台窗口的句柄(node)
 * @returns 
 */
export declare const getConsoleHandle: hmc_win32["getConsoleHandle"];

/**
* 隐藏当前控制台窗口(node)
* @returns 
*/
export declare const hideConsole: hmc_win32["hideConsole"];

/**
* 显示当前控制台窗口(node)
* @returns 
*/
export declare const showConsole: hmc_win32["showConsole"];
/**
 * 判断该键值是否存在子项
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 */
export declare const isRegistrTreeKey: hmc_win32["isRegistrTreeKey"];
/**
* 删除该目录下的所有内容（树遍历）
* @param HKEY 根路径
* @param Path 路径
* @param key 键
* @returns 
*/
export declare const removeStringTree: hmc_win32["removeStringTree"];
/**
 * 向剪贴板写入文件列表
 * @param FilePaths 
 */
export declare const setClipboardFilePaths: hmc_win32["setClipboardFilePaths"];
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
export declare const deleteFile: hmc_win32["deleteFile"];
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
export declare const trash: hmc_win32["deleteFile"];

/**
 * 获取当前剪贴板内容的id(如果被重新写入了该id会变动)
 * @returns 
 */
export declare const getClipboardSequenceNumber: hmc_win32["getClipboardSequenceNumber"];
/**
 * 当剪贴板内容变更后发生回调
 * @param CallBack 回调函数
 * @param nextAwaitMs 每次判断内容变化用时 默认 `150` ms
 * @returns 
 */
export declare const watchClipboard: hmc_win32["watchClipboard"];
/**
    * 当驱动器添加或者移除后发生回调
    * @param CallBack 回调函数
    * @param nextAwaitMs 每次判断内容变化用时 默认 `800` ms
    * @returns 
    */
export declare const watchUSB: hmc_win32["watchUSB"];

/**
 * 所有窗口操作方法的归类合集 (拥有统一化名称) 
 */
export declare const window: hmc_win32["window"];

/**所有监听函数的合集 (拥有统一化名称)  */
export declare const watch: hmc_win32["watch"];

export {
  native
}
export default hmc;
module.exports = hmc;


type SystemDecoderKey = keyof chcpList;
type SystemDecoder = chcpList[SystemDecoderKey]


