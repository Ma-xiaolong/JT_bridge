#pragma once
#include "EventBridge.h"

extern "C" {

	//ʼ VR-Link + ģ
	__declspec(dllexport) bool __stdcall InitVRLink(const char* federation, const char* federate);

	// ע JavaصJava ָ
	__declspec(dllexport) void __stdcall SetEventCallback(JavaEventCallback cb);

	// ÿ֡ãdrainInput + tick뽻
	__declspec(dllexport) void __stdcall PumpVRLinkOnce();

	// Publish radarcontrol interaction
	__declspec(dllexport) bool __stdcall PublishRadarControlInteraction(const char* platform_id, const char* equipment_id, int state, double mission_time);

	// ͷ
	__declspec(dllexport) void __stdcall ShutdownVRLink();
}
