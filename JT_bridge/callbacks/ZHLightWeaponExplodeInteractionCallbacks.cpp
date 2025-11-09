#include "ZHLightWeaponExplodeInteractionCallbacks.h"
#include "../EventBridge.h"
#include "../ZHLightWeaponExplodeInter/CtZHLightWeaponExplodeReqinteraction.h"

#include <sstream>

// 回调包装函数 - 用于 ZHLightWeaponExplodeReq 交互接收
void onZHLightWeaponExplodeReqInteractionReceived(CtZHLightWeaponExplodeReqInteraction* inter, void* userData) {
    if (!inter) return;
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
        std::ostringstream ss;
        ss << "{"
            << "\"WeaponID\":\"" << inter->WeaponID() << "\","
            << "\"TargetID\":\"" << inter->TargetID() << "\","
            << "\"Timestamp\":" << inter->Timestamp() << ","
            << "\"explodeX\":" << inter->explodeX() << ","
            << "\"explodeY\":" << inter->explodeY() << ","
            << "\"explodeZ\":" << inter->explodeZ() << ","
            << "\"platform_id\":\"" << inter->platform_id() << "\","
            << "\"equipment_id\":\"" << inter->equipment_id() << "\","
            << "\"State\":\"" << inter->State() << "\"";
        
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
        
        cb("INTERACTION", "ZHLightWeaponExplodeReq_INTERACTION", "RemoteFederate",
            inter->WeaponID().c_str(), ss.str().c_str());
    }
}

