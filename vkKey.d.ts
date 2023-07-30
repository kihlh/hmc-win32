export declare let KeyboardcodeComparisonTable: Map<string, VK_VirtualKey>;
export declare const KeyboardVKcodeComparisonEmenList: Array<[VK_key, VK_code | null, VK_keyCode, VK_VirtualKey] | [VK_key, VK_code | null, VK_keyCode, VK_VirtualKey, VK_Nickname]>;
/**
 * 格式化键值码
 * @param key
 * @returns
 */
export declare function vkKey(key: any): number | null;
export declare const KeyboardVKcodeEmenList: Array<[VK_key, VK_code | null, VK_keyCode, VK_VirtualKey] | [VK_key, VK_code | null, VK_keyCode, VK_VirtualKey, VK_Nickname]>;
export type VK_key = string;
export type VK_code = string;
export type VK_keyCode = number;
export type VK_VirtualKey = number;
export type VK_Nickname = string[] | undefined;
export declare const KeyboardcodeEmenList: Map<VK_VirtualKey, typeof KeyboardVKcodeEmenList[0]>;
