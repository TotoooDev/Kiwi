#pragma once
#include <Kiwi/Solver.h>
#include <iostream>

namespace Kiwi
{
    class PositionSolver : public Solver
    {
    public:
        void Solve(std::vector<Collision>& collisions, float timestep) override; 
    };
}
