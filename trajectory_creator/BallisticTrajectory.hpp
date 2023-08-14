#pragma once

#include "../math/Vector.hpp"
#include "ITrajectory.hpp"

class BallisticTrajectory : public ITrajectory {
public:
    BallisticTrajectory(Vector3d startVelocity);
    std::vector<Vector3d> getValues(double step);
protected:
    Vector3d startVelocity;
};