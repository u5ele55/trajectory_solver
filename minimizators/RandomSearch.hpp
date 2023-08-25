#pragma once

#include <random>

#include "IMinimizer.hpp"
#include "../function/IFunction.hpp"
#include "../utilities/RandomVector.hpp"

template <int dim>
class RandomSearch : public IMinimizer<double, double, dim> {
public:
    RandomSearch(IFunction<double, double, dim> &function, Vector<Vector2d, dim> boundaries, int iterations = 100);
    std::pair<double, Vector<double, dim>> minimize();
protected:
    RandomVector<dim> generator;
    Vector<std::uniform_real_distribution<>, dim> distributions;
    IFunction<double, double, dim> &function;
    int iterations;
};

template <int dim>
inline RandomSearch<dim>::RandomSearch(
    IFunction<double, double, dim> &function,
    Vector<Vector2d, dim> boundaries, 
    int iterations
) : generator(boundaries),
    function(function),
    iterations(iterations) {}

template <int dim>
inline std::pair<double, Vector<double, dim>> RandomSearch<dim>::minimize()
{
    Vector<double, dim> point, minPoint;
    double min = 1e100;

    for (int _ = 0; _ < iterations; _ ++) {
        point = generator.generate();
        std::cout << point;

        double res = function(point);
        if (res < min) {
            min = res;
            minPoint = point;
        }
    }

    return {min, minPoint};
}
