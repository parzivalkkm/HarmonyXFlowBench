#include "napi/native_api.h"
#include "hilog/log.h"

static napi_value LeakData(napi_env env, napi_callback_info info)
{

    size_t argc = 1;
    napi_value argv[1] = {nullptr};
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    napi_value result = nullptr;
    napi_get_named_property(env, argv[0], "data", &result);
    char *str = new char[256];
    napi_get_value_string_utf8(env, result, str, 256, nullptr);
    OH_LOG_INFO(LOG_APP, "ComplexData.data = %{public}s", str);
    return nullptr;
}

static napi_value LeakOther(napi_env env, napi_callback_info info)
{

    size_t argc = 1;
    napi_value argv[1] = {nullptr};
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    napi_value result = nullptr;
    napi_get_named_property(env, argv[0], "other", &result);
    char *str = new char[256];
     napi_get_value_string_utf8(env, result, str, 256, nullptr);
    OH_LOG_INFO(LOG_APP, "ComplexData.other = %{public}s", str);
    return nullptr;
}

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports)
{
    napi_property_descriptor desc[] = {
        { "leakData", nullptr, LeakData, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "leakOther", nullptr, LeakOther, nullptr, nullptr, nullptr, napi_default, nullptr }
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
