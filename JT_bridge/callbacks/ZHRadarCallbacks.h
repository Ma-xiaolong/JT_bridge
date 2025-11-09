#pragma once

#include "../zhradar/CtRefZHRadar.h"
#include "../zhradar/CtRefZHRadarList.h"

// ZHRadar 对象回调函数声明

// 对象添加回调
void onZHRadarAdded(CtRefZHRadar* obj, void* userData);

// 对象更新回调
void onZHRadarUpdated(CtRefZHRadar* obj, void* userData);

// 对象移除回调
void onZHRadarRemoved(CtRefZHRadar* obj, void* userData);

