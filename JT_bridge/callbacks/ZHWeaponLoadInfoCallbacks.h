#pragma once

#include "../ZHWeaponLoadInfo/CtRefZHWeaponLoadInfo.h"
#include "../ZHWeaponLoadInfo/CtRefZHWeaponLoadInfoList.h"

// ZHWeaponLoadInfo 对象回调函数声明

// 对象添加回调
void onZHWeaponLoadInfoAdded(CtRefZHWeaponLoadInfo* obj, void* userData);

// 对象更新回调
void onZHWeaponLoadInfoUpdated(CtRefZHWeaponLoadInfo* obj, void* userData);

// 对象移除回调
void onZHWeaponLoadInfoRemoved(CtRefZHWeaponLoadInfo* obj, void* userData);

