#include "Object.h"

extern Destroyer destroyer;
bool Object::onTheHeap = false;
extern std::stack<std::vector<Object*>> objects;

static void* Object::operator new(size_t sz)
{
    onTheHeap = true;
    return ::operator new(sz);
}

Object::Object()
{
    if (!onTheHeap) {
        objects.top().push_back(this);
        //destroyer.addObject(this);
    }
    onTheHeap = false;
}

Object::~Object() {
    //printf("Destroying Object\n");
}

std::stack<std::vector<Object*>> objects;
