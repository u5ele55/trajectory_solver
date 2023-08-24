#pragma once

#include "ISystem.hpp"

class DummyTrajectory : public ISystem<2> {
public:
    Vector2d f(const Vector2d &state) {
        return {state[1], -0.1}; 
    }
    Vector2d getInitialState() const {
        return {10, 10};
    }
};