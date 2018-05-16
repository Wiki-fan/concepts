#include "TypeInfo.h"

std::map<void*, std::string> ObjToClassNameMap;
std::map<std::string, TypeInfo> TypeNameToTypeInfo;
std::map<void*, void*> PtrToMostDerivedPtr;

void PopulatePtrs(TypeInfo& ti, void* ths) {
    int currentShift = 0;
    PtrToMostDerivedPtr.emplace(ths, ths);
    for (auto& parentName: ti.parentNames) {
        for (auto& p: TypeNameToTypeInfo[parentName].BaseNameToShiftMap) {
            PtrToMostDerivedPtr[(char*)ths+p.second+currentShift] = ths;
        }
        currentShift += TypeNameToTypeInfo[parentName].size;
    }
}
