#include "ZHAircraftSimulatorConfigInteractionCallbacks.h"
#include "../EventBridge.h"
#include "../ZHAircraftSimulatorConfigInter/CtZHAircraftSimulatorConfigReqinteraction.h"

#include <sstream>

// 回调包装函数 - 用于 ZHAircraftSimulatorConfigReq 交互接收
void onZHAircraftSimulatorConfigReqInteractionReceived(CtZHAircraftSimulatorConfigReqInteraction* inter, void* userData) {
    if (!inter) return;
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
        std::ostringstream ss;
        ss << "{"
            << "\"PlatformID\":\"" << inter->PlatformID() << "\","
            << "\"Timestamp\":" << inter->Timestamp() << ","
            << "\"SimulateID\":\"" << inter->SimulateID() << "\","
            << "\"entityID\":\"" << inter->entityID() << "\","
            << "\"statue\":" << (inter->statue() ? "true" : "false");
        
        if (!inter->other1().empty()) {
            ss << ",\"other1\":\"" << inter->other1() << "\"";
        }
        if (!inter->other2().empty()) {
            ss << ",\"other2\":\"" << inter->other2() << "\"";
        }
        if (!inter->other3().empty()) {
            ss << ",\"other3\":\"" << inter->other3() << "\"";
        }
        if (!inter->other4().empty()) {
            ss << ",\"other4\":\"" << inter->other4() << "\"";
        }
        if (!inter->other5().empty()) {
            ss << ",\"other5\":\"" << inter->other5() << "\"";
        }
        if (!inter->other6().empty()) {
            ss << ",\"other6\":\"" << inter->other6() << "\"";
        }
        
        ss << "}";
        
        cb("INTERACTION", "ZHAircraftSimulatorConfigReq_INTERACTION", "RemoteFederate",
            inter->PlatformID().c_str(), ss.str().c_str());
    }
}

