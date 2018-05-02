#include "DynamicCast.h"
#include <cassert>

void walk(TypeInfo ti, int baseShift) {
    int currentShift = baseShift;
    for (int i = 0; i<ti.parentNames.size(); ++i) {
        ti.BaseNameToShiftMap[ti.parentNames[i]] = currentShift;
        currentShift += TypeNameToTypeInfo[ti.parentNames[i]].size;
    }
}

void* processDynamicCast(TypeInfo& curType, TypeInfo targetType, void* obj) {
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
        return reinterpret_cast<char*>(obj)+curType.BaseNameToShiftMap[targetType.name];
    }
    // 4
    /*if (targetType.name == "void*") {
        return ObjToClassNameMap
    }*/
    //5a
    std::string mostDerivedName = ObjToClassNameMap[obj];
    TypeInfo& mostDerivedTypeInfo = TypeNameToTypeInfo[mostDerivedName];
    if (mostDerivedTypeInfo.BaseNameToShiftMap.find(targetType.name) != mostDerivedTypeInfo.BaseNameToShiftMap.end()) {
        return reinterpret_cast<char*>(obj)+mostDerivedTypeInfo.BaseNameToShiftMap[targetType.name];
    }
    assert(false);
}