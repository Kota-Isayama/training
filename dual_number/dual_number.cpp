#include "dual_number.hpp"

namespace trainlib {
    DualNumber1d::DualNumber1d(double first, double second=0): first(first), second(second) {}
    DualNumber1d::DualNumber1d(const DualNumber1d& other): first(other.first), second(other.second) {}
    DualNumber1d::DualNumber1d(const DualNumber1d&& other): first(other.first), second(other.second) {}
    DualNumber1d::DualNumber1d(): DualNumber1d(0, 0) {}

    DualNumber1d DualNumber1d::operator+() const {
        return *this;
    }

    DualNumber1d DualNumber1d::operator-() const {
        DualNumber1d answer = DualNumber1d(*this);
        answer.first *= -1;
        answer.second *= -1;

        return answer;
    }

    DualNumber1d& DualNumber1d::operator=(const DualNumber1d& other) {
        this->first = other.first;
        this->second = other.second;

        return *this;
    }

    DualNumber1d& DualNumber1d::operator=(const DualNumber1d&& other) {
        *this = other;

        return *this;
    }

    DualNumber1d& DualNumber1d::operator+=(const DualNumber1d& other) {
        this->first += other.first;
        this->second += other.second;

        return *this;
    }

    DualNumber1d& DualNumber1d::operator-=(const DualNumber1d& other) {
        this->first -= other.first;
        this->second -= other.second;

        return *this;
    }

    DualNumber1d& DualNumber1d::operator*=(const DualNumber1d& other) {
        *this = DualNumber1d(this->first * other.first, this->second * other.first + this->first * other.second);
        return *this;
    }

    DualNumber1d& DualNumber1d::operator/=(const DualNumber1d& other) {
        *this = DualNumber1d(this->first * other.first / (other.first * other.first), (this->second * other.first - this->first * other.second) / (other.first * other.first));
        *this;
    }
    
    bool operator==(const DualNumber1d& left, const DualNumber1d& right) {
        return (left.first == right.first) && (left.second == right.second);
    }

    bool  operator!=(const DualNumber1d& left, const DualNumber1d& right) {
        return !(left == right);
    }

    DualNumber1d operator+(const DualNumber1d& left, const DualNumber1d& right) {
        return DualNumber1d(left.first + right.first, left.second + right.second);
    }

    DualNumber1d operator-(const DualNumber1d& left, const DualNumber1d& right) {
        return DualNumber1d(left.first - right.first, left.second - right.second);
    }

    DualNumber1d operator*(const DualNumber1d& left, const DualNumber1d& right) {
        return DualNumber1d(left.first * right.first, left.second * right.first + left.first * right.second);
    }

    DualNumber1d operator/(const DualNumber1d& left, const DualNumber1d& right) {
        return DualNumber1d(left.first / right.first, (left.second * right.first - left.first * right.second) / (right.first * right.first));
    }

    // not necessary?
	DualNumber1d operator+(const DualNumber1d &left, const double &right) {
        return DualNumber1d(left.first + right, left.second);
    }

	DualNumber1d operator+(const double &left, const DualNumber1d &right) {
        return right + left;
    }

	DualNumber1d operator-(const DualNumber1d &left, const double &right) {
        return left + (-right);
    }

	DualNumber1d operator-(const double &left, const DualNumber1d &right) {
        return -right + left;
    }

	DualNumber1d operator*(const DualNumber1d &left, const double &right) {
        return DualNumber1d(left.first * right, left.second * right);
    }

	DualNumber1d operator*(const double &left, const DualNumber1d &right) {
        return right * left;
    }

	DualNumber1d operator/(const DualNumber1d &left, const double &right) {
        return left * (1 / right);
    }

	DualNumber1d operator/(const double &left, const DualNumber1d &right) {
        return DualNumber1d(left / right.first, -left * right.second / (right.first * right.first));
    }


}