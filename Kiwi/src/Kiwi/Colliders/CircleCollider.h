#pragma once
#include <Kiwi/Collider.h>

namespace Kiwi
{
    struct CircleCollider : public Collider
    {
        glm::vec2 Center;
        float Radius;

        CollisionPoints TestCollision(const Transform* selfTransform, const Collider* collider, const Transform* colliderTransform) const override;
        CollisionPoints TestCollision(const Transform* selfTransform, const CircleCollider* collider, const Transform* colliderTransform) const override;
        CollisionPoints TestCollision(const Transform* selfTransform, const LineCollider* collider, const Transform* colliderTransform) const override;
        
    };
}
