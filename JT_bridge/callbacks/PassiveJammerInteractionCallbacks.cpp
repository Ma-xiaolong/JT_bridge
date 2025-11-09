#include "PassiveJammerInteractionCallbacks.h"
#include "../EventBridge.h"
#include "../passiveJammerInter/CtIPassiveJammerinteraction.h"

#include <sstream>

// 回调包装函数 - 用于 IPassiveJammer 交互接收
void onIPassiveJammerInteractionReceived(CtIPassiveJammerInteraction* inter, void* userData) {
    if (!inter) return;
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
        std::ostringstream ss;
        ss << "{"
            << "\"passiveJammerId\":\"" << inter->passiveJammerId() << "\","
            << "\"ht\":" << inter->ht() << ","
            << "\"bt\":" << inter->bt() << ","
            << "\"jam_mode\":" << inter->jam_mode() << ","
            << "\"btgrkd\":" << inter->btgrkd() << ","
            << "\"btgrgd\":" << inter->btgrgd() << ","
            << "\"btgrsl\":" << inter->btgrsl() << ","
            << "\"btgryxxs\":" << inter->btgryxxs() << ","
            << "\"btgrsc\":" << inter->btgrsc() << ","
            << "\"btgrsg\":" << inter->btgrsg() << ","
            << "\"btgrzksj\":" << inter->btgrzksj() << ","
            << "\"btgrlksj\":" << inter->btgrlksj() << ","
            << "\"rcs\":" << inter->rcs() << ","
            << "\"sjxjflbc\":" << inter->sjxjflbc();
        
        if (!inter->other1().empty()) {
            ss << ",\"other1\":\"" << inter->other1() << "\"";
        }
        if (!inter->other2().empty()) {
            ss << ",\"other2\":\"" << inter->other2() << "\"";
        }
        if (!inter->other3().empty()) {
            ss << ",\"other3\":\"" << inter->other3() << "\"";
        }
        
        ss << "}";
        
        cb("INTERACTION", "IPassiveJammer_INTERACTION", "RemoteFederate",
            inter->passiveJammerId().c_str(), ss.str().c_str());
    }
}

