#include "TypeInfo.h"
#include "DynamicCast.h"




RTTI_CLASS(Base1)
CONSTRUCTOR(Base1)
CONSTRUCTOR_END()
    int b1a;
    int b1b;
RTTI_CLASS_END(Base1)

RTTI_CLASS(Base2)
CONSTRUCTOR(Base2)
CONSTRUCTOR_END()
    int b2a;
    int b2b;
    int b2c;
RTTI_CLASS_END(Base2)

RTTI_CLASS(Derived, Base1, Base2)
CONSTRUCTOR(Derived)
CONSTRUCTOR_END()
    int da;
RTTI_CLASS_END(Derived, Base1, Base2)

int main() {
    REGISTER_CLASS(Base1);
    REGISTER_CLASS(Base2);
    REGISTER_CLASS(Derived);

    Base1 b1;
    Derived d;
    std::cout << TYPEINFO(Derived)::hash <<std::endl;
    std::cout <<TYPEID(&b1).hash <<std::endl;
    std::cout <<TYPEID(&d).hash <<std::endl;
    /*BaseType& t = TypeInfoTest;
    std::cout << t.name;*/
    //DYNAMIC_CAST(A, t1);
    /*Test* t1_ptr = &t1;
    DYNAMIC_CAST(Test, t1_ptr);*/
    //std::cout << DYNAMIC_CAST(Test, t1_ptr) <<std::endl;
    return 0;
}
