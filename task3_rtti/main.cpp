#include "TypeInfo.h"
#include "DynamicCast.h"

CLASS(BaseTest1)
    int bt1a;
    int bt1b;
};

CLASS(BaseTest2)
    int bt2a;
    int bt2b;
    int bt2c;
};

CLASS(Derived, public BaseTest1, public BaseTest2)
    int da;
};

int main() {
    BEGIN_CLASS_DECLARATION;
    DECLARE_CLASS(BaseTest1);
    DECLARE_CLASS(BaseTest2);
    DECLARE_CLASS(Derived);

    END_CLASS_DECLARATION;
    OBJECT(BaseTest1, bt1);
    OBJECT(Derived, t1);
    std::cout << TYPEINFO(Test)::hash <<std::endl;
    std::cout <<TYPEID(&t1).hash <<std::endl;
    /*BaseType& t = TypeInfoTest;
    std::cout << t.name;*/
    //DYNAMIC_CAST(A, t1);
    Test* t1_ptr = &t1;
    DYNAMIC_CAST(Test, t1_ptr);
    //std::cout << DYNAMIC_CAST(Test, t1_ptr) <<std::endl;
    return 0;
}
