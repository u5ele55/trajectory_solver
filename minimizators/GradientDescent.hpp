#pragma once

#include <random>
#include <vector>

#include "IMinimizer.hpp"
#include "../function/IFunction.hpp"
#include "../utilities/RandomVector.hpp"

template <int dim>
class GradientDescent : public IMinimizer<double, double, dim> {
public:
    GradientDescent(
        IFunction<double, double, dim> &function, 
        Vector<Vector2d, dim> boundaries, 
        int starts = 10, 
        double gamma = 0.01,
        int iterations = 50, 
        double dx = 1e-3);
    std::pair<double, Vector<double, dim>> minimize();
protected:
    std::pair<double, Vector<double, dim>> descent(const Vector<double, dim> &startPoint);
    Vector<double, dim> gradient(const Vector<double, dim> &point);
protected:
    IFunction<double, double, dim> &function;
    RandomVector<dim> generator;
    int starts;
    double gamma;
    int iterations;
    double dx;
};

template <int dim>
inline GradientDescent<dim>::GradientDescent(
    IFunction<double, double, dim> &function, 
    Vector<Vector2d, dim> boundaries, 
    int starts, 
    double gamma,
    int iterations,
    double dx
)   : function(function), 
    generator(boundaries),
    starts(starts), 
    gamma(gamma),
    iterations(iterations),
    dx(dx) {}

template <int dim>
inline std::pair<double, Vector<double, dim>> GradientDescent<dim>::minimize()
{
    double min = 1e100;
    Vector<double, dim> minPoint;

    for (int i = 0; i < starts; i ++) {
        auto startPoint = generator.generate();
        std::cout << "Starting at " << startPoint << '\n';
        auto result = descent(startPoint);
        std::cout << "Descent into " << result.second << '\n';

        if (result.first < min) {
            min = result.first;
            minPoint = result.second;
        }
    }
    return {min, minPoint};
}

template <int dim>
inline std::pair<double, Vector<double, dim>> GradientDescent<dim>::descent(const Vector<double, dim> &startPoint)
{
    Vector<double, dim> dF_xn, dF_xn_1, gradDifference; // dF_xn - gradient at n'th step,  dF_xn_1 - at n-1'th step
    Vector<double, dim> x_n = startPoint, x_n_1;
    // start values
    double gamma_n = gamma;
    dF_xn = gradient(x_n);

    for(int n = 0; n < iterations; n++) {
        x_n_1 = x_n;
        dF_xn_1 = dF_xn;
        
        x_n = x_n_1 - dF_xn_1 * gamma_n;
        dF_xn = gradient(x_n);
        gradDifference = dF_xn - dF_xn_1;
        // TODO: if gradDifference == 0 use different gamma
        // gamma_n = fabs((x_n - x_n_1).dot(gradDifference)) / gradDifference.sqrnorm();
        // std::cout << "After " << n << " iteration: gamma=" << gamma_n << " xn=" << x_n << " xn_1=" << x_n_1 << " dFxn=" << dF_xn << '\n';
    }
    

    return {function(x_n), x_n};
}

template <int dim>
inline Vector<double, dim> GradientDescent<dim>::gradient(const Vector<double, dim> &point)
{
    Vector<double, dim> grad, delta, shifted;

    auto value = function(point);
    //std::cout << "Grad at " << point << " w/value " << value << '\n'; 

    for (int i = 0; i < dim; i ++) {
        delta[i] = dx;
        shifted = point + delta;
        //std::cout << "got: " << shifted << ' ' << function(shifted) << '\n';

        grad[i] = ( function(shifted) - value ) / dx;
        
        delta[i] = 0;
    }
    //std::cout << "res grad: " << grad << '\n';

    return grad;
}
