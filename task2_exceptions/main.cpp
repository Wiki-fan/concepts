#include "Exceptions.h"

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <cassert>
#include <string>

#include "Destroyer.h"
#include "Object.h"

class TestException : public BaseException {
 public:
    std::string msg() override {
        return "I'm TestException";
    }
};

class Test2Exception : public BaseException {
 public:
    std::string msg() override {
        return "I'm Test2Exception";
    }
};

class TestObject : public Object {
 public:
    ~TestObject() {
        printf("Destroying TestObject\n");
    }
};

class Test2Object : public Object {
 public:
    ~Test2Object() {
        printf("Destroying Test2Object\n");
    }
};

class ThrowingObject : public Object {
 public:
    ~ThrowingObject() {
        THROW(TestException());
    }
};

void throwingFunc() {
    TestObject to;
    THROW(TestException());
}

int main() {
    TRY {
        TestObject to;
        printf("Hello world\n");
    } EXCEPT(TestException, e,  {
        printf("I see from here %s\n", e.msg().c_str());
    })
    printf("\n");
    TRY {
        TestObject to;
        printf("Hello world\n");
        THROW(TestException());
    } EXCEPT(TestException, e,  {
        printf("I see from here %s\n", e.msg().c_str());
    })
    printf("\n");
    TRY {
        Test2Object to;
        TRY {
            TestObject to;
            printf("Hello world\n");
            THROW(TestException());
        } EXCEPT(Test2Exception, e, {
            printf("Test2Exception\n");
        })
    } EXCEPT(TestException, e, {
        printf("TestException\n");
    })
    printf("\n");
    TRY {
        TRY {
            TestObject to;
            printf("Hello world\n");
            THROW(Test2Exception());
        } EXCEPT(Test2Exception, e, {
            THROW(TestException());
            printf("Test2Exception\n");
        })
    } EXCEPT(TestException, e, {
        printf("TestException\n");
    })
    printf("\n");
    TRY {
        Test2Object to2;
        printf("Hello world\n");
        {
            TestObject to;
            THROW(TestException());
        }
    } EXCEPT(TestException, e,  {
        printf("I see from here %s\n", e.msg().c_str());
    })
    printf("\n");
    TRY {
        Test2Object to2;
        printf("Hello world\n");
        throwingFunc();
    } EXCEPT(TestException, e,  {
        printf("I see from here %s\n", e.msg().c_str());
    })
    printf("\n");
    TRY {
        Test2Object t2o;
        TRY {
            Test2Object t2o;
            printf("Hello world\n");
            throwingFunc();
        } EXCEPT(Test2Exception, e, {
            THROW(TestException());
            printf("Test2Exception\n");
        })
    } EXCEPT(TestException, e, {
        printf("TestException\n");
    })
    printf("\n");
    TRY {
        ThrowingObject obj;
        THROW(Test2Exception);
    } EXCEPT(Test2Exception, e, {
        printf("Exception while cleaning\n");
    })

    return 0;
}
