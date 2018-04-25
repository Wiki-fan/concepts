#pragma once
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>


#define OBJECT(CLASS, OBJNAME, INITIALIZATION...) \
CLASS OBJNAME INITIALIZATION; \
ObjToClassNameMap.insert(std::make_pair(reinterpret_cast<void*>(&OBJNAME), std::string(#CLASS)));

struct TypeInfo {
    TypeInfo() {}
    TypeInfo(std::string name_, const char* parentNames_) : name(name_) {
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
    std::string name;
    std::string hash;
    std::vector<std::string> parentNames;
};

extern std::map<void*, std::string> ObjToClassNameMap;
extern std::map<std::string, TypeInfo> TypeNameToTypeInfo;

#define TYPEID(OBJ) TypeNameToTypeInfo[ObjToClassNameMap[reinterpret_cast<void*>(OBJ)]]
#define TYPEINFO(TYPE) TypeInfo##TYPE

#define BEGIN_CLASS_DECLARATION
#define DECLARE_CLASS(CLASSNAME) \
if (TypeNameToTypeInfo.find(#CLASS) == TypeNameToTypeInfo.end()) {\
    TypeNameToTypeInfo.insert(std::make_pair(#CLASS, TypeInfo(TypeInfo##CLASS::name, TypeInfo##CLASS::parentNames))); \
}

#define END_CLASS_DECLARATION

#define CLASS(TYPENAME, ...) \
struct TypeInfo##TYPENAME { \
    int index; \
    constexpr static char* name = #TYPENAME; \
    constexpr static char* hash = #TYPENAME "LOL"; \
    constexpr static char* parentNames = #__VA_ARGS__; \
}; \
class TYPENAME __VA_OPT__(:) __VA_ARGS__

//constexpr static std::vector<std::string> parentNames = {#__VA_ARGS__};
