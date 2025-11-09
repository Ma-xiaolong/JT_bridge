#include "ZHRadarCallbacks.h"
#include "../EventBridge.h"
#include "../zhradar/CtZHRadarStateRepository.h"

#include <sstream>

// 前向声明更新回调
void onZHRadarUpdated(CtRefZHRadar* obj, void* userData);

// 回调包装函数 - 用于 ZHRadar 添加
void onZHRadarAdded(CtRefZHRadar* obj, void* userData) {
    if (!obj) return;
    
    // 为新添加的对象注册更新回调
    obj->addPostUpdateCallback(onZHRadarUpdated, nullptr);
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
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
        
        cb("OBJECT", "ZHRadar_DISCOVER", "RemoteFederate",
            rep->id().c_str(), ss.str().c_str());
    }
}

// 回调包装函数 - 用于 ZHRadar 更新
void onZHRadarUpdated(CtRefZHRadar* obj, void* userData) {
    if (!obj) return;
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
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
        
        cb("OBJECT", "ZHRadar_UPDATE", "RemoteFederate",
            rep->id().c_str(), ss.str().c_str());
    }
}

// 回调包装函数 - 用于 ZHRadar 移除
void onZHRadarRemoved(CtRefZHRadar* obj, void* userData) {
    if (!obj) return;
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
        CtZHRadarStateRepository* rep = obj->ZHRadarStateRepository();
        if (!rep) return;
        
        cb("OBJECT", "ZHRadar_REMOVED", "RemoteFederate",
            rep->id().c_str(),
            "{\"removed\":true}");
    }
}

