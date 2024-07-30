
#include "../dual_number_with_vector.hpp"
#include "../dual_number_math_with_vector.hpp"
#include "../auto_diff_with_vector.hpp"
#include "../numeric_diff.hpp"

#include <iostream>
#include <cmath>
#include <vector>

template<class T>
T func(const std::vector<T> &x) {
  using namespace std;
  using namespace trainlib;
  return 3 * x[0] * x[0] * x[0] * x[1] * x[2] + x[2] * sin(x[1]);
}

template<class T>
std::vector<T> multi_func(const std::vector<T> &x) {
  using namespace std;
  using namespace trainlib;

  std::vector<T> res(3);
  res[0] = x[0] * x[1];
  res[1] = sin(x[0] * x[1]);
  res[2] = exp(x[0]) * exp(x[1]);

  return res;
}

int main(void) {
  // auto f_dual = [](const std::vector<trainlib::DualNumber>& x) {
  //   using namespace trainlib;
  //   return 3 * x[0] * x[0] * x[0] * x[1] * x[2] + x[2] * sin(x[1]);
  // };

  // auto f_double = [](const std::vector<double> &x) {
  //   using namespace std;
  //   return 3 * x[0] * x[0] * x[0] * x[1] * x[2] + x[2] * sin(x[1]);˜
  // };

  auto grad = trainlib::gradient(func<trainlib::DualNumber>, {2, M_PI, 3});
  auto grad_num = trainlib::numeric_gradient(func<double>, {2, M_PI, 3});

  std::cout << grad[0] << " " << grad_num[0] << " " << 108 * M_PI << std::endl;
  std::cout << grad[1] << " " << grad_num[1] << " " << 69 << std::endl;
  std::cout << grad[2] << " " << grad_num[2] << " " << 24 * M_PI << std::endl;

  auto jacobi = trainlib::jacobian(multi_func<trainlib::DualNumber>, {2, 3});
  std::cout << "ok" << std::endl;
  auto jacobi_num = trainlib::numeric_jacobian(multi_func<double>, {2, 3});

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 2; ++j) {
      std::cout << jacobi[i][j] << " (dual)  =?= " << jacobi_num[i][j] << " (num) ";
    }
    std::cout << std::endl;
  }
  return 0;
}
