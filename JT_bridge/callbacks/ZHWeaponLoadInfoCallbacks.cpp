#include "ZHWeaponLoadInfoCallbacks.h"
#include "../EventBridge.h"
#include "../ZHWeaponLoadInfo/CtZHWeaponLoadInfoStateRepository.h"

#include <sstream>

// 前向声明更新回调
void onZHWeaponLoadInfoUpdated(CtRefZHWeaponLoadInfo* obj, void* userData);

// 回调包装函数 - 用于 ZHWeaponLoadInfo 添加
void onZHWeaponLoadInfoAdded(CtRefZHWeaponLoadInfo* obj, void* userData) {
    if (!obj) return;
    
    // 为新添加的对象注册更新回调
    obj->addPostUpdateCallback(onZHWeaponLoadInfoUpdated, nullptr);
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
        CtZHWeaponLoadInfoStateRepository* rep = obj->ZHWeaponLoadInfoStateRepository();
        if (!rep) return;
        
        std::ostringstream ss;
        ss << "{"
            << "\"Timestamp\":" << rep->Timestamp() << ","
            << "\"Result\":\"" << rep->Result() << "\"";
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
        
        // 使用Timestamp作为ID
        std::ostringstream idStream;
        idStream << rep->Timestamp();
        
        cb("OBJECT", "ZHWeaponLoadInfo_DISCOVER", "RemoteFederate",
            idStream.str().c_str(), ss.str().c_str());
    }
}

// 回调包装函数 - 用于 ZHWeaponLoadInfo 更新
void onZHWeaponLoadInfoUpdated(CtRefZHWeaponLoadInfo* obj, void* userData) {
    if (!obj) return;
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
        CtZHWeaponLoadInfoStateRepository* rep = obj->ZHWeaponLoadInfoStateRepository();
        if (!rep) return;
        
        std::ostringstream ss;
        ss << "{"
            << "\"Timestamp\":" << rep->Timestamp() << ","
            << "\"Result\":\"" << rep->Result() << "\"";
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
        
        // 使用Timestamp作为ID
        std::ostringstream idStream;
        idStream << rep->Timestamp();
        
        cb("OBJECT", "ZHWeaponLoadInfo_UPDATE", "RemoteFederate",
            idStream.str().c_str(), ss.str().c_str());
    }
}

// 回调包装函数 - 用于 ZHWeaponLoadInfo 移除
void onZHWeaponLoadInfoRemoved(CtRefZHWeaponLoadInfo* obj, void* userData) {
    if (!obj) return;
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
        CtZHWeaponLoadInfoStateRepository* rep = obj->ZHWeaponLoadInfoStateRepository();
        if (!rep) return;
        
        // 使用Timestamp作为ID
        std::ostringstream idStream;
        idStream << rep->Timestamp();
        
        cb("OBJECT", "ZHWeaponLoadInfo_REMOVED", "RemoteFederate",
            idStream.str().c_str(),
            "{\"removed\":true}");
    }
}

