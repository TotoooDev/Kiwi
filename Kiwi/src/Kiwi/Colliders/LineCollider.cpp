#include <Kiwi/Colliders/LineCollider.h>
#include <Kiwi/Colliders/CircleCollider.h>

namespace Kiwi
{
    CollisionPoints LineCollider::TestCollision(const Transform* selfTransform, const Collider* collider, const Transform* colliderTransform) const
    {
        return collider->TestCollision(colliderTransform, this, selfTransform);
    }

    CollisionPoints LineCollider::TestCollision(const Transform* selfTransform, const CircleCollider* collider, const Transform* colliderTransform) const
    {
        CollisionPoints points = collider->TestCollision(colliderTransform, this, selfTransform);

        glm::vec2 temp = points.A;
        points.A = points.B;
        points.B = temp;
        points.Normal = -points.Normal;
        return points;
    }

    CollisionPoints LineCollider::TestCollision(const Transform* selfTransform, const LineCollider* collider, const Transform* colliderTransform) const
    {
        return {}; // Line v line is not so useful yet
    }
}
