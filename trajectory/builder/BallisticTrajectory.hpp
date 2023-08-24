#pragma once

#include "ISystem.hpp"

class BallisticTrajectory : public ISystem<4> {
public:
    BallisticTrajectory(Vector2d startVelocity, double mass, double k);
    Vector<double, 4> f(const Vector<double, 4> &state);
    Vector<double, 4> getInitialState() const;

protected:
    Vector2d startVelocity;
    double mass; 
    double k; 
};