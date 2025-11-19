#pragma once

#include "../ZHElectroOpticalRadarResult/CtRefZHElectroOpticalRadarResult.h"

// ZHElectroOpticalRadarResult 对象回调函数声明
void onZHElectroOpticalRadarResultAdded(CtRefZHElectroOpticalRadarResult* obj, void* userData);
void onZHElectroOpticalRadarResultUpdated(CtRefZHElectroOpticalRadarResult* obj, void* userData);
void onZHElectroOpticalRadarResultRemoved(CtRefZHElectroOpticalRadarResult* obj, void* userData);


