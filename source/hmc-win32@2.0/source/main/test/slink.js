var PATH_LSIT = {
    "文件_硬链接": ("F:\\MagicPockets\\version.dll2"),
    "文件_符号连接文件": ("F:\\MagicPockets\\2566.dll"),
    "文件_普通": ("F:\\MagicPockets\\HM神奇口袋.exe"),
    "文件夹链接点": ("F:\\MagicPockets\\11111"),
    "文件夹符号": ("F:\\MagicPockets\\lib - 符号连接"),
    "文件夹": ("F:\\MagicPockets\\swiftshader")
};
var PATH_KEY_TYPE_LIST = Object.keys(PATH_LSIT);
var FUN_NAME_LIST = ["hasFsLink2", "hasHardLink2", "hasSymbolicDirLink2", "hasDirLink2"];
var data = new Map();
for (var index = 0; index < PATH_KEY_TYPE_LIST.length; index++) {
    var key = PATH_KEY_TYPE_LIST[index];
    var path = PATH_LSIT[key];
    // for (let index = 0; index < FUN_NAME_LIST.length; index++) {
    //     const FUN_NAME = FUN_NAME_LIST[index];
    // }
    data.set(key, {
        "hasFsLink2": await hmc.Shell.hasFsLink2(path),
        "hasHardLink2": await hmc.Shell.hasHardLink2(path),
        "hasSymbolicDirLink2": await hmc.Shell.hasSymbolicDirLink2(path),
        "hasDirLink2": await hmc.Shell.hasDirLink2(path),
    });
}
