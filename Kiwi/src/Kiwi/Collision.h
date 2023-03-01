#pragma once
#include <Kiwi/Collider.h>

namespace Kiwi
{
    class Object;
    
    struct Collision
    {
        Object* ObjA;
        Object* ObjB;
        CollisionPoints Points;
    };
}
