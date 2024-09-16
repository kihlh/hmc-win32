
import type _hmc = require("../../../mian/hmc");
import type { HMC } from "../../../mian/hmc";

// vs编译设置里面的最后一个命令行是 .node 文件
import fs = require("fs-extra");
import jsonfm = require("jsonfm");
import shake = require("hmc-shake");

export type Native = {


}

const native: _hmc.HMC.G_HMC_NATIVE & HMC.Native & Native = require(process.argv.at(-1) || "");

import log4js = require("log4js");
import { ref } from "hmc-win32";
log4js.configure({ appenders: { cheese: { type: "file", filename: "cheese.log" } }, categories: { default: { appenders: ["cheese"], level: "error" } } });
const log = log4js.getLogger("cheese");




(async function () {

    native.getThumbnailPng("F:\\Magick++_tutorial.pdf",256,"F:/1.png");

})();

process.exitCode = 666;
