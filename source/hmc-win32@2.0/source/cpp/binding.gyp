{
  "targets": [
    {
      "target_name": "HMC_Beta",
      "conditions": [
        ['OS=="win"', {
          "sources": [
            "../../../hmc-module/src/hmc_string_util.cpp",
            "../../../hmc-module/src/hmc_automation_util.cpp",
            "../../../hmc-module/src/hmc_byte_util.cpp",
            "../../../hmc-module/src/hmc_clip_util.cpp",
            "../../../hmc-module/src/hmc_console_util.cpp",
            "../../../hmc-module/src/hmc_json_util.cpp",
            "../../../hmc-module/src/hmc_napi_value_util.cpp",
            "../../../hmc-module/src/hmc_process_util.cpp",
            "../../../hmc-module/src/hmc_registr_util.cpp",
            "../../../hmc-module/src/hmc_screen_util.cpp",
            "../../../hmc-module/src/hmc_shell_util.cpp",
            "../../../hmc-module/src/hmc_string_util.cpp",
            "../../../hmc-module/src/hmc_usb_util.cpp",
            "../../../hmc-module/src/hmc_util.cpp",
            "../../../hmc-module/src/hmc_windows_util.cpp",
            "./export/shell.cpp",
            "./export/screen.cpp",
            "./export/clip.cpp",
            "./export/window.cpp",
            "main.cpp",
          ], 
          "include_dirs": ["../../../hmc-module/include","./export"],
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
       "libraries": [],
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
