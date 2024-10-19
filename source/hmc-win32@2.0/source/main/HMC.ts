
export namespace HMC {

    export function ALL_NONE_FUN_CALLBECK(...arg: any[]) { }

    export const HMCNotPlatform = "HMC::HMC current method only supports win32 platform";

    export enum ENV_INFO_COMMAND {

        // getProcessCommandLine2   `string`
        GET_COMMAND = 1,
        // getProcessCwdPath2 `string`
        GET_CWD = 2,
        // getProcessCpuUsage2 `float`
        GET_PROCESS_CPU_USAGE = 3,
        // getProcessStartTime2 `number`
        GET_PROCESS_START_TIME = 5,
        // EnumProcesses `json`
        GET_ENUM_PROCESSES_LIST = 6,
        // getAllProcessList2(true) `json`
        GET_ALL_PROCESS_LIST_PID_NAME = 7,
        // getAllProcessList2 `json`
        GET_ALL_PROCESS_LIST_NONE_NAME = 8,
        // getDetailsProcessList2 `json`
        GET_ALL_PROCESS_LIST_DETAILS = 7,
        // getAllProcessListSnp2 `json`
        GET_ALL_PROCESS_LIST_SNP = 10,
        // getAllProcessListNt2 `json`
        GET_ALL_PROCESS_LIST_NT = 11,
        //  getProcessThreadList `json`
        GET_ALL_THREAD_LIST = 12,
        //  getParentProcessID2 `long`
        GET_PARENT_PROCESS_ID = 13,
        // existProcess `bool`
        GET_EXIST_PROCESS = 15,
        // getSubProcess `Array<int>`
        GET_SUB_PROCESS = 19,
        // isProcessWow64 `bool`
        GET_IS_PROCESS_WOW64 = 20,
        // getExecutableCwdList `Array<string>`
        GET_EXECUTABLE_CWD_LIST = 21,
        // sleep(ms);
        SEND_SLEEP = 22,
    };

    export type GET_PROCESS_LIST_COMMAND =
        ENV_INFO_COMMAND.GET_ENUM_PROCESSES_LIST |
        ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_DETAILS |
        ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_SNP |
        ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_NT |
        ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_PID_NAME |
        ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_NONE_NAME;

    export enum ENV_INFO_COMMAND {
        NONE = 0,
        // export function getRegistrQword(HKey: HKEY, SubKey: string, key: string | null): bigint | null;
        GET_REGISTR_QWORD = 70,
        // export function setRegistrQword(HKey: HKEY, SubKey: string, key: string | null, Qword: bigint | number): boolean;
        SET_REGISTR_QWORD = 71,
        // export function getRegistrDword(HKey: HKEY, SubKey: string, key: string | null): number | null;
        GET_REGISTR_DWORD = 72,
        // export function setRegistrDword(HKey: HKEY, SubKey: string, key: string | null, Dword: bigint | number): boolean;
        SET_REGISTR_DWORD = 73,
        // export function getRegistrString(HKey: HKEY, SubKey: string, key: string | null): string | null;
        GET_REGISTR_STRING = 74,
        // export function setRegistrString(HKey: HKEY, SubKey: string, key: string | null, String: string): boolean;
        SET_REGISTR_STRING = 75,
        // export function getRegistrKeys(HKey: HKEY, SubKey: string, key: string | null): chQueryFolderKey;
        GET_REGISTR_KEYS = 76,
        // export function getRegistrStringList(HKey: HKEY, SubKey: string, key: string | null): string[] | null;
        GET_REGISTR_STRING_LIST = 77,
        // export function setRegistrStringList(HKey: HKEY, SubKey: string, key: string | null, StringList?: string[]): boolean;
        SET_REGISTR_STRING_LIST = 78,
        // export function getRegistrBuffer(HKey: HKEY, SubKey: string, key: string | null): Buffer | null;
        GET_REGISTR_BUFFER = 79,
        // export function setRegistrBuffer(HKey: HKEY, SubKey: string, key: string | null, String: Buffer): boolean;
        SET_REGISTR_BUFFER = 710,
        // export function getRegistrValue(HKey: HKEY, SubKey: string, key: string | null): REG_VALUE | null;
        GET_REGISTR_VALUE = 711,
        // export function copyRegistrValue(HKey: HKEY, SourceSubKey: string, Sourcekey: string | null, NewSubKey: string, Newkey: string | null): boolean;
        COPY_REGISTR_VALUE = 712,
        // export function copyRegistrFolder(HKey: HKEY, SourceSubKey: string, NewSubKey: string): boolean;
        COPY_REGISTR_FOLDER = 713,
        // export function setRegistrValue(HKey: HKEY, SubKey: string, key: string | null, data: REG_VALUE): boolean;
        SET_REGISTR_VALUE = 714,
        // export function getRegistrValueStat(HKey: HKEY, SubKey: string, key: string | null): RegistrValueStat;
        GET_REGISTR_VALUE_STAT = 715,
        // export function getRegistrFolderStat(HKey: HKEY, SubKey: string, key: string | null): RegistrFolderStat;
        GET_REGISTR_FOLDER_STAT = 716,
        // export function clearRegistrValue(HKey: HKEY, SubKey: string, key: string | null): boolean;
        CLEAR_REGISTR_VALUE = 717,
        // export function clearRegistrFolder(HKey: HKEY, SubKey: string, key: string | null): boolean;
        CLEAR_REGISTR_FOLDER = 718,
        // export function removeRegistrValue(HKey: HKEY, SubKey: string, key: string | null): boolean;
        REMOVE_REGISTR_VALUE = 719,
        // export function removeRegistrFolder(HKey: HKEY, SubKey: string): boolean;
        REMOVE_REGISTR_FOLDER = 720,
        // export function removeRegistrFolderTree(HKey: HKEY, SubKey: string): boolean;
        REMOVE_REGISTR_FOLDER_TREE = 721,
        // export function createRegistrFolder(HKey: HKEY, SubKey: string): boolean;
        CREATE_REGISTR_FOLDER = 722,
        // export function createRegistrValueKey(HKey: HKEY, SubKey: string, key: string | string[]): boolean;
        CREATE_REGISTR_VALUE_KEY = 723,
        // export function hasRegistrKey(HKey: HKEY, SubKey: string, key: string | null): boolean;
        HAS_REGISTR_KEY = 724,
        // export function hasRegistrFolderKey(HKey: HKEY, SubKey: string): boolean;
        HAS_REGISTR_FOLDER_KEY = 725,
    };

