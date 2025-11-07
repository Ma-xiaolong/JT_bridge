#pragma once

// 统一事件桥：所有对象/交互都通过它回调给 Java
typedef void(__stdcall* JavaEventCallback)(
    const char* category,      // "OBJECT" / "INTERACTION"
    const char* type,          // "JAMMER_DISCOVERED" / "JAMMER_UPDATE" / "JAMMER_REMOVED" / "FIRE_INTERACTION"
    const char* sourceFed,     // 来源联邦成员
    const char* id,            // 对象ID(对象类) 或 触发实体ID(交互类)
    const char* jsonPayload    // 事件载荷(JSON)
    );

struct EventBridge {
    static void set(JavaEventCallback cb);
    static JavaEventCallback get();
};