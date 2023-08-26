#include "Core.hpp"
#include <iostream>
#include <cmath>
#include <fstream>
#include "../math/Vector.hpp"
#include "../math/Constants.hpp"
#include "../trajectory/builder/BallisticTrajectory.hpp"

#include "../function/EndpointDistance.hpp"
#include "../trajectory/creator/BallisticConstMassKCreator.hpp"
#include "../trajectory/solver/RK4Solver.hpp"

#include "../minimizators/RandomSearch.hpp"
#include "../minimizators/GradientDescent.hpp"

void Core::start()
{
    double mass = 0.2;
    double radius = 0.05;
    double k = 0.5 * Constants::SPHERE_DRAG_COEFFICIENT * Constants::AIR_DENSITY * M_PI * radius * radius;

    BallisticConstMassKCreator creator(mass, k);
    RK4Solver<4> solver(creator({0,0}));
     
    EndpointDistance<2, 4> function(solver, creator, {4, 1}, 1);
    GradientDescent<2> gd(function, {{2,10}, {2,10}});

    auto res = gd.minimize();
    std::cout << res.first << " "<< res.second << '\n';

    // outputting trajectory to ensure result
    auto traj = creator(res.second);
    solver.setSystem(traj);
    double step = 0.01;
    std::ofstream out("out.txt");
    
    for (int i = 1; i < 1800; i ++) {
        auto state = solver.solve(i * step);
        out << state << '\n';
        if (state[traj->verticalCoordinateStateIndex()] < 0) {
            break;
        }
    }

    delete traj;
}