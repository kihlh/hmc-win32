{
  "targets": [
    {
      "target_name": "AutoItX_x64",
      "conditions": [
        ['OS=="win"', {
          "sources": [
            "./util/hmc_string_util.cpp",
            "Main.cpp"
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
       "libraries": [
        "AutoItX3/AutoItX3_DLL.lib",
        "AutoItX3/AutoItX3_x64_DLL.lib"
      ],
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
