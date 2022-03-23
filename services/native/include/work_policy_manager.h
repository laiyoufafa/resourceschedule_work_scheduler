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
#ifndef FOUNDATION_RESOURCESCHEDULE_WORKSCHEDULER_WORK_SCHED_SERVICES_POLICY_MANAGER_H
#define FOUNDATION_RESOURCESCHEDULE_WORKSCHEDULER_WORK_SCHED_SERVICES_POLICY_MANAGER_H
#include <map>
#include <memory>
#include <mutex>
#include <vector>

#include "policy_type.h"
#include "policy/app_removed_listener.h"
#include "policy/ipolicy_filter.h"
#include "work_conn_manager.h"
#include "work_info.h"
#include "work_queue.h"
#include "work_scheduler_service.h"
#include "work_sched_common.h"
#include "work_status.h"

namespace OHOS {
namespace WorkScheduler {
class WorkSchedulerService;
class WorkEventHandler;
class AppRemovedListener;
class AppDataClearListener;
class Watchdog;
class WorkPolicyManager {
public:
    const size_t MAX_WORK_COUNT_PER_UID = 10;
    explicit WorkPolicyManager(const wptr<WorkSchedulerService>& wss);
    ~WorkPolicyManager() = default;
    /**
     * @brief The Init.
     * @return True if success,else false
     */
    bool Init();
    /**
     * @brief The Add listener.
     * @return True if success,else false
     */
    bool AddListener();
    /**
     * @brief The Add policy filter.
     */
    void AddPolicyFilter(std::shared_ptr<IPolicyFilter> filter);
    /**
     * @brief The Add work.
     * @return True if success,else false
     */
    bool AddWork(std::shared_ptr<WorkStatus> workStatus, int32_t uid);
    /**
     * @brief The Remove work.
     * @return True if success,else false
     */
    bool RemoveWork(std::shared_ptr<WorkStatus> workStatus, int32_t uid);
    /**
     * @brief The Stop work.
     * @return True if success,else false
     */
    bool StopWork(std::shared_ptr<WorkStatus> workStatus, int32_t uid, const bool needCancel, bool isTimeOut);
    /**
     * @brief The Stop and clear works.
     * @return True if success,else false
     */
    bool StopAndClearWorks(int32_t uid);
    /**
     * @brief The Is last work timeout.
     * @return True if success,else false
     */
    bool IsLastWorkTimeout(int32_t workId, int32_t uid);
    std::shared_ptr<WorkStatus> FindWorkStatus(WorkInfo& workInfo, int32_t uid);
    /**
     * @brief The OnConditionReady callback.
     */
    void OnConditionReady(std::shared_ptr<std::vector<std::shared_ptr<WorkStatus>>> workStatusVector);
    /**
     * @brief The OnPolicyChanged callback.
     */
    void OnPolicyChanged(PolicyType policyType, std::shared_ptr<DetectorValue> detectorVal);
    std::list<std::shared_ptr<WorkInfo>> ObtainAllWorks(int32_t &uid);
    std::shared_ptr<WorkInfo> GetWorkStatus(int32_t &uid, int32_t &workInfo);
    std::list<std::shared_ptr<WorkStatus>> GetAllWorkStatus(int32_t &uid);
    void Dump(std::string& result);
    int32_t currentRunningCount = 0;
    /**
     * @brief The Check work to run.
     */
    void CheckWorkToRun();
    /**
     * @brief The Send retrigger.
     */
    void SendRetrigger(int64_t delayTime);
    /**
     * @brief The Add app remove listener.
     */
    void AddAppRemoveListener(std::shared_ptr<AppRemovedListener> listener);
    /**
     * @brief The Add app data clear listener.
     */
    void AddAppDataClearListener(std::shared_ptr<AppDataClearListener> listener);
    /**
     * @brief The Watchdog timeout.
     */
    void WatchdogTimeOut(uint32_t watchdogId);
    /**
     * @brief The Set memory by dump.
     */
    void SetMemoryByDump(int32_t memory);
    int32_t GetDumpSetMemory();
    /**
     * @brief The Set watchdog time.
     */
    void SetWatchdogTime(int time);
    int GetWatchdogTime();

private:
    int32_t GetMaxRunningCount();
    int32_t GetRunningCount();
    void DumpConditionReadyQueue(std::string& result);
    void DumpUidQueueMap(std::string& result);
    void RemoveFromUidQueue(std::shared_ptr<WorkStatus> workStatus, int32_t uid);
    void RemoveFromReadyQueue(std::shared_ptr<WorkStatus> workStatus);
    void AddToReadyQueue(std::shared_ptr<std::vector<std::shared_ptr<WorkStatus>>> workStatusVector);
    void RealStartWork(std::shared_ptr<WorkStatus> workStatus);
    void AddToRunningQueue(std::shared_ptr<WorkStatus> workStatus);
    void RemoveConditionUnReady();
    std::shared_ptr<WorkStatus> GetWorkToRun();
    void RemoveAllUnReady();
    uint32_t NewWatchdogId();
    void AddWatchdogForWork(std::shared_ptr<WorkStatus> workStatus);
    std::shared_ptr<WorkStatus> GetWorkFromWatchdog(uint32_t id);

    const wptr<WorkSchedulerService> wss_;
    std::shared_ptr<WorkConnManager> workConnManager_;
    std::shared_ptr<WorkEventHandler> handler_;

    std::mutex uidMapMutex_;
    std::map<int32_t, std::shared_ptr<WorkQueue>> uidQueueMap_;

    std::mutex conditionReadyMutex_;
    std::shared_ptr<WorkQueue> conditionReadyQueue_;

    std::list<std::shared_ptr<IPolicyFilter>> policyFilters_;
    std::shared_ptr<AppRemovedListener> appRemovedListener_;
    std::shared_ptr<AppDataClearListener> appDataClearListener_;

    std::shared_ptr<Watchdog> watchdog_;

    std::mutex watchdogIdMapMutex_;
    std::map<uint32_t, std::shared_ptr<WorkStatus>> watchdogIdMap_;

    uint32_t watchdogId_;
    int32_t dumpSetMemory_;
    int watchdogTime_;
};
} // namespace WorkScheduler
} // namespace OHOS

#endif // FOUNDATION_RESOURCESCHEDULE_WORKSCHEDULER_WORK_SCHED_SERVICES_POLICY_MANAGER_H