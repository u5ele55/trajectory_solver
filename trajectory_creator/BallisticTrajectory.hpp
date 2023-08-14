#pragma once

#include "../math/Vector.hpp"
#include "ITrajectory.hpp"

class BallisticTrajectory : public ITrajectory {
public:
    BallisticTrajectory(Vector3d startVelocity);
protected:
    Vector3d startVelocity;
};