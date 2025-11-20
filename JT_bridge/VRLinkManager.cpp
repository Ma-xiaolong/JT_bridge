#include "VRLinkManager.h"

// VR-Link
#include <vl/exerciseConn.h>
#include <vl/rprFomMap.h>
#include <vl/reflEntList.h>

// 对象列表
#include "jammer/CtRefIJammer.h"
#include "jammer/CtIJammerStateRepository.h"
#include "jammer/CtRefIJammerList.h"

#include "passiveJammer/CtRefIPassiveJammer.h"
#include "passiveJammer/CtIPassiveJammerStateRepository.h"
#include "passiveJammer/CtRefIPassiveJammerList.h"

#include "ZHAircraftEntity/CtRefZHAircraftEntity.h"
#include "ZHAircraftEntity/CtZHAircraftEntityStateRepository.h"
#include "ZHAircraftEntity/CtRefZHAircraftEntityList.h"

#include "zhradar/CtRefZHRadar.h"
#include "zhradar/CtZHRadarStateRepository.h"
#include "zhradar/CtRefZHRadarList.h"

#include "radar/CtRefRadar.h"
#include "radar/CtRadarStateRepository.h"
#include "radar/CtRefRadarList.h"

#include "ZHLightWeaponPayload/CtRefZHLightWeaponPayload.h"
#include "ZHLightWeaponPayload/CtZHLightWeaponPayloadStateRepository.h"
#include "ZHLightWeaponPayload/CtRefZHLightWeaponPayloadList.h"

#include "zhradarresult/CtRefZHRadarResult.h"
#include "zhradarresult/CtZHRadarResultStateRepository.h"
#include "zhradarresult/CtRefZHRadarResultList.h"

#include "radarresult/CtRefRadarResults.h"
#include "radarresult/CtRadarResultsStateRepository.h"
#include "radarresult/CtRefRadarResultsList.h"

#include "ExtendEntity/CtRefExtendEntity.h"
#include "ExtendEntity/CtExtendEntityStateRepository.h"
#include "ExtendEntity/CtRefExtendEntityList.h"

#include "ZHWeaponLoadInfo/CtRefZHWeaponLoadInfo.h"
#include "ZHWeaponLoadInfo/CtZHWeaponLoadInfoStateRepository.h"
#include "ZHWeaponLoadInfo/CtRefZHWeaponLoadInfoList.h"

#include "ZHElectroOpticalRadarResult/CtRefZHElectroOpticalRadarResult.h"
#include "ZHElectroOpticalRadarResult/CtZHElectroOpticalRadarResultStateRepository.h"
#include "ZHElectroOpticalRadarResult/CtRefZHElectroOpticalRadarResultList.h"

// 回调函数
#include "callbacks/JammerCallbacks.h"
#include "callbacks/PassiveJammerCallbacks.h"
#include "callbacks/ZHAircraftEntityCallbacks.h"
#include "callbacks/ZHRadarCallbacks.h"
#include "callbacks/ZHLightWeaponPayloadCallbacks.h"
#include "callbacks/ZHRadarResultCallbacks.h"
#include "callbacks/ZHWeaponLoadInfoCallbacks.h"
#include "callbacks/RadarCallbacks.h"
#include "callbacks/ExtendEntityCallbacks.h"
#include "callbacks/RadarResultsCallbacks.h"
#include "callbacks/ZHElectroOpticalRadarResultCallbacks.h"
#include "callbacks/EntityCallbacks.h"
#include "callbacks/JammerInteractionCallbacks.h"
#include "callbacks/PassiveJammerInteractionCallbacks.h"
#include "callbacks/WeatherInitInteractionCallbacks.h"
#include "callbacks/WeatherResultInteractionCallbacks.h"
#include "callbacks/ZHAircraftSimulatorConfigInteractionCallbacks.h"
#include "callbacks/ZHRadarReqInteractionCallbacks.h"
#include "callbacks/ZHLightWeaponDamageInteractionCallbacks.h"
#include "callbacks/ZHLightWeaponExplodeInteractionCallbacks.h"

