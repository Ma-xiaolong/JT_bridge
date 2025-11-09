#include "PassiveJammerCallbacks.h"
#include "../EventBridge.h"
#include "../passiveJammer/CtIPassiveJammerStateRepository.h"

#include <sstream>

// 前向声明更新回调
void onIPassiveJammerUpdated(CtRefIPassiveJammer* obj, void* userData);

// 回调包装函数 - 用于 PassiveJammer 添加
void onIPassiveJammerAdded(CtRefIPassiveJammer* obj, void* userData) {
    if (!obj) return;
    
    // 为新添加的对象注册更新回调
    obj->addPostUpdateCallback(onIPassiveJammerUpdated, nullptr);
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
        CtIPassiveJammerStateRepository* rep = obj->IPassiveJammerStateRepository();
        if (!rep) return;
        
        std::ostringstream ss;
        ss << "{"
            << "\"passiveJammerId\":\"" << rep->passiveJammerId() << "\","
            << "\"ht\":" << rep->ht() << ","
            << "\"bt\":" << rep->bt() << ","
            << "\"jam_mode\":" << rep->jam_mode() << ","
            << "\"rcs\":" << rep->rcs() << ","
            << "\"btgrkd\":" << rep->btgrkd() << ","
            << "\"btgrgd\":" << rep->btgrgd() << ","
            << "\"btgrsl\":" << rep->btgrsl() << ","
            << "\"btgryxxs\":" << rep->btgryxxs() << ","
            << "\"btgrsc\":" << rep->btgrsc() << ","
            << "\"btgrsg\":" << rep->btgrsg() << ","
            << "\"btgrzksj\":" << rep->btgrzksj() << ","
            << "\"btgrlksj\":" << rep->btgrlksj() << ","
            << "\"sjxjflbc\":" << rep->sjxjflbc();
        if (!rep->other1().empty()) {
            ss << ",\"other1\":\"" << rep->other1() << "\"";
        }
        if (!rep->other2().empty()) {
            ss << ",\"other2\":\"" << rep->other2() << "\"";
        }
        if (!rep->other3().empty()) {
            ss << ",\"other3\":\"" << rep->other3() << "\"";
        }
        ss << "}";
        
        cb("OBJECT", "IPassiveJammer_DISCOVER", "RemoteFederate",
            rep->passiveJammerId().c_str(), ss.str().c_str());
    }
}

// 回调包装函数 - 用于 PassiveJammer 更新
void onIPassiveJammerUpdated(CtRefIPassiveJammer* obj, void* userData) {
    if (!obj) return;
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
        CtIPassiveJammerStateRepository* rep = obj->IPassiveJammerStateRepository();
        if (!rep) return;
        
        std::ostringstream ss;
        ss << "{"
            << "\"passiveJammerId\":\"" << rep->passiveJammerId() << "\","
            << "\"ht\":" << rep->ht() << ","
            << "\"bt\":" << rep->bt() << ","
            << "\"jam_mode\":" << rep->jam_mode() << ","
            << "\"rcs\":" << rep->rcs() << ","
            << "\"btgrkd\":" << rep->btgrkd() << ","
            << "\"btgrgd\":" << rep->btgrgd() << ","
            << "\"btgrsl\":" << rep->btgrsl() << ","
            << "\"btgryxxs\":" << rep->btgryxxs() << ","
            << "\"btgrsc\":" << rep->btgrsc() << ","
            << "\"btgrsg\":" << rep->btgrsg() << ","
            << "\"btgrzksj\":" << rep->btgrzksj() << ","
            << "\"btgrlksj\":" << rep->btgrlksj() << ","
            << "\"sjxjflbc\":" << rep->sjxjflbc();
        if (!rep->other1().empty()) {
            ss << ",\"other1\":\"" << rep->other1() << "\"";
        }
        if (!rep->other2().empty()) {
            ss << ",\"other2\":\"" << rep->other2() << "\"";
        }
        if (!rep->other3().empty()) {
            ss << ",\"other3\":\"" << rep->other3() << "\"";
        }
        ss << "}";
        
        cb("OBJECT", "IPassiveJammer_UPDATE", "RemoteFederate",
            rep->passiveJammerId().c_str(), ss.str().c_str());
    }
}

// 回调包装函数 - 用于 PassiveJammer 移除
void onIPassiveJammerRemoved(CtRefIPassiveJammer* obj, void* userData) {
    if (!obj) return;
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
        CtIPassiveJammerStateRepository* rep = obj->IPassiveJammerStateRepository();
        if (!rep) return;
        
        cb("OBJECT", "IPassiveJammer_REMOVED", "RemoteFederate",
            rep->passiveJammerId().c_str(),
            "{\"removed\":true}");
    }
}

