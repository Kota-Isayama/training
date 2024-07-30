#ifndef NEWTON_H_
#define NEWTON_H_

#include "dual_number_with_vector.hpp"
#include "auto_diff_with_vector.hpp"
#include <vector>
#include <cmath>
#include <type_traits>

namespace trainlib {
	template<class F>
	concept MultiDualFunc = requires(F func, const std::vector<DualNumber>& x) {
		{ func(x) } -> std::convertible_to<std::vector<DualNumber>>;
	};

	double calcNorm(const std::vector<double>& x) {
		double sum = 0;
		for (size_t i = 0; i < x.size(); ++i) {
			sum += x[i] * x[i];
		}

		return std::sqrt(sum);
	}

	void print_matrix(std::vector<std::vector<double>> a) {
		for (int i = 0; i < a.size(); ++i) {
			for (int j = 0; j < a[0].size(); ++j) {
				std::cout << a[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

	// support only regular matrix
	std::vector<double> gaussian_elimination(const std::vector<std::vector<double>>& A, const std::vector<double>& y) {
		// size check
		if (y.size() == 0) {
			throw std::logic_error("Invalid inputs. Size of y should be greater then 0");
		}
		if (A.size() != y.size()) {
			throw std::logic_error("Invalid inputs. Sizes of A and y should be same.");
		}
		for (size_t i = 0; i < A.size(); ++i) {
			if (A[i].size() != y.size()) {
				throw std::logic_error("Invalid inputs. Sizes of A and y should be same.");
			}
		}

		constexpr double eps = 1e-10;
		size_t n = A.size();
		std::vector<std::vector<double>> augmented_coefficient_matrix(n);
		for (size_t i = 0; i < n; ++i) {
			augmented_coefficient_matrix[i] = A[i];
			augmented_coefficient_matrix[i].push_back(y[i]);
		}

		// forward elimination
		for (size_t i = 0; i < n; ++i) {
			// select pivot
			for (size_t k = i; k < n; ++k) {
				if (std::abs(augmented_coefficient_matrix[k][i]) > eps) {
					std::swap(augmented_coefficient_matrix[i], augmented_coefficient_matrix[k]);
					// std::cout << "pivot is " << k << std::endl;
					// print_matrix(augmented_coefficient_matrix);
					break;
				}
				if (k == n-1) {
					throw std::logic_error("gaussian_elimination: A is not regular");
				}
			}
			
			// forward elimination
			for (size_t k = i + 1; k < n; ++k) {
				double val_at_ki = augmented_coefficient_matrix[k][i];
				for (size_t j = i; j < n + 1; ++j) {
					augmented_coefficient_matrix[k][j] -= (augmented_coefficient_matrix[i][j] / augmented_coefficient_matrix[i][i]) * val_at_ki;
				}
			}
			// std::cout << "after eliminated\n";
			// print_matrix(augmented_coefficient_matrix);
		}

		// backward assignment
		std::vector<double> answer(n);
		for (int i = n - 1; i >= 0; --i) {
			double temp_sum = augmented_coefficient_matrix[i][n];

			for (size_t j = i + 1; j < n; ++j) {
				temp_sum -= augmented_coefficient_matrix[i][j] * answer[j];
			}

			answer[i] = temp_sum / augmented_coefficient_matrix[i][i];
		}

		return answer;
	}

	
	// multiply a matrix to a vector
	std::vector<double> mat_mul(const std::vector<std::vector<double>>& A, const std::vector<double>& x) {
		// check size
		if (x.size() == 0) {
			throw std::logic_error("Invalid input: the size of x should be greater than 0. (mult_mat)");
		}
		if (A.size() == 0) {
			throw std::logic_error("Invalid input: the row size of A should be greater than 0. (mult_mat)");
		}
		for (size_t i = 0; i < A.size(); ++i) {
			if (A[i].size() != x.size()) {
				throw std::logic_error("Invalid input: the column size of A and size of x should be same. (mult_mat)");
			}
		}

		std::vector<double> y(A.size(), 0);
		for (size_t i = 0; i < A.size(); ++i) {
			for (size_t j = 0; j < A[i].size(); ++j) {
				y[i] += A[i][j] * x[j];
			}
		}

		return y;
	}

	std::vector<double> vec_sub(const std::vector<double>& x, const std::vector<double>& y) {
		if (x.size() != y.size()) {
			throw std::logic_error("Invalid inputs: x and y should be same size. (vec_sub)");
		}

		std::vector<double> z(x.size());
		for (size_t i = 0; i < x.size(); ++i) {
			z[i] = x[i] - y[i];
		}

		return z;
	}

	class NewtonMethod {
	public:
		NewtonMethod(double tol = 1e-8, size_t max_iter = 10000): tol(tol), max_iter(max_iter) {}

		template<class F>
		requires MultiDualFunc<F>
		std::vector<double> dual_eval(F func, const std::vector<double>& x) {
			std::vector<DualNumber> dualX;
			for (size_t i = 0; i < x.size(); ++i) {
				dualX.push_back(DualNumber(x[i]));
			}
			std::vector<DualNumber> dual_value = func(dualX);
			std::vector<double> value(dual_value.size());

			for (size_t i = 0; i < value.size(); ++i) {
				value[i] = dual_value[i].getReal();
			}

			return value;
		}

		template<class F>
		requires MultiDualFunc<F>
		std::vector<double> solve(F func, std::vector<double> init) {
			auto currentPoint = std::move(init);

			for (size_t k = 0; k < max_iter; ++k) {
				auto currentValue = dual_eval<F>(func, currentPoint);
				auto norm = calcNorm(currentValue);
				if (norm < tol) {
					return currentPoint;
				}

				auto jacobi = jacobian(func, currentPoint);
				try {
					auto nextPoint = gaussian_elimination(jacobi, vec_sub(mat_mul(jacobi, currentPoint), currentValue));
					swap(nextPoint, currentPoint);
				}
				catch (std::logic_error e) {
					throw std::logic_error("Invalid function: Jacobian is not regular. (trainlib::NewtonMethod)");
				}
			}

			throw std::logic_error("Don't converge. (trainlib::NewtonMethod)");
		}
	private:
		double tol;
		size_t max_iter;
	};
}// trainlib

#endif