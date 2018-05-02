#include "DynamicCast.h"

void walk(TypeInfo ti, int baseShift) {
    int currentShift = baseShift;
    for (int i = 0; i<ti.parentNames.size(); ++i) {
        ti.BaseNameToShiftMap[ti.parentNames[i]] = currentShift;
        currentShift += TypeNameToTypeInfo[ti.parentNames[i]].size;
    }
}

void* processDynamicCast(TypeInfo& curType, TypeInfo targetType, void* obj) {
    if (curType == targetType) {
        return obj;
    }
    if (obj == nullptr) {
        return nullptr;
    }
}