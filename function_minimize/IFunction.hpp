#pragma once

#include "../math/Vector.hpp"

template <class T, class I, int dim>
class IFunction {
public:
    virtual T operator()(const Vector<I, dim>& input) = 0;
};