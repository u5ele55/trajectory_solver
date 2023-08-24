#pragma once
#include <vector>
#include "../../math/Vector.hpp"

template <int stateSize>
class ISystem {
public:
    virtual Vector<double, stateSize> f(const Vector<double, stateSize> &state) = 0;
    virtual Vector<double, stateSize> getInitialState() const = 0;
};