    export namespace Usb {
        export type Volume = {
            // 卷的路径 如 F:\\
            path: string;
            // Volume名称 如 "\\\\?\\Volume{00000000-000000-000000-0000-000000}\\"
            name: string;
            // 内核驱动器名称 如 "\\Device\\HarddiskVolume6"
            device: string;
            // HarddiskVolume6
            device_id: string;
            // 00000000-000000-000000-0000-000000
            volume_id: string;
        };

    }

    export namespace Auto {

        export type MouseMovePoints = {
            // 坐标 x 左边到右边的距离(px)
            "x": number | null,
            // 坐标 y 顶边到底部的距离(px)
            "y": number | null,
            // 此任务的发生时间
            "time": number | null,
            // 预留数据
            "dwExtraInfo": number | null
        }

        export const chcpList = {
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

        export type SystemDecoderKey = keyof typeof chcpList;

        // 键盘四大功能键的状态
        export type BASIC_KEYS = {
            // shift 被按下
            shift: boolean;
            // alt 被按下
            alt: boolean;
            // ctrl 被按下
            ctrl: boolean;
            // win 被按下
            win: boolean;
        }

        export interface HMC_KEYBOARD_CLASS {
            initKeyboardEventHook(): boolean;
            isValidHookKeyboard(): false | number;
            getAllKeyboardEventJson(): `KeyboardEvent[]`;
            stopHookKeyboard(): boolean;
            hasKeysBasic(): BASIC_KEYS;
            hasKeyActivate(KeysEvent: number): boolean;
        }

        export interface HMC_MOUSE_CLASS {
            initMouseEventHook(): boolean;
            isValidHookMouse(): false | number;
            getMouseEventListJson(): string;
            stopHookMouse(): boolean;
            setShakeEventTime(ms: number): boolean;
            setLimitMouseRange(ms: number, x: number, y: number, right: number, bottom: number): boolean;
            hasLimitMouseRangeWorker(): boolean;
            stopLimitMouseRangeWorker(): boolean;
        }

        // 鼠标按钮变化
        export enum MouseKeyName {
            UNKNOWN = "unknown",
            // 左键按下
            WM_LBUTTONDOWN = "left-button-down",
            // 右键按下
            WM_RBUTTONDOWN = "right-button-down",
            // 左键释放
            WM_LBUTTONUP = "left-button-up",
            // 右键释放
            WM_RBUTTONUP = "right-button-up",
            // 中键按下
            WM_MBUTTONDOWN = "mouse-button-down",
            // 中键释放
            WM_MBUTTONUP = "mouse-button-up",
            // 滚轮向上
            WM_MOUSEWHEEL = "mouse-wheel",
            // 鼠标移动
            WM_MOUSEMOVE = "move"
        }

        export interface KeyboardEvent {
            /**事件id (每次结束时次记) */
            id: number;
            /**事件时间 */
            time: number;
            /**是否按下 */
            down: boolean;
            /**扩展键标志 */
            flags: number;
            /**键码 */
            keyCode: number;
            /**执行的设备id */
            scanCode: number;
            /**映射代码 例如 A 0 1 */
            key: string;
            /**映射代码 例如 KeyE , KeyA */
            code: string;
        }

        export type MouseEventButtonName = "left-mouse-button" | "right-mouse-button" | "middle-mouse-button" | null;

        // 鼠标按钮变化
        export enum MouseKey {
            WM_MOUSEMOVE = 512,
            // 左键按下
            WM_LBUTTONDOWN = 0x0201,
            // 右键按下
            WM_RBUTTONDOWN = 0x0204,
            // 左键释放
            WM_LBUTTONUP = 0x0202,
            // 右键释放
            WM_RBUTTONUP = 0x0205,
            // 中键按下
            WM_MBUTTONDOWN = 0x0207,
            // 中键释放
            WM_MBUTTONUP = 0x0208,
            // 滚轮
            WM_MOUSEWHEEL = 522,
        }

        export interface MouseNulEventItme {
            // 事件id (每次结束时次记)
            id: 0,
            // 事件时间
            time: 0
        }

        export interface MouseMoveEventItme {
            // 事件id (每次结束时次记)
            id: number;
            // 事件时间
            time: number;
            // 按键名称
            button: MouseKey.WM_MOUSEMOVE;
            // 坐标 左到右边
            x: number;
            // 坐标 顶部到底部
            y: number;
        }

        export interface MouseEventItme {
            // 事件id (每次结束时次记)
            id: number;
            // 事件时间
            time: number;
            // 按键名称
            name: MouseEventButtonName;
            // 当前按下的按钮
            button: MouseKey;
            // true 向上 false 向下
            buttonDown: boolean;
            // 滚轮步进数量 负数为向下
            wheelDelta: number;
        }

    }

