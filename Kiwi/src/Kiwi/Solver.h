#pragma once
#include <Kiwi/Collision.h>
#include <vector>

namespace Kiwi
{
    class Solver
    {
    public:
        virtual void Solve(std::vector<Collision>& collisions, float timestep) = 0;
    };
}
