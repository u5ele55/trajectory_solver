#pragma once

#include <random>

#include "../math/Vector.hpp"

template <int dim>
class RandomVector {
public:
    RandomVector(const Vector<Vector2d, dim> &boundaries);
    Vector<double, dim> generate();
private:
    std::mt19937 generator;
    Vector<std::uniform_real_distribution<>, dim> distributions;
};

template <int dim>
inline RandomVector<dim>::RandomVector(const Vector<Vector2d, dim> &boundaries) : generator((std::random_device())())
{
    for (int i = 0; i < dim; i ++) {
        distributions[i] = std::uniform_real_distribution<>(boundaries[i][0], boundaries[i][1]);
    }
}

template <int dim>
inline Vector<double, dim> RandomVector<dim>::generate()
{
    Vector<double, dim> point;
    for (int i = 0; i < dim; i ++) {
        point[i] = distributions[i](generator);
    }
    return point;
}
