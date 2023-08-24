#include <iostream>
#include <cmath>
#include <fstream>
#include "math/Vector.hpp"
#include "math/Constants.hpp"
#include "trajectory/builder/BallisticTrajectory.hpp"
#include "trajectory/solver/RK4Solver.hpp"

int main() {    
    double angle = 30.0 / 180 * M_PI; // in radians
    Vector2d startVelocity = {50 * cos(angle), 50 * sin(angle)};
    
    double mass = 0.2;
    double radius = 0.1;
    double k = 0.5 * Constants::SPHERE_DRAG_COEFFICIENT * Constants::AIR_DENSITY * M_PI * radius * radius;
    
    BallisticTrajectory traj(startVelocity, mass, k);
    RK4Solver<4> solver(traj);
    
    std::ofstream out("out.txt");

    double step = 0.01;

    for (int i = 1; i < 1800; i ++) {
        auto state = solver.solve(i * 0.01);
        if (state[2] < 0) {
            std::cout << "Reached zero at " << i * step << " s" << '\n';
            break;
        }
        out << solver.solve(i * step) << '\n';
    }

    return 0;
}