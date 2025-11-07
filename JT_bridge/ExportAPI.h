#pragma once
#include "EventBridge.h"

extern "C" {

	// 初始化 VR-Link + 模块
	__declspec(dllexport) bool __stdcall InitVRLink(const char* federation, const char* federate);

	// 注册 Java 回调（Java 传函数指针进来）
	__declspec(dllexport) void __stdcall SetEventCallback(JavaEventCallback cb);

	// 每帧调用：drainInput + tick（驱动对象与交互）
	__declspec(dllexport) void __stdcall PumpVRLinkOnce();

	// 释放
	__declspec(dllexport) void __stdcall ShutdownVRLink();
}

