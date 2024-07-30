#ifndef AUTO_DIFF_WITH_VECTOR_H_
#define AUTO_DIFF_WITH_VECTOR_H_

#include <iostream>
#include <vector>
#include <tuple>
#include <utility>
#include <type_traits>
#include <concepts>

#include "dual_number_math_with_vector.hpp"

namespace trainlib {
  template<class F>
  concept DualFunction = requires(F func, const std::vector<DualNumber>& x) {
    { func(x) } -> std::convertible_to<DualNumber>;
  };

  template<class F>
  concept MultiDualFunction = requires(F func, const std::vector<DualNumber>& x) {
    { func(x) } -> std::convertible_to<std::vector<DualNumber>>;
  };

  template<class F>
  requires DualFunction<F>
  std::vector<double> gradient(F func, const std::vector<double>& x) {
    auto dim = x.size();
    std::vector<DualNumber> dualX;;
    for (size_t i = 0; i < dim; ++i) {
      dualX.push_back(DualNumber(x[i], i));
    }

    DualNumber y = func(dualX);

    return y.getDual();
  }

  template<class F>
  requires DualFunction<F>
  double derivative(F func, size_t index, const std::vector<double>& x) {
    auto grad = gradient(func, x);

    return grad[index];
  }

  template<class F>
  requires MultiDualFunction<F>
  std::vector<std::vector<double>> jacobian(F func, const std::vector<double>& x) {
    auto dim = x.size();
    std::vector<DualNumber> dualX;;
    for (size_t i = 0; i < dim; ++i) {
      dualX.push_back(DualNumber(x[i], i));
    }

    std::vector<DualNumber> y = func(dualX);
    std::vector<std::vector<double>> jacobi;
    for (int i = 0; i < y.size(); ++i) {
      jacobi.push_back(y[i].getDual());
    }

    return jacobi;
  }
}

#endif