    export namespace Clipboard {
        export type CLIP_HTML_INFO = {
            /**剪贴板中的 HTML 数据 */
            data: string;
            /**片段结束位置（HTML 内容的结束偏移量） */
            EndFragment: number;
            /**HTML 内容的结束偏移量 */
            EndHTML: number;
            /**数据是否有效（是否为有效的 HTML 剪贴板数据） */
            is_valid: boolean;
            /**源 URL（HTML 内容来源的 URL） */
            SourceURL: string;
            /**片段起始位置（HTML 内容的开始偏移量） */
            StartFragment: number;
            /** HTML 内容的开始偏移量 */
            StartHTML: number;
            /**剪贴板数据的版本号 */
            Version: number;
        }
    }


    export namespace Process {

        /**
         * （进程快照）PROCESSENTRY 结构体  它包含了进程的各种信息，如进程 ID、线程计数器、优先级等等
         */
        export type PROCESSENTRY = {
            /**结构体的大小，以字节为单位。 */
            dwSize: number;
            /**引用计数。 */
            cntUsage: number;
            /**进程 ID。 */
            th32ProcessID: number;
            /**默认堆 ID */
            th32DefaultHeapID: number;
            /**模块 ID */
            th32ModuleID: number;
            /**线程计数器。 */
            cntThreads: number;
            /** 父进程 ID。 */
            th32ParentProcessID: number;
            /**基本优先级。 */
            pcPriClassBase: number;
            /**标志位。 */
            dwFlags: number;
            /**进程名。 */
            szExeFile: string;

            // 以下是通过js扩展的

            /**进程名称 */
            name: string,
            /**进程id */
            pid: number;
        };

        export type PROCESSENTRY_DEFAULT = {
            /**进程名称 */
            name: string,
            /**进程id */
            pid: number;
            /**进程路径 */
            path: string;
        };

        export type PROCESSENTRY_NONE_NAME = {
            /**进程名称 */
            name: string | null,
            /**进程id */
            pid: number;
            /**进程路径 */
            path: null;
        };

        export interface PSYSTEM_PROCESS_INFORMATION {
            /**
             * 结构体实例的偏移量
             * - 这是无用的数据
             * - 下一个结构体实例的偏移量，用于遍历多个结构体。
             */
            NextEntryOffset: number;
            /**
             * 进程线程数量。
             */
            NumberOfThreads: number;
            /**进程的镜像名称 */
            ImageName: string;
            /**进程的基本优先级。 */
            BasePriority: number;
            /**进程的唯一标识符。(pid) */
            UniqueProcessId: number;
            /**进程的句柄数。 */
            HandleCount: number;
            /**进程所在的会话 ID。 */
            SessionId: number;
            /**进程的峰值虚拟内存大小。 */
            PeakVirtualSize: number;
            /**进程的虚拟内存大小。 */
            VirtualSize: number;
            /**进程的峰值工作集大小。 */
            PeakWorkingSetSize: number;
            /**进程的实际工作集大小。 */
            WorkingSetSize: number;
            /**
             * `分页池配额使用量`
             * - 分配给进程的分页池配额使用量。
             */
            QuotaPagedPoolUsage: number;
            /**
             * `非分页池内存大小`
             * - 分配给进程的非分页池配额使用量。非分页池是内核提供的内存池，用于驻留在物理内存中，并且不会被换出到磁盘页面文件。该字段表示进程当前使用的非分页池内存大小。
             */
            QuotaNonPagedPoolUsage: number;
            /**
             * `进程的页面文件使用量`
             * - 页面文件是用于交换进程数据的虚拟内存扩展，当物理内存不足时，部分数据会被交换到页面文件中以释放内存。 
             **/
            PagefileUsage: number;
            /**
             * `进程的峰值页面文件使用量`
             * - 进程的峰值页面文件使用量。这是进程在其生命周期内达到的最高页面文件使用量。
             */
            PeakPagefileUsage: number;
            /**
             *`进程的私有页计数`
             * - 私有页是进程专用的虚拟内存页面，不被其他进程共享。
             */
            PrivatePageCount: number;

            // 以下是通过js扩展的

            /**进程名称 */
            name: string,
            /**进程id */
            pid: number;
        }

        /**是一个结构体，它定义在 `tlhelp32.h` 头文件中。它描述了在系统执行快照时正在执行的线程列表中的条目*/
        export type THREADENTRY32 = {
            /**线程使用计数 */
            cntUsage: number,
            /**保留，不再使用 */
            dwFlags: 0,
            /**结构体的大小，以字节为单位 */
            dwSize: number,
            /**创建线程的进程标识符 */
            th32OwnerProcessID: number,
            /**线程标识符，与 `CreateProcess` 函数返回的线程标识符兼容 */
            th32ThreadID: number,
            /**分配给线程的内核基优先级 */
            tpBasePri: number,
            /**线程优先级相对于基本优先级的增量 */
            tpDeltaPri: number
        }

        export enum GET_PROCESS_NAME_TYPE {
            // 查找所有名字
            GET_AII = 1,
            // 使用内核法查找
            GET_NT = 2,
            // 获取进程快照的名字
            GET_SNP = 3,
            // 找到时就停下 [默认]
            GET_FIND = 5,
            // 找模块名
            GET_MODE = 7,
            // 默认 找到时就停下 
            GET_DEFAULT = 0,
            // 即便是从可执行文件中路径获取文件名也行
            GET_FILE_NAME = 8
        };
    }

