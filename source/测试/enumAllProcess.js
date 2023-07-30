let HMC_x64 = require("F:/515/hmc-win32/source/CPP/build/Release/HMC_x64.node");

let cp_id =  HMC_x64.enumAllProcess();

let p = setInterval(_=>{
    _ = HMC_x64.enumAllProcessPolling(cp_id);
    
    if(_){
        // console.log(_) ;
    }
},15);
