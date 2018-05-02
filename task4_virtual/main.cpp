#include <iostream>
#include <string>
#include <map>
#include <functional>



#define CONSTRUCTOR(CLASS, ARGS...) \
CLASS(ARGS) { \
    vptr = &CLASS##vtbl;

#define CONSTRUCTOR_DERIVED(CLASS, BASE, ARGS...) \
CLASS(ARGS) { \
    vptr = &CLASS##vtbl; \
    Base::vptr = reinterpret_cast<std::map<std::string, std::function<void(BASE*)>>*>(vptr);

#define END_CONSTRUCTOR() }


#define VIRTUAL_CLASS(CLASS) \
struct CLASS; \
std::map<std::string, std::function<void(CLASS*)>> CLASS##vtbl; \
struct CLASS { \
std::map<std::string, std::function<void(CLASS*)>>* vptr;

#define VIRTUAL_CLASS_DERIVED(CLASS, BASE) \
struct CLASS; \
std::map<std::string, std::function<void(CLASS*)>> CLASS##vtbl; \
struct CLASS : BASE { \
std::map<std::string, std::function<void(CLASS*)>>* vptr;

#define END_CLASS() };


#define VIRTUAL_METHOD(CLASS, METHOD) \
void CLASS##METHOD (CLASS* obj)

VIRTUAL_CLASS(Base)
    int a;

    CONSTRUCTOR(Base)
    END_CONSTRUCTOR()
END_CLASS()

VIRTUAL_METHOD(Base, OnlyBase) {
    std::cout << "Base::OnlyBase" <<std::endl;
}
VIRTUAL_METHOD(Base, Both) {
    std::cout << "Base::Both a = " << obj->a <<std::endl;
}

VIRTUAL_CLASS_DERIVED(Derived, Base)
    int b;
    CONSTRUCTOR_DERIVED(Derived, Base)
    END_CONSTRUCTOR()
END_CLASS()

VIRTUAL_METHOD(Derived, Both) {
    std::cout << "Derived::Both b = " << obj->b <<std::endl;
}

VIRTUAL_METHOD(Derived, OnlyDerived) {
    std::cout << "Derived::OnlyDerived" <<std::endl;
}


#define REGISTER_VIRTUAL_METHOD(CLASS, METHOD) \
CLASS##vtbl.insert(std::make_pair(#METHOD, CLASS##METHOD));

#define POPULATE_VTBL(CLASS, BASE) \
for (auto&& iter = BASE##vtbl.begin(); iter != BASE##vtbl.end(); ++iter) { \
    std::string methodName = iter->first; \
    if (CLASS##vtbl.find(methodName) == CLASS##vtbl.end()) { \
        CLASS##vtbl.insert(std::make_pair(methodName, BASE##vtbl[methodName])); \
    } \
}

#define VIRTUAL_CALL(OBJ_PTR, METHOD) \
(OBJ_PTR)->vptr->at(#METHOD)(OBJ_PTR);

int main()
{
    REGISTER_VIRTUAL_METHOD(Base, OnlyBase);
    REGISTER_VIRTUAL_METHOD(Base, Both);
    REGISTER_VIRTUAL_METHOD(Derived, Both);
    REGISTER_VIRTUAL_METHOD(Derived, OnlyDerived);

    POPULATE_VTBL(Derived, Base);

    Base base;
    base.a = 0; // работаем как со структурой
    Derived derived;
    derived.b = 1;
    // полиморфизм
    Base* reallyDerived = reinterpret_cast<Base*>(&derived);

    VIRTUAL_CALL(&base, Both); // печатает “Base::Both a = 0”
    VIRTUAL_CALL(&derived, OnlyBase); // печатает “Base::OnlyBase”
    VIRTUAL_CALL(reallyDerived, Both); // печатает “Derived::Both b = 1”
    VIRTUAL_CALL(reallyDerived, OnlyBase);  // печатает “Base::OnlyBase”
    VIRTUAL_CALL(reallyDerived, OnlyDerived); // печатает “Derived::OnlyDerived”

    return sizeof(Base);
}