    export namespace Shell {

        // 快捷方式的信息
        export interface SHORTCUT_LINK {
            /** 工作环境文件夹**/
            cwd: string;
            /** 进程图标(例如来自1.dll)**/
            icon: string;
            /**图标索引位置 */
            iconIndex: number;
            /** 描述**/
            desc: string;
            /** 启动命令**/
            args: string;
            /** 启动属性**/
            showCmd: number;
            /** hotkey**/
            hotkey: number;
            /** 目标路径**/
            path: string;
        }

        export interface HMC_SHELL_STARTUP_CLASS {
            has: (keyName: string) => boolean;
            hasOnce: (keyName: string) => boolean;
            remove: (keyName: string) => boolean;
            removeOnce: (keyName: string) => boolean;
            set: (keyName: string, path: string, cmd: string) => boolean;
            setOnce: (keyName: string, path: string, cmd: string) => boolean;
        }

        export interface HMC_SHELL_CLASS {
            trashFile?: (trash_path: string, is_Recycle: boolean, isShow: boolean) => boolean;
            clearTrash?: (root_path: string, isShow: boolean) => boolean;
            copyFile?: (filePath: string, newFilePath: string, isShowConfirm: boolean, isShow: boolean, isShowProgress: boolean) => boolean;
            moveFile?: (filePath: string, newFilePath: string, isShowConfirm: boolean, isShow: boolean, isShowProgress: boolean) => boolean;
            showContextMenu?: (hwnd: number | null, file: string | string[], x: number, y: number) => boolean;
        }

        export enum LINK_TYPE_INFO {
            /**硬链接*/
            HARD_LINK_FILE = 170,
            /**软链接*/
            SOFT_LINK_FILE = 168,
            /**目录软链接*/
            SOFT_LINK_DIR = 166,
            /**目录链接点*/
            SYMBOLIC_LINK_DIR = 172,
            /**是个未知的类型 */
            UNKNOWN = 0
        };

        export type Link_TYPE_NAME = keyof typeof LINK_TYPE_INFO;

        export type LINK_FOR_FILE = {
            "isdir": boolean,
            "path": null,
            "size": 0,
            "type": "UNKNOWN",
            "valid": false
        };

        export type LINK_FOR_DIR = {
            "isdir": boolean,
            "path": null,
            "size": 0,
            "type": "UNKNOWN",
            "valid": false
        };

        export type LINK_FOR_SYMBOLIC_LINK_DIR = {
            "isdir": true,
            "path": string | null,
            "size": 1,
            "type": "SYMBOLIC_LINK_DIR",
            "valid": true
        };

        export type LINK_FOR_LINK_DIR = {
            "isdir": true,
            "path": string | null,
            "size": 1,
            "type": "SOFT_LINK_DIR",
            "valid": true
        };

        export type LINK_FOR_SOFT_LINK_FILER = {
            "isdir": false,
            "path": string | null,
            "size": 1,
            "type": "SOFT_LINK_FILE",
            "valid": true
        };

        export type LINK_FOR_HARD_LINK_FILER = {
            "isdir": false,
            "path": string | null,
            "size": number,
            "type": "HARD_LINK_FILE",
            "valid": true,
            "volume": null | Usb.Volume
        };

        export type LINK_TARGET = LINK_FOR_FILE | LINK_FOR_DIR | LINK_FOR_SYMBOLIC_LINK_DIR | LINK_FOR_LINK_DIR | LINK_FOR_SOFT_LINK_FILER | LINK_FOR_HARD_LINK_FILER;

        export interface FileAttributesStat {
            // 文件属性 的源位运算值
            attributes: number;
            // 其中包含的值 运算值 列表
            list: FILE_ATTRIBUTE_INFO_LIST[];
        };

        export enum FS_MK_LINK_TARGET_TYPE {
            /**
             * 文件夹链接
             */
            CREATE_DIR_SYMLINK = 166,
            /**
             * 软链接
             */
            CREATE_SYMLINK = 168,
            /**
             * 硬链接
             */
            CREATE_HARD_LINK = 170,
            /**
             * 目录连接点
             */
            CREATE_JUNCTION_POINT_LINK = 172
        }

        export enum LINK_TYPE {
            /**硬链接*/
            HARD_LINK_FILE = 170,
            /**软链接*/
            SOFT_LINK_FILE = 168,
            /**目录软链接*/
            SOFT_LINK_DIR = 166,
            /**目录链接点*/
            JUNCTION_POINT_DIR = 172,
            /**是个未知的类型 */
            UNKNOWN = 0
        };

        export interface LINK_TYPE_EQ {
            // 类型id
            type: LINK_TYPE;
            // 类型名称
            type_name: keyof typeof LINK_TYPE;
            // 是否是基于文件夹
            isDir: boolean;
        }

        export enum FILE_ATTRIBUTE_INFO_LIST {
            /** 文件是只读的 */
            FILE_ATTRIBUTE_READONLY = 0x00000001,

            /** 文件是隐藏的 */
            FILE_ATTRIBUTE_HIDDEN = 0x00000002,

            /** 文件是系统文件 */
            FILE_ATTRIBUTE_SYSTEM = 0x00000004,

            /** 文件是一个目录 */
            FILE_ATTRIBUTE_DIRECTORY = 0x00000010,

            /** 文件将被备份或归档 */
            FILE_ATTRIBUTE_ARCHIVE = 0x00000020,

            /** 保留，不用于文件 */
            FILE_ATTRIBUTE_DEVICE = 0x00000040,

