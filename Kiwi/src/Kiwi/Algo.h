#pragma once
#include <Kiwi/Colliders/CircleCollider.h>
#include <Kiwi/Colliders/LineCollider.h>

namespace Kiwi
{
    namespace Algo
    {
        namespace FindCollisionPoints
        {
            CollisionPoints CircleCircle(const CircleCollider* a, const Transform* transformA, const CircleCollider* b, const Transform* transformB);
            CollisionPoints CircleLine(const CircleCollider* a, const Transform* transformA, const LineCollider* b, const Transform* transformB);
        }
    }
}
