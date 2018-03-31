#include "Destroyer.h"
#include <cassert>

extern std::stack<std::vector<Object*>> objects;

void Destroyer::createFrame() {
    objects.emplace();
}

/*void Destroyer::addObject(Object* obj) {
    assert(!objects.empty());
    objects.top().push_back(obj);
}*/

void Destroyer::unwindFrame() {
    for (auto& obj: objects.top()) {
        obj->~Object();
    }
    objects.pop();
}

Destroyer destroyer;