            /** 文件没有其他属性集 */
            FILE_ATTRIBUTE_NORMAL = 0x00000080,

            /** 文件用于临时存储，尽快删除 */
            FILE_ATTRIBUTE_TEMPORARY = 0x00000100,

            /** 文件是稀疏文件，节省磁盘空间 */
            FILE_ATTRIBUTE_SPARSE_FILE = 0x00000200,

            /** 文件或目录具有重解析点 */
            FILE_ATTRIBUTE_REPARSE_POINT = 0x00000400,

            /** 文件或目录是压缩的 */
            FILE_ATTRIBUTE_COMPRESSED = 0x00000800,

            /** 文件的数据没有立即可用 */
            FILE_ATTRIBUTE_OFFLINE = 0x00001000,

            /** 文件或目录不被内容索引 */
            FILE_ATTRIBUTE_NOT_CONTENT_INDEXED = 0x00002000,

            /** 文件或目录是加密的 */
            FILE_ATTRIBUTE_ENCRYPTED = 0x00004000,

            /** 保留，供未来使用 */
            FILE_ATTRIBUTE_VIRTUAL = 0x00010000,

            /** 文件包含完整性流 */
            FILE_ATTRIBUTE_INTEGRITY_STREAM = 0x00008000,

            /** 文件禁止自动数据擦除功能 */
            FILE_ATTRIBUTE_NO_SCRUB_DATA = 0x00020000,

            /** 文件包含扩展属性 (EA) */
            FILE_ATTRIBUTE_EA = 0x00040000,

            /** 文件为固定文件 */
            FILE_ATTRIBUTE_PINNED = 0x00080000,

            /** 文件为未固定文件 */
            FILE_ATTRIBUTE_UNPINNED = 0x00100000
        }

        // 托盘图标信息
        export interface TRAY_ICON {
            // 可执行文件路径
            path: string;
            // 停留时显示的文本
            info: string;
            // 句柄
            handle: number;
        }
    }

    export namespace Registr {

        /**注册表根目录 */
        export const Hkey = {
            /**用作默认用户首选设置|也作为单个用户的首选设置 */
            HKEY_CURRENT_CONFIG: "HKEY_CURRENT_CONFIG" as "HKEY_CURRENT_CONFIG",
            /**用作默认用户首选设置|也作为单个用户的首选设置 */
            HKEY_USERS: "HKEY_USERS" as "HKEY_USERS",
            /**是与文档类型和 OLE\COM 相关的信息的支持键。这个键是 */
            HKEY_CLASSES_ROOT: "HKEY_CLASSES_ROOT" as "HKEY_CLASSES_ROOT",
            /**包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息 */
            HKEY_LOCAL_MACHINE: "HKEY_LOCAL_MACHINE" as "HKEY_LOCAL_MACHINE",
            /**管理系统当前的用户信息 */
            HKEY_CURRENT_USER: "HKEY_CURRENT_USER" as "HKEY_CURRENT_USER",
        };

        // 注册表根目录
        export type HKEY = keyof typeof Hkey;

        /**
         * 注册表格式类型
         */
        export enum REG_TYPE {
            /** 没有值 */
            REG_NONE = 0,

            /** 以空字符结尾的字符串 */
            REG_SZ = 1,

            /** 可扩展的字符串（例如环境变量） */
            REG_EXPAND_SZ = 2,

            /** 原始的二进制数据 */
            REG_BINARY = 3,

            /** 32位数字，使用小端字节序 */
            REG_DWORD = 4,

            /** 32位数字，使用小端字节序（与 REG_DWORD 相同） */
            REG_DWORD_LITTLE_ENDIAN = 4,

            /** 32位数字，使用大端字节序 */
            REG_DWORD_BIG_ENDIAN = 5,

            /** 符号链接，使用 Unicode 编码 */
            REG_LINK = 6,

            /** 多个以空字符结尾的 Unicode 字符串 */
            REG_MULTI_SZ = 7,

            /** 资源列表，存储在资源映射中 */
            REG_RESOURCE_LIST = 8,

            /** 硬件描述中的资源列表 */
            REG_FULL_RESOURCE_DESCRIPTOR = 9,

            /** 资源需求列表 */
            REG_RESOURCE_REQUIREMENTS_LIST = 10,

            /** 64位数字，使用小端字节序 */
            REG_QWORD = 11,

            /** 64位数字，使用小端字节序（与 REG_QWORD 相同） */
            REG_QWORD_LITTLE_ENDIAN = 11,
        }

        export type RegistrValueStat = {
            /**此值的类型 */
            type: REG_TYPE;
            /**内容大小 */
            size: number;
            /**此内容是否存在 */
            exists: boolean;
            /**类型 格式文本化*/
            type_name: REG_VALUE_TYPE_NAME;
        };


        export interface REG_SZ_VALUE {
            type: 1;
            typeName: "REG_SZ";
            data: string;
            size: number;
        }

        export interface REG_EXPAND_SZ_VALUE {
            type: REG_TYPE.REG_EXPAND_SZ;
            typeName: "REG_EXPAND_SZ";
            data: string;
            dataExpand: string;
            size: number;
        }

        export interface REG_DWORD_VALUE {
            type: REG_TYPE.REG_DWORD | REG_TYPE.REG_DWORD_BIG_ENDIAN | REG_TYPE.REG_DWORD_LITTLE_ENDIAN;
            typeName: "REG_DWORD" | "REG_DWORD_BIG_ENDIAN" | "REG_DWORD_LITTLE_ENDIAN";
            data: number;
            size: number;
        }

