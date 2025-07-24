#include "napi/native_api.h"
#include <cstring>

static napi_value ContractPhiTest(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[2];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    
    // 获取字符串长度
    size_t str1_length = 0;
    size_t str2_length = 0;
    napi_get_value_string_utf8(env, args[0], nullptr, 0, &str1_length);
    napi_get_value_string_utf8(env, args[1], nullptr, 0, &str2_length);
    
    // 分配内存空间
    char* str1 = new char[str1_length + 1];
    char* str2 = new char[str2_length + 1];
    char* result = new char[str1_length + str2_length + 1];
    
    // 获取字符串内容
    napi_get_value_string_utf8(env, args[0], str1, str1_length + 1, nullptr);
    napi_get_value_string_utf8(env, args[1], str2, str2_length + 1, nullptr);
    
    // 使用 strcat 连接字符串
    char* dst = strcpy(result, str1);
    char* contracted = strcat(dst, str2);
    
    // 创建返回值
    napi_value output;
    napi_create_string_utf8(env, contracted, NAPI_AUTO_LENGTH, &output);
    
    // 释放内存
    delete[] str1;
    delete[] str2;
    delete[] result;
    
    return output;
}



EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports)
{    napi_property_descriptor desc[] = {
        {"contractPhiTest", nullptr, ContractPhiTest, nullptr, nullptr, nullptr, napi_default, nullptr},
    };
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}
EXTERN_C_END

static napi_module demoModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "entry",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void RegisterEntryModule(void)
{
    napi_module_register(&demoModule);
}
