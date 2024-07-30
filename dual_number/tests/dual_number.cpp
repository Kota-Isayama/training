#include "../dual_number_with_vector.hpp"
#include "../dual_number_math_with_vector.hpp"

#include <iostream>
#include <cmath>


int main(void) {
  auto x = trainlib::DualNumber(10, {1, 2});
  auto y = trainlib::DualNumber(3, {3, 1});

  auto x_plus_y = x + y;
  auto x_minus_y = x - y;
  auto x_mult_y = x * y;
  auto x_div_y = x / y;
  
  std::cout << x_plus_y.getReal() << std::endl;
  for (int i = 0; i < 2; ++i) {
    std::cout << x_plus_y.getDual()[i] << " ";
  }
  std::cout << std::endl;

  std::cout << x_minus_y.getReal() << std::endl;
  for (int i = 0; i < 2; ++i) {
    std::cout << x_minus_y.getDual()[i] << " ";
  }
  std::cout << std::endl;

  std::cout << x_mult_y.getReal() << std::endl;
  for (int i = 0; i < 2; ++i) {
    std::cout << x_mult_y.getDual()[i] << " ";
  }
  std::cout << std::endl;

  std::cout << x_div_y.getReal() << std::endl;
  for (int i = 0; i < 2; ++i) {
    std::cout << x_div_y.getDual()[i] << " ";
  }
  std::cout << std::endl;

  std::cout << "cmath" << std::endl;
  auto f = [](trainlib::DualNumber x, trainlib::DualNumber y) {
    return 3 * x * x + 5 * x * y - 2 * y * y * y;
  };

  auto z = f(trainlib::DualNumber(5, 0), trainlib::DualNumber(2, 1));
  std::cout << z.getReal() << " " << z.getDual()[0] << " " << z.getDual()[1] << std::endl;

  auto g = [](trainlib::DualNumber x, trainlib::DualNumber y) {
    using namespace trainlib;
    return x * x * x * cos(y);
  };

  auto u = g(trainlib::DualNumber(2, 0), trainlib::DualNumber(M_PI / 2, 1));
  std::cout << u.getReal() << " " << u.getDual()[0] << " " << u.getDual()[1] << std::endl;

  auto h = [](trainlib::DualNumber x, trainlib::DualNumber y) {
    using namespace trainlib;
    return exp(log(x));
  };

  auto w = h(trainlib::DualNumber(10, 0), trainlib::DualNumber(10, 1));
  std::cout << w.getReal() << " " << w.at(0) << " " << w.at(1) << std::endl;

  return 0;
}