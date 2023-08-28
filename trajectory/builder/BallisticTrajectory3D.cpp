#include "BallisticTrajectory3D.hpp"
#include "../../math/Constants.hpp"
#include <cmath>

BallisticTrajectory3D::BallisticTrajectory3D(Vector3d startVelocity, double mass, double k)
    : startVelocity(startVelocity),
    mass(mass),
    k(k)
{}

BallisticTrajectory3D::~BallisticTrajectory3D() {}

Vector<double, 6> BallisticTrajectory3D::f(const Vector<double, 6> &state)
{
    double xdot = state[1], ydot = state[3], zdot = state[5];

    double v = sqrt(xdot*xdot + ydot*ydot + zdot*zdot);
    Vector<double, 6> stateDerivative = {xdot, 0, ydot, 0, zdot, 0};
    stateDerivative[1] = -k / mass * v * xdot;
    stateDerivative[3] = -k / mass * v * ydot;
    stateDerivative[5] = -k / mass * v * zdot - Constants::g;
    
    return stateDerivative;
}

Vector<double, 6> BallisticTrajectory3D::getInitialState() const
{
    return {0, startVelocity[0], 0, startVelocity[1], 0, startVelocity[2]};
}

int BallisticTrajectory3D::verticalCoordinateStateIndex() const
{
    return 4; // z
}

std::vector<int> BallisticTrajectory3D::coordinateStateIndex() const
{
    return {0, 2, 4};
}
