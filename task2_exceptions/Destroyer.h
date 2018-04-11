#pragma once
#include <stack>
#include <vector>

class Object;
class Destroyer {
    std::stack<std::vector<Object*>> objects;
 public:
    void createFrame();

    void addObject(Object* obj);

    void unwindFrame();
};

extern Destroyer destroyer;
extern bool isCleaningStack;
extern bool isInException;