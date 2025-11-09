#include "ZHRadarResultCallbacks.h"
#include "../EventBridge.h"
#include "../zhradarresult/CtZHRadarResultStateRepository.h"

#include <sstream>

// 前向声明更新回调
void onZHRadarResultUpdated(CtRefZHRadarResult* obj, void* userData);

// 回调包装函数 - 用于 ZHRadarResult 添加
void onZHRadarResultAdded(CtRefZHRadarResult* obj, void* userData) {
    if (!obj) return;
    
    // 为新添加的对象注册更新回调
    obj->addPostUpdateCallback(onZHRadarResultUpdated, nullptr);
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
        CtZHRadarResultStateRepository* rep = obj->ZHRadarResultStateRepository();
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
        
        cb("OBJECT", "ZHRadarResult_DISCOVER", "RemoteFederate",
            idStream.str().c_str(), ss.str().c_str());
    }
}

// 回调包装函数 - 用于 ZHRadarResult 更新
void onZHRadarResultUpdated(CtRefZHRadarResult* obj, void* userData) {
    if (!obj) return;
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
        CtZHRadarResultStateRepository* rep = obj->ZHRadarResultStateRepository();
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
        
        cb("OBJECT", "ZHRadarResult_UPDATE", "RemoteFederate",
            idStream.str().c_str(), ss.str().c_str());
    }
}

// 回调包装函数 - 用于 ZHRadarResult 移除
void onZHRadarResultRemoved(CtRefZHRadarResult* obj, void* userData) {
    if (!obj) return;
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
        CtZHRadarResultStateRepository* rep = obj->ZHRadarResultStateRepository();
        if (!rep) return;
        
        // 使用Timestamp作为ID
        std::ostringstream idStream;
        idStream << rep->Timestamp();
        
        cb("OBJECT", "ZHRadarResult_REMOVED", "RemoteFederate",
            idStream.str().c_str(),
            "{\"removed\":true}");
    }
}

