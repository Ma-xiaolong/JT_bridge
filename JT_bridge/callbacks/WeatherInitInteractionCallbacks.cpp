#include "WeatherInitInteractionCallbacks.h"
#include "../EventBridge.h"
#include "../weatherinit/CtIWeatherInitinteraction.h"

#include <sstream>

// 回调包装函数 - 用于 IWeatherInit 交互接收
void onIWeatherInitInteractionReceived(CtIWeatherInitInteraction* inter, void* userData) {
    if (!inter) return;
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
        std::ostringstream ss;
        ss << "{"
            << "\"startTime\":" << inter->startTime() << ","
            << "\"weatherType\":" << inter->weatherType() << ","
            << "\"left\":" << inter->left() << ","
            << "\"bottom\":" << inter->bottom() << ","
            << "\"right\":" << inter->right() << ","
            << "\"top\":" << inter->top()
            << "}";
        
        cb("INTERACTION", "IWeatherInit_INTERACTION", "RemoteFederate",
            "", ss.str().c_str());
    }
}

