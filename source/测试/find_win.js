let HMC_x64 = require("../CPP/build/Release/HMC_x64.node");

console.log(
    // findWindow (class?:string|null , title?:string|null)
    `[findWindow]   [ class , *title ] ->   ${HMC_x64.findWindow(null, "模板助手")}\n`,
    `[findWindow]   [*class , *title ] ->   ${HMC_x64.findWindow("Chrome_WidgetWin_1", "模板助手")}\n`,
    `[findWindow]   [*class ,  title ] ->   ${HMC_x64.findWindow("Chrome_WidgetWin_1", null)}
    ----------------------------------------------------------------------------------\n`,

    // findWindowEx (hWndParent:number|null ,hWndChildAfter:number|null , class:string|null , title:string|null )
    `[findWindowEx]   [ ? , ? , ? , title] ->   ${HMC_x64.findWindowEx(null, null, null, "模板助手")}\n`,
    `[findWindowEx]   [ ? , ? , class , title] ->   ${HMC_x64.findWindowEx(null, null, "Chrome_WidgetWin_1", "模板助手")}\n`,
    `[findWindowEx]   [ Parent , ? , class , ? , ? ] ->   ${HMC_x64.findWindowEx(396976, null, "Chrome_RenderWidgetHostHWND", null)}\n`,
    `[findWindowEx]   [ Parent , ChildAfter , class , ? , ? ] ->   ${HMC_x64.findWindowEx(49844, 131754, "DirectUIHWND", null)}
    ----------------------------------------------------------------------------------\n`,

);

// console.log(
//     // findAllWindow (class:string|null , title:string|null , isWindow:boolean|null = true , isCaseSensitive:boolean|null = true  )
//     `[findAllWindow]   [ ? , title  ?  ? ] ->   ${JSON.stringify(HMC_x64.findAllWindow(null, "模板助手", null, null))}\n`,
//     `[findAllWindow]   [ class , title  ?  ? ] ->   ${JSON.stringify(HMC_x64.findAllWindow("Chrome_WidgetWin_1", "模板助手", null, null))}\n`,
//     `[findAllWindow][class , ?  ?  ? ] -> ${JSON.stringify(HMC_x64.findAllWindow("Chrome_RenderWidgetHostHWND", null, null, null))}\n`,
//     `[findAllWindow][class , ? false ? ] -> ${JSON.stringify(HMC_x64.findAllWindow("Chrome_RenderWidgetHostHWND", null, false, null))}\n`,
//     `[findAllWindow][class , ? false  true ]-> ${JSON.stringify(HMC_x64.findAllWindow("CHRome_RenderWidgetHostHWND", null, false, true))}\n`,
//     `[findAllWindow][class , ? false  false ]-> ${JSON.stringify(HMC_x64.findAllWindow("CHRome_RenderWidgetHostHWND", null, false, false))}\n 
//     ----------------------------------------------------------------------------------
//     `
// );