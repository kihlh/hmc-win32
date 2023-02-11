{
  "targets": [
    {
      "target_name": "HMC",
      "conditions": [
        ['OS=="win"', {
          "sources": [
            "Main.cpp",
            "test.cpp",
            "usb.cpp",
            "util.cpp",
            "clip.cpp",
            "registr.cpp"
            
          ],
          'msvs_settings': {
            'VCCLCompilerTool': {
              'AdditionalOptions': [
                '/W3',
                '/Qspectre',
                '/guard:cf'
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
