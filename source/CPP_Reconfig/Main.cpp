#include <windows.h>
#include <assert.h>
#define NAPI_EXPERIMENTAL // 开启实验性功能 比如异步(多线程)
#include <node_api.h>
#include "./util/util.h";

using namespace hmc_napi_util;
using namespace std;

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>

// 截屏的存储为文件
#include <fstream>

// 小写转换
#include <algorithm>

using namespace std;

napi_value bufferInfo(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1];
    napi_status status;
    status = napi_get_cb_info(env, info, &argc, args, NULL, NULL);
    assert(status == napi_ok);
    vector<unsigned char> buf;
    hmc_napi_util::get_value::buffer_vector(env, args[0], buf);
    const char *filename = "binary_data.bmp";

    std::ofstream outFile(filename, std::ios::binary);

    outFile.write(reinterpret_cast<const char *>(buf.data()), buf.size());

    // 关闭文件流
    outFile.close();

    return NULL;
}

static napi_value Init(napi_env env, napi_value exports)
{
    vector<unsigned char> buffer;
    hmc_screen::CaptureBmpToBuff(buffer, 0, 0, 0, 0);

    napi_property_descriptor BIND_NAPI_METHOD[] = {
        {"version", 0, 0, 0, 0, hmc_napi_util::create_value::String(env, "1.0.0"), napi_default, 0},
        {"versioncc", 0, 0, 0, 0, hmc_napi_util::create_value::Buffer(env, buffer), napi_default, 0},
        {"bufferInfo", 0, bufferInfo, 0, 0, 0, napi_default, 0}};

    napi_define_properties(env, exports, sizeof(BIND_NAPI_METHOD) / sizeof(BIND_NAPI_METHOD[0]), BIND_NAPI_METHOD);
    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);
