#include "EntityCallbacks.h"
#include "../EventBridge.h"

#include <vl/reflEntList.h>
#include <vl/entityPub.h>
#include <matrix/vlVector.h>
#include <sstream>
#include <unordered_set>
#include <iomanip>

// Forward declaration of update callback
void onEntityUpdated(DtReflectedEntity* obj, void* userData);

// Track objects that have already triggered a DISCOVER event
// Use the object pointer as the key because it remains stable during the lifecycle
static std::unordered_set<DtReflectedEntity*> g_discoveredEntities;

// Helper: format entity ID as string
std::string formatEntityID(DtReflectedEntity* obj) {
    if (!obj) {
        return "0.0.0";
    }
    std::ostringstream ss;
    ss << obj->id();
    return ss.str();
}

// Callback wrapper - entity addition
void onEntityAdded(DtReflectedEntity* obj, void* userData) {
    if (!obj) return;
    
    // Register the update callback for the newly discovered object
    // Do not send DISCOVER here because the attributes may still be default values
    // Wait for the first attribute update to send the DISCOVER event
    obj->addPostUpdateCallback(onEntityUpdated, nullptr);
}

// Callback wrapper - entity update
void onEntityUpdated(DtReflectedEntity* obj, void* userData) {
    if (!obj) return;
    
    JavaEventCallback cb = EventBridge::get();
    if (!cb) return;
    
    DtEntityStateRepository* esr = obj->esr();
    if (!esr) return;
    
    // Retrieve entity identifier
    std::string entityIdStr = formatEntityID(obj);
    
    // Retrieve entity type
    DtEntityType entityType = esr->entityType();
    
    // Retrieve location
    DtVector location = esr->location();
    
    // Retrieve velocity
    DtVector velocity = esr->velocity();
    
    // Retrieve acceleration
    DtVector acceleration = esr->acceleration();
    
    // Retrieve orientation
    auto orientation = esr->orientation();
    
    // Frozen flag (default false if API is unavailable)
    bool isFrozen = false;
    
    // Build JSON payload
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(6);
    ss << "{"
        << "\"EntityID\":\"" << entityIdStr << "\","
        << "\"EntityType\":{"
            << "\"kind\":" << (int)entityType.kind() << ","
            << "\"domain\":" << (int)entityType.domain() << ","
            << "\"country\":" << entityType.country() << ","
            << "\"category\":" << (int)entityType.category() << ","
            << "\"subcategory\":" << (int)entityType.subCategory() << ","
            << "\"specific\":" << (int)entityType.specific() << ","
            << "\"extra\":" << (int)entityType.extra()
        << "},"
        << "\"WorldLocation\":{"
            << "\"x\":" << location.x() << ","
            << "\"y\":" << location.y() << ","
            << "\"z\":" << location.z()
        << "},"
        << "\"VelocityVector\":{"
            << "\"vx\":" << velocity.x() << ","
            << "\"vy\":" << velocity.y() << ","
            << "\"vz\":" << velocity.z()
        << "},"
        << "\"AccelerationVector\":{"
            << "\"ax\":" << acceleration.x() << ","
            << "\"ay\":" << acceleration.y() << ","
            << "\"az\":" << acceleration.z()
        << "},"
        << "\"Orientation\":{"
            << "\"psi\":" << orientation.psi() << ","
            << "\"theta\":" << orientation.theta() << ","
            << "\"phi\":" << orientation.phi()
        << "},"
        << "\"IsFrozen\":" << (isFrozen ? "true" : "false")
        << "}";
    
    // Check if it's the first update (i.e., the first update after discovery)
    // If it's the first update, send DISCOVER event; otherwise, send UPDATE event
    bool isFirstUpdate = (g_discoveredEntities.find(obj) == g_discoveredEntities.end());
    
    if (isFirstUpdate) {
        // First update: send DISCOVER event
        g_discoveredEntities.insert(obj);
        cb("Entity_DISCOVER",
            entityIdStr.c_str(), ss.str().c_str());
    } else {
        // Subsequent updates: send UPDATE event
        cb("Entity_UPDATE",
            entityIdStr.c_str(), ss.str().c_str());
    }
}

// Callback wrapper - entity removal
void onEntityRemoved(DtReflectedEntity* obj, void* userData) {
    if (!obj) return;
    
    // Remove from discovered set
    g_discoveredEntities.erase(obj);
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
        std::string entityIdStr = formatEntityID(obj);
        
        cb("Entity_REMOVED",
            entityIdStr.c_str(),
            "{\"removed\":true}");
    }
}

