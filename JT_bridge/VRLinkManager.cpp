#include "VRLinkManager.h"
#include "EventBridge.h"

// VR-Link
#include <vl/exerciseConn.h>
#include <vl/rprFomMap.h>

// Jammer 模块
#include "jammer/CtRefIJammer.h"
#include "jammer/CtIJammerStateRepository.h"
#include "jammer/CtRefIJammerList.h"

#include <sstream>
#include <memory>

// 实现自定义删除器
void DtExerciseConnDeleter::operator()(DtExerciseConn* p) const {
    if (p) {
        delete p;
    }
}

static std::unique_ptr<CtRefIJammerList> g_jammerList;

// 前向声明回调函数
static void onIJammerUpdated(CtRefIJammer* obj, void* userData);

// 回调包装函数 - 用于 Jammer 添加
static void onIJammerAdded(CtRefIJammer* obj, void* userData) {
    if (!obj) return;
    
    // 为新添加的对象注册更新回调
    obj->addPostUpdateCallback(onIJammerUpdated, nullptr);
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
        CtIJammerStateRepository* rep = obj->IJammerStateRepository();
        if (!rep) return;
        
        std::ostringstream ss;
        ss << "{"
            << "\"JammerID\":\"" << rep->JammerID() << "\","
            << "\"power\":" << rep->JM_power() << ","
            << "\"freq\":" << rep->center_frequency() << ","
            << "\"bandwidth\":" << rep->bandwidth() << ","
            << "\"beamwidth\":" << rep->beamwidth() << ","
            << "\"mode\":" << rep->interference_mode()
            << "}";
        cb("OBJECT", "IJammer_DISCOVER", "RemoteFederate",
            rep->JammerID().c_str(), ss.str().c_str());
    }
}

// 回调包装函数 - 用于 Jammer 更新
static void onIJammerUpdated(CtRefIJammer* obj, void* userData) {
    if (!obj) return;
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
        CtIJammerStateRepository* rep = obj->IJammerStateRepository();
        if (!rep) return;
        
        std::ostringstream ss;
        ss << "{"
            << "\"JammerID\":\"" << rep->JammerID() << "\","
            << "\"power\":" << rep->JM_power() << ","
            << "\"freq\":" << rep->center_frequency() << ","
            << "\"bandwidth\":" << rep->bandwidth() << ","
            << "\"beamwidth\":" << rep->beamwidth() << ","
            << "\"mode\":" << rep->interference_mode()
            << "}";
        cb("OBJECT", "IJammer_UPDATE", "RemoteFederate",
            rep->JammerID().c_str(), ss.str().c_str());
    }
}

// 回调包装函数 - 用于 Jammer 移除
static void onIJammerRemoved(CtRefIJammer* obj, void* userData) {
    if (!obj) return;
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
        CtIJammerStateRepository* rep = obj->IJammerStateRepository();
        if (!rep) return;
        
        cb("OBJECT", "IJammer_REMOVED", "RemoteFederate",
            rep->JammerID().c_str(),
            "{\"removed\":true}");
    }
}

VRLinkManager& VRLinkManager::I() {
    static VRLinkManager instance;
    return instance;
}

bool VRLinkManager::init(const char* fed, const char* fdr) {
    // Step 1: 建立 VR-Link 联邦连接
    _conn.reset(new DtExerciseConn(fed, fdr, new DtRprFomMapper(0.8)));

    // Step 2: 设置对象仓库创建函数
    CtRefIJammer::setStateRepCreator(CtIJammerStateRepository::create);

    // Step 3: 创建对象订阅列表
    // 注意：构造函数中会自动调用 addObjectClassByName("HLAobjectRoot.IJammer")
    // 这会向RTI订阅该类对象，当远程联邦成员发布该类对象时，会自动收到通知
    g_jammerList.reset(new CtRefIJammerList(_conn.get()));

    // Step 4: 注册回调
    // 添加回调：当远程联邦成员发布新的IJammer对象时触发
    g_jammerList->addIJammerAdditionCallback(onIJammerAdded, nullptr);
    // 移除回调：当远程IJammer对象被删除时触发
    g_jammerList->addIJammerRemovalCallback(onIJammerRemoved, nullptr);
    
    // Step 5: 为已存在的对象注册更新回调（如果有的话）
    // 注意：在初始化时通常还没有对象，因为对象发现是异步的
    // 但如果有对象（例如从之前的会话恢复），需要为它们注册更新回调
    CtRefIJammer* obj = g_jammerList->first();
    while (obj) {
        obj->addPostUpdateCallback(onIJammerUpdated, nullptr);
        obj = obj->next();
    }

    return true;
}

void VRLinkManager::pumpOnce() {
    if (!_conn) return;
    // drainInput() 会处理从RTI接收到的所有消息，包括：
    // 1. 对象发现消息 -> 触发 onIJammerAdded 回调
    // 2. 对象属性更新消息 -> 触发 onIJammerUpdated 回调（通过对象的postUpdate回调）
    // 3. 对象删除消息 -> 触发 onIJammerRemoved 回调
    _conn->drainInput();
    // 注意：CtRefIJammerList 继承自 DtReflectedObjectList，不需要显式调用 tick()
    // VR-Link 会在 drainInput() 内部自动处理对象列表的更新和回调触发
}

VRLinkManager::~VRLinkManager() {
    // 析构函数实现，确保 DtExerciseConn 的完整定义可见
    // 直接清理资源，shutdown() 可能已经被调用过
    g_jammerList.reset();
    _conn.reset();
}

void VRLinkManager::shutdown() {
    g_jammerList.reset();
    _conn.reset();
}

