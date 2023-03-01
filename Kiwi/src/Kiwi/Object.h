#pragma once
#include <Kiwi/Collider.h>
#include <Kiwi/Collision.h>
#include <glm/glm.hpp>
#include <functional>

namespace Kiwi
{
    class Object
    {
    public:
        Object(Transform* transform, Collider* collider, bool isTrigger = false)
            : m_Transform(transform), m_Collider(collider), m_IsTrigger(isTrigger)
        {}

        Transform* GetTransform() { return m_Transform; }
        Collider* GetCollider() { return m_Collider; }
        bool IsTrigger() { return m_IsTrigger; }

        void SetOnCollision(std::function<void(Collision&, float)> function) { m_OnCollision = function; }
        void SetTransform(Transform* transform) { m_Transform = transform; }
        void SetCollider(Collider* collider) { m_Collider = collider; }
        void SetIsTrigger(bool isTrigger) { m_IsTrigger = isTrigger; }

    protected:
        std::function<void(Collision&, float)> m_OnCollision;
        
        Transform* m_Transform;
        Collider* m_Collider;
        bool m_IsTrigger;
        bool m_IsDynamic;
    };

    class RigidBody : public Object
    {
    public:
        RigidBody(Transform* transform, Collider* collider)
            : Object(transform, collider)
        {}

        glm::vec2 GetGravity() { return m_Gravity; }
        glm::vec2 GetForce() { return m_Force; }
        glm::vec2 GetVelocity() { return m_Velocity; }
        float GetMass() { return m_Mass; }
        bool GetAffectedByGravity() { return m_AffectedByGravity; }
        float GetStaticFriction() { return m_StaticFriction; }
        float GetDynamicFriction() { return m_DynamicFriction; }
        float GetRestitution() { return m_Restitution; }

        void SetGravity(glm::vec2 gravity) { m_Gravity = gravity; }
        void SetForce(glm::vec2 force) { m_Force = force; }
        void SetVelocity(glm::vec2 velocity) { m_Velocity = velocity; }
        void SetMass(float mass) { m_Mass = mass; }
        void SetAffectedByGravity(bool affectedByGravity) { m_AffectedByGravity = affectedByGravity; }
        void SetStaticFriction(float friction) { m_StaticFriction = friction; }
        void SetDynamicFriction(float friction) { m_DynamicFriction = friction; }
        void SetRestitution(float restitution) { m_Restitution = restitution; }

    private:
        glm::vec2 m_Gravity = glm::vec2(0.0f, -9.81f);
        glm::vec2 m_Force; // Net force
        glm::vec2 m_Velocity;

        float m_Mass;
        bool m_AffectedByGravity;

        float m_StaticFriction;
        float m_DynamicFriction;
        float m_Restitution; // Bounciness
    };
}
