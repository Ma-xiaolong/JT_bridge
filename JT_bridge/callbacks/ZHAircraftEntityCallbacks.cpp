#include "ZHAircraftEntityCallbacks.h"
#include "../EventBridge.h"
#include "../ZHAircraftEntity/CtZHAircraftEntityStateRepository.h"

#include <sstream>

// 前向声明更新回调
void onZHAircraftEntityUpdated(CtRefZHAircraftEntity* obj, void* userData);

// 回调包装函数 - 用于 ZHAircraftEntity 添加
void onZHAircraftEntityAdded(CtRefZHAircraftEntity* obj, void* userData) {
    if (!obj) return;
    
    // 为新添加的对象注册更新回调
    obj->addPostUpdateCallback(onZHAircraftEntityUpdated, nullptr);
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
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
        
        cb("OBJECT", "ZHAircraftEntity_DISCOVER", "RemoteFederate",
            rep->id().c_str(), ss.str().c_str());
    }
}

// 回调包装函数 - 用于 ZHAircraftEntity 更新
void onZHAircraftEntityUpdated(CtRefZHAircraftEntity* obj, void* userData) {
    if (!obj) return;
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
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
        
        cb("OBJECT", "ZHAircraftEntity_UPDATE", "RemoteFederate",
            rep->id().c_str(), ss.str().c_str());
    }
}

// 回调包装函数 - 用于 ZHAircraftEntity 移除
void onZHAircraftEntityRemoved(CtRefZHAircraftEntity* obj, void* userData) {
    if (!obj) return;
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
        CtZHAircraftEntityStateRepository* rep = obj->ZHAircraftEntityStateRepository();
        if (!rep) return;
        
        cb("OBJECT", "ZHAircraftEntity_REMOVED", "RemoteFederate",
            rep->id().c_str(),
            "{\"removed\":true}");
    }
}

