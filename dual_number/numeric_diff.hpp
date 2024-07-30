#ifndef NUMERIC_DIFF_HPP_
#define NUMERIC_DIFF_HPP_

#include <iostream>
#include <vector>
#include <tuple>
#include <utility>
#include <type_traits>
#include <concepts>


namespace trainlib {
  template<class F>
  concept DoubleFunction = requires(F func, const std::vector<double>& x) {
    { func(x) } -> std::convertible_to<double>;
  };

  template<class F>
  concept MultiDoubleFunction = requires(F func, const std::vector<double>& x) {
    { func(x) } -> std::convertible_to<std::vector<double>>;
  };

  template<class F>
  requires DoubleFunction<F>
  std::vector<double> numeric_gradient(F func, const std::vector<double>& x) {
    double h = 1e-6;
    std::vector<double> g;
    std::vector<double> y = x;
    std::vector<double> z = x;

    for (int i = 0; i < x.size(); ++i) {
      y[i] += h;
      z[i] -= h;

      g.push_back((func(y) - func(z)) / (2 * h));

      y[i] -= h;
      z[i] += h;
    }

    return g;
  }

  template<class F>
  requires MultiDoubleFunction<F>
  std::vector<std::vector<double>> numeric_jacobian(F func, const std::vector<double>& x) {
    std::vector<std::vector<double>> jacobi(x.size());
    double h = 1e-6;
    std::vector<double> y = x;
    std::vector<double> z = x;

    for (int i = 0; i < x.size(); ++i) {
      y[i] += h;
      z[i] -= h;

      auto f_y = func(y);
      auto f_z = func(z);

      for (int j = 0; j < f_y.size(); ++j) {
        jacobi[i].push_back((f_y[j] - f_z[j]) / (2 * h));
      }

      y[i] -= h;
      z[i] += h;
    }

    std::vector<std::vector<double>> res(jacobi[0].size());
    for (int i = 0; i < jacobi[0].size(); ++i) {
      for (int j = 0; j < x.size(); ++j) {
        res[i].push_back(jacobi[j][i]);
      }
    }

    return res;
  }
  
}

#endif