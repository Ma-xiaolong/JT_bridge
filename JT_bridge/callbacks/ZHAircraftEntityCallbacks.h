#pragma once

#include "../ZHAircraftEntity/CtRefZHAircraftEntity.h"
#include "../ZHAircraftEntity/CtRefZHAircraftEntityList.h"

// ZHAircraftEntity 对象回调函数声明

// 对象添加回调
void onZHAircraftEntityAdded(CtRefZHAircraftEntity* obj, void* userData);

// 对象更新回调
void onZHAircraftEntityUpdated(CtRefZHAircraftEntity* obj, void* userData);

// 对象移除回调
void onZHAircraftEntityRemoved(CtRefZHAircraftEntity* obj, void* userData);

