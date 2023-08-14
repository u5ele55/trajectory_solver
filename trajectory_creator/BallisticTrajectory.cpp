#include "BallisticTrajectory.hpp"
#include "../math/Constants.hpp"

BallisticTrajectory::BallisticTrajectory(Vector3d startVelocity) : startVelocity(startVelocity)
{
    std::cout << "hi";
}   

std::vector<Vector3d> BallisticTrajectory::getValues(double step)
{
    std::vector<Vector3d> result;
    auto velocity = startVelocity;

    Vector3d coord;

    while (coord[2] >= 0) {
        coord = coord + velocity * step;
        velocity[2] -= step * Constants::G;
        std::cout << velocity << " " << coord << '\n';
    }

    return result;
}