// 交互类
#include "jamInter/CtIJammerinteraction.h"
#include "passiveJammerInter/CtIPassiveJammerinteraction.h"
#include "weatherinit/CtIWeatherInitinteraction.h"
#include "weatherresultinter/CtIWeatherResultsinteraction.h"
#include "ZHAircraftSimulatorConfigInter/CtZHAircraftSimulatorConfigReqinteraction.h"
#include "zhradarinter/CtZHRadarReqinteraction.h"
#include "ZHLightWeaponDamageInter/CtZHLightWeaponDamageReqinteraction.h"
#include "ZHLightWeaponExplodeInter/CtZHLightWeaponExplodeReqinteraction.h"
#include "radarcontrol/CtIRadarControllerinteraction.h"

#include <memory>

// 实现自定义删除器
void DtExerciseConnDeleter::operator()(DtExerciseConn* p) const {
    if (p) {
        delete p;
    }
}

// 全局对象列表
static std::unique_ptr<CtRefIJammerList> g_jammerList;
static std::unique_ptr<CtRefIPassiveJammerList> g_passiveJammerList;
static std::unique_ptr<CtRefZHAircraftEntityList> g_zhAircraftEntityList;
static std::unique_ptr<CtRefZHRadarList> g_zhRadarList;
static std::unique_ptr<CtRefZHLightWeaponPayloadList> g_zhLightWeaponPayloadList;
static std::unique_ptr<CtRefZHRadarResultList> g_zhRadarResultList;
static std::unique_ptr<CtRefZHWeaponLoadInfoList> g_zhWeaponLoadInfoList;
static std::unique_ptr<CtRefRadarList> g_radarList;
static std::unique_ptr<CtRefExtendEntityList> g_extendEntityList;
static std::unique_ptr<CtRefRadarResultsList> g_radarResultsList;
static std::unique_ptr<CtRefZHElectroOpticalRadarResultList> g_zhElectroOpticalRadarResultList;
static std::unique_ptr<DtReflectedEntityList> g_entityList;

VRLinkManager& VRLinkManager::I() {
    static VRLinkManager instance;
    return instance;
}

