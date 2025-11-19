#pragma once

#include "../radarresult/CtRefRadarResults.h"

// RadarResults 对象回调函数声明
void onRadarResultsAdded(CtRefRadarResults* obj, void* userData);
void onRadarResultsUpdated(CtRefRadarResults* obj, void* userData);
void onRadarResultsRemoved(CtRefRadarResults* obj, void* userData);


