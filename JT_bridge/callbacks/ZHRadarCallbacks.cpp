#include "ZHRadarCallbacks.h"
#include "../EventBridge.h"
#include "../zhradar/CtZHRadarStateRepository.h"

#include <sstream>
#include <unordered_set>

// 前向声明更新回调
void onZHRadarUpdated(CtRefZHRadar* obj, void* userData);

// 用于跟踪已经发送过DISCOVER事件的对象
static std::unordered_set<CtRefZHRadar*> g_discoveredRadars;

// 回调包装函数 - 用于 ZHRadar 添加
void onZHRadarAdded(CtRefZHRadar* obj, void* userData) {
    if (!obj) return;
    
    // 为新添加的对象注册更新回调
    // 注意：不在这里发送DISCOVER事件，因为此时对象属性可能还是默认值
    // 等待第一次属性更新后再发送DISCOVER事件
    obj->addPostUpdateCallback(onZHRadarUpdated, nullptr);
}

// 回调包装函数 - 用于 ZHRadar 更新
void onZHRadarUpdated(CtRefZHRadar* obj, void* userData) {
    if (!obj) return;
    
    JavaEventCallback cb = EventBridge::get();
    if (!cb) return;
    
    CtZHRadarStateRepository* rep = obj->ZHRadarStateRepository();
    if (!rep) return;
    
    std::ostringstream ss;
    ss << "{"
        << "\"id\":\"" << rep->id() << "\","
        << "\"type\":" << rep->type() << ","
        << "\"power1\":" << rep->power1() << ","
        << "\"max_range\":" << rep->max_range() << ","
        << "\"hori_range\":" << rep->hori_range() << ","
        << "\"vert_range\":" << rep->vert_range() << ","
        << "\"dir_follow_precision\":" << rep->dir_follow_precision() << ","
        << "\"work_type\":" << rep->work_type() << ","
        << "\"power\":" << rep->power() << ","
        << "\"width\":" << rep->width() << ","
        << "\"dis_precision\":" << rep->dis_precision() << ","
        << "\"dis_follow_range\":" << rep->dis_follow_range() << ","
        << "\"dis_follow_precision\":" << rep->dis_follow_precision() << ","
        << "\"select_target_type\":" << rep->select_target_type() << ","
        << "\"success_value\":" << rep->success_value() << ","
        << "\"receive_sensitivity\":" << rep->receive_sensitivity() << ","
        << "\"confidence\":" << rep->confidence();
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
    bool isFirstUpdate = (g_discoveredRadars.find(obj) == g_discoveredRadars.end());
    
    if (isFirstUpdate) {
        // 第一次更新：发送DISCOVER事件
        g_discoveredRadars.insert(obj);
        cb("ZHRadar_DISCOVER",
            rep->id().c_str(), ss.str().c_str());
    } else {
        // 后续更新：发送UPDATE事件
        cb("ZHRadar_UPDATE",
            rep->id().c_str(), ss.str().c_str());
    }
}

// 回调包装函数 - 用于 ZHRadar 移除
void onZHRadarRemoved(CtRefZHRadar* obj, void* userData) {
    if (!obj) return;
    
    // 从已发现列表中移除
    g_discoveredRadars.erase(obj);
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
        CtZHRadarStateRepository* rep = obj->ZHRadarStateRepository();
        if (!rep) return;
        
        cb("ZHRadar_REMOVED",
            rep->id().c_str(),
            "{\"removed\":true}");
    }
}

