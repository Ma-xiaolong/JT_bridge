#include "EventBridge.h"
static JavaEventCallback g_cb = nullptr;
void EventBridge::set(JavaEventCallback cb) { g_cb = cb; }
JavaEventCallback EventBridge::get() { return g_cb; }
