#pragma once

// 统一事件桥接，通过回调函数传递事件给 Java
typedef void(__stdcall* JavaEventCallback)(
    const char* type,          // "JAMMER_DISCOVERED" / "JAMMER_UPDATE" / "JAMMER_REMOVED" / "FIRE_INTERACTION"
    const char* id,            // 对象ID(对象类) 或 交互实例ID(交互类)
    const char* jsonPayload    // 事件载荷(JSON)
    );

struct EventBridge {
    static void set(JavaEventCallback cb);
    static JavaEventCallback get();
};
