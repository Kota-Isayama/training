#include "../newton.hpp"
#include "../dual_number_math_with_vector.hpp"
#include <vector>

std::vector<trainlib::DualNumber> test_func(const std::vector<trainlib::DualNumber>& x) {
	using namespace trainlib;

	std::vector<DualNumber> res(2);
	res[0] = 5 * x[0] * x[0] + x[0] * x[1] * x[1] + sin(2 * x[1]) * sin(2 * x[1]) - 2;
	res[1] = exp(2 * x[0] - x[1]) + 4 * x[1] - 3;

	return res;
}

std::vector<trainlib::DualNumber> test_func2(const std::vector<trainlib::DualNumber>& x) {
	return {x[0] * x[0] - 2};
}

int main(void) {
	auto x1 = trainlib::gaussian_elimination(
		{
			{1, 1},
			{2, 5}
		},
		{2, 7}
	);
	std::cout << x1[0] << " " << x1[0] << std::endl;

	auto x2 = trainlib::gaussian_elimination(
		{
			{1, 2, 0},
			{3, -1, 1},
			{2, 1, 1}
		},
		{3, 0, 1}
	);
	std::cout << x2[0] << " " << x2[1] << " " << x2[2] << std::endl;

	try {
		trainlib::gaussian_elimination(
			{
				{1, 1, -3},
				{1, -1, 5},
				{2, 2, -6}
			},
			{2, 10, 5}
		);
	}
	catch (std::logic_error e) {
		std::cout << "no solution!" << std::endl;
	}

	double tol = 1.0 / (1.1 * 1.1 * 1.1);
	auto newton = trainlib::NewtonMethod();

	auto solution = newton.solve(test_func, {1.0, 1.0});

	std::cout << solution[0] << " " << solution[1] << std::endl;

	auto solution2 = newton.solve(test_func2, {2});
	std::cout << solution2[0] << std::endl;
	
	return 0;
}