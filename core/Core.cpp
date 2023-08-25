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


void Core::start()
{
    double mass = 0.2;
    double radius = 0.05;
    double k = 0.5 * Constants::SPHERE_DRAG_COEFFICIENT * Constants::AIR_DENSITY * M_PI * radius * radius;

    BallisticConstMassKCreator creator(mass, k);
    RK4Solver<4> solver(creator({0,0}));
     

    EndpointDistance<2, 4> function(solver, creator, {4, 12}, 1);
    std::cout << function({20,40});
}