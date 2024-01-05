#pragma once

// 防止重复导入
#ifndef MODE_INTERNAL_INCLUDE_HMC_REGISTR_V2_HPP
#define MODE_INTERNAL_INCLUDE_HMC_REGISTR_V2_HPP

#include "./util/hmc_string_util.hpp"
#include "./util/hmc_registr_util.hpp"
#include "./Mian.hpp"

extern napi_value getStringRegKey(napi_env env, napi_callback_info info);
extern napi_value removeRegistrFolder(napi_env env, napi_callback_info info);
extern napi_value removeRegistrValue(napi_env env, napi_callback_info info);

extern napi_value hasRegistrValue(napi_env env, napi_callback_info info);
extern napi_value createRegistrFolder(napi_env env, napi_callback_info info);
extern napi_value getRegistrFolderStat(napi_env env, napi_callback_info info);
extern napi_value getRegistrValueStat(napi_env env, napi_callback_info info);
extern napi_value getRegistrBuffValue(napi_env env, napi_callback_info info);
extern napi_value getRegistrDword(napi_env env, napi_callback_info info);
extern napi_value setRegistrDword(napi_env env, napi_callback_info info);
extern napi_value getRegistrQword(napi_env env, napi_callback_info info);
extern napi_value setRegistrQword(napi_env env, napi_callback_info info);
extern napi_value setRegistrValue(napi_env env, napi_callback_info info);

#endif // MODE_INTERNAL_INCLUDE_HMC_REGISTR_V2_HPP