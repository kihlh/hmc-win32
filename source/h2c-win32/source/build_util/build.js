"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
// @ts-ignore
const hmc = require("hmc-win32");
const { GetProcessCommandLineByPid, GetCurrentWorkingDirectory } = require("./GetProcessCommandLineByPid_x64.node");
let g_is_build_ing = false;
// 判断是否正在编译中
setInterval(() => {
    const findProcessList = hmc.findProcess("node.exe");
    let is_build_ing = false;
    for (let index = 0; index < findProcessList.length; index++) {
        const findProcess = findProcessList[index];
        const commandLine = GetProcessCommandLineByPid(findProcess.pid);
        if (commandLine === null || commandLine === void 0 ? void 0 : commandLine.includes("node-gyp.js rebuild")) {
            is_build_ing = true;
            const CurrentWorkingDirectory = GetCurrentWorkingDirectory(findProcess.pid);
            if (is_build_ing != g_is_build_ing) {
                g_is_build_ing = is_build_ing;
                if (is_build_ing) {
                    console.log("commandLine->%s    cwd->%s", commandLine, CurrentWorkingDirectory);
                }
            }
        }
        ;
    }
    g_is_build_ing = is_build_ing;
}, 200);
