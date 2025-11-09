#include "WeatherResultInteractionCallbacks.h"
#include "../EventBridge.h"
#include "../weatherresultinter/CtIWeatherResultsinteraction.h"

#include <sstream>

// 回调包装函数 - 用于 IWeatherResults 交互接收
void onIWeatherResultsInteractionReceived(CtIWeatherResultsInteraction* inter, void* userData) {
    if (!inter) return;
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
        std::ostringstream ss;
        ss << "{"
            << "\"bagSum\":" << inter->bagSum() << ","
            << "\"bagNo\":" << inter->bagNo() << ","
            << "\"bagID\":" << inter->bagID() << ","
            << "\"bagSize\":" << inter->bagSize() << ","
            << "\"bagValue\":\"" << inter->bagValue() << "\""
            << "}";
        
        cb("INTERACTION", "IWeatherResults_INTERACTION", "RemoteFederate",
            "", ss.str().c_str());
    }
}