bool VRLinkManager::init(const char* fed, const char* fdr) {
    // Step 1: 建立 VR-Link 联邦连接
    _conn.reset(new DtExerciseConn("MyLink20251108", "addAttr", new DtRprFomMapper(1.0), "D:\\MAK\\vrlink4.0.9d\\examples\\addAttr\\MyLink20251108.xml"));

    // Step 2: 设置对象仓库创建函数
    CtRefIJammer::setStateRepCreator(CtIJammerStateRepository::create);
    CtRefIPassiveJammer::setStateRepCreator(CtIPassiveJammerStateRepository::create);
    CtRefZHAircraftEntity::setStateRepCreator(CtZHAircraftEntityStateRepository::create);
    CtRefZHRadar::setStateRepCreator(CtZHRadarStateRepository::create);
    CtRefZHLightWeaponPayload::setStateRepCreator(CtZHLightWeaponPayloadStateRepository::create);
    CtRefZHRadarResult::setStateRepCreator(CtZHRadarResultStateRepository::create);
    CtRefZHWeaponLoadInfo::setStateRepCreator(CtZHWeaponLoadInfoStateRepository::create);
    CtRefRadar::setStateRepCreator(CtRadarStateRepository::create);
    CtRefExtendEntity::setStateRepCreator(CtExtendEntityStateRepository::create);
    CtRefRadarResults::setStateRepCreator(CtRadarResultsStateRepository::create);
    CtRefZHElectroOpticalRadarResult::setStateRepCreator(CtZHElectroOpticalRadarResultStateRepository::create);

    // Step 3: 创建对象订阅列表
    // 注意：构造函数中会自动调用 addObjectClassByName("HLAobjectRoot.IJammer")
    // 这会向RTI订阅该类对象，当远程联邦成员发布该类对象时，会自动收到通知
    g_jammerList.reset(new CtRefIJammerList(_conn.get()));
    g_passiveJammerList.reset(new CtRefIPassiveJammerList(_conn.get()));
    g_zhAircraftEntityList.reset(new CtRefZHAircraftEntityList(_conn.get()));
    g_zhRadarList.reset(new CtRefZHRadarList(_conn.get()));
    g_zhLightWeaponPayloadList.reset(new CtRefZHLightWeaponPayloadList(_conn.get()));
    g_zhRadarResultList.reset(new CtRefZHRadarResultList(_conn.get()));
    g_zhWeaponLoadInfoList.reset(new CtRefZHWeaponLoadInfoList(_conn.get()));
    g_radarList.reset(new CtRefRadarList(_conn.get()));
    g_extendEntityList.reset(new CtRefExtendEntityList(_conn.get()));
    g_radarResultsList.reset(new CtRefRadarResultsList(_conn.get()));
    g_zhElectroOpticalRadarResultList.reset(new CtRefZHElectroOpticalRadarResultList(_conn.get()));
    
    // 创建标准装备实体列表（订阅 BaseEntity 类型）
    // 注意：DtReflectedEntityList 默认订阅所有 BaseEntity 类型的实体
    // 我们会在回调函数中过滤特定的实体类型 DtEntityType(1, 1, 225, 1, 1, 0, 0)
    g_entityList.reset(new DtReflectedEntityList(_conn.get()));

    // Step 4: 注册回调
    // IJammer 添加回调：当远程联邦成员发布新的IJammer对象时触发
    g_jammerList->addIJammerAdditionCallback(onIJammerAdded, nullptr);
    // IJammer 移除回调：当远程IJammer对象被删除时触发
    g_jammerList->addIJammerRemovalCallback(onIJammerRemoved, nullptr);
    
    // IPassiveJammer 添加回调：当远程联邦成员发布新的IPassiveJammer对象时触发
    g_passiveJammerList->addIPassiveJammerAdditionCallback(onIPassiveJammerAdded, nullptr);
    // IPassiveJammer 移除回调：当远程IPassiveJammer对象被删除时触发
    g_passiveJammerList->addIPassiveJammerRemovalCallback(onIPassiveJammerRemoved, nullptr);
    
    // ZHAircraftEntity 添加回调：当远程联邦成员发布新的ZHAircraftEntity对象时触发
    g_zhAircraftEntityList->addZHAircraftEntityAdditionCallback(onZHAircraftEntityAdded, nullptr);
    // ZHAircraftEntity 移除回调：当远程ZHAircraftEntity对象被删除时触发
    g_zhAircraftEntityList->addZHAircraftEntityRemovalCallback(onZHAircraftEntityRemoved, nullptr);
    
    // ZHRadar 添加回调：当远程联邦成员发布新的ZHRadar对象时触发
    g_zhRadarList->addZHRadarAdditionCallback(onZHRadarAdded, nullptr);
    // ZHRadar 移除回调：当远程ZHRadar对象被删除时触发
    g_zhRadarList->addZHRadarRemovalCallback(onZHRadarRemoved, nullptr);
    
    // ZHLightWeaponPayload 添加回调：当远程联邦成员发布新的ZHLightWeaponPayload对象时触发
    g_zhLightWeaponPayloadList->addZHLightWeaponPayloadAdditionCallback(onZHLightWeaponPayloadAdded, nullptr);
    // ZHLightWeaponPayload 移除回调：当远程ZHLightWeaponPayload对象被删除时触发
    g_zhLightWeaponPayloadList->addZHLightWeaponPayloadRemovalCallback(onZHLightWeaponPayloadRemoved, nullptr);
    
    // ZHRadarResult 添加回调：当远程联邦成员发布新的ZHRadarResult对象时触发
    g_zhRadarResultList->addZHRadarResultAdditionCallback(onZHRadarResultAdded, nullptr);
    // ZHRadarResult 移除回调：当远程ZHRadarResult对象被删除时触发
    g_zhRadarResultList->addZHRadarResultRemovalCallback(onZHRadarResultRemoved, nullptr);
    
    // ZHWeaponLoadInfo 添加回调：当远程联邦成员发布新的ZHWeaponLoadInfo对象时触发
    g_zhWeaponLoadInfoList->addZHWeaponLoadInfoAdditionCallback(onZHWeaponLoadInfoAdded, nullptr);
    // ZHWeaponLoadInfo 移除回调：当远程ZHWeaponLoadInfo对象被删除时触发
    g_zhWeaponLoadInfoList->addZHWeaponLoadInfoRemovalCallback(onZHWeaponLoadInfoRemoved, nullptr);

    // Radar 添加回调
    g_radarList->addRadarAdditionCallback(onRadarAdded, nullptr);
    // Radar 移除回调
    g_radarList->addRadarRemovalCallback(onRadarRemoved, nullptr);

    // ExtendEntity 添加回调
    g_extendEntityList->addExtendEntityAdditionCallback(onExtendEntityAdded, nullptr);
    // ExtendEntity 移除回调
    g_extendEntityList->addExtendEntityRemovalCallback(onExtendEntityRemoved, nullptr);

    // RadarResults 添加回调
    g_radarResultsList->addRadarResultsAdditionCallback(onRadarResultsAdded, nullptr);
    // RadarResults 移除回调
    g_radarResultsList->addRadarResultsRemovalCallback(onRadarResultsRemoved, nullptr);

    // ZHElectroOpticalRadarResult 添加回调
    g_zhElectroOpticalRadarResultList->addZHElectroOpticalRadarResultAdditionCallback(onZHElectroOpticalRadarResultAdded, nullptr);
    // ZHElectroOpticalRadarResult 移除回调
    g_zhElectroOpticalRadarResultList->addZHElectroOpticalRadarResultRemovalCallback(onZHElectroOpticalRadarResultRemoved, nullptr);
    
    // 标准装备实体添加回调：当远程联邦成员发布新的BaseEntity对象时触发
    g_entityList->addEntityAdditionCallback(onEntityAdded, nullptr);
    // 标准装备实体移除回调：当远程BaseEntity对象被删除时触发
    g_entityList->addEntityRemovalCallback(onEntityRemoved, nullptr);
    
    // Step 5: 为已存在的对象注册更新回调（如果有的话）
    // 注意：在初始化时通常还没有对象，因为对象发现是异步的
    // 但如果有对象（例如从之前的会话恢复），需要为它们注册更新回调
    
    // 为已存在的 IJammer 对象注册更新回调
    CtRefIJammer* obj = g_jammerList->first();
    while (obj) {
        obj->addPostUpdateCallback(onIJammerUpdated, nullptr);
        obj = obj->next();
    }
    
    // 为已存在的 IPassiveJammer 对象注册更新回调
    CtRefIPassiveJammer* passiveObj = g_passiveJammerList->first();
    while (passiveObj) {
        passiveObj->addPostUpdateCallback(onIPassiveJammerUpdated, nullptr);
        passiveObj = passiveObj->next();
    }
    
    // 为已存在的 ZHAircraftEntity 对象注册更新回调
    CtRefZHAircraftEntity* aircraftObj = g_zhAircraftEntityList->first();
    while (aircraftObj) {
        aircraftObj->addPostUpdateCallback(onZHAircraftEntityUpdated, nullptr);
        aircraftObj = aircraftObj->next();
    }
    
    // 为已存在的 ZHRadar 对象注册更新回调
    CtRefZHRadar* radarObj = g_zhRadarList->first();
    while (radarObj) {
        radarObj->addPostUpdateCallback(onZHRadarUpdated, nullptr);
        radarObj = radarObj->next();
    }
    
    // 为已存在的 ZHLightWeaponPayload 对象注册更新回调
    CtRefZHLightWeaponPayload* lightWeaponObj = g_zhLightWeaponPayloadList->first();
    while (lightWeaponObj) {
        lightWeaponObj->addPostUpdateCallback(onZHLightWeaponPayloadUpdated, nullptr);
        lightWeaponObj = lightWeaponObj->next();
    }
    
    // 为已存在的 ZHRadarResult 对象注册更新回调
    CtRefZHRadarResult* radarResultObj = g_zhRadarResultList->first();
    while (radarResultObj) {
        radarResultObj->addPostUpdateCallback(onZHRadarResultUpdated, nullptr);
        radarResultObj = radarResultObj->next();
    }
    
    // 为已存在的 ZHWeaponLoadInfo 对象注册更新回调
    CtRefZHWeaponLoadInfo* weaponLoadInfoObj = g_zhWeaponLoadInfoList->first();
    while (weaponLoadInfoObj) {
        weaponLoadInfoObj->addPostUpdateCallback(onZHWeaponLoadInfoUpdated, nullptr);
        weaponLoadInfoObj = weaponLoadInfoObj->next();
    }

    // 为已存在的 Radar 对象注册更新回调
    CtRefRadar* legacyRadarObj = g_radarList->first();
    while (legacyRadarObj) {
        legacyRadarObj->addPostUpdateCallback(onRadarUpdated, nullptr);
        legacyRadarObj = legacyRadarObj->next();
    }

    // 为已存在的 ExtendEntity 对象注册更新回调
    CtRefExtendEntity* extendObj = g_extendEntityList->first();
    while (extendObj) {
        extendObj->addPostUpdateCallback(onExtendEntityUpdated, nullptr);
        extendObj = extendObj->next();
    }

    // 为已存在的 RadarResults 对象注册更新回调
    CtRefRadarResults* radarResultsObj = g_radarResultsList->first();
    while (radarResultsObj) {
        radarResultsObj->addPostUpdateCallback(onRadarResultsUpdated, nullptr);
        radarResultsObj = radarResultsObj->next();
    }

    // 为已存在的 ZHElectroOpticalRadarResult 对象注册更新回调
    CtRefZHElectroOpticalRadarResult* electroResultObj = g_zhElectroOpticalRadarResultList->first();
    while (electroResultObj) {
        electroResultObj->addPostUpdateCallback(onZHElectroOpticalRadarResultUpdated, nullptr);
        electroResultObj = electroResultObj->next();
    }
    
    // 为已存在的标准装备实体对象注册更新回调
    DtReflectedEntity* entityObj = g_entityList->first();
    while (entityObj) {
        entityObj->addPostUpdateCallback(onEntityUpdated, nullptr);
        entityObj = entityObj->next();
    }
    
    // Step 6: 注册交互回调
    // IJammer 交互回调：当远程联邦成员发送 IJammer 交互时触发
    CtIJammerInteraction::addCallback(_conn.get(), onIJammerInteractionReceived, nullptr);
    
    // IPassiveJammer 交互回调：当远程联邦成员发送 IPassiveJammer 交互时触发
    CtIPassiveJammerInteraction::addCallback(_conn.get(), onIPassiveJammerInteractionReceived, nullptr);
    
    // IWeatherInit 交互回调：当远程联邦成员发送 IWeatherInit 交互时触发
    CtIWeatherInitInteraction::addCallback(_conn.get(), onIWeatherInitInteractionReceived, nullptr);
    
    // IWeatherResults 交互回调：当远程联邦成员发送 IWeatherResults 交互时触发
    CtIWeatherResultsInteraction::addCallback(_conn.get(), onIWeatherResultsInteractionReceived, nullptr);
    
    // ZHAircraftSimulatorConfigReq 交互回调：当远程联邦成员发送 ZHAircraftSimulatorConfigReq 交互时触发
    CtZHAircraftSimulatorConfigReqInteraction::addCallback(_conn.get(), onZHAircraftSimulatorConfigReqInteractionReceived, nullptr);
    
    // ZHRadarReq 交互回调：当远程联邦成员发送 ZHRadarReq 交互时触发
    CtZHRadarReqInteraction::addCallback(_conn.get(), onZHRadarReqInteractionReceived, nullptr);
    
    // ZHLightWeaponDamageReq 交互回调：当远程联邦成员发送 ZHLightWeaponDamageReq 交互时触发
    CtZHLightWeaponDamageReqInteraction::addCallback(_conn.get(), onZHLightWeaponDamageReqInteractionReceived, nullptr);
    
    // ZHLightWeaponExplodeReq 交互回调：当远程联邦成员发送 ZHLightWeaponExplodeReq 交互时触发
    CtZHLightWeaponExplodeReqInteraction::addCallback(_conn.get(), onZHLightWeaponExplodeReqInteractionReceived, nullptr);

    return true;
}

