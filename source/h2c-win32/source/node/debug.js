"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const native = require(process.argv.at(-1) || "");
const log4js = require("D:/source/\u9B54\u6CD5\u81EA\u52A8\u66F4\u65B0/node_modules/log4js");
log4js.configure({ appenders: { cheese: { type: "file", filename: "cheese.log" } }, categories: { default: { appenders: ["cheese"], level: "error" } } });
const log = log4js.getLogger("cheese");
(async function () {
})();
process.exitCode = 666;
