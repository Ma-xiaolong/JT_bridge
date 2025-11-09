#include "VRLinkManager.h"

// VR-Link
#include <vl/exerciseConn.h>
#include <vl/rprFomMap.h>

// 对象列表
#include "jammer/CtRefIJammer.h"
#include "jammer/CtIJammerStateRepository.h"
#include "jammer/CtRefIJammerList.h"

#include "passiveJammer/CtRefIPassiveJammer.h"
#include "passiveJammer/CtIPassiveJammerStateRepository.h"
#include "passiveJammer/CtRefIPassiveJammerList.h"

// 回调函数
#include "callbacks/JammerCallbacks.h"
#include "callbacks/PassiveJammerCallbacks.h"

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

VRLinkManager& VRLinkManager::I() {
    static VRLinkManager instance;
    return instance;
}

bool VRLinkManager::init(const char* fed, const char* fdr) {
    // Step 1: 建立 VR-Link 联邦连接
    _conn.reset(new DtExerciseConn(fed, fdr, new DtRprFomMapper(0.8)));

    // Step 2: 设置对象仓库创建函数
    CtRefIJammer::setStateRepCreator(CtIJammerStateRepository::create);
    CtRefIPassiveJammer::setStateRepCreator(CtIPassiveJammerStateRepository::create);

    // Step 3: 创建对象订阅列表
    // 注意：构造函数中会自动调用 addObjectClassByName("HLAobjectRoot.IJammer")
    // 这会向RTI订阅该类对象，当远程联邦成员发布该类对象时，会自动收到通知
    g_jammerList.reset(new CtRefIJammerList(_conn.get()));
    g_passiveJammerList.reset(new CtRefIPassiveJammerList(_conn.get()));

    // Step 4: 注册回调
    // IJammer 添加回调：当远程联邦成员发布新的IJammer对象时触发
    g_jammerList->addIJammerAdditionCallback(onIJammerAdded, nullptr);
    // IJammer 移除回调：当远程IJammer对象被删除时触发
    g_jammerList->addIJammerRemovalCallback(onIJammerRemoved, nullptr);
    
    // IPassiveJammer 添加回调：当远程联邦成员发布新的IPassiveJammer对象时触发
    g_passiveJammerList->addIPassiveJammerAdditionCallback(onIPassiveJammerAdded, nullptr);
    // IPassiveJammer 移除回调：当远程IPassiveJammer对象被删除时触发
    g_passiveJammerList->addIPassiveJammerRemovalCallback(onIPassiveJammerRemoved, nullptr);
    
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
    _conn->drainInput();
    // 注意：CtRefIJammerList 和 CtRefIPassiveJammerList 继承自 DtReflectedObjectList，
    // 不需要显式调用 tick()，VR-Link 会在 drainInput() 内部自动处理对象列表的更新和回调触发
}

VRLinkManager::~VRLinkManager() {
    // 析构函数实现，确保 DtExerciseConn 的完整定义可见
    // 直接清理资源，shutdown() 可能已经被调用过
    g_jammerList.reset();
    g_passiveJammerList.reset();
    _conn.reset();
}

void VRLinkManager::shutdown() {
    g_jammerList.reset();
    g_passiveJammerList.reset();
    _conn.reset();
}

