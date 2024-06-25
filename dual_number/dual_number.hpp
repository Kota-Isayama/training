#ifndef _DUAL_NUMBER_H
#define _DUAL_NUMBER_H

#include <iostream>
#include <memory>

namespace trainlib {
	class DualNumber1d {
	public:
		// constructors
		// default constructor
		DualNumber1d();
		// constructor
		DualNumber1d(double first, double second=0);	// should be explicit?
		// copy constructor
		DualNumber1d(const DualNumber1d&);
		// move constructor
		DualNumber1d(const DualNumber1d&&);


		// operator overload
		DualNumber1d operator+() const;
		DualNumber1d operator-() const;

		DualNumber1d& operator=(const DualNumber1d&);	// copy
		DualNumber1d& operator=(const DualNumber1d&&);	// move

		DualNumber1d& operator+=(const DualNumber1d&);
		DualNumber1d& operator-=(const DualNumber1d&);
		DualNumber1d& operator*=(const DualNumber1d&);
		DualNumber1d& operator/=(const DualNumber1d&);
		
		double first;
		double second;
	};

	bool operator==(const DualNumber1d&, const DualNumber1d&);
	bool operator!=(const DualNumber1d&, const DualNumber1d&);

	DualNumber1d operator+(const DualNumber1d&, const DualNumber1d&);
	DualNumber1d operator-(const DualNumber1d&, const DualNumber1d&);
	DualNumber1d operator*(const DualNumber1d&, const DualNumber1d&);
	DualNumber1d operator/(const DualNumber1d&, const DualNumber1d&);

	// not necessary?
	DualNumber1d operator+(const DualNumber1d&, const double&);
	DualNumber1d operator+(const double&, const DualNumber1d&);
	DualNumber1d operator-(const DualNumber1d&, const double&);
	DualNumber1d operator-(const double&, const DualNumber1d&);
	DualNumber1d operator*(const DualNumber1d&, const double&);
	DualNumber1d operator*(const double&, const DualNumber1d&);
	DualNumber1d operator/(const DualNumber1d&, const double&);
	DualNumber1d operator/(const double&, const DualNumber1d&);


	class DualNumber {
	public:
		DualNumber();
		DualNumber(std::size_t);

		std::size_t dim;
		std::unique_ptr<double> firsts;
		std::unique_ptr<double> seconds;
	}
}

#endif