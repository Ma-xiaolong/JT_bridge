#include "ZHRadarReqInteractionCallbacks.h"
#include "../EventBridge.h"
#include "../zhradarinter/CtZHRadarReqinteraction.h"

#include <sstream>

// 回调包装函数 - 用于 ZHRadarReq 交互接收
void onZHRadarReqInteractionReceived(CtZHRadarReqInteraction* inter, void* userData) {
    if (!inter) return;
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
        std::ostringstream ss;
        ss << "{"
            << "\"RadarID\":\"" << inter->RadarID() << "\","
            << "\"Timestamp\":" << inter->Timestamp() << ","
            << "\"type\":" << inter->type() << ","
            << "\"power1\":" << inter->power1() << ","
            << "\"max_range\":" << inter->max_range() << ","
            << "\"hori_range\":" << inter->hori_range() << ","
            << "\"vert_range\":" << inter->vert_range() << ","
            << "\"dir_follow_precision\":" << inter->dir_follow_precision() << ","
            << "\"work_type\":" << inter->work_type() << ","
            << "\"power\":" << inter->power() << ","
            << "\"width\":" << inter->width() << ","
            << "\"dis_precision\":" << inter->dis_precision() << ","
            << "\"dis_follow_range\":" << inter->dis_follow_range() << ","
            << "\"dis_follow_precision\":" << inter->dis_follow_precision() << ","
            << "\"select_target_type\":" << inter->select_target_type() << ","
            << "\"success_value\":" << inter->success_value() << ","
            << "\"receive_sensitivity\":" << inter->receive_sensitivity() << ","
            << "\"confidence\":" << inter->confidence();
        
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
        
        cb("ZHRadarReq_INTERACTION",
            inter->RadarID().c_str(), ss.str().c_str());
    }
}

