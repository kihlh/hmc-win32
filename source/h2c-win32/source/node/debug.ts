
import type _hmc = require("../../../mian/hmc");
import type { HMC } from "../../../mian/hmc";

// vs编译设置里面的最后一个命令行是 .node 文件
import fs = require("fs-extra");
import jsonfm = require("jsonfm");
import shake = require("hmc-shake");

const native: _hmc.HMC.G_HMC_NATIVE & HMC.Native = require(process.argv.at(-1) || "");
import log4js = require("D:/source/魔法自动更新/node_modules/log4js");
import { ref } from "hmc-win32";
log4js.configure({ appenders: { cheese: { type: "file", filename: "cheese.log" } }, categories: { default: { appenders: ["cheese"], level: "error" } } });
const log = log4js.getLogger("cheese");

(async function () {

    


})();

process.exitCode = 666;
