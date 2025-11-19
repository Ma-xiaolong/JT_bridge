#include "RadarResultsCallbacks.h"
#include "../EventBridge.h"
#include "../radarresult/CtRadarResultsStateRepository.h"

#include <sstream>
#include <string>
#include <unordered_set>

void onRadarResultsUpdated(CtRefRadarResults* obj, void* userData);

static std::unordered_set<CtRefRadarResults*> g_discoveredRadarResults;

static std::string radarResultsIdentifier(CtRefRadarResults* obj, CtRadarResultsStateRepository* rep) {
    if (rep && !rep->ID().empty()) {
        return rep->ID();
    }
    std::ostringstream ss;
    ss << "RadarResults@" << obj;
    return ss.str();
}

void onRadarResultsAdded(CtRefRadarResults* obj, void* userData) {
    if (!obj) return;
    obj->addPostUpdateCallback(onRadarResultsUpdated, nullptr);
}

void onRadarResultsUpdated(CtRefRadarResults* obj, void* userData) {
    if (!obj) return;

    JavaEventCallback cb = EventBridge::get();
    if (!cb) return;

    CtRadarResultsStateRepository* rep = obj->RadarResultsStateRepository();
    if (!rep) return;

    std::ostringstream ss;
    ss << "{"
       << "\"ID\":\"" << rep->ID() << "\","
    //    << "\"fedTime\":" << rep->fedTime() << ","
    //    << "\"targetId\":\"" << rep->targetId() << "\","
       << "\"batch_number\":\"" << rep->batch_number() << "\","
       << "\"red_fusion\":\"" << rep->red_fusion() << "\","
    //    << "\"blue_fusion\":\"" << rep->blue_fusion() << "\","
    //    << "\"other1\":\"" << rep->other1() << "\","
    //    << "\"other2\":\"" << rep->other2() << "\","
    //    << "\"other3\":\"" << rep->other3() << "\""
       << "}";

    const std::string objectId = radarResultsIdentifier(obj, rep);
    const bool isFirstUpdate = (g_discoveredRadarResults.find(obj) == g_discoveredRadarResults.end());
    const std::string payload = ss.str();

    if (isFirstUpdate) {
        g_discoveredRadarResults.insert(obj);
        cb("RadarResults_DISCOVER", objectId.c_str(), payload.c_str());
    } else {
        cb("RadarResults_UPDATE", objectId.c_str(), payload.c_str());
    }
}

void onRadarResultsRemoved(CtRefRadarResults* obj, void* userData) {
    if (!obj) return;

    g_discoveredRadarResults.erase(obj);

    JavaEventCallback cb = EventBridge::get();
    if (!cb) return;

    CtRadarResultsStateRepository* rep = obj->RadarResultsStateRepository();
    if (!rep) return;

    const std::string objectId = radarResultsIdentifier(obj, rep);
    cb("RadarResults_REMOVED", objectId.c_str(), "{\"removed\":true}");
}


