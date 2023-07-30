export let KeyboardcodeComparisonTable: Map<string,VK_VirtualKey> =new Map();

export const KeyboardVKcodeComparisonEmenList: Array<[VK_key, VK_code | null, VK_keyCode, VK_VirtualKey] | [VK_key, VK_code | null, VK_keyCode, VK_VirtualKey, VK_Nickname]> = [
    ["Escape", null, 27, 0x1b, ["esc"]],
    ["F1", null, 112, 0x70],
];

function installKeyboardcodeComparisonTable(){
    KeyboardcodeEmenList.forEach(function(value,key){
        if(value.length == 5){
            if(value[4])for (let index = 0; index < value[4].length; index++) {
                const of_value = value[4][index];
                KeyboardcodeComparisonTable.set(of_value.toUpperCase(),key);
            }
        }
        if(typeof value[0] =="string"){
            KeyboardcodeComparisonTable.set(value[0].toUpperCase(),key);
        }
        if(typeof value[1] =="string"){
            KeyboardcodeComparisonTable.set(value[1].toUpperCase(),key);
        }
    });
}

/**
 * 格式化键值码
 * @param key 
 * @returns 
 */
export function vkKey(key: any): number | null {
    if (typeof key == "number") return key;
    if (typeof key == "string") {
        key = key.toUpperCase();
        if(!KeyboardcodeComparisonTable.size)installKeyboardcodeComparisonTable();
        if(KeyboardcodeComparisonTable?.has(key)){
            return KeyboardcodeComparisonTable.get(key)||null;
        }
    }
    return null;
}

