#include "ZHLightWeaponPayloadCallbacks.h"
#include "../EventBridge.h"
#include "../ZHLightWeaponPayload/CtZHLightWeaponPayloadStateRepository.h"

#include <sstream>
#include <unordered_set>

// 前向声明更新回调
void onZHLightWeaponPayloadUpdated(CtRefZHLightWeaponPayload* obj, void* userData);

// 用于跟踪已经发送过DISCOVER事件的对象
static std::unordered_set<CtRefZHLightWeaponPayload*> g_discoveredLightWeaponPayloads;

// 回调包装函数 - 用于 ZHLightWeaponPayload 添加
void onZHLightWeaponPayloadAdded(CtRefZHLightWeaponPayload* obj, void* userData) {
    if (!obj) return;
    
    // 为新添加的对象注册更新回调
    // 注意：不在这里发送DISCOVER事件，因为此时对象属性可能还是默认值
    // 等待第一次属性更新后再发送DISCOVER事件
    obj->addPostUpdateCallback(onZHLightWeaponPayloadUpdated, nullptr);
}

// 回调包装函数 - 用于 ZHLightWeaponPayload 更新
void onZHLightWeaponPayloadUpdated(CtRefZHLightWeaponPayload* obj, void* userData) {
    if (!obj) return;
    
    JavaEventCallback cb = EventBridge::get();
    if (!cb) return;
    
    CtZHLightWeaponPayloadStateRepository* rep = obj->ZHLightWeaponPayloadStateRepository();
    if (!rep) return;
    
    std::ostringstream ss;
    ss << "{"
        << "\"id\":\"" << rep->id() << "\","
        << "\"weapon_type\":" << rep->weapon_type() << ","
        << "\"max_range_m\":" << rep->max_range_m() << ","
        << "\"cone_angle_deg\":" << rep->cone_angle_deg() << ","
        << "\"kill_probability\":" << rep->kill_probability() << ","
        << "\"burst_delay_s\":" << rep->burst_delay_s();
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
    bool isFirstUpdate = (g_discoveredLightWeaponPayloads.find(obj) == g_discoveredLightWeaponPayloads.end());
    
    if (isFirstUpdate) {
        // 第一次更新：发送DISCOVER事件
        g_discoveredLightWeaponPayloads.insert(obj);
        cb("ZHLightWeaponPayload_DISCOVER",
            rep->id().c_str(), ss.str().c_str());
    } else {
        // 后续更新：发送UPDATE事件
        cb("ZHLightWeaponPayload_UPDATE",
            rep->id().c_str(), ss.str().c_str());
    }
}

// 回调包装函数 - 用于 ZHLightWeaponPayload 移除
void onZHLightWeaponPayloadRemoved(CtRefZHLightWeaponPayload* obj, void* userData) {
    if (!obj) return;
    
    // 从已发现列表中移除
    g_discoveredLightWeaponPayloads.erase(obj);
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
        CtZHLightWeaponPayloadStateRepository* rep = obj->ZHLightWeaponPayloadStateRepository();
        if (!rep) return;
        
        cb("ZHLightWeaponPayload_REMOVED",
            rep->id().c_str(),
            "{\"removed\":true}");
    }
}

