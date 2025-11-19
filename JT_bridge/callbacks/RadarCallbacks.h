#pragma once

#include "../radar/CtRefRadar.h"

// Radar 对象回调函数声明

// 对象添加回调
void onRadarAdded(CtRefRadar* obj, void* userData);

// 对象更新回调
void onRadarUpdated(CtRefRadar* obj, void* userData);

// 对象移除回调
void onRadarRemoved(CtRefRadar* obj, void* userData);