void VRLinkManager::pumpOnce() {
    if (!_conn) return;
    // drainInput() 会处理从RTI接收到的所有消息，包括：
    // IJammer:
    //   1. 对象发现消息 -> 触发 onIJammerAdded 回调
    //   2. 对象属性更新消息 -> 触发 onIJammerUpdated 回调（通过对象的postUpdate回调）
    //   3. 对象删除消息 -> 触发 onIJammerRemoved 回调
    // IPassiveJammer:
    //   1. 对象发现消息 -> 触发 onIPassiveJammerAdded 回调
    //   2. 对象属性更新消息 -> 触发 onIPassiveJammerUpdated 回调（通过对象的postUpdate回调）
    //   3. 对象删除消息 -> 触发 onIPassiveJammerRemoved 回调
    // ZHAircraftEntity:
    //   1. 对象发现消息 -> 触发 onZHAircraftEntityAdded 回调
    //   2. 对象属性更新消息 -> 触发 onZHAircraftEntityUpdated 回调（通过对象的postUpdate回调）
    //   3. 对象删除消息 -> 触发 onZHAircraftEntityRemoved 回调
    // ZHRadar:
    //   1. 对象发现消息 -> 触发 onZHRadarAdded 回调
    //   2. 对象属性更新消息 -> 触发 onZHRadarUpdated 回调（通过对象的postUpdate回调）
    //   3. 对象删除消息 -> 触发 onZHRadarRemoved 回调
    // ZHLightWeaponPayload:
    //   1. 对象发现消息 -> 触发 onZHLightWeaponPayloadAdded 回调
    //   2. 对象属性更新消息 -> 触发 onZHLightWeaponPayloadUpdated 回调（通过对象的postUpdate回调）
    //   3. 对象删除消息 -> 触发 onZHLightWeaponPayloadRemoved 回调
    // ZHRadarResult:
    //   1. 对象发现消息 -> 触发 onZHRadarResultAdded 回调
    //   2. 对象属性更新消息 -> 触发 onZHRadarResultUpdated 回调（通过对象的postUpdate回调）
    //   3. 对象删除消息 -> 触发 onZHRadarResultRemoved 回调
    // ZHWeaponLoadInfo:
    //   1. 对象发现消息 -> 触发 onZHWeaponLoadInfoAdded 回调
    //   2. 对象属性更新消息 -> 触发 onZHWeaponLoadInfoUpdated 回调（通过对象的postUpdate回调）
    //   3. 对象删除消息 -> 触发 onZHWeaponLoadInfoRemoved 回调
    // IJammer 交互:
    //   1. 交互接收消息 -> 触发 onIJammerInteractionReceived 回调
    // IPassiveJammer 交互:
    //   1. 交互接收消息 -> 触发 onIPassiveJammerInteractionReceived 回调
    // IWeatherInit 交互:
    //   1. 交互接收消息 -> 触发 onIWeatherInitInteractionReceived 回调
    // IWeatherResults 交互:
    //   1. 交互接收消息 -> 触发 onIWeatherResultsInteractionReceived 回调
    // ZHAircraftSimulatorConfigReq 交互:
    //   1. 交互接收消息 -> 触发 onZHAircraftSimulatorConfigReqInteractionReceived 回调
    // ZHRadarReq 交互:
    //   1. 交互接收消息 -> 触发 onZHRadarReqInteractionReceived 回调
    // ZHLightWeaponDamageReq 交互:
    //   1. 交互接收消息 -> 触发 onZHLightWeaponDamageReqInteractionReceived 回调
    // ZHLightWeaponExplodeReq 交互:
    //   1. 交互接收消息 -> 触发 onZHLightWeaponExplodeReqInteractionReceived 回调
    _conn->drainInput();
    // 注意：CtRefIJammerList 和 CtRefIPassiveJammerList 继承自 DtReflectedObjectList，
    // 不需要显式调用 tick()，VR-Link 会在 drainInput() 内部自动处理对象列表的更新和回调触发
}

