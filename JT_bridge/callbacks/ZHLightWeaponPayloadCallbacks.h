#pragma once

#include "../ZHLightWeaponPayload/CtRefZHLightWeaponPayload.h"
#include "../ZHLightWeaponPayload/CtRefZHLightWeaponPayloadList.h"

// ZHLightWeaponPayload 对象回调函数声明

// 对象添加回调
void onZHLightWeaponPayloadAdded(CtRefZHLightWeaponPayload* obj, void* userData);

// 对象更新回调
void onZHLightWeaponPayloadUpdated(CtRefZHLightWeaponPayload* obj, void* userData);

// 对象移除回调
void onZHLightWeaponPayloadRemoved(CtRefZHLightWeaponPayload* obj, void* userData);

