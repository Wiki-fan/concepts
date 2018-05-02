#include "DynamicCast.h"
#include <cassert>

void* processDynamicCast(TypeInfo& targetType, void* obj) {
    while (PtrToMostDerivedPtr[obj] != obj) {
        obj = PtrToMostDerivedPtr[obj];
    }
    TypeInfo& curType = TYPEID(PtrToMostDerivedPtr[obj]);
    // 1
    if (curType == targetType) {
        return obj;
    }
    // 2
    if (obj == nullptr) {
        return nullptr;
    }
    // 3
    if (curType.BaseNameToShiftMap.find(targetType.name) != curType.BaseNameToShiftMap.end()) {
        return reinterpret_cast<char*>(obj) + curType.BaseNameToShiftMap[targetType.name];
    }
    // 4
    /*if (targetType.name == "void*") {
        return ObjToClassNameMap
    }*/
    //5a
    std::string mostDerivedName = ObjToClassNameMap[obj];
    TypeInfo& mostDerivedTypeInfo = TypeNameToTypeInfo[mostDerivedName];
    if (mostDerivedTypeInfo.BaseNameToShiftMap.find(targetType.name) != mostDerivedTypeInfo.BaseNameToShiftMap.end()) {
        return reinterpret_cast<char*>(obj) + mostDerivedTypeInfo.BaseNameToShiftMap[targetType.name];
    }
    assert(false);
}
