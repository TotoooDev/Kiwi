#pragma once
#include <Kiwi/Object.h>
#include <Kiwi/Solver.h>
#include <vector>

namespace Kiwi
{
    class PhysicsWorld
    {
    public:
        void AddObject(Object* object);
        void RemoveObject(Object* object);

        void AddSolver(Solver* solver);
        void RemoveSolver(Solver* solver);

        void Step(float timestep);

        float SimulationSpeed = 1.0f;

    private:
        void ApplyForces(float timestep);
        void ResolveCollisions(float timestep);

        std::vector<Object*> m_Objects;
        std::vector<Solver*> m_Solvers;
        glm::vec2 m_Gravity = glm::vec2(0.0f, -9.81f);
    };
}
