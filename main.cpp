#include <iostream>
#include "math/Vector.hpp"
#include "trajectory_creator/BallisticTrajectory.hpp"

int main() {
    Vector  a, b;
    a[0] = 1; a[1] = 3; a[2] = 1.1;
    b[0] = 1; b[1] = 3; b[2] = 1.1;
    
    std::cout << a-b << a+b << a*b; 

    std::cout << a << b;

    std::cout << a.sqrnorm();

    BallisticTrajectory kl(a);

    std::cout << 'a';

    return 0;
}