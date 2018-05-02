#include "TypeInfo.h"
#include "DynamicCast.h"

RTTI_CLASS(Base)
CONSTRUCTOR(Base)
CONSTRUCTOR_END()
int ba = 0;
RTTI_CLASS_END(Base)

RTTI_CLASS(Base1)
CONSTRUCTOR(Base1)
CONSTRUCTOR_END()
    int b1a = 1;
    int b1b = 2;
RTTI_CLASS_END(Base1)

RTTI_CLASS(Base2, Base)
CONSTRUCTOR(Base2)
CONSTRUCTOR_END()
    int b2a = 3;
    int b2b = 4;
    int b2c = 5;
RTTI_CLASS_END(Base2, Base)

RTTI_CLASS(Derived, Base1, Base2)
CONSTRUCTOR(Derived)
CONSTRUCTOR_END()
    int da = 6;
RTTI_CLASS_END(Derived, Base1, Base2)

int main() {
    REGISTER_CLASS(Base);
    REGISTER_CLASS(Base1);
    REGISTER_CLASS(Base2);
    REGISTER_CLASS(Derived);

    Base1 b1;
    Derived d;
    Base* polymorphic = (Base*)&d;
    std::cout <<TYPEINFO(Derived)::hash <<std::endl;
    std::cout <<TYPEID(&b1).hash <<std::endl;
    std::cout <<TYPEID(&d).hash <<std::endl;

    auto cast1 = DYNAMIC_CAST(Base1, &d);
    auto cast2 = DYNAMIC_CAST(Base1, polymorphic);
    /*Test* t1_ptr = &t1;
    DYNAMIC_CAST(Test, t1_ptr);*/
    //std::cout << DYNAMIC_CAST(Test, t1_ptr) <<std::endl;
    return 0;
}
