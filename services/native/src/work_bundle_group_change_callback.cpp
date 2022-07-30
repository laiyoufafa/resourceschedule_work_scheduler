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

#ifdef DEVICE_USAGE_STATISTICS_ENABLE
#include "work_bundle_group_change_callback.h"

namespace OHOS {
namespace WorkScheduler {
WorkBundleGroupChangeCallback::WorkBundleGroupChangeCallback(std::shared_ptr<WorkQueueManager>
    workQueueManager)
{
    workQueueManager_ = workQueueManager;
}

void WorkBundleGroupChangeCallback::OnBundleGroupChanged(
    const DeviceUsageStats::BundleActiveGroupCallbackInfo &bundleActiveGroupCallbackInfo)
{
    int32_t newGroup = bundleActiveGroupCallbackInfo.GetNewGroup();
    int32_t oldGroup = bundleActiveGroupCallbackInfo.GetOldGroup();
    int32_t userId = bundleActiveGroupCallbackInfo.GetUserId();
    std::string bundleName = bundleActiveGroupCallbackInfo.GetBundleName();
    WS_HILOGD("Bundle group changed to %{public}d with userId = %{public}d, bundleName = %{public}s",
        newGroup, userId, bundleName.c_str());
    if (!workQueueManager_) {
        WS_HILOGE("workQueueManager_ is nullptr.");
        return;
    }
    if (newGroup < oldGroup) {
        bool groupChange = true;
        workQueueManager_->OnConditionChanged(WorkCondition::Type::GROUP,
            std::make_shared<DetectorValue>(newGroup, userId, groupChange, bundleName));
    }
}
}  // namespace WorkScheduler
}  // namespace OHOS
#endif