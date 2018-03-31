#pragma once
#include <stack>
#include <vector>

#include "Object.h"

class Destroyer {

 public:
    void createFrame();

    //void addObject(Object* obj);

    void unwindFrame();
};

extern Destroyer destroyer;