export const KeyboardVKcodeEmenList: Array<[VK_key, VK_code | null, VK_keyCode, VK_VirtualKey] | [VK_key, VK_code | null, VK_keyCode, VK_VirtualKey, VK_Nickname]> = [
    // key ,code , keyCode , VirtualKey
    ["0", "Digit0", 48, 0x30],
    ["1", "Digit1", 49, 0x31],
    ["2", "Digit2", 50, 0x32],
    ["3", "Digit3", 51, 0x33],
    ["4", "Digit4", 52, 0x34],
    ["5", "Digit5", 53, 0x35],
    ["6", "Digit6", 54, 0x36],
    ["7", "Digit7", 55, 0x37],
    ["8", "Digit8", 56, 0x38],
    ["9", "Digit9", 57, 0x39],
    ["A", "KeyA", 65, 0x41],
    ["B", "KeyB", 66, 0x42],
    ["C", "KeyC", 67, 0x43],
    ["D", "KeyD", 68, 0x44],
    ["E", "KeyE", 69, 0x45],
    ["F", "KeyF", 70, 0x46],
    ["G", "KeyG", 71, 0x47],
    ["H", "KeyH", 72, 0x48],
    ["I", "KeyI", 73, 0x49],
    ["J", "KeyJ", 74, 0x4a],
    ["K", "KeyK", 75, 0x4b],
    ["L", "KeyL", 76, 0x4c],
    ["M", "KeyM", 77, 0x4d],
    ["N", "KeyN", 78, 0x4e],
    ["O", "KeyO", 79, 0x4f],
    ["P", "KeyP", 80, 0x50],
    ["Q", "KeyQ", 81, 0x51],
    ["R", "KeyR", 82, 0x52],
    ["S", "KeyS", 83, 0x53],
    ["T", "KeyT", 84, 0x54],
    ["U", "KeyU", 85, 0x55],
    ["V", "KeyV", 86, 0x56],
    ["W", "KeyW", 87, 0x57],
    ["X", "KeyX", 88, 0x58],
    ["Y", "KeyY", 89, 0x59],
    ["Z", "KeyZ", 90, 0x5a],
    ["0", "Numpad0", 96, 0x60],
    ["1", "Numpad1", 97, 0x61],
    ["2", "Numpad2", 98, 0x62],
    ["3", "Numpad3", 99, 0x63],
    ["4", "Numpad4", 100, 0x64],
    ["5", "Numpad5", 101, 0x65],
    ["6", "Numpad6", 102, 0x66],
    ["7", "Numpad7", 103, 0x67],
    ["8", "Numpad8", 104, 0x68],
    ["9", "Numpad9", 105, 0x69],
    ["Alt", "Alt", 18, 0x12],
    ["Alt", "AltLeft", 164, 0xa4],
    ["Alt", "AltRight", 165, 0xa5],
    ["CapsLock", "CapsLock", 20, 0x14],
    ["Control", "Control", 17, 0x11, ["ctrl"]],
    ["Control", "ControlLeft", 162, 0xa2, ["ctrl"]],
    ["Control", "ControlRight", 163, 0xa3, ["ctrl"]],
    ["Win", "MetaLeft", 91, 0x5b],
    ["Win", "MetaRight", 92, 0x5c],
    ["NumLock", "NumLock", 144, 0x90],
    ["ScrollLock", null, 145, 0x91],
    ["Shift", "Shift", 16, 0x10],
    ["Shift", "ShiftLeft", 160, 0xa0],
    ["Shift", "ShiftRight", 161, 0xa1],
    ["Enter", "Enter", 13, 13, ["\r\n", "\r", "\n"]],
    ["Tab", "Tab", 9, 0x09],
    ["Space", "Space", 32, 0x20],
    ["ArrowDown", null, 40, 0x28],
    ["ArrowLeft", null, 37, 0x25],
    ["ArrowRight", null, 39, 0x27],
    ["ArrowUp", null, 38, 0x26],
    ["End", "End", 35, 0x23],
    ["Home", "Home", 36, 0x24],
    ["PageDown", null, 34, 0x22],
    ["PageUp", null, 33, 0x21],
    ["Backspace", null, 8, 0x08],
    ["Clear", null, 12, 0x0C],
    ["Clear", null, 254, 0xfe],
    ["CrSel", null, 247, 0xf7],
    ["Delete", null, 46, 0x2e],
    ["EraseEof", null, 249, 0xf9],
    ["ExSel", null, 248, 0xf8],
    ["Insert", null, 45, 0x2d],
    ["Accept", null, 30, 0x1e],
    ["ContextMenu", null, 93, 0x5d],
    ["Escape", null, 27, 0x1b, ["esc"]],
    ["Execute", null, 43, 0x2b],
    ["Finish", null, 241, 0xf1],
    ["Help", null, 47, 0x2f],
    ["Pause", null, 19, 0x13],
    ["Play", null, 250, 0xfa],
    ["Select", null, 41, 0x29],
    ["PrintScreen", null, 44, 0x2c],
    ["Standby", null, 95, 0x5f],
    ["Alphanumeric", null, 240, 0xf0],
    ["Convert", null, 28, 0x1c],
    ["FinalMode", null, 24, 0x18],
    ["ModeChange", null, 31, 0x1f],
    ["NonConvert", null, 29, 0x1d],
    ["Process", null, 229, 0xe5],
    ["HangulMode", null, 21, 0x15],
    ["HanjaMode", null, 25, 0x19],
    ["JunjaMode", null, 23, 0x17],
    ["Hankaku", null, 243, 0xf3],
    ["Hiragana", null, 242, 0xf2],
    ["KanaMode", null, 246, 0xf6],
    ["Romaji", null, 245, 0xf5],
    ["Zenkaku", null, 244, 0xf4],
    ["F1", null, 112, 0x70],
    ["F2", null, 113, 0x71],
    ["F3", null, 114, 0x72],
    ["F4", null, 115, 0x73],
    ["F5", null, 116, 0x74],
    ["F6", null, 117, 0x75],
    ["F7", null, 118, 0x76],
    ["F8", null, 119, 0x77],
    ["F9", null, 120, 0x78],
    ["F10", null, 121, 0x79],
    ["F11", null, 122, 0x7a],
    ["F12", null, 123, 0x7b],
    ["F13", null, 124, 0x7c],
    ["F14", null, 125, 0x7d],
    ["F15", null, 126, 0x7e],
    ["F16", null, 127, 0x7f],
    ["F17", null, 128, 0x80],
    ["F18", null, 129, 0x81],
    ["F19", null, 130, 0x82],
    ["F20", null, 131, 0x83],
    ["MediaPlayPause", null, 179, 0xb3],
    ["MediaStop", null, 178, 0xb2],
    ["MediaTrackNext", null, 176, 0xb0],
    ["MediaTrackPrevious", null, 177, 0xb1],
    ["AudioVolumeDown", null, 174, 0xae],
    ["AudioVolumeMute", null, 173, 0xad],
    ["AudioVolumeUp", null, 175, 0xaf],
    ["ZoomToggle", null, 251, 0xfb],
    ["LaunchMail", null, 180, 0xb4],
    ["LaunchMediaPlayer", null, 181, 0xb5],
    ["LaunchApplication1", null, 182, 0xb6],
    ["LaunchApplication2", null, 183, 0xb7],
    ["BrowserBack", null, 166, 0xa6],
    ["BrowserFavorites", null, 171, 0xab],
    ["BrowserForward", null, 167, 0xa7],
    ["BrowserHome", null, 172, 0xac],
    ["BrowserRefresh", null, 168, 0xa8],
    ["BrowserSearch", null, 170, 0xaa],
    ["BrowserStop", null, 169, 0xa9],
    [".", "NumpadDecimal", 110, 0x6e],
    ["*", "NumpadMultiply", 106, 0x6a],
    ["+", "NumpadAdd", 107, 0x6b],
    ["/", "NumpadDivide", 111, 0x6f],
    ["-", "NumpadSubtract", 109, 0x6d],
    ["Separator", null, 108, 0x6c],
    [";", "Semicolon", 186, 0xba],
    ["+", "Equal", 187, 0xbb],
    [",", "Comma", 188, 0xbc],
    ["-", "Minus", 189, 0xbd],
    [".", "Period", 190, 0xbe],
    ["/", "Slash", 191, 0xbf],
    ["`", "Backquote", 192, 0xc0],
    ["[", "BracketLeft", 219, 0xdb],
    ["\\", "Backslash", 220, 0xdc],
    ["]", "BracketLeft", 221, 0xdd],
    ["'", "Quote", 222, 0xde],
    ["Win", "MetaLeft", 91, 0x5B],
    ["Win", "MetaRight", 92, 0x5C]
];
export type VK_key = string
export type VK_code = string
export type VK_keyCode = number
export type VK_VirtualKey = number
export type VK_Nickname = string[] | undefined;


export const KeyboardcodeEmenList: Map<VK_VirtualKey, typeof KeyboardVKcodeEmenList[0]> = (() => {
    let data = new Map();
    for (let index = 0; index < KeyboardVKcodeEmenList.length; index++) {
        const [VK_key, VK_code, VK_keyCode, VK_VirtualKey, VK_Nickname] = KeyboardVKcodeEmenList[index];
        data.set(VK_VirtualKey, KeyboardVKcodeEmenList[index]);
    }
    return data
})();

