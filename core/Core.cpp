#include "Core.hpp"
#include <iostream>
#include <cmath>
#include <fstream>

#include "../math/Vector.hpp"
#include "../math/Constants.hpp"

#include "../trajectory/builder/BallisticTrajectory.hpp"
#include "../trajectory/creator/BallisticConstMassKCreator.hpp"

#include "../trajectory/builder/BallisticTrajectory3D.hpp"
#include "../trajectory/creator/Ballistic3DConstMassKCreator.hpp"

#include "../function/EndpointDistance.hpp"
#include "../trajectory/solver/RK4Solver.hpp"

#include "../minimizators/RandomSearch.hpp"
#include "../minimizators/GradientDescent.hpp"

void Core::start()
{
    double mass = 27 * 5.5;
    double radius = 0.32;
    double k = 0.5 * Constants::SPHERE_DRAG_COEFFICIENT * Constants::AIR_DENSITY * M_PI * radius * radius;

    Ballistic3DConstMassKCreator creator(mass, k);
    RK4Solver<6> solver(creator({0,0,0}));

    Vector3d target = {100, 100, 5}; // x, y, z
    int verticalIndex = 2; // z index
    Vector<Vector2d, 3> velocityBoundaries = {{3,15}, {3,15}, {3,15}};
     
    EndpointDistance<3, 6> function(solver, creator, target, verticalIndex);
    GradientDescent<3> gd(function, velocityBoundaries);

    auto res = gd.minimize();
    std::cout << res.first << " "<< res.second << '\n';

    // outputting trajectory to ensure result
    auto traj = creator(res.second);
    solver.setSystem(traj);
    double step = 0.01;
    std::ofstream out("out.txt");
    out << target << '\n';
    
    for (int i = 1; i < 10000; i ++) {
        auto state = solver.solve(i * step);
        out << state << '\n';
        if (state[traj->verticalCoordinateStateIndex()] < 0) {
            break;
        }
    }

    delete traj;
}