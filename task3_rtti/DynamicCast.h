#pragma once
#include <iostream>

#include "TypeInfo.h"

void* processDynamicCast(TypeInfo& targetType, void* obj);

#define DYNAMIC_CAST(TARGET_TYPE, OBJ_PTR) \
reinterpret_cast<TARGET_TYPE*>(processDynamicCast( TypeNameToTypeInfo[#TARGET_TYPE], reinterpret_cast<void*>(OBJ_PTR)))
