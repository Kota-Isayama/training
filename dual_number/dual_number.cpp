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

    DualNumber1d& DualNumber1d::operator=(DualNumber1d&& other) {
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


    DualNumber::DualNumber(std::size_t dim): dim(dim), ptr(std::make_unique<DualNumber1d[]>(dim)) {}
    DualNumber::DualNumber(const DualNumber& other): dim(dim) {
        ptr = std::make_unique<DualNumber1d[]>(dim);
        for (std::size_t i = 0; i < dim; ++i) {
            ptr[i] = other[i];
        }
    }
    DualNumber::DualNumber(DualNumber&& other): dim(dim), ptr(std::move(other.ptr)) {}
    
    DualNumber DualNumber::operator+() const {
        return *this;
    }

    DualNumber DualNumber::operator-() const {
        DualNumber answer{this->dim};
        for (std::size_t i = 0; i < this->dim; ++i) {
            answer[i] = -(*this)[i];
        }
        return answer;
    }

    DualNumber& DualNumber::operator=(const DualNumber& other) {
        if (this->dim != other.dim) {
            this->ptr = std::make_unique<DualNumber1d[]>(other.dim);
        }

        this->dim = other.dim;
        for (std::size_t i = 0; i < other.dim; ++i) {
            (*this)[i] = other[i];
        }

        return *this;
    }

    DualNumber& DualNumber::operator=(DualNumber&& other) {
        this->dim = other.dim;
        this->ptr = std::move(other.ptr);

        return *this;
    }

    DualNumber& DualNumber::operator+=(const DualNumber& other) {
        if (this->dim != other.dim) {
            throw std::runtime_error("Invalid input: two DualNumber shoud be same dimension.");
        }

        for (std::size_t i = 0; i < this->dim; ++i) {
            (*this)[i] += other[i];
        }

        return *this;
    }

    DualNumber& DualNumber::operator-=(const DualNumber& other) {
        if (this->dim != other.dim) {
            throw std::runtime_error("Invalid input: two DualNumber shoud be same dimension.");
        }

        for (std::size_t i = 0; i < this->dim; ++i) {
            (*this)[i] -= other[i];
        }

        return *this;
    }

    DualNumber& DualNumber::operator*=(const double& other) {
        for (std::size_t i = 0; i < this->dim; ++i) {
            (*this)[i] *= other;
        }

        return *this;
    }

    DualNumber& DualNumber::operator/=(const double& other) {
        for (std::size_t i = 0; i < this->dim; ++i) {
            (*this)[i] /= other;
        }

        return *this;
    }

    bool operator==(const DualNumber& lhs, const DualNumber& rhs) {
        if (lhs.dim != rhs.dim) {
            return false;
        }

        for (std::size_t i = 0; i < lhs.dim; ++i) {
            if (lhs[i] != rhs[i]) {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const DualNumber& lhs, const DualNumber& rhs) {
        return !(lhs == rhs);
    }
	
    DualNumber operator+(const DualNumber& lhs, const DualNumber& rhs) {
        if (lhs.dim != rhs.dim) {
            throw std::runtime_error("Invalid input: two DualNumber shoud be same dimension.");
        }

        auto answer = DualNumber{lhs.dim};

        for (std::size_t i = 0; i < lhs.dim; ++i) {
            answer[i] = lhs[i] + rhs[i];
        }

        return answer;
    }

	DualNumber operator+(const DualNumber& lhs, DualNumber&& rhs) {
        if (lhs.dim != rhs.dim) {
            throw std::runtime_error("Invalid input: two DualNumber shoud be same dimension.");
        }

        auto answer = std::move(rhs);

        for (std::size_t i = 0; i < lhs.dim; ++i) {
            answer[i] = lhs[i] + rhs[i];
        }

        return answer;
    }

	DualNumber operator+(DualNumber&& lhs, const DualNumber& rhs) {
        return rhs + lhs;
    }

	DualNumber operator+(DualNumber&& lhs, DualNumber&& rhs) {
        return std::move(lhs) + rhs;
    }

	DualNumber operator-(const DualNumber& lhs, const DualNumber& rhs) {
        if (lhs.dim != rhs.dim) {
            throw std::runtime_error("Invalid input: two DualNumber shoud be same dimension.");
        }

        auto answer = DualNumber{lhs.dim};

        for (std::size_t i = 0; i < lhs.dim; ++i) {
            answer[i] = lhs[i] - rhs[i];
        }

        return answer;
    }

	DualNumber operator-(const DualNumber& lhs, DualNumber&& rhs) {
        if (lhs.dim != rhs.dim) {
            throw std::runtime_error("Invalid input: two DualNumber shoud be same dimension.");
        }

        auto answer = std::move(rhs);

        for (std::size_t i = 0; i < lhs.dim; ++i) {
            answer[i] = lhs[i] - rhs[i];
        }

        return answer;
    }

	DualNumber operator-(DualNumber&& lhs, const DualNumber& rhs) {
        return rhs - lhs;
    }

	DualNumber operator-(DualNumber&& lhs, DualNumber&& rhs) {
        return std::move(lhs) - rhs;
    }

	DualNumber operator*(const double& lhs, const DualNumber& rhs) {
        auto answer = rhs;
        for (std::size_t i = 0; i < rhs.dim; ++i) {
            answer[i] = lhs * rhs[i];
        }

        return answer;
    }

	DualNumber operator*(const DualNumber& lhs, const double& rhs) {
        return rhs * lhs;
    }

	DualNumber operator*(const double& lhs, DualNumber&& rhs) {
        auto answer = std::move(rhs);
        for (std::size_t i = 0; i < rhs.dim; ++i) {
            answer[i] = lhs * rhs[i];
        }

        return answer;
    }

	DualNumber operator*(DualNumber&& lhs, const double& rhs) {
        return rhs * std::move(lhs);
    }

	DualNumber operator/(const double& lhs, const DualNumber& rhs) {
        return (1 / lhs) * rhs;
    }

	DualNumber operator/(const DualNumber& lhs, const double& rhs) {
        return lhs * (1 / rhs);
    }

	DualNumber operator/(const double& lhs, DualNumber&& rhs) {
        return (1 / lhs) * std::move(rhs);
    }

	DualNumber operator/(DualNumber&& lhs, const double& rhs) {
        return std::move(lhs) * (1 / rhs);
    }
}