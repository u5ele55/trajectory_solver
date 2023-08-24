#include "BallisticTrajectory.hpp"
#include "../../math/Constants.hpp"
#include <cmath>

BallisticTrajectory::BallisticTrajectory(Vector2d startVelocity, double mass, double k) 
    : startVelocity(startVelocity),
    mass(mass),
    k(k)
{}

Vector<double, 4> BallisticTrajectory::f(const Vector<double, 4> &state)
{
    double xdot = state[1], ydot = state[3];
    double v = sqrt(xdot*xdot + ydot*ydot);
    Vector<double, 4> stateDerivative = {xdot, 0, ydot, 0};
    stateDerivative[1] = -k / mass * v * xdot;
    stateDerivative[3] = -k / mass * v * ydot - Constants::G;
    
    return stateDerivative;
} 

Vector<double, 4> BallisticTrajectory::getInitialState() const
{
    return {0, startVelocity[0], 0, startVelocity[1]};
}
