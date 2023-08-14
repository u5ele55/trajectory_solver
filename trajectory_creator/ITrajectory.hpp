#pragma once
#include <vector>

class ITrajectory {
public:
    std::vector<double> getValues(double step = 0.01);
};