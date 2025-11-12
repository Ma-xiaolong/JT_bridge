#include "JammerCallbacks.h"
#include "../EventBridge.h"
#include "../jammer/CtIJammerStateRepository.h"

#include <sstream>
#include <unordered_set>

// 前向声明更新回调
void onIJammerUpdated(CtRefIJammer* obj, void* userData);

// 用于跟踪已经发送过DISCOVER事件的对象
// 使用对象指针作为键，因为对象在生命周期内指针不会改变
static std::unordered_set<CtRefIJammer*> g_discoveredJammers;

// 回调包装函数 - 用于 Jammer 添加
void onIJammerAdded(CtRefIJammer* obj, void* userData) {
    if (!obj) return;
    
    // 为新添加的对象注册更新回调
    // 注意：不在这里发送DISCOVER事件，因为此时对象属性可能还是默认值
    // 等待第一次属性更新后再发送DISCOVER事件
    obj->addPostUpdateCallback(onIJammerUpdated, nullptr);
}

// 回调包装函数 - 用于 Jammer 更新
void onIJammerUpdated(CtRefIJammer* obj, void* userData) {
    if (!obj) return;
    
    JavaEventCallback cb = EventBridge::get();
    if (!cb) return;
    
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
    
    // 检查是否是第一次更新（即对象刚被发现后的第一次更新）
    // 如果是第一次，发送DISCOVER事件；否则发送UPDATE事件
    bool isFirstUpdate = (g_discoveredJammers.find(obj) == g_discoveredJammers.end());
    
    if (isFirstUpdate) {
        // 第一次更新：发送DISCOVER事件
        g_discoveredJammers.insert(obj);
        cb("IJammer_DISCOVER",
            rep->JammerID().c_str(), ss.str().c_str());
    } else {
        // 后续更新：发送UPDATE事件
        cb("IJammer_UPDATE",
            rep->JammerID().c_str(), ss.str().c_str());
    }
}

// 回调包装函数 - 用于 Jammer 移除
void onIJammerRemoved(CtRefIJammer* obj, void* userData) {
    if (!obj) return;
    
    // 从已发现列表中移除
    g_discoveredJammers.erase(obj);
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
        CtIJammerStateRepository* rep = obj->IJammerStateRepository();
        if (!rep) return;
        
        cb("IJammer_REMOVED",
            rep->JammerID().c_str(),
            "{\"removed\":true}");
    }
}

