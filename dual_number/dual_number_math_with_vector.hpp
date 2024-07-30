#ifndef _DUAL_NUMBER_MATH_WITH_VECTOR_H
#define _DUAL_NUMBER_MATH_WITH_VECTOR_H

#include "dual_number_with_vector.hpp"
#include <cmath>

namespace trainlib {
    // trigonometric functions
    DualNumber cos(const DualNumber& x) {
        double res_real = std::cos(x.getReal());
        auto res_dual = x.getDual();
        auto dim = x.getDim();

        for (size_t i = 0; i < dim; ++i) {
            res_dual[i] = -std::sin(x.getReal()) * res_dual[i];
        }

        return DualNumber(res_real, res_dual);
    }
    
    
    DualNumber sin(const DualNumber& x) {
        double res_real = std::sin(x.getReal());
        auto res_dual = x.getDual();
        auto dim = x.getDim();

        for (size_t i = 0; i < dim; ++i) {
            res_dual[i] = std::cos(x.getReal()) * res_dual[i];
        }

        return DualNumber(res_real, res_dual);
    }

    
    DualNumber tan(const DualNumber& x) {
        double res_real = std::tan(x.getReal());
        auto res_dual = x.getDual();
        auto dim = x.getDim();

        for (size_t i = 0; i < dim; ++i) {
            res_dual[i] = res_dual[i] / (std::cos(res_dual[i]) * std::cos(res_dual[i]));
        }

        return DualNumber(res_real, res_dual);
    }


    // hyperbolic functions
    DualNumber sinh(const DualNumber& x) {
        double res_real = std::sinh(x.getReal());
        auto res_dual = x.getDual();
        auto dim = x.getDim();

        for (size_t i = 0; i < dim; ++i) {
            res_dual[i] = res_dual[i] * std::cosh(x.getReal());
        }
        return DualNumber(res_real, res_dual);
    }

    
    DualNumber cosh(const DualNumber& x) {
        double res_real = std::cosh(x.getReal());
        auto res_dual = x.getDual();
        auto dim = x.getDim();

        for (size_t i = 0; i < dim; ++i) {
            res_dual[i] = res_dual[i] * std::sinh((x.getReal()));
        }
        return DualNumber(res_real, res_dual);
    }

    
    DualNumber tanh(const DualNumber& x) {
        double res_real = std::tanh(x.getReal());
        auto res_dual = x.getDual();
        auto dim = x.getDim();

        for (size_t i = 0; i < dim; ++i) {
            res_dual[i] = res_dual[i] / (std::cosh(x.getReal()) * std::cosh(x.getReal()));
        }
        return DualNumber(res_real, res_dual);
    }
    

    // exponential functions
    DualNumber exp(const DualNumber& x) {
        double res_real = std::exp(x.getReal());
        auto res_dual = x.getDual();
        auto dim = x.getDim();

        for (size_t i = 0; i < dim; ++i) {
            res_dual[i] = res_dual[i] * std::exp(x.getReal());
        }
        return DualNumber(res_real, res_dual);
    }

    
    DualNumber exp2(const DualNumber& x) {
        double res_real = std::exp2(x.getReal());
        auto res_dual = x.getDual();
        auto dim = x.getDim();

        for (size_t i = 0; i < dim; ++i) {
            res_dual[i] = res_dual[i] * std::exp(x.getReal()) * std::log(2);
        }
        return DualNumber(res_real, res_dual);
    }


    
    DualNumber log(const DualNumber& x) {
        double res_real = std::log(x.getReal());
        auto res_dual = x.getDual();
        auto dim = x.getDim();

        for (size_t i = 0; i < dim; ++i) {
            res_dual[i] = res_dual[i] / x.getReal();
        }
        return DualNumber(res_real, res_dual);
    }


    // polynomial
    DualNumber pow(const DualNumber& x, const double& y) {
        double res_real = std::pow(x.getReal(), y);
        auto res_dual = x.getDual();
        auto dim = x.getDim();

        for (size_t i = 0; i < dim; ++i) {
            res_dual[i] = res_dual[i] * y * std::pow(x.getReal(), y-1);
        }
        return DualNumber(res_real, res_dual);
    }
    
    
    DualNumber sqrt(const DualNumber& x) {
        double res_real = std::sqrt(x.getReal());
        auto res_dual = x.getDual();
        auto dim = x.getDim();

        for (size_t i = 0; i < dim; ++i) {
            res_dual[i] = res_dual[i] / (2 * std::sqrt(x.getReal()));
        }
        return DualNumber(res_real, res_dual);
    }

}

#endif