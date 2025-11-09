#include "ZHLightWeaponPayloadCallbacks.h"
#include "../EventBridge.h"
#include "../ZHLightWeaponPayload/CtZHLightWeaponPayloadStateRepository.h"

#include <sstream>

// 前向声明更新回调
void onZHLightWeaponPayloadUpdated(CtRefZHLightWeaponPayload* obj, void* userData);

// 回调包装函数 - 用于 ZHLightWeaponPayload 添加
void onZHLightWeaponPayloadAdded(CtRefZHLightWeaponPayload* obj, void* userData) {
    if (!obj) return;
    
    // 为新添加的对象注册更新回调
    obj->addPostUpdateCallback(onZHLightWeaponPayloadUpdated, nullptr);
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
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
        
        cb("OBJECT", "ZHLightWeaponPayload_DISCOVER", "RemoteFederate",
            rep->id().c_str(), ss.str().c_str());
    }
}

// 回调包装函数 - 用于 ZHLightWeaponPayload 更新
void onZHLightWeaponPayloadUpdated(CtRefZHLightWeaponPayload* obj, void* userData) {
    if (!obj) return;
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
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
        
        cb("OBJECT", "ZHLightWeaponPayload_UPDATE", "RemoteFederate",
            rep->id().c_str(), ss.str().c_str());
    }
}

// 回调包装函数 - 用于 ZHLightWeaponPayload 移除
void onZHLightWeaponPayloadRemoved(CtRefZHLightWeaponPayload* obj, void* userData) {
    if (!obj) return;
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
        CtZHLightWeaponPayloadStateRepository* rep = obj->ZHLightWeaponPayloadStateRepository();
        if (!rep) return;
        
        cb("OBJECT", "ZHLightWeaponPayload_REMOVED", "RemoteFederate",
            rep->id().c_str(),
            "{\"removed\":true}");
    }
}

