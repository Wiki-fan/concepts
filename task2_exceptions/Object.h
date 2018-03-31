#pragma once

#include <stack>
#include <vector>
#include <csetjmp>
#include <cstdio>

#include "Destroyer.h"

class Object {
 protected:
    static bool onTheHeap;
 public:
    static void *operator new(size_t sz);

    Object();

    virtual ~Object();
};







