#include "RadarCallbacks.h"
#include "../EventBridge.h"
#include "../radar/CtRadarStateRepository.h"

#include <sstream>
#include <string>
#include <unordered_set>

// 前向声明更新回调
void onRadarUpdated(CtRefRadar* obj, void* userData);

// 已发现对象集合
static std::unordered_set<CtRefRadar*> g_discoveredRadars;

static std::string radarIdentifier(CtRefRadar* obj, CtRadarStateRepository* rep) {
    if (rep && !rep->RadarID().empty()) {
        return rep->RadarID();
    }
    std::ostringstream ss;
    ss << "Radar@" << obj;
    return ss.str();
}

// 回调 - Radar 添加
void onRadarAdded(CtRefRadar* obj, void* userData) {
    if (!obj) return;
    obj->addPostUpdateCallback(onRadarUpdated, nullptr);
}

// 回调 - Radar 更新
void onRadarUpdated(CtRefRadar* obj, void* userData) {
    if (!obj) return;

    JavaEventCallback cb = EventBridge::get();
    if (!cb) return;

    CtRadarStateRepository* rep = obj->RadarStateRepository();
    if (!rep) return;

    std::ostringstream ss;
    ss << "{"
       << "\"RadarID\":\"" << rep->RadarID() << "\","
       << "\"Timestamp\":" << rep->Timestamp() << ","
       << "\"RD_bandwidth\":" << rep->RD_bandwidth() << ","
       << "\"RD_power\":" << rep->RD_power() << ","
       << "\"freq\":" << rep->freq() << ","
       << "\"repetition_rate\":" << rep->repetition_rate() << ","
       << "\"pulse_duration\":" << rep->pulse_duration() << ","
       << "\"freq_characteristics\":" << rep->freq_characteristics() << ","
       << "\"repetition_characteristics\":" << rep->repetition_characteristics() << ","
       << "\"jagged_progression\":" << rep->jagged_progression() << ","
       << "\"pulse_encoding\":" << rep->pulse_encoding() << ","
       << "\"polarization_mode\":" << rep->polarization_mode() << ","
       << "\"scan_mode\":" << rep->scan_mode() << ","
       << "\"antenna_speed\":" << rep->antenna_speed() << ","
       << "\"horizontal_beamwidth\":" << rep->horizontal_beamwidth() << ","
       << "\"vertical_beamwidth\":" << rep->vertical_beamwidth() << ","
       << "\"horizontal_scan_range\":\"" << rep->horizontal_scan_range() << "\","
       << "\"max_range\":" << rep->max_range() << ","
       << "\"antenna_height\":" << rep->antenna_height() << ","
       << "\"RD_main_gain\":" << rep->RD_main_gain() << ","
       << "\"RD_minor_gain\":" << rep->RD_minor_gain() << ","
       << "\"RD_receiver_sensitivity\":" << rep->RD_receiver_sensitivity() << ","
       << "\"inner_loss\":" << rep->inner_loss() << ","
       << "\"noice_factor\":" << rep->noice_factor() << ","
       << "\"antenna_type\":" << rep->antenna_type() << ","
       << "\"vertical_scan_range\":\"" << rep->vertical_scan_range() << "\","
       << "\"measuring_range\":" << rep->measuring_range() << ","
       << "\"discovery_probablity\":" << rep->discovery_probablity() << ","
       << "\"falsealarm_probablity\":" << rep->falsealarm_probablity() << ","
       << "\"init_flag\":" << rep->init_flag() << ","
       << "\"other1\":\"" << rep->other1() << "\","
       << "\"other2\":\"" << rep->other2() << "\","
       << "\"other3\":\"" << rep->other3() << "\","
       << "\"init_fusion\":" << rep->init_fusion()
       << "}";

    const std::string objectId = radarIdentifier(obj, rep);
    const bool isFirstUpdate = (g_discoveredRadars.find(obj) == g_discoveredRadars.end());

    const std::string payload = ss.str();
    if (isFirstUpdate) {
        g_discoveredRadars.insert(obj);
        cb("Radar_DISCOVER", objectId.c_str(), payload.c_str());
    } else {
        cb("Radar_UPDATE", objectId.c_str(), payload.c_str());
    }
}

// 回调 - Radar 移除
void onRadarRemoved(CtRefRadar* obj, void* userData) {
    if (!obj) return;

    g_discoveredRadars.erase(obj);

    JavaEventCallback cb = EventBridge::get();
    if (!cb) return;

    CtRadarStateRepository* rep = obj->RadarStateRepository();
    if (!rep) return;

    const std::string objectId = radarIdentifier(obj, rep);
    cb("Radar_REMOVED", objectId.c_str(), "{\"removed\":true}");
}


