#pragma once
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>

struct TypeInfo {
    TypeInfo() {}
    TypeInfo(std::string name_, const char* parentNames_, int size_) : name(name_), size(size_) {
        std::string parentNamesStr(parentNames_);
        hash = name+"lol";
        std::replace( parentNamesStr.begin(), parentNamesStr.end(), ',', ' ');
        std::istringstream iss(parentNamesStr);
        int i = 0;
        do {
            std::string subs;
            iss >> subs;
            if (i%2==1) {
                parentNames.push_back(subs);
            }
            ++i;
        } while (iss);
    }

    bool operator==(const TypeInfo& other) {
        return hash == other.hash;
    }
    bool operator!=(const TypeInfo& other) {
        return !operator==(other);
    }

    std::string name;
    std::string hash;
    std::vector<std::string> parentNames;
    std::map<std::string, int> BaseNameToShiftMap;
    int size;
};

extern std::map<void*, std::string> ObjToClassNameMap;
extern std::map<std::string, TypeInfo> TypeNameToTypeInfo;

#define CONSTRUCTOR(CLASS, ARGS...) \
CLASS(ARGS) { \
ObjToClassNameMap[reinterpret_cast<void*>(this)] = std::string(#CLASS);
#define CONSTRUCTOR_END() }


#define RTTI_CLASS(TYPENAME, ...) \
struct TYPENAME __VA_OPT__(:) __VA_ARGS__ {

#define RTTI_CLASS_END(TYPENAME, ...) }; \
struct TypeInfo##TYPENAME { \
    int index; \
    constexpr static char* name = #TYPENAME; \
    constexpr static char* hash = #TYPENAME "LOL"; \
    constexpr static char* parentNames = #__VA_ARGS__; \
    constexpr static long size = sizeof(TYPENAME); \
};


#define REGISTER_CLASS(CLASS) \
if (TypeNameToTypeInfo.find(#CLASS) == TypeNameToTypeInfo.end()) {\
    TypeNameToTypeInfo.insert(std::make_pair(#CLASS, \
                              TypeInfo(TypeInfo##CLASS::name, \
                              TypeInfo##CLASS::parentNames, \
                              TypeInfo##CLASS::size))); \
}

#define TYPEID(OBJ) TypeNameToTypeInfo[ObjToClassNameMap[reinterpret_cast<void*>(OBJ)]]
#define TYPEINFO(TYPE) TypeInfo##TYPE
