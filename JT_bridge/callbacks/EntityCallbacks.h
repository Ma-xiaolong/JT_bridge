#pragma once

#include <vl/reflEntList.h>

// 装备实体对象回调函数声明

// 对象添加回调
void onEntityAdded(DtReflectedEntity* obj, void* userData);

// 对象更新回调
void onEntityUpdated(DtReflectedEntity* obj, void* userData);

// 对象移除回调
void onEntityRemoved(DtReflectedEntity* obj, void* userData);

