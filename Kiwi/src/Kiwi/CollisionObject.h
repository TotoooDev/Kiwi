#pragma once
#include <Kiwi/Collider.h>
#include <Kiwi/Solver.h>
#include <glm/glm.hpp>
#include <functional>

namespace Kiwi
{
    class CollisionObject
    {
    public:
        CollisionObject(Transform* transform, Collider* collider, bool isTrigger = false)
            : m_Transform(transform), m_Collider(collider), m_IsTrigger(isTrigger)
        {}

        void SetTransform(Transform* transform) { m_Transform = transform; }
        void SetCollider(Collider* collider) { m_Collider = collider; }
        void SetIsTrigger(bool isTrigger) { m_IsTrigger = isTrigger; }
        void SetOnCollisionFunction(std::function<void(Collision&, float)> func) { m_OnCollision = func; }

        Transform* GetTransform() { return m_Transform; }
        Collider* GetCollider() { return m_Collider; }
        bool IsTrigger() { return m_IsTrigger; }

    private:
        Transform* m_Transform = nullptr;
        Collider* m_Collider = nullptr;
        bool m_IsTrigger = false;
        bool m_IsDynamic = true;

        std::function<void(Collision&, float)> m_OnCollision;
    };

    class RigidBody : public CollisionObject
    {

    };
}
