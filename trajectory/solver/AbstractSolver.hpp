#pragma once

#include "../builder/ISystem.hpp"

template <int stateSize>
class AbstractSolver {
public:
    explicit AbstractSolver(ISystem<stateSize> &trajectory, double step = 0.01)
        : trajectory(trajectory), step(step) {}

    virtual Vector<double, stateSize> methodStep(const Vector<double, stateSize> &state, double time) = 0;

    virtual Vector<double, stateSize> solve(double time); 

protected:
    ISystem<stateSize> &trajectory;
    double step;
    std::vector<Vector<double, stateSize>> states;
};

template <int stateSize>
inline Vector<double, stateSize> AbstractSolver<stateSize>::solve(double time)
{
    if (states.empty()) {
        states.push_back(trajectory.getInitialState());
    }
    Vector<double, stateSize> state;
    int stepsInTime = static_cast<int>(time / step);

    if (time < (states.size() - 1) * step) {
        state = states[stepsInTime];
    } else {
        state = states[states.size() - 1];
        for(int _ = states.size() - 1; _ < static_cast<int>(time / step); _++) {
            state = methodStep(state, step);
            states.push_back(state);
        }
    }

    // recalculate more precisely for case when t != step * k for some whole k
    double wholePart = step * static_cast<int>(time / step);
    double timeDiff = time - wholePart;

    if (timeDiff != 0) {
        state = methodStep(state, timeDiff);
    }

    return state;
}
