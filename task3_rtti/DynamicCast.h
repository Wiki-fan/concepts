#pragma once
#include <iostream>

#include "TypeInfo.h"

void* processDynamicCast(TypeInfo& curType, TypeInfo targetType, void* obj) {
    if (curType == targetType) {
        return OBJ;
    }
    if (OBJ == nullptr) {
        return nullptr;
    }
}
#define DYNAMIC_CAST(TARGET_TYPE, OBJ_PTR) \
reinterpret_cast<TARGET_TYPE*>(processDynamicCast( TYPEID(OBJ), TypeNameToTypeInfo[#TARGET_TYPE], reinterpret_cast<void*>(OBJ_PTR)))

/*std::string typeName = #TARGET_TYPE; \
TypeInfo curType = TYPEID(OBJ); \
TypeInfo targetType = TypeNameToTypeInfo[#TARGET_TYPE]; \
std::cout <<curType.name <<' ' <<targetType.name <<std::endl; \*/

/*if (curType == targetType) { \
    return OBJ; \
} \
if (OBJ == nullptr) { \
    return nullptr; \
} \*/