        export interface REG_QWORD_VALUE {
            type: REG_TYPE.REG_QWORD | REG_TYPE.REG_QWORD_LITTLE_ENDIAN;
            typeName: "REG_QWORD" | "REG_QWORD_LITTLE_ENDIAN";
            data: bigint;
            size: number;
        }

        export interface REG_BINARY_VALUE {
            type: REG_TYPE.REG_BINARY;
            typeName: "REG_BINARY";
            data: Buffer;
            size: number;
        }

        export interface REG_MULTI_SZ_VALUE {
            type: REG_TYPE.REG_MULTI_SZ;
            typeName: "REG_MULTI_SZ";
            data: string[];
            size: number;
        }

        export interface REG_NONE_VALUE {
            type: REG_TYPE.REG_NONE;
            typeName: "REG_NONE";
            data: null;
            size: number;
        }

        export interface REG_ANY_VALUE {
            type: REG_TYPE.REG_FULL_RESOURCE_DESCRIPTOR | REG_TYPE.REG_LINK | REG_TYPE.REG_NONE | REG_TYPE.REG_RESOURCE_LIST | REG_TYPE.REG_RESOURCE_REQUIREMENTS_LIST;
            typeName: "REG_FULL_RESOURCE_DESCRIPTOR" | "REG_LINK" | "REG_RESOURCE_LIST" | "REG_RESOURCE_REQUIREMENTS_LIST";
            data: Buffer;
            size: number;
        }

        export type REG_VALUE = REG_SZ_VALUE | REG_EXPAND_SZ_VALUE | REG_DWORD_VALUE | REG_QWORD_VALUE | REG_BINARY_VALUE | REG_MULTI_SZ_VALUE | REG_ANY_VALUE;

        export type REG_VALUE_DATA_TYPE = REG_SZ_VALUE["data"] | REG_EXPAND_SZ_VALUE["data"] | REG_DWORD_VALUE["data"] | REG_QWORD_VALUE["data"] | REG_BINARY_VALUE["data"] | REG_MULTI_SZ_VALUE["data"] | REG_ANY_VALUE["data"];

        export type REG_VALUE_TYPE_NAME = `${keyof typeof REG_TYPE}`;//"REG_RESOURCE_REQUIREMENTS_LIST"|"REG_FULL_RESOURCE_DESCRIPTOR"|"REG_RESOURCE_LIST"|"REG_MULTI_SZ"|"REG_LINK"|"REG_QWORD"|"REG_DWORD"|"REG_BINARY"|"REG_EXPAND_SZ"|"REG_SZ"|"REG_NONE";

        export type chQueryValueKeyItem = {
            /**名称 */
            name: string;
            /**类型 */
            type: number;
            /**类型 格式文本化*/
            type_name: REG_VALUE_TYPE_NAME;
            /**大小 */
            size: number;
        };

        export type chQueryFolderKeyItem = {
            /**名称 */
            name: string;
            /**上次修订时间 */
            time: number;
        };

        export type chQueryFolderInfo = {
            /**目录键列表 */
            folderKeyList: chQueryFolderKeyItem[];
            /**值键列表 */
            valueKeyList: chQueryValueKeyItem[];
            /**此内容是否存在 */
            exists: boolean;
            /**大小 */
            size: number;
            /**目录键数量 */
            folderSize: number;
            /**该目录下有多少个值键 */
            keySize: number;
            /**该目录上次写入的时间戳 毫秒 */
            time: number;
            /**该目录下最大的值键的内容大小 */
            maxValueDataSize: number;
        };

    }

    export namespace Net {
        // ? net
        export interface ipv4Item {
            /**
             * @brief 广播地址，表示当前子网的广播 IP
             * @example "192.168.1.255"
             */
            broadcast: string;

            /**
             * @brief 子网掩码，用于确定 IP 地址的网络部分和主机部分
             * @example "255.255.255.0"
             */
            netmask: string;

            /**
             * @brief IPv4 地址的字符串表示
             * @example "192.168.1.1"
             */
            ipaddress: string;
        }

        export enum network_type {
            /**
             * @brief 未指定的地址族
             */
            AF_UNSPEC = 0,

            /**
             * @brief Unix 本地到本地的通信协议
             */
            AF_UNIX = 1,

            /**
             * @brief IPv4 协议族
             */
            AF_INET = 2,

            /**
             * @brief ARPANET IMP 协议族
             */
            AF_IMPLINK = 3,

            /**
             * @brief PUP 网络协议
             */
            AF_PUP = 4,

            /**
             * @brief CHAOS 网络协议
             */
            AF_CHAOS = 5,

            /**
             * @brief Xerox NS 协议族
             */
            AF_NS = 6,

            /**
             * @brief IPX 协议族 (Novell 网络)
             */
            AF_IPX = 6,

            /**
             * @brief ISO 协议族
             */
            AF_ISO = 7,

            /**
             * @brief OSI 协议族
             */
            AF_OSI = 7,

            /**
             * @brief ECMA 标准协议族
             */
            AF_ECMA = 8,

            /**
             * @brief Datakit 协议族
             */
            AF_DATAKIT = 9,

            /**
             * @brief CCITT 协议族
             */
            AF_CCITT = 10,

            /**
             * @brief SNA 协议族
             */
            AF_SNA = 11,

            /**
             * @brief DECnet 协议族 (Digital Equipment Corporation 网络)
             */
            AF_DECnet = 12,

            /**
             * @brief Direct Link Interface 协议
             */
            AF_DLI = 13,

            /**
             * @brief LAT 协议 (Local Area Transport)
             */
            AF_LAT = 14,

