#pragma once

#include <cassert>

#include "IFunction.hpp"
#include "../trajectory/solver/AbstractSolver.hpp"
#include "../trajectory/creator/ISystemCreator.hpp"
#include "../trajectory/builder/ISystem.hpp"

template <class I, int dim, int stateSize>
class EndpointDistance : public IFunction<double, I, dim> {
public:
    EndpointDistance(
        AbstractSolver<stateSize> &solver, 
        ISystemCreator<stateSize, dim> &creator, 
        const Vector<double, dim>& endpoint,
        int verticalIndex,
        double tolerance = 1e-3);
    double operator()(const Vector<I, dim>& input);
protected:
    AbstractSolver<stateSize> &solver;
    ISystemCreator<stateSize, dim> &creator;
    Vector<double, dim> endpoint;
    double tolerance;
    int verticalIndex;
protected:
    bool anyMatch(
        const Vector<double, stateSize> &stateVector, 
        const Vector<double, dim> &b, 
        const std::vector<int> &indexes);
    double distance(
        const Vector<double, stateSize> &stateVector, 
        const Vector<double, dim> &b, 
        const std::vector<int> &indexes);
    Vector<double, stateSize> bsMatchY(
        double l, double r, double Y, int yIndex, bool ascending
    );
};

template <class I, int dim, int stateSize>
inline EndpointDistance<I, dim, stateSize>::EndpointDistance(
    AbstractSolver<stateSize> &solver, 
    ISystemCreator<stateSize, dim> &creator, 
    const Vector<double, dim>& endpoint,
    int verticalIndex,
    double tolerance
) : solver(solver), 
    creator(creator), 
    endpoint(endpoint), 
    tolerance(tolerance),
    verticalIndex(verticalIndex) {
        assert(endpoint[verticalIndex] >= 0);
    }

template <class I, int dim, int stateSize>
inline double EndpointDistance<I, dim, stateSize>::operator()(const Vector<I, dim> &input)
{
    ISystem<stateSize>* system = creator(input);

    auto pointCoordinates = system->coordinateStateIndex();
    assert(pointCoordinates.size() == dim);

    solver.setSystem(system);

    double rightBound;

    Vector<double, stateSize> state, state1, state2;
    double l = 0, r = 4, midLeft, midRight;
    int yIndex = system->verticalCoordinateStateIndex();

    // we will find x s.t. solve(x).y < 0 
    state[yIndex] = 1;
    while (state[yIndex] > 0) {
        r *= 1.5;
        state = solver.solve(r);
    }
    rightBound = r;

    // ternary search to find highest point
    while (r - l > tolerance) {
        midLeft = l + (r-l)/3;
        midRight = r - (r-l)/3; 
        
        state2 = solver.solve(midRight);
        state1 = solver.solve(midLeft);
        
        if (state1[yIndex] < state2[yIndex]) {
            l = midLeft;
        }
        else {
            r = midRight;
        }
    }
    double highest = (r + l) / 2;

    std::cout << "Highest at " << highest << " s. Value:" << solver.solve(highest) << '\n';
        // if (fabs(value) > fabs(state[yIndex])) {
        //     value = state[yIndex];
        // }
    state = solver.solve(highest);
    if (state[yIndex] < endpoint[verticalIndex]) {
        // calculate distance from highest point ? 
        return distance(state, endpoint, pointCoordinates);
    }
    // now find x: solve(x).y == endpoint.y for two parts: [0; highest], [highest, rightBound]
    state1 = bsMatchY(0, highest, endpoint[verticalIndex], yIndex, true);
    state2 = bsMatchY(highest, rightBound, endpoint[verticalIndex], yIndex, false);
    
    std::cout << state1 << " " << state2 << '\n';

    double d1 = distance(state1, endpoint, pointCoordinates);
    double d2 = distance(state2, endpoint, pointCoordinates);

    return d1 < d2 ? d1 : d2;
}

template <class I, int dim, int stateSize>
inline bool EndpointDistance<I, dim, stateSize>::anyMatch(
    const Vector<double, stateSize> &stateVector, const Vector<double, dim> &b, const std::vector<int> &indexes
)
{
    for(int i = 0; i < dim; i ++) {
        if (fabs(stateVector[indexes[i]] - b[i]) < tolerance) {
            return true;
        }
    }
    return false;
}

template <class I, int dim, int stateSize>
inline double EndpointDistance<I, dim, stateSize>::distance(
    const Vector<double, stateSize> &stateVector, const Vector<double, dim> &b, const std::vector<int> &indexes
)
{
    double dist = 0, d;
    for(int i = 0; i < dim; i ++) {
        d = stateVector[indexes[i]] - b[i];
        dist += d*d;
    }
    return dist;
}

template <class I, int dim, int stateSize>
inline Vector<double, stateSize> EndpointDistance<I, dim, stateSize>::bsMatchY(double l, double r, double Y, int yIndex, bool ascending)
{
    double mid;
    Vector<double, stateSize> state;
    state[yIndex] = Y + tolerance * 10;

    while (fabs(Y - state[yIndex]) > tolerance) {
        mid = (r+l) / 2;
        state = solver.solve(mid);
        if ((state[yIndex] > Y) ^ ascending) {
            l = mid;
        }
        else {
            r = mid;
        }
    }
    return state;
}
