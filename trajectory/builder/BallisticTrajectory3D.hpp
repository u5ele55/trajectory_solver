#pragma once

#include "ISystem.hpp"

class BallisticTrajectory3D : public ISystem<6> {
public:
    BallisticTrajectory3D(Vector3d startVelocity, double mass, double k);
    ~BallisticTrajectory3D();
    Vector<double, 6> f(const Vector<double, 6> &state);
    Vector<double, 6> getInitialState() const;
    int verticalCoordinateStateIndex() const;
    std::vector<int> coordinateStateIndex() const;

protected:
    Vector3d startVelocity;
    double mass; 
    double k; 
};