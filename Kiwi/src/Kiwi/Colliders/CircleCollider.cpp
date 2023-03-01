#include <Kiwi/Colliders/CircleCollider.h>
#include <Kiwi/Algo.h>

namespace Kiwi
{
    CollisionPoints CircleCollider::TestCollision(const Transform* selfTransform, const Collider* collider, const Transform* colliderTransform) const
    {
        return collider->TestCollision(colliderTransform, this, selfTransform);
    }

    CollisionPoints CircleCollider::TestCollision(const Transform* selfTransform, const CircleCollider* collider, const Transform* colliderTransform) const
    {
        return Algo::FindCollisionPoints::CircleCircle(this, selfTransform, collider, colliderTransform);
    }

    CollisionPoints CircleCollider::TestCollision(const Transform* selfTransform, const LineCollider* collider, const Transform* colliderTransform) const
    {
        return Algo::FindCollisionPoints::CircleLine(this, selfTransform, collider, colliderTransform);
    }
}
