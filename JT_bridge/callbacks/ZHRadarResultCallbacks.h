#pragma once

#include "../zhradarresult/CtRefZHRadarResult.h"
#include "../zhradarresult/CtRefZHRadarResultList.h"

// ZHRadarResult 对象回调函数声明

// 对象添加回调
void onZHRadarResultAdded(CtRefZHRadarResult* obj, void* userData);

// 对象更新回调
void onZHRadarResultUpdated(CtRefZHRadarResult* obj, void* userData);

// 对象移除回调
void onZHRadarResultRemoved(CtRefZHRadarResult* obj, void* userData);

