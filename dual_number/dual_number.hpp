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
		DualNumber1d& operator=(DualNumber1d&&);	// move

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
		DualNumber() = delete;
		DualNumber(std::size_t);

		DualNumber(const DualNumber&);
		DualNumber(DualNumber&&);

		DualNumber1d& operator[](const std::size_t& i) {
			return ptr[i];
		}
		const DualNumber1d& operator[](const std::size_t& i) const {
			return ptr[i];
		}

		DualNumber operator+() const;
		DualNumber operator-() const;

		DualNumber& operator=(const DualNumber&);
		DualNumber& operator=(DualNumber&&);
		
		DualNumber& operator+=(const DualNumber&);
		DualNumber& operator-=(const DualNumber&);
		DualNumber& operator*=(const double&);
		DualNumber& operator/=(const double&);

		std::size_t dim;
		std::unique_ptr<DualNumber1d[]> ptr;
	};

	bool operator==(const DualNumber&, const DualNumber&);

	bool operator!=(const DualNumber&, const DualNumber&);

	DualNumber operator+(const DualNumber&, const DualNumber&);
	DualNumber operator+(const DualNumber&, DualNumber&&);
	DualNumber operator+(DualNumber&&, const DualNumber&);
	DualNumber operator+(DualNumber&&, DualNumber&&);
	DualNumber operator-(const DualNumber&, const DualNumber&);
	DualNumber operator-(const DualNumber&, DualNumber&&);
	DualNumber operator-(DualNumber&&, const DualNumber&);
	DualNumber operator-(DualNumber&&, DualNumber&&);
	DualNumber operator*(const double&, const DualNumber&);
	DualNumber operator*(const DualNumber&, const double&);
	DualNumber operator*(const double&, DualNumber&&);
	DualNumber operator*(DualNumber&&, const double&);
	DualNumber operator/(const double&, const DualNumber&);
	DualNumber operator/(const DualNumber&, const double&);
	DualNumber operator/(const double&, DualNumber&&);
	DualNumber operator/(DualNumber&&, const double&);
}

#endif