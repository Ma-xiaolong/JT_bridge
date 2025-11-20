#include "ExportAPI.h"
#include "VRLinkManager.h"
#include "EventBridge.h"

extern "C" {

	bool __stdcall InitVRLink(const char* f, const char* r) {
		return VRLinkManager::I().init(f, r);
	}

	void __stdcall SetEventCallback(JavaEventCallback cb) {
		EventBridge::set(cb);
	}

	void __stdcall PumpVRLinkOnce() {
		VRLinkManager::I().pumpOnce();
	}

	bool __stdcall PublishRadarControlInteraction(const char* platform_id, const char* equipment_id, int state, double mission_time) {
		return VRLinkManager::I().publishRadarControlInteraction(platform_id, equipment_id, state, mission_time);
	}

	void __stdcall ShutdownVRLink() {
		VRLinkManager::I().shutdown();
	}

} // extern "C"
