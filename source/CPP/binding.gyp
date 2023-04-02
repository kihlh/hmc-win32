{
  "targets": [
    {
      "target_name": "HMC_x64",
      "conditions": [
        ['OS=="win"', {
          "sources": [
            "Main.cpp",
            "test.cpp",
            "usb.cpp",
            "util.cpp",
            "clip.cpp",
            "registr.cpp",
            "auto.cpp",
            "windows.cpp",
            "process.cpp"
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
