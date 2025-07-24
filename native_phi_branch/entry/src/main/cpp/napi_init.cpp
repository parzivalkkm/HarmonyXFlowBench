#include "napi/native_api.h"
#include <cstring>

static napi_value BranchPhiTest(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[2];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    
    char* str0 = new char[256];
    char* str1 = new char[256];
    
    napi_get_value_string_utf8(env, args[0], str0, NAPI_AUTO_LENGTH, nullptr);
    napi_get_value_string_utf8(env, args[1], str1, NAPI_AUTO_LENGTH, nullptr);
    
    napi_value a1, a2;
    napi_create_string_utf8(env, str0, NAPI_AUTO_LENGTH, &a1);
    napi_create_string_utf8(env, str1, NAPI_AUTO_LENGTH, &a2);
    
    int x = 65534;
    
    if (x*(x+1)%2 == 0){
        return a1;
    }else{
        return a2;
    }
}

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports)
{    napi_property_descriptor desc[] = {
        {"branchPhiTest", nullptr, BranchPhiTest, nullptr, nullptr, nullptr, napi_default, nullptr},
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
