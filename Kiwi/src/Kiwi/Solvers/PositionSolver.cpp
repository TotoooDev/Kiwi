#include <Kiwi/Solvers/PositionSolver.h>

namespace Kiwi
{
    void PositionSolver::Solve(std::vector<Collision>& collisions, float timestep)
    {
        for (Collision& collision : collisions)
        {
            collision.ObjA->Velocity *= -1;
            collision.ObjB->Velocity *= -1;
        }
    }
}
