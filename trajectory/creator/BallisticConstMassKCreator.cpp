#include "BallisticConstMassKCreator.hpp"

BallisticConstMassKCreator::BallisticConstMassKCreator(double mass, double k) 
    : mass(mass), k(k) {}

BallisticTrajectory* BallisticConstMassKCreator::operator()(const Vector<double, 2> &args)
{
    return new BallisticTrajectory(args, mass, k); 
}
