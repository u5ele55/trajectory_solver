#pragma once

#include "ISystemCreator.hpp"
#include "../builder/BallisticTrajectory3D.hpp"

class Ballistic3DConstMassKCreator : public ISystemCreator<6, 3> {
public:
    Ballistic3DConstMassKCreator(double mass, double k) : mass(mass), k(k) {};
    BallisticTrajectory3D* operator()(const Vector3d& args) {
        return new BallisticTrajectory3D(args, mass, k); 
    };
protected:
    double mass;
    double k;
};
