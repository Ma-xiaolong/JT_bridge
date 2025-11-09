#pragma once

#include "../passiveJammer/CtRefIPassiveJammer.h"
#include "../passiveJammer/CtRefIPassiveJammerList.h"

// PassiveJammer 对象回调函数声明

// 对象添加回调
void onIPassiveJammerAdded(CtRefIPassiveJammer* obj, void* userData);

// 对象更新回调
void onIPassiveJammerUpdated(CtRefIPassiveJammer* obj, void* userData);

// 对象移除回调
void onIPassiveJammerRemoved(CtRefIPassiveJammer* obj, void* userData);

