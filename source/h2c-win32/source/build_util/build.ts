// @ts-ignore
import fs = require('fs');
// @ts-ignore
import hmc = require('hmc-win32');
const { GetProcessCommandLineByPid, GetCurrentWorkingDirectory } = require("./GetProcessCommandLineByPid_x64.node") as {
    GetProcessCommandLineByPid(pid: number): string | null,
    GetCurrentWorkingDirectory(pid: number): string | null
};

let g_is_build_ing = false;

// 判断是否正在编译中
setInterval(() => {
    const findProcessList = hmc.findProcess("node.exe");

    let is_build_ing = false;

    for (let index = 0; index < findProcessList.length; index++) {
        const findProcess = findProcessList[index];
        const commandLine = GetProcessCommandLineByPid(findProcess.pid);

        if (commandLine?.includes("node-gyp.js rebuild")) {
            is_build_ing = true;
            const CurrentWorkingDirectory = GetCurrentWorkingDirectory(findProcess.pid);

            if (is_build_ing != g_is_build_ing) {
                g_is_build_ing = is_build_ing;

                if (is_build_ing) {
                    console.log("commandLine->%s    cwd->%s", commandLine, CurrentWorkingDirectory)
                }

            }
        };

    }

    g_is_build_ing = is_build_ing;


}, 200);

