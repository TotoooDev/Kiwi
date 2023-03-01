#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Kiwi
{
    struct CollisionPoints
    {
        glm::vec2 A; // Furthest point of A into B
        glm::vec2 B; // Furthest point of B into A
        glm::vec2 Normal; // B - A normalized
        float Depth; // Length of B - A
        bool HasCollision;
    };

    struct Transform
    {
        glm::vec2 Position;
        glm::vec2 Scale;
        glm::quat Rotation;
    };

    struct CircleCollider;
    struct LineCollider;

    struct Collider
    {
        virtual CollisionPoints TestCollision(const Transform* selfTransform, const Collider* collider, const Transform* colliderTransform) const = 0;
        virtual CollisionPoints TestCollision(const Transform* selfTransform, const CircleCollider* collider, const Transform* colliderTransform) const = 0;
        virtual CollisionPoints TestCollision(const Transform* selfTransform, const LineCollider* collider, const Transform* colliderTransform) const = 0;
    };
}
