#pragma once

#include "AbstractSolver.hpp"

template <int stateSize>
class RK4Solver : public AbstractSolver<stateSize> {
public:
    RK4Solver(ISystem<stateSize> *system, double step = 0.01) 
        : AbstractSolver<stateSize>(system, step) {};
    Vector<double, stateSize> methodStep(const Vector<double, stateSize> &state, double time);
protected:
    Vector<double, stateSize> k1, k2, k3, k4;
};

template <int stateSize>
inline Vector<double, stateSize> RK4Solver<stateSize>::methodStep(const Vector<double, stateSize> &state, double time)
{
    k1 = this->system->f(state);
    k2 = this->system->f(state + k1 * 0.5 * time);
    k3 = this->system->f(state + k2 * 0.5 * time);
    k4 = this->system->f(state + k3 * time);
    return state + (k1 + k2*2 + k3*2 + k4) * (time / 6);
}
