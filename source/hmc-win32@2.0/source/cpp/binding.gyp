{
  "targets": [
    {
      "target_name": "HMC_Beta",
      "conditions": [
        ['OS=="win"', {
          "sources": [
            "../../../hmc-module-static/src/hmc_napi_value_util.cpp",
            # 以下是hmc-module-static的源文件 可以使用hmc-module-static-static 的.lib库替代
            "../../../hmc-module-static/src/hmc_automation_util.cpp",
            "../../../hmc-module-static/src/hmc_registr_util.cpp",
            "../../../hmc-module-static/src/hmc_screen_util.cpp",
            "../../../hmc-module-static/src/hmc_shell_util.cpp",
            "../../../hmc-module-static/src/hmc_string_util.cpp",
            "../../../hmc-module-static/src/hmc_usb_util.cpp",
            "../../../hmc-module-static/src/hmc_util.cpp",
            "../../../hmc-module-static/src/hmc_windows_util.cpp",
            "../../../hmc-module-static/src/hmc_string_util.cpp",
            "../../../hmc-module-static/src/hmc_automation_util.cpp",
            "../../../hmc-module-static/src/hmc_byte_util.cpp",
            "../../../hmc-module-static/src/hmc_clip_util.cpp",
            # "../../../hmc-module-static/src/hmc_console_util.cpp",
            "../../../hmc-module-static/src/hmc_json_util.cpp",
            "./export/shell.cpp",
            "./export/screen.cpp",
            "./export/clip.cpp",
            "./export/window.cpp",
            "main.cpp",
          ], 
          "include_dirs": ["../../../hmc-module-static/include/*","./export"],
          "libraries": [
            # "<(module_root_dir)/SharedLibrary/hmc-module-static-static_RELEASE_X64.lib>",
            # "<(module_root_dir)/SharedLibrary/hmc-module-static-static_RELEASE_X86.lib>",
            # "<(module_root_dir)/SharedLibrary/hmc-module-static-static_DEBUG_X64.lib>",
            # "<(module_root_dir)/SharedLibrary/hmc-module-static-static_DEBUG_X86.lib>",
          ],
          'msvs_settings': {
            'VCCLCompilerTool': {
              'AdditionalOptions': [
                '/W3',
                '/Qspectre',
                '/guard:cf',
                "/wd4819",
                "/wd4067",
                "/wd4101",
                "/wd4312",
                "/wd4311",
                "/wd4302",
                "/wd4060",
                "/wd4700",
                "/wd4081",
                "/wd4530",
                "/wd4715",
                "/wd4018"
              ]
            },
            'VCLinkerTool': {
              'AdditionalOptions': [
                '/guard:cf'
              ]
            }
          },
        }]
      ]
    }
  ]
}
