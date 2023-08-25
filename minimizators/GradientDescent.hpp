#pragma once

#include <random>

#include "IMinimizer.hpp"
#include "../function/IFunction.hpp"

template <int dim>
class GradientDescent : public IMinimizer<double, double, dim> {
public:
    GradientDescent(IFunction<double, double, dim> &function, Vector<Vector2d, dim> boundaries, int starts = 10);
    std::pair<double, Vector<double, dim>> minimize();
protected:

};