            /**
             * @brief Hylink 协议族
             */
            AF_HYLINK = 15,

            /**
             * @brief AppleTalk 协议族
             */
            AF_APPLETALK = 16,

            /**
             * @brief NetBIOS 协议族
             */
            AF_NETBIOS = 17,

            /**
             * @brief VoiceView 协议
             */
            AF_VOICEVIEW = 18,

            /**
             * @brief Firefox 协议族
             */
            AF_FIREFOX = 19,

            /**
             * @brief 未知的协议类型 1
             */
            AF_UNKNOWN1 = 20,

            /**
             * @brief BAN 协议族
             */
            AF_BAN = 21,

            /**
             * @brief ATM 协议族 (异步传输模式)
             */
            AF_ATM = 22,

            /**
             * @brief IPv6 协议族
             */
            AF_INET6 = 23,

            /**
             * @brief Windows Cluster 协议族
             */
            AF_CLUSTER = 24,

            /**
             * @brief 12844 标准协议族
             */
            AF_12844 = 25,

            /**
             * @brief IrDA (红外数据协议)
             */
            AF_IRDA = 26,

            /**
             * @brief NetDES 协议族
             */
            AF_NETDES = 28
        }

        export interface hmc_addr_item {
            /**
             * @brief IP 地址的字符串表示
             * - IPv4 示例: "192.168.1.1"
             * - IPv6 示例: "fe80::1ff:fe23:4567:890a"
             * @example "192.168.1.1"
             */
            ipaddress: string;

            /**
             * @brief IP 地址类型名称
             * - "IPv4": 使用 IPv4 协议的地址
             * - "IPv6": 使用 IPv6 协议的地址
             * @example "IPv4"
             */
            typeName: "IPv4" | "IPv6";

            /**
             * @brief 网络类型 (根据具体定义，可能为枚举或其他类型)
             */
            type: network_type;
        }

        export interface hmc_net_addr_item {
            name: string;
            addr_item: hmc_addr_item;
        }

        export interface ConnectNet {
            /**
             * @brief 网络连接类型名称
             * - "UDP": 用户数据报协议
             * - "TCP": 传输控制协议
             * - "TCP6": 基于 IPv6 的传输控制协议
             * - "UDP6": 基于 IPv6 的用户数据报协议
             * @example "TCP"
             */
            typeName: "UDP" | "TCP" | "TCP6" | "UDP6";

            /**
             * @brief 网络连接类型值
             * - 6: TCP / TCP6
             * - 17: UDP / UDP6
             * @example 6
             */
            type: number;

            /**
             * @brief 本地 IP 地址 (DWORD 格式)
             * @example 3232235777
             */
            ipAddr: number;

            /**
             * @brief 解析后的本地 IP 地址 (字符串格式)
             * @example "192.168.1.1"
             */
            ip: string;

            /**
             * @brief 本地端口
             * @example 8080
             */
            port: number;

            /**
             * @brief 绑定端口的进程 ID
             * @example 1234
             */
            pid: number;

            /**
             * @brief 此进程是否存在
             * @example true
             */
            existsProcess: boolean;
        }

        export interface ConnectNetTCP extends ConnectNet {
            /**
             * @brief 远程端口
             * @example 80
             */
            remotePort: number;

            /**
             * @brief 远程 IP 地址 (DWORD 格式)
             * @example 3232235777
             */
            remoteIPAddr: number;

            /**
             * @brief 解析后的远程 IP 地址 (字符串格式)
             * @example "8.8.8.8"
             */
            remoteIP: string;

            /**
             * @brief TCP 连接状态
             * - "CLOSED": 连接关闭
             * - "LISTEN": 监听状态
             * - "SYN-SENT": 同步请求已发送
             * - "SYN-RECEIVED": 同步请求已接收
             * - "ESTABLISHED": 连接已建立
             * - "FIN-WAIT-1": 终止等待 1
             * - "FIN-WAIT-2": 终止等待 2
             * - "CLOSE-WAIT": 关闭等待
             * - "CLOSING": 正在关闭
             * - "LAST-ACK": 最后确认
             * - "TIME-WAIT": 时间等待
             * - "DELETE-TCB": 删除 TCB
             * - "UNKNOWN": 未知状态
             * @example "ESTABLISHED"
             */
            state: "CLOSED" | "LISTEN" | "SYN-SENT" | "SYN-RECEIVED" | "ESTABLISHED" | "FIN-WAIT-1" | "FIN-WAIT-2" | "CLOSE-WAIT" | "CLOSING" | "LAST-ACK" | "TIME-WAIT" | "DELETE-TCB" | "UNKNOWN";
        }

        export interface hmc_NetParams {
            /**
             * @brief 主机名称
             * @example "host123"
             */
            hostName: string;

            /**
             * @brief 域名
             * @example "example.com"
             */
            domainName: string;

            /**
             * @brief DNS 服务器地址列表
             * @example ["8.8.8.8", "8.8.4.4"]
             */
            dnsServers: string[];

            /**
             * @brief 节点类型
             * - BROADCAST_NODETYPE
             * - HYBRID_NODETYPE
             * - MIXED_NODETYPE
             * - PEER_TO_PEER_NODETYPE
             * - UNKNOWN:<UINT>
             * @example "BROADCAST_NODETYPE"
             */
            nodeType: `UNKNOWN:<${number}>` | "BROADCAST_NODETYPE" | "HYBRID_NODETYPE" | "MIXED_NODETYPE" | "PEER_TO_PEER_NODETYPE";

            /**
             * @brief DHCP 范围名称
             * @example "MyScope"
             */
            dhcpScopeName: string;

