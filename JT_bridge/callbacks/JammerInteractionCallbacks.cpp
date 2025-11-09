#include "JammerInteractionCallbacks.h"
#include "../EventBridge.h"
#include "../jamInter/CtIJammerinteraction.h"

#include <sstream>

// 回调包装函数 - 用于 IJammer 交互接收
void onIJammerInteractionReceived(CtIJammerInteraction* inter, void* userData) {
    if (!inter) return;
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
        std::ostringstream ss;
        ss << "{"
            << "\"JammerId\":\"" << inter->JammerId() << "\","
            << "\"Jam_target\":\"" << inter->Jam_target() << "\","
            << "\"Jam_pos_x\":" << inter->Jam_pos_x() << ","
            << "\"Jam_pos_y\":" << inter->Jam_pos_y() << ","
            << "\"Jam_pos_z\":" << inter->Jam_pos_z() << ","
            << "\"power\":" << inter->power() << ","
            << "\"emission_gain\":" << inter->emission_gain() << ","
            << "\"center_frequency\":" << inter->center_frequency() << ","
            << "\"bandwidth\":" << inter->bandwidth() << ","
            << "\"polarization_mode\":" << inter->polarization_mode() << ","
            << "\"beamwidth\":" << inter->beamwidth() << ","
            << "\"reconnaissance_reception_sensitivity\":" << inter->reconnaissance_reception_sensitivity() << ","
            << "\"reconnaissance_reception_buff\":" << inter->reconnaissance_reception_buff() << ","
            << "\"signal_reconnaissance_time\":" << inter->signal_reconnaissance_time() << ","
            << "\"interference_mode\":" << inter->interference_mode();
        
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
        
        cb("INTERACTION", "IJammer_INTERACTION", "RemoteFederate",
            inter->JammerId().c_str(), ss.str().c_str());
    }
}

