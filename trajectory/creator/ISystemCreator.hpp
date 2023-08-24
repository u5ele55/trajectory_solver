#pragma once

#include "../builder/ISystem.hpp"

template <int stateSize, int inputSize>
class ISystemCreator {
public:
    virtual ISystem<stateSize>* operator()(const Vector<double, inputSize>& args) = 0;
};