#pragma once

#include <random>

#include "IMinimizer.hpp"
#include "../function/IFunction.hpp"

template <int dim>
class RandomSearch : public IMinimizer<double, double, dim> {
public:
    RandomSearch(IFunction<double, double, dim> &function, Vector<Vector2d, dim> boundaries, int iterations = 100);
    std::pair<double, Vector<double, dim>> minimize();
protected:
    std::mt19937 generator;
    Vector<std::uniform_real_distribution<>, dim> distributions;
    IFunction<double, double, dim> &function;
    int iterations;
};

template <int dim>
inline RandomSearch<dim>::RandomSearch(
    IFunction<double, double, dim> &function,
    Vector<Vector2d, dim> boundaries, 
    int iterations
) : generator((std::random_device())()),
    function(function),
    iterations(iterations)
{
    for (int i = 0; i < dim; i ++) {
        distributions[i] = std::uniform_real_distribution<>(boundaries[i][0], boundaries[i][1]);
    }
}

template <int dim>
inline std::pair<double, Vector<double, dim>> RandomSearch<dim>::minimize()
{
    Vector<double, dim> point, minPoint;
    double min = 1e100;

    for (int _ = 0; _ < iterations; _ ++) {
        for (int i = 0; i < dim; i ++) {
            point[i] = distributions[i](generator);
        }
        std::cout << point << '\n';

        double res = function(point);
        if (res < min) {
            min = res;
            minPoint = point;
        }
    }

    return {min, minPoint};
}
