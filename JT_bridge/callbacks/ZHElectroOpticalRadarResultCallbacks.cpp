#include "ZHElectroOpticalRadarResultCallbacks.h"
#include "../EventBridge.h"
#include "../ZHElectroOpticalRadarResult/CtZHElectroOpticalRadarResultStateRepository.h"

#include <sstream>
#include <string>
#include <unordered_set>

void onZHElectroOpticalRadarResultUpdated(CtRefZHElectroOpticalRadarResult* obj, void* userData);

static std::unordered_set<CtRefZHElectroOpticalRadarResult*> g_discoveredElectroResults;

static std::string electroResultIdentifier(CtRefZHElectroOpticalRadarResult* obj,
                                           CtZHElectroOpticalRadarResultStateRepository* rep) {
    if (rep) {
        std::ostringstream ss;
        ss << rep->Timestamp();
        return ss.str();
    }
    std::ostringstream ss;
    ss << "ZHElectroOpticalRadarResult@" << obj;
    return ss.str();
}

void onZHElectroOpticalRadarResultAdded(CtRefZHElectroOpticalRadarResult* obj, void* userData) {
    if (!obj) return;
    obj->addPostUpdateCallback(onZHElectroOpticalRadarResultUpdated, nullptr);
}

void onZHElectroOpticalRadarResultUpdated(CtRefZHElectroOpticalRadarResult* obj, void* userData) {
    if (!obj) return;

    JavaEventCallback cb = EventBridge::get();
    if (!cb) return;

    CtZHElectroOpticalRadarResultStateRepository* rep = obj->ZHElectroOpticalRadarResultStateRepository();
    if (!rep) return;

    std::ostringstream ss;
    ss << "{"
       << "\"Timestamp\":" << rep->Timestamp() << ","
       << "\"Result\":\"" << rep->Result() << "\","
       << "\"other1\":\"" << rep->other1() << "\","
       << "\"other2\":\"" << rep->other2() << "\","
       << "\"other3\":\"" << rep->other3() << "\","
       << "\"other4\":\"" << rep->other4() << "\","
       << "\"other5\":\"" << rep->other5() << "\","
       << "\"other6\":\"" << rep->other6() << "\""
       << "}";

    const std::string objectId = electroResultIdentifier(obj, rep);
    const bool isFirstUpdate = (g_discoveredElectroResults.find(obj) == g_discoveredElectroResults.end());
    const std::string payload = ss.str();

    if (isFirstUpdate) {
        g_discoveredElectroResults.insert(obj);
        cb("ZHElectroOpticalRadarResult_DISCOVER", objectId.c_str(), payload.c_str());
    } else {
        cb("ZHElectroOpticalRadarResult_UPDATE", objectId.c_str(), payload.c_str());
    }
}

void onZHElectroOpticalRadarResultRemoved(CtRefZHElectroOpticalRadarResult* obj, void* userData) {
    if (!obj) return;

    g_discoveredElectroResults.erase(obj);

    JavaEventCallback cb = EventBridge::get();
    if (!cb) return;

    CtZHElectroOpticalRadarResultStateRepository* rep = obj->ZHElectroOpticalRadarResultStateRepository();
    if (!rep) return;

    const std::string objectId = electroResultIdentifier(obj, rep);
    cb("ZHElectroOpticalRadarResult_REMOVED", objectId.c_str(), "{\"removed\":true}");
}


