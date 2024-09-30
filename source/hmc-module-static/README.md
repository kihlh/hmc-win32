# hmc-module

 hmc-win32 是一个调用常用winapi的node模块，它包含了接近两百个API 本存储库的c++代码是hmc的核心功能支持库

##### 他支持静态调用 （也为其预编译了以下标头）

- X64_MT_Release 
- X86_MT_Release 
- X64_MDd_Debug
- X86_MDd_Debug

**但是他仅限于Windows平台**

-----------------------------------------

![static call C++14 + ](https://img.shields.io/badge/C++%2014+%20-static%20call-24ACF2.svg?longCache=true) ![Compile from code C++14](https://img.shields.io/badge/C++%2020%20-Compile%20from%20code-5DA2E0.svg?longCache=true)

#### hmc的开发宗旨永远在于

- 内存安全 [安全永远高于效率]
- 高效
- 代码可移植性
- 避免C语言语法  因为他的安全性很难控制



##### hmc目前已经包含了几个功能大类

- **hmc_sock_util**     本机网络io
- **hmc_usb_util**     一些简单的usb获取
- **hmc_string_util**     简单的文本处理
- **hmc_registr_util**     注册表封装
- **hmc_shell_util**     对文件系统/ 资源管理器的一些调用
- **hmc_napi_value_util**     纯node_api 的接口封装
- **hmc_clip_util**      对剪贴板的操作
- **hmc_automation_util**      自动化 例如键鼠操作
- **hmc_byte_util**      一些简单的进制转换 
- **hmc_process_util**      进程api封装
- **hmc_windows_util**      窗口操作



## 开始

#### 1.初始化标头

```c++
#include <Windows.h>
#include <iostream>

#ifdef _DEBUG  
#ifdef _WIN64 
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

```

#### 2.添加 include 环境

![image-20240915074954827](/assets/msvc_include_config.png)

### 案例

#### 1.拦截win键 创建低级键盘HOOK

```c++
#include <hmc_automation_util.h>
// 方法1 函数获取法支持拦截
    bool is_hook = hmc_Keyboard::keyboardHook::initKeyboardEventHook([](hmc_Keyboard::keyboardHook::KeyboardEvent event) {

        //拦截win键
        if (event.keyCode == VK_LWIN || event.keyCode == VK_RWIN) {
            return false;
        }

        if (event.id >= 500) {
            
            //终止
            hmc_Keyboard::keyboardHook::stopHookKeyboard();
        }

        std::cout << event.to_json()<< "\n";

        //返回false拦截
        return true;
    });
```

- 使用轮询法调用

 ```c++
 #include <hmc_automation_util.h>
 // 轮询调用
      hmc_Keyboard::keyboardHook::initKeyboardEventHook();
      // 初始化需要时间
      Sleep(500);
      do
      {
  
         Sleep(100);
         auto key_env_list = hmc_Keyboard::keyboardHook::getAllKeyboardEvent();
         for (size_t i = 0; i < key_env_list.size(); i++)
         {
             auto& at = key_env_list.at(i);
             if (at.id >= 500) {
                 //终止
                 hmc_Keyboard::keyboardHook::stopHookKeyboard();
             }
             std::cout << at.to_json() << "\n";
         }
  
         // 持续轮询
      } while (hmc_Keyboard::keyboardHook::isValidHookKeyboard());
  
 ```

####  2.获取MAC地址

```c++
#include <hmc_sock_util.h>

auto mac_list = hmc_sock_util::getMacAddresses();
for (size_t i = 0; i < mac_list.size(); i++)
{
    auto& mac = mac_list.at(i);
    std::cout <<"mac [ "<<i<<" ]  " <<"< " << mac <<" >" << "\n";
}

```
