#ifndef _DUAL_NUMBER_MATH_H
#define _DUAL_NUMBER_MATH_H

#include "dual_number.hpp"
#include <cmath>

namespace trainlib {
    // trigonometric functions
    DualNumber1d dual_cos(const DualNumber1d& x) {
        return DualNumber1d(std::cos(x.first), - std::sin(x.first) * x.second);
    }
    
    DualNumber1d dual_cos(DualNumber1d&& x);

    DualNumber1d dual_sin(const DualNumber1d& x) {
        return DualNumber1d(std::sin(x.first), std::cos(x.first) * x.second);
    }

    DualNumber1d dual_sin(DualNumber1d&& x);

    DualNumber1d dual_tan(const DualNumber1d& x) {
        double numerator = std::cos(x.first) * std::cos(x.first);
        double first_denominator = std::sin(x.first) * std::sin(x.first);
        double second_denominator = 2 * std::sin(x.first) * std::cos(x.first) * x.second;
        return DualNumber1d(first_denominator / numerator, second_denominator / numerator);
    }

    DualNumber1d dual_tan(DualNumber1d&& x);

    DualNumber1d dual_asin(const DualNumber1d& x);
    DualNumber1d dual_asin(DualNumber1d&& x);
    DualNumber1d dual_acos(const DualNumber1d& x);
    DualNumber1d dual_acos(DualNumber1d&& x);
    DualNumber1d dual_atan(const DualNumber1d& x);
    DualNumber1d dual_atan(DualNumber1d&& x);

    // hyperbolic functions
    DualNumber1d dual_sinh(const DualNumber1d& x) {
        return DualNumber1d(std::sinh(x.first), x.second * std::cosh(x.first));
    }
    DualNumber1d dual_sinh(DualNumber1d&& x);

    DualNumber1d dual_cosh(const DualNumber1d& x) {
        return DualNumber1d(std::cosh(x.first), x.second * std::sinh(x.first));
    }
    DualNumber1d dual_cosh(DualNumber1d&& x);

    DualNumber1d dual_tanh(const DualNumber1d& x) {
        return DualNumber1d(std::sinh(2 * x.first) / (2 * std::cosh(x.first) * std::cosh(x.first)), x.second / (std::cosh(x.first) * std::cosh(x.first)));
    }
    DualNumber1d dual_tanh(DualNumber1d&& x);

    // exponential functions
    DualNumber1d dual_exp(const DualNumber1d& x) {
        return DualNumber1d(std::exp(x.first), std::exp(x.first) * x.second);
    }

    DualNumber1d dual_exp(DualNumber&& x);

    DualNumber1d dual_exp2(const DualNumber1d& x) {
        return DualNumber1d(std::exp2(x.first), std::exp2(x.first) * std::log(2) * x.second);
    }

    DualNumber1d dual_exp2(DualNumber1d&& x);

    DualNumber1d dual_log(const DualNumber1d& x) {
        return DualNumber1d(x.first, x.second / x.first);
    }

    DualNumber1d dual_log(DualNumber1d&& x);

    DualNumber1d dual_log10(const DualNumber1d&);
    DualNumber1d dual_log10(DualNumber1d&&);
    DualNumber1d dual_log2(const DualNumber1d&);
    DualNumber1d dual_log2(DualNumber1d&&);


    // polynomial
    DualNumber1d dual_pow(const DualNumber1d& x, const double& y) {
        return DualNumber1d(std::pow(x.first, y), y * std::pow(x.first, y-1) * x.second);
    }
    DualNumber1d dual_pow(DualNumber1d&& x, const double& y);

    DualNumber1d dual_sqrt(const DualNumber1d& x) {
        return DualNumber1d(std::sqrt(x.first), x.second / (2 * std::sqrt(x.first)));
    }
    DualNumber1d dual_sqrt(DualNumber1d&& x);


}

#endif