const child_process = require(`child_process`);
const fs = require(`fs`);
const path = require(`path`);

const  childInfo = child_process.execSync(`node-gyp `+[`rebuild`,`--arch=x64`,`--msvs_version=2019`].join(' '),{cwd:process.cwd()});
if(childInfo.toString(`utf8`).match(/hmc_bin.vcxproj ->.+hmc_bin.node/)){
  fs.copyFileSync(path.join(process.cwd(),`build/Release/hmc_bin.node`),`./bin/HMC_X64.node`)
}

const  childInfo2 = child_process.execSync(`node-gyp `+[`rebuild`,`--arch=ia32`,`--msvs_version=2019`].join(' '),{cwd:process.cwd()});
if(childInfo2.toString(`utf8`).match(/hmc_bin.vcxproj ->.+hmc_bin.node/)){
  fs.copyFileSync(path.join(process.cwd(),`build/Release/hmc_bin.node`),`./bin/HMC_X86.node`)
}