#pragma once

#include "ISystemCreator.hpp"
#include "../builder/BallisticTrajectory.hpp"

class BallisticConstMassKCreator : public ISystemCreator<4, 2> {
public:
    BallisticConstMassKCreator(double mass, double k);
    BallisticTrajectory* operator()(const Vector<double, 2>& args);
protected:
    double mass;
    double k;
};
