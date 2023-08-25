#pragma once

#include "../function/IFunction.hpp"

template <class T, class I, int dim>
class IMinimizer {
public:
    /// @brief Minimizes function
    /// @return minimal value found and argument
    virtual std::pair<T, Vector<I, dim>> minimize() = 0;
};