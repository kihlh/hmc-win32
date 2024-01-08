/// <reference types="node" />
import { HMC } from "../../";
export interface Native {
    /**
     * 设置注册表值 （提供了初级和低级操作）
     * @param Hive 根目录
     * @param folderPath 目录路径
     * @param keyName 值键
     * @param data 数据体
     * - null 设置空值
     * - string 约 2^31 - 1 个字符 (2GB) 但是不建议存储过大数据 会出问题
     * - number DWORD 标准范围约为 0(0x0) 到 4294967295(0xffffffff) (即 2^32 - 1)
     * - bigint QWORD 标准范围约为  0n(0x0) 到 18446744073709551615n (0xffffffffffffffff)（即 2^64 - 1）
     * - boolean 布尔 以DWORD状态存储 范围 0-1
     * - Buffer 二进制  1024KB 以内
     * - Date 时间戳 以浮点二进制存储
     * - string[] 文本数组 REG_MULTI_SZ格式 允许存储空文本但是不建议 (因为非标准) 但是数组末尾的元素是空文本会被清空
     * @param type 类型
     * - true 文本时将转义到转义类型
     * - HMC.REG_TYPE 强制转义 仅限二进制类型
     */
    setRegistrValue(Hive: HMC.HKEY, folderPath: string, keyName: string | null, data: null | number | bigint | boolean | Buffer | Date | string | string[], type: undefined | boolean | HMC.REG_TYPE): boolean;
}
/**
 * 设置注册表值
 * @param Hive 根目录
 * @param folderPath 目录路径
 * @param keyName 值键
 * @param data 数据体
 * @param is_expand 是否让其可以被自动转义 例如 %temp%/123 -> c:.../temp/123
 */
export declare function setRegistrValue(Hive: HMC.HKEY, folderPath: string, keyName: string | null, data: string, is_expand?: boolean): boolean;
/**
 * 设置注册表值
 * @param Hive 根目录
 * @param folderPath 目录路径
 * @param keyName 值键
 * @param data 数据体
 * @param to_type 转义类型 详见 HMC.REG_TYPE https://learn.microsoft.com/zh-cn/windows/win32/sysinfo/registry-value-types
 */
export declare function setRegistrValue(Hive: HMC.HKEY, folderPath: string, keyName: string | null, data: Buffer, to_type?: HMC.REG_TYPE): boolean;
/**
 * 设置注册表值
 * @param Hive 根目录
 * @param folderPath 目录路径
 * @param keyName 值键
 */
export declare function setRegistrValue(Hive: HMC.HKEY, folderPath: string, keyName: string | null): boolean;
/**
 * 设置注册表值 文本数组
 * - REG_MULTI_SZ格式
 * ? 允许存储空文本但是不建议 (因为非标准) 但是数组末尾的元素是空文本会被清空
 * @param Hive 根目录
 * @param folderPath 目录路径
 * @param keyName 值键
 */
export declare function setRegistrValue(Hive: HMC.HKEY, folderPath: string, keyName: string, data: string[]): boolean;
/**
 * 设置注册表值
 * @param Hive 根目录
 * @param folderPath 目录路径
 * @param keyName 值键
 * @param data 数据体
 * - number DWORD 标准范围约为 0(0x0) 到 4294967295(0xffffffff) (即 2^32 - 1)
 * - bigint QWORD 标准范围约为  0n(0x0) 到 18446744073709551615n (0xffffffffffffffff)（即 2^64 - 1）
 * - boolean 布尔 以DWORD状态存储 范围 0-1
 * - Buffer 二进制  1024KB 以内
 * - Date 时间戳 以浮点二进制存储
 */
export declare function setRegistrValue(Hive: HMC.HKEY, folderPath: string, keyName: string | null, data: number | bigint | boolean | Date): boolean;
