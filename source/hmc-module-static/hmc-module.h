#include <vector>
#include <string>
#include <hmc_util.h>
#include <hmc_automation_util.h>
#include <hmc_byte_util.h>
#include <hmc_clip_util.h>

// node.js api
#ifdef SRC_NODE_API_H_
#include <hmc_napi_value_util.h>
#endif  // SRC_NODE_API_H_

#include <hmc_process_util.h>
#include <hmc_registr_util.h>
#include <hmc_screen_util.h>
#include <hmc_shell_util.h>
#include <hmc_sock_util.h>
#include <hmc_string_util.h>
#include <hmc_usb_util.h>
#include <hmc_windows_util.h>

#ifdef _DEBUG  
#ifdef _WIN64 
// 如果发现无法找到静态文件可以测试以下方法(其中一种)
// 1. 将路径替换为绝对的路径(d:/SharedLibrary/hmc-module-static_DEBUG_X64.lib)
// 2. 在vs属性页中配置 VC++目录 ->常规->库目录 ($(静态模块位置)/SharedLibrary)
// 3. 在vs属性页中配置 链接器->常规->附加库目录($(静态模块位置)/SharedLibrary)
#pragma comment(lib, "hmc-module-static_DEBUG_X64.lib")
#else  
#pragma comment(lib, "hmc-module-static_DEBUG_X86.lib")
#endif
#else 
#ifdef _WIN64
#pragma comment(lib, "hmc-module-static_RELEASE_X64.lib")
#else 
#pragma comment(lib, "hmc-module-static_RELEASE_X86.lib")
#endif
#endif

