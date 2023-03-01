#include <Kiwi/PhysicsWorld.h>
#include <algorithm>
#include <iostream>

namespace Kiwi
{
    void PhysicsWorld::AddObject(Object* object)
    {
        m_Objects.push_back(object);
    }

    void PhysicsWorld::RemoveObject(Object* object)
    {
        auto it = std::find(m_Objects.begin(), m_Objects.end(), object);
        if (it != m_Objects.end())
            m_Objects.erase(it);
    }

    void PhysicsWorld::AddSolver(Solver* solver)
    {
        m_Solvers.push_back(solver);
    }

    void PhysicsWorld::RemoveSolver(Solver* solver)
    {
        auto it = std::find(m_Solvers.begin(), m_Solvers.end(), solver);
        if (it != m_Solvers.end())
            m_Solvers.erase(it);
    }

    void PhysicsWorld::Step(float timestep)
    {
        ResolveCollisions(timestep);
        ApplyForces(timestep);
    }

    void PhysicsWorld::ApplyForces(float timestep)
    {
        for (Object* object : m_Objects)
        {
            if (object->AffectedByGravity)
                object->Force += object->Mass * m_Gravity; // Apply gravity force

            object->Velocity += object->Force / object->Mass * timestep * SimulationSpeed;
            object->MyTransform->Position += object->Velocity * timestep * SimulationSpeed;

            object->Force = glm::vec3(0.0f); // Reset net force
        }
    }

    void PhysicsWorld::ResolveCollisions(float timestep)
    {
        std::vector<Collision> collisions;
        for (Object* a : m_Objects)
        {
            for (Object* b : m_Objects)
            {
                if (a == b)
                    break;

                if (!a->MyCollider || !b->MyCollider)
                    continue;

                CollisionPoints points = a->MyCollider->TestCollision(a->MyTransform, b->MyCollider, b->MyTransform);
                if (points.HasCollision)
                    collisions.push_back({ a, b, points });
            }
        }

        for (Solver* solver : m_Solvers)
        {
            solver->Solve(collisions, timestep);
        }
    }
}
