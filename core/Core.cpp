#include "Core.hpp"
#include <iostream>
#include <cmath>
#include <fstream>
#include "../math/Vector.hpp"
#include "../math/Constants.hpp"
#include "../trajectory/builder/BallisticTrajectory.hpp"

#include "../function_minimize/EndpointDistance.hpp"
#include "../trajectory/creator/BallisticConstMassKCreator.hpp"
#include "../trajectory/solver/RK4Solver.hpp"


void Core::start()
{
    double mass = 0.2;
    double radius = 0.1;
    double k = 0.5 * Constants::SPHERE_DRAG_COEFFICIENT * Constants::AIR_DENSITY * M_PI * radius * radius;

    BallisticConstMassKCreator creator(mass, k);
    RK4Solver<4> solver(creator({0,0}));
     

    EndpointDistance<double, 2, 4> function(solver, creator, {1,1});
    function({10,10});
}