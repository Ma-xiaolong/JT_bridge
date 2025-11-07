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

	void __stdcall ShutdownVRLink() {
		VRLinkManager::I().shutdown();
	}

} // extern "C"