bool VRLinkManager::publishRadarControlInteraction(const char* platform_id,
    const char* equipment_id,
    int state,
    double mission_time) {
    if (!_conn) {
        return false;
    }
    if (!platform_id || !equipment_id) {
        return false;
    }

    try {
        CtIRadarControllerInteraction interaction;
        interaction.setplatform_id(platform_id);
        interaction.setequipment_id(equipment_id);
        interaction.setstate(state);
        interaction.setmission_time(mission_time);
        _conn->sendStamped(interaction);
        return true;
    }
    catch (...) {
        return false;
    }
}

VRLinkManager::~VRLinkManager() {
    // 析构函数实现，确保 DtExerciseConn 的完整定义可见
    // 直接清理资源，shutdown() 可能已经被调用过
    g_jammerList.reset();
    g_passiveJammerList.reset();
    g_zhAircraftEntityList.reset();
    g_zhRadarList.reset();
    g_zhLightWeaponPayloadList.reset();
    g_zhRadarResultList.reset();
    g_zhWeaponLoadInfoList.reset();
    g_radarList.reset();
    g_extendEntityList.reset();
    g_radarResultsList.reset();
    g_zhElectroOpticalRadarResultList.reset();
    g_entityList.reset();
    _conn.reset();
}

void VRLinkManager::shutdown() {
    g_jammerList.reset();
    g_passiveJammerList.reset();
    g_zhAircraftEntityList.reset();
    g_zhRadarList.reset();
    g_zhLightWeaponPayloadList.reset();
    g_zhRadarResultList.reset();
    g_zhWeaponLoadInfoList.reset();
    g_radarList.reset();
    g_extendEntityList.reset();
    g_radarResultsList.reset();
    g_zhElectroOpticalRadarResultList.reset();
    g_entityList.reset();
    _conn.reset();
}

