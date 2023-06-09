/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef FOUNDATION_RESOURCESCHEDULE_WORKSCHEDULER_INTERFACES_KITS_NAPI_INCLUDE_COMMON
#define FOUNDATION_RESOURCESCHEDULE_WORKSCHEDULER_INTERFACES_KITS_NAPI_INCLUDE_COMMON

#include "napi/native_api.h"
#include "napi/native_node_api.h"
#include "work_info.h"

namespace OHOS {
namespace WorkScheduler {
struct CallbackPromiseInfo {
    napi_ref callback = nullptr;
    napi_deferred deferred = nullptr;
    bool isCallback = false;
    int32_t errorCode = 0;
};

struct AsyncWorkData {
    explicit AsyncWorkData(napi_env napiEnv);
    virtual ~AsyncWorkData();
    napi_env env;
    napi_async_work asyncWork = nullptr;
    napi_deferred deferred = nullptr;
    napi_ref callback = nullptr;
};

class Common {
public:
    /**
     * @brief Napi get null.
     *
     * @param env The env.
     * @return The result.
     */
    static napi_value NapiGetNull(napi_env env);
    /**
     * @brief Get the info of work.
     *
     * @param env The env.
     * @param objValue The obj value.
     * @param workInfo The info of work.
     * @return True if success,else false
     */
    static bool GetWorkInfo(napi_env env, napi_value objValue, WorkInfo &WorkInfo);
    /**
     * @brief Get int property.
     *
     * @param env The env.
     * @param object The object.
     * @param propertyName The name of property.
     * @return Int value.
     */
    static int32_t GetIntProperty(napi_env env, napi_value object, const std::string &propertyName);
    /**
     * @brief Get bool property.
     *
     * @param env The env.
     * @param object The object.
     * @param propertyName The name of property.
     * @return True if success,else false
     */
    static bool GetBoolProperty(napi_env env, napi_value object, const std::string &propertyName);
    /**
     * @brief Get bool to int property.
     *
     * @param env The env.
     * @param object The object.
     * @param propertyName The name of property.
     * @return Bool to int property.
     */
    static int32_t GetBoolToIntProperty(napi_env env, napi_value object, const std::string &propertyName);
    /**
     * @brief Get string property.
     *
     * @param env The env.
     * @param object The object.
     * @param propertyName The name of property.
     * @return String property.
     */
    static std::string GetStringProperty(napi_env env, napi_value object, const std::string &propertyName);
    /**
     * @brief Match value type.
     *
     * @param env The env.
     * @param value The value.
     * @param targetType The target type.
     * @return True if success,else false
     */
    static bool MatchValueType(napi_env env, napi_value value, napi_valuetype targetType);
    /**
     * @brief JS para error.
     *
     * @param env The env.
     * @param callback The callback.
     * @return Result or promise.
     */
    static napi_value JSParaError(const napi_env &env, const napi_ref &callback);
    /**
     * @brief Padding callback promise info.
     *
     * @param env The env
     * @param callback The callback.
     * @param info The info.
     * @param promise The promise.
     */
    static void PaddingCallbackPromiseInfo(
        const napi_env &env, const napi_ref &callback, CallbackPromiseInfo &info, napi_value &promise);
    /**
     * @brief Get the workInfo of napi.
     *
     * @param env The env.
     * @param workInfo The info of work.
     * @return Napi work info.
     */
    static napi_value GetNapiWorkInfo(napi_env env, std::shared_ptr<WorkInfo> &workInfo);
    /**
     * @brief Get callback error value.
     *
     * @param env The env.
     * @param errCode The errCode.
     * @return Callback error value.
     */
    static napi_value GetCallbackErrorValue(napi_env env, int32_t errCode);
    /**
     * @brief Set callback.
     *
     * @param env The env.
     * @param callbackIn The callbackIn.
     * @param errorCode The errorCode.
     * @param result The result.
     */
    static void SetCallback(const napi_env &env, const napi_ref &callbackIn, const int32_t &errorCode,
        const napi_value &result);
    /**
     * @brief Set promise.
     *
     * @param env The env.
     * @param info The info.
     * @param result The result.
     * @return The result.
     */
    static napi_value SetPromise(const napi_env &env, const CallbackPromiseInfo &info, const napi_value &result);
    /**
     * @brief Return callback promise.
     *
     * @param env The env.
     * @param info The info.
     * @param result The result.
     */
    static void ReturnCallbackPromise(const napi_env &env, const CallbackPromiseInfo &info,
        const napi_value &result);

private:
    static bool GetBaseWorkInfo(napi_env env, napi_value objValue, WorkInfo &WorkInfo);
    static bool GetNetWorkInfo(napi_env env, napi_value objValue, WorkInfo &WorkInfo);
    static bool GetChargeInfo(napi_env env, napi_value objValue, WorkInfo &WorkInfo);
    static bool GetBatteryInfo(napi_env env, napi_value objValue, WorkInfo &WorkInfo);
    static bool GetStorageInfo(napi_env env, napi_value objValue, WorkInfo &WorkInfo);
    static bool GetRepeatInfo(napi_env env, napi_value objValue, WorkInfo &WorkInfo);
};
} // namespace WorkScheduler
} // namespace OHOS
#endif // FOUNDATION_RESOURCESCHEDULE_WORKSCHEDULER_INTERFACES_KITS_NAPI_INCLUDE_COMMON