            /**
             * @brief 是否启用路由功能
             * @example true
             */
            enableRouting: boolean;

            /**
             * @brief 是否启用 ARP 代理
             * @example false
             */
            enableArpProxy: boolean;

            /**
             * @brief 是否启用 DNS
             * @example true
             */
            enableDns: boolean;
        }
    }


    // *************** Usb ***********************************
    export type Volume = Usb.Volume;

    // *************** Auto ***********************************
    export type BASIC_KEYS = Auto.BASIC_KEYS;
    export type HMC_KEYBOARD_CLASS = Auto.HMC_KEYBOARD_CLASS;
    export type HMC_MOUSE_CLASS = Auto.HMC_MOUSE_CLASS;
    export type MouseKeyName = Auto.MouseKeyName;
    export type KeyboardEvent = Auto.KeyboardEvent;
    export type MouseEventButtonName = Auto.MouseEventButtonName;
    export type MouseKey = Auto.MouseKey;
    export type MouseNulEventItme = Auto.MouseNulEventItme;
    export type MouseMoveEventItme = Auto.MouseMoveEventItme;
    export type MouseEventItme = Auto.MouseEventItme;
    export type MouseMovePoints = Auto.MouseMovePoints;

    // *************** Clipboard ***********************************
    export type CLIP_HTML_INFO = Clipboard.CLIP_HTML_INFO;

    // *************** Process ***********************************
    export type PROCESSENTRY = Process.PROCESSENTRY;
    export type PROCESSENTRY_DEFAULT = Process.PROCESSENTRY_DEFAULT;
    export type PROCESSENTRY_NONE_NAME = Process.PROCESSENTRY_NONE_NAME;
    export type PSYSTEM_PROCESS_INFORMATION = Process.PSYSTEM_PROCESS_INFORMATION;
    export type THREADENTRY32 = Process.THREADENTRY32;

    // *************** Shell ***********************************
    export type SHORTCUT_LINK = Shell.SHORTCUT_LINK;
    export type HMC_SHELL_STARTUP_CLASS = Shell.HMC_SHELL_STARTUP_CLASS;
    export type HMC_SHELL_CLASS = Shell.HMC_SHELL_CLASS;
    export type LINK_TYPE_INFO = Shell.LINK_TYPE_INFO;
    export type Link_TYPE_NAME = Shell.Link_TYPE_NAME;
    export type LINK_FOR_FILE = Shell.LINK_FOR_FILE;
    export type LINK_FOR_DIR = Shell.LINK_FOR_DIR;
    export type LINK_FOR_SYMBOLIC_LINK_DIR = Shell.LINK_FOR_SYMBOLIC_LINK_DIR;
    export type LINK_FOR_LINK_DIR = Shell.LINK_FOR_LINK_DIR;
    export type LINK_FOR_SOFT_LINK_FILER = Shell.LINK_FOR_SOFT_LINK_FILER;
    export type LINK_FOR_HARD_LINK_FILER = Shell.LINK_FOR_HARD_LINK_FILER;
    export type LINK_TARGET = Shell.LINK_TARGET;
    export type FileAttributesStat = Shell.FileAttributesStat;
    export type FS_MK_LINK_TARGET_TYPE = Shell.FS_MK_LINK_TARGET_TYPE;
    export type LINK_TYPE = Shell.LINK_TYPE;
    export type LINK_TYPE_EQ = Shell.LINK_TYPE_EQ;
    export type FILE_ATTRIBUTE_INFO_LIST = Shell.FILE_ATTRIBUTE_INFO_LIST;
    export type TRAY_ICON = Shell.TRAY_ICON;

    // *************** Registr ***********************************
    export type HKEY = Registr.HKEY;
    export type REG_TYPE = Registr.REG_TYPE;
    export type RegistrValueStat = Registr.RegistrValueStat;
    export type REG_SZ_VALUE = Registr.REG_SZ_VALUE;
    export type REG_EXPAND_SZ_VALUE = Registr.REG_EXPAND_SZ_VALUE;
    export type REG_DWORD_VALUE = Registr.REG_DWORD_VALUE;
    export type REG_QWORD_VALUE = Registr.REG_QWORD_VALUE;
    export type REG_BINARY_VALUE = Registr.REG_BINARY_VALUE;
    export type REG_MULTI_SZ_VALUE = Registr.REG_MULTI_SZ_VALUE;
    export type REG_NONE_VALUE = Registr.REG_NONE_VALUE;
    export type REG_ANY_VALUE = Registr.REG_ANY_VALUE;
    export type REG_VALUE = Registr.REG_VALUE;
    export type REG_VALUE_DATA_TYPE = Registr.REG_VALUE_DATA_TYPE;
    export type REG_VALUE_TYPE_NAME = Registr.REG_VALUE_TYPE_NAME;
    export type chQueryValueKeyItem = Registr.chQueryValueKeyItem;
    export type chQueryFolderKeyItem = Registr.chQueryFolderKeyItem;
    export type chQueryFolderInfo = Registr.chQueryFolderInfo;


    /**注册表根目录 */
    export const Hkey = Registr.Hkey;


    // *************** Net ***********************************

    export type ipv4Item = Net.ipv4Item;
    export type network_type = Net.network_type;
    export type hmc_addr_item = Net.hmc_addr_item;
    export type hmc_net_addr_item = Net.hmc_net_addr_item;
    export type ConnectNet = Net.ConnectNet;
    export type ConnectNetTCP = Net.ConnectNetTCP;
    export type hmc_NetParams = Net.hmc_NetParams;

}
