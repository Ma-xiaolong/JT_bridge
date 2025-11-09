#pragma once

#include "../jammer/CtRefIJammer.h"
#include "../jammer/CtRefIJammerList.h"

// Jammer 对象回调函数声明

// 对象添加回调
void onIJammerAdded(CtRefIJammer* obj, void* userData);

// 对象更新回调
void onIJammerUpdated(CtRefIJammer* obj, void* userData);

// 对象移除回调
void onIJammerRemoved(CtRefIJammer* obj, void* userData);

