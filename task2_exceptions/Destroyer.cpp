#include "Destroyer.h"
#include "Object.h"
#include <cassert>

//extern std::stack<std::vector<Object*>> objects;
bool isCleaningStack = false;
bool isInException = false;

void Destroyer::createFrame() {
    objects.emplace();
}

void Destroyer::addObject(Object* obj) {
    assert(!objects.empty());
    objects.top().push_back(obj);
}

void Destroyer::unwindFrame() {
    ++isInException;
    isCleaningStack = true;
    for (auto& obj: objects.top()) {
        obj->~Object();
    }
    objects.pop();
    isCleaningStack = false;
}

Destroyer destroyer;
