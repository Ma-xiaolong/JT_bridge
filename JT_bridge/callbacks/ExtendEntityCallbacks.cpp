#include "ExtendEntityCallbacks.h"
#include "../EventBridge.h"
#include "../ExtendEntity/CtExtendEntityStateRepository.h"

#include <sstream>
#include <string>
#include <unordered_set>

void onExtendEntityUpdated(CtRefExtendEntity* obj, void* userData);

static std::unordered_set<CtRefExtendEntity*> g_discoveredExtendEntities;

static std::string extendEntityIdentifier(CtRefExtendEntity* obj, CtExtendEntityStateRepository* rep) {
    if (rep && !rep->globleId().empty()) {
        return rep->globleId();
    }
    std::ostringstream ss;
    ss << "ExtendEntity@" << obj;
    return ss.str();
}

void onExtendEntityAdded(CtRefExtendEntity* obj, void* userData) {
    if (!obj) return;
    obj->addPostUpdateCallback(onExtendEntityUpdated, nullptr);
}

void onExtendEntityUpdated(CtRefExtendEntity* obj, void* userData) {
    if (!obj) return;

    JavaEventCallback cb = EventBridge::get();
    if (!cb) return;

    CtExtendEntityStateRepository* rep = obj->ExtendEntityStateRepository();
    if (!rep) return;

    std::ostringstream ss;
    ss << "{"
       << "\"globleId\":\"" << rep->globleId() << "\","
       << "\"Timestamp\":" << rep->Timestamp() << ","
       << "\"Fuel\":\"" << rep->Fuel() << "\","
       << "\"weaponLoadouts\":\"" << rep->weaponLoadouts() << "\","
       << "\"other1\":\"" << rep->other1() << "\","
       << "\"other2\":\"" << rep->other2() << "\","
       << "\"other3\":\"" << rep->other3() << "\","
       << "\"other4\":\"" << rep->other4() << "\","
       << "\"other5\":\"" << rep->other5() << "\","
       << "\"other6\":\"" << rep->other6() << "\""
       << "}";

    const std::string objectId = extendEntityIdentifier(obj, rep);
    const bool isFirstUpdate = (g_discoveredExtendEntities.find(obj) == g_discoveredExtendEntities.end());
    const std::string payload = ss.str();

    if (isFirstUpdate) {
        g_discoveredExtendEntities.insert(obj);
        cb("ExtendEntity_DISCOVER", objectId.c_str(), payload.c_str());
    } else {
        cb("ExtendEntity_UPDATE", objectId.c_str(), payload.c_str());
    }
}

void onExtendEntityRemoved(CtRefExtendEntity* obj, void* userData) {
    if (!obj) return;

    g_discoveredExtendEntities.erase(obj);

    JavaEventCallback cb = EventBridge::get();
    if (!cb) return;

    CtExtendEntityStateRepository* rep = obj->ExtendEntityStateRepository();
    if (!rep) return;

    const std::string objectId = extendEntityIdentifier(obj, rep);
    cb("ExtendEntity_REMOVED", objectId.c_str(), "{\"removed\":true}");
}


