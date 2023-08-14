#pragma once
#include <vector>
#include "../math/Vector.hpp"

class ITrajectory {
public:
    virtual std::vector<Vector3d> getValues(double step = 0.01) = 0;
};