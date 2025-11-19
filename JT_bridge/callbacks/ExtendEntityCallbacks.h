#pragma once

#include "../ExtendEntity/CtRefExtendEntity.h"

// ExtendEntity 对象回调函数声明
void onExtendEntityAdded(CtRefExtendEntity* obj, void* userData);
void onExtendEntityUpdated(CtRefExtendEntity* obj, void* userData);
void onExtendEntityRemoved(CtRefExtendEntity* obj, void* userData);


