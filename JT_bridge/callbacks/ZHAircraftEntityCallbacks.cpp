#include "ZHAircraftEntityCallbacks.h"
#include "../EventBridge.h"
#include "../ZHAircraftEntity/CtZHAircraftEntityStateRepository.h"

#include <sstream>
#include <unordered_set>

// 前向声明更新回调
void onZHAircraftEntityUpdated(CtRefZHAircraftEntity* obj, void* userData);

// 用于跟踪已经发送过DISCOVER事件的对象
static std::unordered_set<CtRefZHAircraftEntity*> g_discoveredAircraftEntities;

// 回调包装函数 - 用于 ZHAircraftEntity 添加
void onZHAircraftEntityAdded(CtRefZHAircraftEntity* obj, void* userData) {
    if (!obj) return;
    
    // 为新添加的对象注册更新回调
    // 注意：不在这里发送DISCOVER事件，因为此时对象属性可能还是默认值
    // 等待第一次属性更新后再发送DISCOVER事件
    obj->addPostUpdateCallback(onZHAircraftEntityUpdated, nullptr);
}

// 回调包装函数 - 用于 ZHAircraftEntity 更新
void onZHAircraftEntityUpdated(CtRefZHAircraftEntity* obj, void* userData) {
    if (!obj) return;
    
    JavaEventCallback cb = EventBridge::get();
    if (!cb) return;
    
    CtZHAircraftEntityStateRepository* rep = obj->ZHAircraftEntityStateRepository();
    if (!rep) return;
    
    std::ostringstream ss;
    ss << "{"
        << "\"id\":\"" << rep->id() << "\","
        << "\"type\":" << rep->type() << ","
        << "\"x\":" << rep->x() << ","
        << "\"y\":" << rep->y() << ","
        << "\"z\":" << rep->z() << ","
        << "\"roll\":" << rep->roll() << ","
        << "\"pitch\":" << rep->pitch() << ","
        << "\"yaw\":" << rep->yaw() << ","
        << "\"vx\":" << rep->vx() << ","
        << "\"vy\":" << rep->vy() << ","
        << "\"vz\":" << rep->vz() << ","
        << "\"damage\":" << rep->damage();
    if (!rep->other1().empty()) {
        ss << ",\"other1\":\"" << rep->other1() << "\"";
    }
    if (!rep->other2().empty()) {
        ss << ",\"other2\":\"" << rep->other2() << "\"";
    }
    if (!rep->other3().empty()) {
        ss << ",\"other3\":\"" << rep->other3() << "\"";
    }
    if (!rep->other4().empty()) {
        ss << ",\"other4\":\"" << rep->other4() << "\"";
    }
    if (!rep->other5().empty()) {
        ss << ",\"other5\":\"" << rep->other5() << "\"";
    }
    if (!rep->other6().empty()) {
        ss << ",\"other6\":\"" << rep->other6() << "\"";
    }
    ss << "}";
    
    // 检查是否是第一次更新
    bool isFirstUpdate = (g_discoveredAircraftEntities.find(obj) == g_discoveredAircraftEntities.end());
    
    if (isFirstUpdate) {
        // 第一次更新：发送DISCOVER事件
        g_discoveredAircraftEntities.insert(obj);
        cb("ZHAircraftEntity_DISCOVER",
            rep->id().c_str(), ss.str().c_str());
    } else {
        // 后续更新：发送UPDATE事件
        cb("ZHAircraftEntity_UPDATE",
            rep->id().c_str(), ss.str().c_str());
    }
}

// 回调包装函数 - 用于 ZHAircraftEntity 移除
void onZHAircraftEntityRemoved(CtRefZHAircraftEntity* obj, void* userData) {
    if (!obj) return;
    
    // 从已发现列表中移除
    g_discoveredAircraftEntities.erase(obj);
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
        CtZHAircraftEntityStateRepository* rep = obj->ZHAircraftEntityStateRepository();
        if (!rep) return;
        
        cb("ZHAircraftEntity_REMOVED",
            rep->id().c_str(),
            "{\"removed\":true}");
    }
}

