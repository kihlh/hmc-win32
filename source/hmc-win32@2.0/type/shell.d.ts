import main = require("./index");
declare class StartupConstructor {
    constructor();
    has(keyName: string): boolean;
    hasOnce(keyName: string): boolean;
    remove(keyName: string): boolean;
    removeOnce(keyName: string): boolean;
    set(keyName: string, path: string, cmd?: string): boolean;
    setOnce(keyName: string, path: string, cmd?: string): boolean;
    enum2(): Promise<{
        [key: string]: string | null;
    }>;
    enum2Sync(): {
        [key: string]: string | null;
    };
    enumOnce2(): Promise<{
        [key: string]: string | null;
    }>;
    enumOnce2Sync(): {
        [key: string]: string | null;
    };
    keys2(): Promise<string[]>;
    keys2Sync(): string[];
    keysOnce2(): Promise<string[]>;
    keysOnce2Sync(): string[];
}
export declare namespace Shell {
    /**
     * 启动项 管理
     */
    const Startup: StartupConstructor;
    /**
        * 弹出右键菜单的接口
        * @param hwnd 调用窗口 / 允许为null
        * @param file 指定需要被显示菜单的文件/文件夹/文件列表/ 为空 "" 为驱动器
        * @param x 坐标 x+y=0的时候将会从鼠标所在的地方显示
        * @param y 坐标
        */
    function showContextMenu(hwnd?: number | null, file?: string | string[], x?: number, y?: number): boolean;
    /**
     * 获取托盘图标列表
     * 1.4.6 起返回json文本
     * ? win11 在22621.1000版本之后失效 具体原因查看https://github.com/kihlh/hmc-win32/issues/36
     */
    function getTrayList2(): Promise<main.HMC2_MODE.TRAY_ICON[]>;
    /**
     * 获取托盘图标列表
     * 1.4.6 起返回json文本
     * ? win11 在22621.1000版本之后失效 具体原因查看https://github.com/kihlh/hmc-win32/issues/36
     */
    function getTrayList2Sync(): main.HMC2_MODE.TRAY_ICON[];
    /**
      * 删除文件到垃圾桶
      * @param trash_path 处理的路径
      * @param is_Recycle 可以回收
      * @param isShow 显示窗口
      */
    function trashFile(trash_path: string, is_Recycle: boolean, isShow: boolean): boolean;
    /**
     * 清空回收站
     * @param root_path 文件或者根目录
     * @param isShow 是否显示窗口
    */
    function clearTrash(root_path: string, isShow: boolean): boolean;
    /**
     *
     * @param filePath
     * @param newFilePath
     * @param isShowConfirm
     * @param isShow
     * @param isShowProgress
     * @param trash_ok
     * @returns
     */
    function copyFile(filePath: string, newFilePath: string, isShowConfirm: boolean, isShow: boolean, isShowProgress: boolean): boolean;
    /**
     *
     * @param filePath
     * @param newFilePath
     * @param isShowConfirm
     * @param isShow
     * @param isShowProgress
     * @param trash_ok
     * @returns
     */
    function moveFile(filePath: string, newFilePath: string, isShowConfirm: boolean, isShow: boolean, isShowProgress: boolean): boolean;
    /**
     * 截图为Bmp 文件/Buffer
     */
    const captureBmp2: {
        (handle: number): Promise<Buffer | null>;
        (handle: number, path: string): Promise<boolean>;
        (path: string, handle: number): Promise<boolean>;
        (path: string): Promise<boolean>;
        (): Promise<Buffer | null>;
        (x: number, y: number, nScopeWidth: number, nScopeHeight: number): Promise<Buffer | null>;
        (path: string, x: number, y: number, nScopeWidth: number, nScopeHeight: number): Promise<boolean>;
        (x: number, y: number, nScopeWidth: number, nScopeHeight: number, path: string): Promise<boolean>;
    };
    /**
    * 截图为Bmp 文件/Buffer
    */
    const captureBmp2Sync: {
        (handle: number): Buffer | null;
        (handle: number, path: string): boolean;
        (path: string, handle: number): boolean;
        (path: string): boolean;
        (): Buffer | null;
        (x: number, y: number, nScopeWidth: number, nScopeHeight: number): Buffer | null;
        (path: string, x: number, y: number, nScopeWidth: number, nScopeHeight: number): boolean;
        (x: number, y: number, nScopeWidth: number, nScopeHeight: number, path: string): boolean;
    };
    const getThumbnailPng2: {
        (filePath: string, output: string, img_size: number): Promise<boolean | null>;
        (filePath: string, output: string): Promise<boolean | null>;
        (filePath: string, img_size: number): Promise<Buffer | null>;
        (filePath: string): Promise<Buffer | null>;
        (filePath: string, output?: string | undefined, img_size?: number | undefined): Promise<unknown>;
    };
    const getThumbnailPng2Sync: {
        (filePath: string, output: string, img_size: number): boolean | null;
        (filePath: string, output: string): boolean | null;
        (filePath: string, img_size: number): Buffer | null;
        (filePath: string): Buffer | null;
        (filePath: string, output?: string | undefined, img_size?: number | undefined): unknown;
    };
    const getFileIcon2: {
        (filePath: string, output: string, img_size: number): Promise<boolean | null>;
        (filePath: string, output: string): Promise<boolean | null>;
        (filePath: string, img_size: number): Promise<Buffer | null>;
        (filePath: string): Promise<Buffer | null>;
        (filePath: string, output?: string | undefined, img_size?: number | undefined): Promise<unknown>;
    };
    const getFileIcon2Sync: {
        (filePath: string, output: string, img_size: number): boolean | null;
        (filePath: string, output: string): boolean | null;
        (filePath: string, img_size: number): Buffer | null;
        (filePath: string): Buffer | null;
        (filePath: string, output?: string | undefined, img_size?: number | undefined): unknown;
    };
    module Symlink {
        /**
         * 判断所有链接类型
         * - 适用 -> [文件]硬链接
         * - 适用 -> [文件]符号连接
         * - 适用 -> [文件夹]符号连接
         * - 适用 -> [文件夹]文件夹连接点
         * @param targetPath 目标路径
         * @returns
         */
        function hasLink2(targetPath: string): Promise<boolean>;
        /**
         * 判断所有链接类型
         * - 适用 -> [文件]硬链接
         * - 适用 -> [文件]符号连接
         * - 适用 -> [文件夹]符号连接
         * - 适用 -> [文件夹]文件夹连接点
         * @param targetPath 目标路径
         * @returns
         */
        function hasLink2Sync(targetPath: string): boolean;
        /**
         * 判断软硬链接类型
         * - 适用 -> [文件]硬链接
         * - 适用 -> [文件]符号连接
         * - 适用 -> [文件夹]符号连接
         * - 适用 -> [文件夹]文件夹连接点
         *
         * @param Path2
         * @returns
         */
        function getLinkType2(targetPath: string): Promise<main.HMC2_MODE.LINK_TYPE_EQ | null>;
        /**
         * 判断软硬链接类型
         * - 适用 -> [文件]硬链接
         * - 适用 -> [文件]符号连接
         * - 适用 -> [文件夹]符号连接
         * - 适用 -> [文件夹]文件夹连接点
         *
         * @param Path2
         * @returns
         */
        function getLinkType2Sync(targetPath: string): main.HMC2_MODE.LINK_TYPE_EQ | null;
        /**
         * 获取 软链接/ 硬链接 指向的路径
         * @param targetPath 目标路径
         */
        function getLinkPath2(targetPath: string): Promise<string | string[] | null>;
        /**
         * 获取 软链接/ 硬链接 指向的路径
         * @param targetPath 目标路径
         */
        function getLinkPath2Sync(targetPath: string): string | string[] | null;
        /**
         * 判断是否是符号链接
         * @example 适用 -> [文件]符号连接
         * @example 适用 -> [文件夹]符号连接
         * @example 适用 -> [文件夹]文件夹符号链接
         * @param targetPath 目标路径
         */
        function hasFileSymbolicLink2(targetPath: string): Promise<boolean>;
        /**
         * 判断是否是符号链接
         * @example 适用 -> [文件]符号连接
         * @example 适用 -> [文件夹]符号连接
         * @example 适用 -> [文件夹]文件夹符号链接
         * @param targetPath 目标路径
         */
        function hasFileSymbolicLink2Sync(targetPath: string): boolean;
        /**
         * 判断是否是硬链接
         * @example 仅适用 -> [文件]硬链接
         * @param targetPath 目标路径
         */
        function hasFileHardLink2(targetPath: string): Promise<boolean>;
        /**
         * 判断是否是硬链接
         * @example 仅适用 -> [文件]硬链接
         * @param targetPath 目标路径
         */
        function hasFileHardLink2Sync(targetPath: string): boolean;
        /**
         * 判断是否是文件夹符号链接
         * @example 适用 -> [文件夹]符号连接
         * @param targetPath 目标路径
         */
        function hasDirSymbolicLink2(targetPath: string): Promise<boolean>;
        /**
         * 判断是否是文件夹符号链接
         * @example 适用 -> [文件夹]符号连接
         * @param targetPath 目标路径
         */
        function hasDirSymbolicLink2Sync(targetPath: string): boolean;
        /**
         * 判断是否是 文件夹链接连接点
         * @example 仅适用 -> [文件夹]文件夹连接点
         * @param targetPath 目标路径
         */
        function hasDirJunctionPoint2(targetPath: string): Promise<boolean>;
        /**
         * 判断是否是 文件夹链接连接点
         * @example 仅适用 -> [文件夹]文件夹连接点
         * @param targetPath 目标路径
         */
        function hasDirJunctionPoint2Sync(targetPath: string): boolean;
        /**
         * 创建链接
         * @param targetType 创建类型
         * - CREATE_HARD_LINK -> [文件]硬链接
         * - CREATE_SYMLINK -> [文件]符号连接
         * - CREATE_DIR_SYMLINK -> [文件夹]符号连接
         * - CREATE_JUNCTION_POINT_LINK -> [文件夹]目录连接点
         * @param targetPath 目标路径
         * @param sourcePath 原始文件路径
         * @returns
         */
        function createLink(targetType: main.HMC2_MODE.FS_MK_LINK_TARGET_TYPE, targetPath: string, sourcePath: string): Promise<boolean>;
        /**
         * 创建链接
         * @param targetType 创建类型
         * - CREATE_HARD_LINK -> [文件]硬链接
         * - CREATE_SYMLINK -> [文件]符号连接
         * - CREATE_DIR_SYMLINK -> [文件夹]符号连接
         * - CREATE_JUNCTION_POINT_LINK -> [文件夹]目录连接点
         * @param targetPath 目标路径
         * @param sourcePath 原始文件路径
         * @returns
         */
        function createLinkSync(targetType: main.HMC2_MODE.FS_MK_LINK_TARGET_TYPE, targetPath: string, sourcePath: string): boolean;
        /**
         * 创建目录连接点
         * @param targetPath 目标路径
         * @param sourcePath 原始文件路径
         * @returns
         */
        function createDirJunctionPoint2(targetPath: string, sourcePath: string): Promise<boolean>;
        /**
         * 创建目录连接点
         * @param targetPath 目标路径
         * @param sourcePath 原始文件路径
         * @returns
         */
        function createDirJunctionPoint2Sync(targetPath: string, sourcePath: string): boolean;
        /**
         * 创建硬链接
         * @param targetPath 目标路径
         * @param sourcePath 原始文件路径
         * @returns
         */
        function createHardLink2(targetPath: string, sourcePath: string): Promise<boolean>;
        /**
         * 创建硬链接
         * @param targetPath 目标路径
         * @param sourcePath 原始文件路径
         * @returns
         */
        function createHardLink2Sync(targetPath: string, sourcePath: string): boolean;
        /**
         * 创建软链接
         * - 适用 -> [文件]符号连接
         * - 适用 -> [文件夹]符号连接
         * @param targetPath 目标路径
         * @param sourcePath 原始文件路径
         * @returns
         */
        function createSymlink2(targetPath: string, sourcePath: string): Promise<boolean>;
        /**
         * 创建软链接
         * - 适用 -> [文件]符号连接
         * - 适用 -> [文件夹]符号连接
         * @param targetPath 目标路径
         * @param sourcePath 原始文件路径
         * @returns
         */
        function createSymlink2Sync(targetPath: string, sourcePath: string): boolean;
        /**
         * 创建目录符号链接
         * @param targetPath 目标路径
         * @param sourcePath 原始文件路径
         * @returns
         */
        function createDirSymlink2(targetPath: string, sourcePath: string): Promise<boolean>;
        /**
         * 创建目录符号链接
         * @param targetPath 目标路径
         * @param sourcePath 原始文件路径
         * @returns
         */
        function createDirSymlink2Sync(targetPath: string, sourcePath: string): boolean;
    }
    /**
     * 检索指定文件或目录的文件系统属性
     * @param targetPath 指定文件或目录
     * @returns
     */
    function getFileAttributes2(targetPath: string): Promise<main.HMC2_MODE.FileAttributesStat | null>;
    /**
     * 检索指定文件或目录的文件系统属性
     * @param targetPath 指定文件或目录
     * @returns
     */
    function getFileAttributes2Sync(targetPath: string): main.HMC2_MODE.FileAttributesStat | null;
    /**
     * 设置文件夹图标
     * @param targetPath 目标 文件/目录 路径
     * @param iconPath 图标路径
     * - .exe 可执行文件
     * - .ico 图标文件
     * - .png 图片文件
     * - *.* 任意文件
     * @param iconIndex 图标索引 比如exe中的0 默认是0
     * @returns
     */
    function setFolderIcon2(targetPath: string, iconPath: string, iconIndex?: number): Promise<boolean>;
    /**
     * 设置文件夹图标
     * @param targetPath 目标 文件/目录 路径
     * @param iconPath 图标路径
     * - .exe 可执行文件
     * - .ico 图标文件
     * - .png 图片文件
     * - *.* 任意文件
     * @param iconIndex 图标索引 比如exe中的0 默认是0
     * @returns
     */
    function setFolderIcon2Sync(targetPath: string, iconPath: string, iconIndex?: number): boolean;
    /**
     * 设置指定扩展名的 图标
     * @param extensionName 扩展名
     * @example .mp3 , .cpp , .js
     * @param typeName 类型名字 比如 HMC打包的音频文件扩展
     * @param iconPath 图标路径
     * - .exe 可执行文件
     * - .ico 图标文件
     * - .png 图片文件
     * - *.* 任意文件
     * @param iconIndex 图标索引 比如exe中的0 默认是0
     * @returns
     */
    function setExtensionIcon2(extensionName: string, typeName: string, iconPath: string, iconIndex?: number): Promise<boolean>;
    /**
     * 设置指定扩展名的 图标
     * @param extensionName 扩展名
     * @example .mp3 , .cpp , .js
     * @param typeName 类型名字 比如 HMC打包的音频文件扩展
     * @param iconPath 图标路径
     * - .exe 可执行文件
     * - .ico 图标文件
     * - .png 图片文件
     * - *.* 任意文件
     * @param iconIndex 图标索引 比如exe中的0 默认是0
     * @returns
     */
    function setExtensionIcon2Sync(extensionName: string, typeName: string, iconPath: string, iconIndex: number): boolean;
    /**
     * 设置url 启动协议 比如 vscode:// 启动应用vscode
     * @param protocolName 协议名 不能带有只允许字母与数字
     * @param appPath 应用路径
     * @param command 启动命令 默认 %1
     * @returns
     */
    function setAppURLProtocol2Sync(protocolName: string, appPath: string, command?: string | string[]): boolean;
    /**
     * 设置url 启动协议 比如 vscode:// 启动应用vscode
     * @param protocolName 协议名 不能带有只允许字母与数字
     * @param appPath 应用路径
     * @param command 启动命令 默认 %1
     * @returns
     */
    function setAppURLProtocol2(protocolName: string, appPath: string, command?: string | string[]): Promise<boolean>;
    /**
     * 查询 快捷方式 目标路径 及 详细信息
     * @param targetPath 快捷方式路径
     * @param QueryDetaile 是否查询详细信息
     */
    function getShortcutLink2(targetPath: string, QueryDetaile: true): Promise<main.HMC2_MODE.SHORTCUT_LINK | null>;
    /**
     * 查询 快捷方式 目标路径 [仅路径]
     * @param targetPath 快捷方式路径
     * @param QueryDetaile 是否查询详细信息
     */
    function getShortcutLink2(targetPath: string, QueryDetaile: false): Promise<string | null>;
    /**
     * 查询 快捷方式 目标路径 [仅路径]
     * @param targetPath 快捷方式路径
     */
    function getShortcutLink2(targetPath: string): Promise<main.HMC2_MODE.SHORTCUT_LINK | null>;
    /**
     * 查询 快捷方式 目标路径 及 详细信息
     * @param targetPath 快捷方式路径
     * @param QueryDetaile 是否查询详细信息
     */
    function getShortcutLink2Sync(targetPath: string, QueryDetaile: true): main.HMC2_MODE.SHORTCUT_LINK | null;
    /**
     * 查询 快捷方式 目标路径 [仅路径]
     * @param targetPath 快捷方式路径
     */
    function getShortcutLink2Sync(targetPath: string, QueryDetaile: false): string | null;
    /**
     * 查询 快捷方式 目标路径 [仅路径]
     * @param targetPath 快捷方式路径
     * @param QueryDetaile 是否查询详细信息
     */
    function getShortcutLink2Sync(targetPath: string): main.HMC2_MODE.SHORTCUT_LINK | null;
    /**
     * 设置快捷方式
     * @param targetPath 快捷方式存放路径
     * @param FilePath 文件路径
     * @param work_dir 工作目录
     * @param desc 详情
     * @param args 命令行
     * @param iShowCmd 启动时显示的内容
     * @param icon 图标位置
     * @param iconIndex 图标索引 默认0
     * @returns
     */
    function setShortcutLink2(targetPath: string, FilePath: string, work_dir?: string, desc?: string, args?: string, iShowCmd?: number, icon?: string, iconIndex?: number): Promise<boolean>;
    /**
     * 将指定文件夹移动到回收站
     * @param trash_path 待回收文件
     * @param is_Recycle 是否可以撤回
     * @param isShow 是否显示窗口
     * @returns
     */
    function trashFile2(trash_path: string, is_Recycle?: boolean, isShow?: boolean): Promise<boolean>;
    /**
     * 清空回收站
     * @param trash_path 盘符 / 全部
     * @param isShow 是否显示窗口
     * @returns
     */
    function clearTrash2(root_path?: string, isShow?: boolean): Promise<boolean>;
    /**
     * 复制文件到指定位置
     * @param filePath 源文件地址
     * @param newFilePath 新的文件地址
     * @param isShowConfirm 是否显示确认窗口（比如文件已存在）
     * @param isShow 是否显示过程窗口
     * @param isShowProgress 是否显示进度条(启用时 isShow 必须为true)
     * @returns
     */
    function copyFile2(filePath: string, newFilePath: string, isShowConfirm?: boolean, isShow?: boolean, isShowProgress?: boolean): Promise<boolean>;
    /**
     * 移动文件到指定位置
     * @param filePath 源文件地址
     * @param newFilePath 新的文件地址
     * @param isShowConfirm 是否显示确认窗口（比如文件已存在）
     * @param isShow 是否显示过程窗口
     * @param isShowProgress 是否显示进度条(启用时 isShow 必须为true)
     * @returns
     */
    function moveFile2(filePath: string, newFilePath: string, isShowConfirm?: boolean, isShow?: boolean, isShowProgress?: boolean): Promise<boolean>;
    /**
     * 设置快捷方式
     * @param targetPath 快捷方式存放路径
     * @param FilePath 文件路径
     * @param work_dir 工作目录
     * @param desc 详情
     * @param args 命令行
     * @param iShowCmd 启动时显示的内容
     * @param icon 图标位置
     * @param iconIndex 图标索引 默认0
     * @returns
     */
    function setShortcutLink2Sync(targetPath: string, FilePath: string, work_dir?: string, desc?: string, args?: string, iShowCmd?: number, icon?: string, iconIndex?: number): boolean;
    /**
     * 将指定文件夹移动到回收站
     * @param trash_path 待回收文件
     * @param is_Recycle 是否可以撤回
     * @param isShow 是否显示窗口
     * @returns
     */
    function trashFile2Sync(trash_path: string, is_Recycle?: boolean, isShow?: boolean): boolean;
    /**
     * 清空回收站
     * @param trash_path 盘符 / 全部
     * @param isShow 是否显示窗口
     * @returns
     */
    function clearTrash2Sync(root_path?: string, isShow?: boolean): boolean;
    /**
     * 复制文件到指定位置
     * @param filePath 源文件地址
     * @param newFilePath 新的文件地址
     * @param isShowConfirm 是否显示确认窗口（比如文件已存在）
     * @param isShow 是否显示过程窗口
     * @param isShowProgress 是否显示进度条(启用时 isShow 必须为true)
     * @returns
     */
    function copyFile2Sync(filePath: string, newFilePath: string, isShowConfirm?: boolean, isShow?: boolean, isShowProgress?: boolean): boolean;
    /**
     * 移动文件到指定位置
     * @param filePath 源文件地址
     * @param newFilePath 新的文件地址
     * @param isShowConfirm 是否显示确认窗口（比如文件已存在）
     * @param isShow 是否显示过程窗口
     * @param isShowProgress 是否显示进度条(启用时 isShow 必须为true)
     * @returns
     */
    function moveFile2Sync(filePath: string, newFilePath: string, isShowConfirm?: boolean, isShow?: boolean, isShowProgress?: boolean): boolean;
    const HMC_GetShellEnvInfo: {
        async: Partial<Record<"getLinkTarget2" | "getFileAttributes2" | "getVolumeList2" | "formatVolumePath2" | "formatVolumeName2" | "formatVolumeNtName2" | "getLinkPath2" | "hasFileSymbolicLink2" | "hasFileHardLink2" | "hasDirSymbolicLink2" | "hasDirJunctionPoint2" | "getLinkType2" | "createLink" | "createDirJunctionPoint2" | "createHardLink2" | "createSymlink2" | "createDirSymlink2" | "setFolderIcon2" | "setExtensionIcon2" | "setAppURLProtocol2" | "getShortcutLink2" | "trashFile2" | "clearTrash2" | "copyFile2" | "moveFile2" | "setShortcutLink2", (...arg: any[]) => Promise<any>>>;
        sync: Partial<Record<"getLinkTarget2" | "getFileAttributes2" | "getVolumeList2" | "formatVolumePath2" | "formatVolumeName2" | "formatVolumeNtName2" | "getLinkPath2" | "hasFileSymbolicLink2" | "hasFileHardLink2" | "hasDirSymbolicLink2" | "hasDirJunctionPoint2" | "getLinkType2" | "createLink" | "createDirJunctionPoint2" | "createHardLink2" | "createSymlink2" | "createDirSymlink2" | "setFolderIcon2" | "setExtensionIcon2" | "setAppURLProtocol2" | "getShortcutLink2" | "trashFile2" | "clearTrash2" | "copyFile2" | "moveFile2" | "setShortcutLink2", (...arg: any[]) => any>>;
        getLinkTarget2(targetPath: string): Promise<main.HMC2_MODE.LINK_TARGET | null>;
        getLinkTarget2Sync(targetPath: string): main.HMC2_MODE.LINK_TARGET | null;
        getFileAttributes2(targetPath: string): Promise<main.HMC2_MODE.FileAttributesStat | null>;
        getFileAttributes2Sync(targetPath: string): main.HMC2_MODE.FileAttributesStat | null;
        getVolumeList2(): Promise<main.HMC2_MODE.Volume[] | null>;
        getVolumeList2Sync(): main.HMC2_MODE.Volume[] | null;
        formatVolumePath2(Path2: string): Promise<string | null>;
        formatVolumePath2Sync(Path2: string): string | null;
        formatVolumeName2(Path2: string): Promise<string | null>;
        formatVolumeName2Sync(Path2: string): string | null;
        formatVolumeNtName2(Path2: string): Promise<string | null>;
        formatVolumeNtName2Sync(Path2: string): string | null;
        getLinkType2(targetPath: string): Promise<main.HMC2_MODE.LINK_TYPE_EQ | null>;
        getLinkType2Sync(targetPath: string): main.HMC2_MODE.LINK_TYPE_EQ | null;
        getLinkPath2(targetPath: string): Promise<string | string[] | null>;
        getLinkPath2Sync(targetPath: string): string | string[] | null;
        hasFileSymbolicLink2(targetPath: string): Promise<boolean>;
        /**
         * 截图为Bmp 文件/Buffer
         */
        hasFileSymbolicLink2Sync(targetPath: string): boolean;
        hasFileHardLink2(targetPath: string): Promise<boolean>;
        hasFileHardLink2Sync(targetPath: string): boolean;
        hasDirSymbolicLink2(targetPath: string): Promise<boolean>;
        hasDirSymbolicLink2Sync(targetPath: string): boolean;
        hasDirJunctionPoint2(targetPath: string): Promise<boolean>;
        hasDirJunctionPoint2Sync(targetPath: string): boolean;
        createLink(targetType: main.HMC2_MODE.FS_MK_LINK_TARGET_TYPE, targetPath: string, sourcePath: string): Promise<boolean>;
        createLinkSync(targetType: main.HMC2_MODE.FS_MK_LINK_TARGET_TYPE, targetPath: string, sourcePath: string): boolean;
        createDirJunctionPoint2(targetPath: string, sourcePath: string): Promise<boolean>;
        createDirJunctionPoint2Sync(targetPath: string, sourcePath: string): boolean; /**
         * 判断软硬链接类型
         * - 适用 -> [文件]硬链接
         * - 适用 -> [文件]符号连接
         * - 适用 -> [文件夹]符号连接
         * - 适用 -> [文件夹]文件夹连接点
         *
         * @param Path2
         * @returns
         */
        createHardLink2(targetPath: string, sourcePath: string): Promise<boolean>;
        createHardLink2Sync(targetPath: string, sourcePath: string): boolean;
        createSymlink2(targetPath: string, sourcePath: string): Promise<boolean>;
        createSymlink2Sync(targetPath: string, sourcePath: string): boolean;
        createDirSymlink2(targetPath: string, sourcePath: string): Promise<boolean>;
        createDirSymlink2Sync(targetPath: string, sourcePath: string): boolean;
        setFolderIcon2(targetPath: string, iconPath: string, iconIndex: number): Promise<boolean>;
        setFolderIcon2Sync(targetPath: string, iconPath: string, iconIndex: number): boolean;
        setExtensionIcon2(extensionName: string, typeName: string, iconPath: string, iconIndex: number): Promise<boolean>;
        setExtensionIcon2Sync(extensionName: string, typeName: string, iconPath: string, iconIndex: number): boolean;
        setAppURLProtocol2(protocolName: string, appPath: string, command: string): Promise<boolean>;
        setAppURLProtocol2Sync(protocolName: string, appPath: string, command: string): boolean;
        getShortcutLink2(targetPath: string, QueryDetaile?: boolean | undefined): Promise<main.HMC2_MODE.SHORTCUT_LINK | null>;
        getShortcutLink2Sync(targetPath: string, QueryDetaile?: boolean | undefined): main.HMC2_MODE.SHORTCUT_LINK | null;
        setShortcutLink2(targetPath: string, FilePath: string, work_dir: string, desc: string, args: string, iShowCmd: number, icon: string, iconIndex: number): Promise<boolean>;
        trashFile2(trash_path: string, is_Recycle: boolean, isShow: boolean): Promise<boolean>;
        clearTrash2(root_path: string, isShow: boolean): Promise<boolean>;
        copyFile2(filePath: string, newFilePath: string, isShowConfirm: boolean, isShow: boolean, isShowProgress: boolean): Promise<boolean>;
        moveFile2(filePath: string, newFilePath: string, isShowConfirm: boolean, isShow: boolean, isShowProgress: boolean): Promise<boolean>;
        setShortcutLink2Sync(targetPath: string, FilePath: string, work_dir: string, desc: string, args: string, iShowCmd: number, icon: string, iconIndex: number): boolean;
        trashFile2Sync(trash_path: string, is_Recycle: boolean, isShow: boolean): boolean;
        clearTrash2Sync(root_path: string, isShow: boolean): boolean;
        copyFile2Sync(filePath: string, newFilePath: string, isShowConfirm: boolean, isShow: boolean, isShowProgress: boolean): boolean;
        moveFile2Sync(filePath: string, newFilePath: string, isShowConfirm: boolean, isShow: boolean, isShowProgress: boolean): boolean;
    };
}
export {};
