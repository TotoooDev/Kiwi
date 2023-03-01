#pragma once
#include <Kiwi/Collider.h>

namespace Kiwi
{
    struct LineCollider : public Collider
    {
        glm::vec2 Vec;
        float Length;

        CollisionPoints TestCollision(const Transform* selfTransform, const Collider* collider, const Transform* colliderTransform) const override;
        CollisionPoints TestCollision(const Transform* selfTransform, const CircleCollider* collider, const Transform* colliderTransform) const override;
        CollisionPoints TestCollision(const Transform* selfTransform, const LineCollider* collider, const Transform* colliderTransform) const override;
    };
}
