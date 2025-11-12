#include "ZHWeaponLoadInfoCallbacks.h"
#include "../EventBridge.h"
#include "../ZHWeaponLoadInfo/CtZHWeaponLoadInfoStateRepository.h"

#include <sstream>
#include <unordered_set>

// 前向声明更新回调
void onZHWeaponLoadInfoUpdated(CtRefZHWeaponLoadInfo* obj, void* userData);

// 用于跟踪已经发送过DISCOVER事件的对象
static std::unordered_set<CtRefZHWeaponLoadInfo*> g_discoveredWeaponLoadInfos;

// 回调包装函数 - 用于 ZHWeaponLoadInfo 添加
void onZHWeaponLoadInfoAdded(CtRefZHWeaponLoadInfo* obj, void* userData) {
    if (!obj) return;
    
    // 为新添加的对象注册更新回调
    // 注意：不在这里发送DISCOVER事件，因为此时对象属性可能还是默认值
    // 等待第一次属性更新后再发送DISCOVER事件
    obj->addPostUpdateCallback(onZHWeaponLoadInfoUpdated, nullptr);
}

// 回调包装函数 - 用于 ZHWeaponLoadInfo 更新
void onZHWeaponLoadInfoUpdated(CtRefZHWeaponLoadInfo* obj, void* userData) {
    if (!obj) return;
    
    JavaEventCallback cb = EventBridge::get();
    if (!cb) return;
    
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
    
    // 检查是否是第一次更新
    bool isFirstUpdate = (g_discoveredWeaponLoadInfos.find(obj) == g_discoveredWeaponLoadInfos.end());
    
    if (isFirstUpdate) {
        // 第一次更新：发送DISCOVER事件
        g_discoveredWeaponLoadInfos.insert(obj);
        cb("ZHWeaponLoadInfo_DISCOVER",
            idStream.str().c_str(), ss.str().c_str());
    } else {
        // 后续更新：发送UPDATE事件
        cb("ZHWeaponLoadInfo_UPDATE",
            idStream.str().c_str(), ss.str().c_str());
    }
}

// 回调包装函数 - 用于 ZHWeaponLoadInfo 移除
void onZHWeaponLoadInfoRemoved(CtRefZHWeaponLoadInfo* obj, void* userData) {
    if (!obj) return;
    
    // 从已发现列表中移除
    g_discoveredWeaponLoadInfos.erase(obj);
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
        CtZHWeaponLoadInfoStateRepository* rep = obj->ZHWeaponLoadInfoStateRepository();
        if (!rep) return;
        
        // 使用Timestamp作为ID
        std::ostringstream idStream;
        idStream << rep->Timestamp();
        
        cb("ZHWeaponLoadInfo_REMOVED",
            idStream.str().c_str(),
            "{\"removed\":true}");
    }
}

