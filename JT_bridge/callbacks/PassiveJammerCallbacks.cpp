#include "PassiveJammerCallbacks.h"
#include "../EventBridge.h"
#include "../passiveJammer/CtIPassiveJammerStateRepository.h"

#include <sstream>
#include <unordered_set>

// 前向声明更新回调
void onIPassiveJammerUpdated(CtRefIPassiveJammer* obj, void* userData);

// 用于跟踪已经发送过DISCOVER事件的对象
static std::unordered_set<CtRefIPassiveJammer*> g_discoveredPassiveJammers;

// 回调包装函数 - 用于 PassiveJammer 添加
void onIPassiveJammerAdded(CtRefIPassiveJammer* obj, void* userData) {
    if (!obj) return;
    
    // 为新添加的对象注册更新回调
    // 注意：不在这里发送DISCOVER事件，因为此时对象属性可能还是默认值
    // 等待第一次属性更新后再发送DISCOVER事件
    obj->addPostUpdateCallback(onIPassiveJammerUpdated, nullptr);
}

// 回调包装函数 - 用于 PassiveJammer 更新
void onIPassiveJammerUpdated(CtRefIPassiveJammer* obj, void* userData) {
    if (!obj) return;
    
    JavaEventCallback cb = EventBridge::get();
    if (!cb) return;
    
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
    
    // 检查是否是第一次更新
    bool isFirstUpdate = (g_discoveredPassiveJammers.find(obj) == g_discoveredPassiveJammers.end());
    
    if (isFirstUpdate) {
        // 第一次更新：发送DISCOVER事件
        g_discoveredPassiveJammers.insert(obj);
        cb("IPassiveJammer_DISCOVER",
            rep->passiveJammerId().c_str(), ss.str().c_str());
    } else {
        // 后续更新：发送UPDATE事件
        cb("IPassiveJammer_UPDATE",
            rep->passiveJammerId().c_str(), ss.str().c_str());
    }
}

// 回调包装函数 - 用于 PassiveJammer 移除
void onIPassiveJammerRemoved(CtRefIPassiveJammer* obj, void* userData) {
    if (!obj) return;
    
    // 从已发现列表中移除
    g_discoveredPassiveJammers.erase(obj);
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
        CtIPassiveJammerStateRepository* rep = obj->IPassiveJammerStateRepository();
        if (!rep) return;
        
        cb("IPassiveJammer_REMOVED",
            rep->passiveJammerId().c_str(),
            "{\"removed\":true}");
    }
}

