#pragma once

#include "IFunction.hpp"
#include "../trajectory/solver/AbstractSolver.hpp"
#include "../trajectory/creator/ISystemCreator.hpp"
#include "../trajectory/builder/ISystem.hpp"

template <class I, int dim, int stateSize>
class EndpointDistance : public IFunction<double, I, dim> {
public:
    EndpointDistance(AbstractSolver<stateSize> &solver, ISystemCreator<stateSize, dim> &creator, const Vector<double, dim>& endpoint);
    double operator()(const Vector<I, dim>& input);
protected:
    AbstractSolver<stateSize> &solver;
    ISystemCreator<stateSize, dim> &creator;
    Vector<double, dim> endpoint;
};

template <class I, int dim, int stateSize>
inline EndpointDistance<I, dim, stateSize>::EndpointDistance(
    AbstractSolver<stateSize> &solver, 
    ISystemCreator<stateSize, dim> &creator, 
    const Vector<double, dim>& endpoint
    ) : solver(solver), creator(creator), endpoint(endpoint) {}

template <class I, int dim, int stateSize>
inline double EndpointDistance<I, dim, stateSize>::operator()(const Vector<I, dim> &input)
{
    ISystem<stateSize>* system = creator(input);
    solver.setSystem(system);
    
    std::ofstream out("out.txt");

    double step = 0.01;
    int yIndex = system->verticalCoordinateStateIndex(); 

    // here will be minimazation of a distance
    for (int i = 1; i < 1800; i ++) {
        auto state = solver.solve(i * 0.01);
        if (state[yIndex] < 0) {
            std::cout << "Reached zero at " << i * step << " s" << '\n';
            break;
        }
        out << solver.solve(i * step) << '\n';
    }
    
    return 0.0;
}
