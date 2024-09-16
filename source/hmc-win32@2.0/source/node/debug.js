"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const native = require(process.argv.at(-1) || "");
const log4js = require("log4js");
log4js.configure({ appenders: { cheese: { type: "file", filename: "cheese.log" } }, categories: { default: { appenders: ["cheese"], level: "error" } } });
const log = log4js.getLogger("cheese");
(async function () {
    native.getThumbnailPng("F:\\Magick++_tutorial.pdf", 256, "F:/1.png");
})();
process.exitCode = 666;
