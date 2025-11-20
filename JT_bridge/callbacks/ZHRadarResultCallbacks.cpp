#include "ZHRadarResultCallbacks.h"
#include "../EventBridge.h"
#include "../zhradarresult/CtZHRadarResultStateRepository.h"

#include <sstream>
#include <unordered_set>

// 前向声明更新回调
void onZHRadarResultUpdated(CtRefZHRadarResult* obj, void* userData);

// 用于跟踪已经发送过DISCOVER事件的对象
static std::unordered_set<CtRefZHRadarResult*> g_discoveredRadarResults;

// 回调包装函数 - 用于 ZHRadarResult 添加
void onZHRadarResultAdded(CtRefZHRadarResult* obj, void* userData) {
    if (!obj) return;
    
    // 为新添加的对象注册更新回调
    // 注意：不在这里发送DISCOVER事件，因为此时对象属性可能还是默认值
    // 等待第一次属性更新后再发送DISCOVER事件
    obj->addPostUpdateCallback(onZHRadarResultUpdated, nullptr);
}

// 回调包装函数 - 用于 ZHRadarResult 更新
void onZHRadarResultUpdated(CtRefZHRadarResult* obj, void* userData) {
    if (!obj) return;
    
    JavaEventCallback cb = EventBridge::get();
    if (!cb) return;
    
    CtZHRadarResultStateRepository* rep = obj->ZHRadarResultStateRepository();
    if (!rep) return;
    
    std::ostringstream ss;
    ss << "{"
        << "\"Timestamp\":" << rep->Timestamp() << ","
        << "\"Result\":\"" << rep->Result() << "\"";
    // if (!rep->other1().empty()) {
    //     ss << ",\"other1\":\"" << rep->other1() << "\"";
    // }
    // if (!rep->other2().empty()) {
    //     ss << ",\"other2\":\"" << rep->other2() << "\"";
    // }
    // if (!rep->other3().empty()) {
    //     ss << ",\"other3\":\"" << rep->other3() << "\"";
    // }
    // if (!rep->other4().empty()) {
    //     ss << ",\"other4\":\"" << rep->other4() << "\"";
    // }
    // if (!rep->other5().empty()) {
    //     ss << ",\"other5\":\"" << rep->other5() << "\"";
    // }
    // if (!rep->other6().empty()) {
    //     ss << ",\"other6\":\"" << rep->other6() << "\"";
    // }
    ss << "}";
    
    // 使用Timestamp作为ID
    std::ostringstream idStream;
    idStream << rep->Timestamp();
    
    // 检查是否是第一次更新
    bool isFirstUpdate = (g_discoveredRadarResults.find(obj) == g_discoveredRadarResults.end());
    
    if (isFirstUpdate) {
        // 第一次更新：发送DISCOVER事件
        g_discoveredRadarResults.insert(obj);
        cb("ZHRadarResult_DISCOVER",
            idStream.str().c_str(), ss.str().c_str());
    } else {
        // 后续更新：发送UPDATE事件
        cb("ZHRadarResult_UPDATE",
            idStream.str().c_str(), ss.str().c_str());
    }
}

// 回调包装函数 - 用于 ZHRadarResult 移除
void onZHRadarResultRemoved(CtRefZHRadarResult* obj, void* userData) {
    if (!obj) return;
    
    // 从已发现列表中移除
    g_discoveredRadarResults.erase(obj);
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
        CtZHRadarResultStateRepository* rep = obj->ZHRadarResultStateRepository();
        if (!rep) return;
        
        // 使用Timestamp作为ID
        std::ostringstream idStream;
        idStream << rep->Timestamp();
        
        cb("ZHRadarResult_REMOVED",
            idStream.str().c_str(),
            "{\"removed\":true}");
    }
}

