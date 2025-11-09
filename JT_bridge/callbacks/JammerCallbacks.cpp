#include "JammerCallbacks.h"
#include "../EventBridge.h"
#include "../jammer/CtIJammerStateRepository.h"

#include <sstream>

// 前向声明更新回调
void onIJammerUpdated(CtRefIJammer* obj, void* userData);

// 回调包装函数 - 用于 Jammer 添加
void onIJammerAdded(CtRefIJammer* obj, void* userData) {
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
void onIJammerUpdated(CtRefIJammer* obj, void* userData) {
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
void onIJammerRemoved(CtRefIJammer* obj, void* userData) {
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

