#ifndef DUAL_NUMBER_WITH_VECTOR_H_
#define DUAL_NUMBER_WITH_VECTOR_H_

#include <vector>
#include <algorithm>

namespace trainlib {
  class DualNumber {
  public:
		DualNumber(): DualNumber(0) {}
  	DualNumber(double real): real(real), dual(1) {}
    DualNumber(double real, size_t variableIndex): DualNumber(real, variableIndex, variableIndex+1) {}
  	DualNumber(double real, size_t variableIndex, size_t dim): real(real), dual(dim) {
  		dual[variableIndex] = 1.0;
  	}
  	DualNumber(double real, std::vector<double> dual): real(real), dual(dual) {}

  	DualNumber(const DualNumber& other): real(other.real), dual(other.dual){}	// copy constructor
  	DualNumber& operator=(const DualNumber& other) = default;

  	DualNumber(DualNumber&& other): real(other.real), dual(std::move(other.dual)){}	// move constructor
  	DualNumber& operator=(DualNumber&& other) = default;

  	// operator overload
  	DualNumber& operator+=(const DualNumber& other) {
      auto newDim = std::max(this->getDim(), other.getDim());
      if (newDim > this->getDim()) {
        dual.resize(newDim, 0);
      }

  		this->real += other.real;
  		for (size_t i = 0; i < newDim; ++i) {
  			this->dual[i] += other.at(i);
  		}

  		return *this;
  	}

  	DualNumber& operator+=(const double other) {
  		this->real += other;
  		return *this;
  	}

  	DualNumber& operator-=(const DualNumber& other) {
      auto newDim = std::max(this->getDim(), other.getDim());
      if (newDim > this->getDim()) {
        dual.resize(newDim, 0);
      }
    
  		this->real -= other.real;
  		for (size_t i = 0; i < newDim; ++i) {
  			this->dual[i] -= other.at(i);
  		}

  		return *this;
  	}

  	DualNumber& operator-=(const double other) {
  		this->real -= other;
  		return *this;
  	}

  	DualNumber& operator*=(const DualNumber& other) {
      auto newDim = std::max(this->getDim(), other.getDim());
      if (newDim > this->getDim()) {
        dual.resize(newDim, 0);
      }

  		for (size_t i = 0; i < newDim; ++i) {
  			this->dual[i] = this->real * other.at(i) + other.real * this->dual[i];
  		}
  		this->real *= other.real;

  		return *this;
  	}

  	DualNumber& operator*=(const double other) {
      auto dim = dual.size();

  		this->real *= other;
  		for (size_t i = 0; i < dim; ++i) {
  			this->dual[i] = other * this->dual[i];
  		}

  		return *this;
  	}

  	DualNumber& operator/=(const DualNumber& other) {
      auto newDim = std::max(this->getDim(), other.getDim());
      if (newDim > this->getDim()) {
        dual.resize(newDim, 0);
      }

  		for (size_t i = 0; i < newDim; ++i) {
  			this->dual[i] = (this->dual[i] * other.real - this->real * other.at(i)) / (other.real * other.real);
  		}
  		this->real /= other.real;

  		return *this;
  	}

  	DualNumber& operator/=(const double other) {
      auto dim = dual.size();

  		this->real /= other;
  		for (size_t i = 0; i < dim; ++i) {
  			this->dual[i] /= other;
  		}

  		return *this;
  	}

    size_t getDim() const {
      return dual.size();
    }

  	double getReal() const {
  		return real;
  	}

  	std::vector<double> getDual() const {
  		return dual;
  	}

    double at(size_t i) const {
      return (i < dual.size() ? dual[i] : 0);
    }

  private:
  	double real;
  	std::vector<double> dual;
  };

  bool operator==(const DualNumber& lhs, const DualNumber& rhs) {
  	if (lhs.getReal() != rhs.getReal()) {
  		return false;
  	}
  	else {
      for (size_t i = 0; i < std::max(lhs.getDim(), rhs.getDim()); ++i) {
        if (lhs.at(i) != rhs.at(i)) {
          return false;
        }
      }
    }
    return true;
  }

  bool operator!=(const DualNumber& lhs, const DualNumber& rhs) {
  	return !(lhs == rhs);
  }


  // overload additional operator
  DualNumber operator+(const DualNumber& lhs, const DualNumber& rhs) {
  	auto res = lhs;
    res += rhs;

  	return res;
  }

  
  DualNumber operator+(const DualNumber& lhs, DualNumber&& rhs) {
  	auto res = std::move(rhs);
  	res += lhs;

  	return res;
  }

  
  DualNumber operator+(DualNumber&& lhs, const DualNumber& rhs) {
  	return rhs + lhs;
  }

  
  DualNumber operator+(DualNumber&& lhs, DualNumber&& rhs) {
  	return lhs + std::move(rhs);
  }

  
  DualNumber operator+(const DualNumber& lhs, double rhs) {
  	auto res = lhs;
  	res += rhs;

  	return res;
  }

  
  DualNumber operator+(DualNumber&& lhs, double rhs) {
  	auto res = std::move(lhs);
  	res += rhs;

  	return res;
  }

  
  DualNumber operator+(double lhs, const DualNumber& rhs) {
  	return rhs + lhs;
  }

  
  DualNumber operator+(double lhs, DualNumber&& rhs) {
  	return std::move(rhs) + lhs;
  }


  // overload subtraction operator
  
  DualNumber operator-(const DualNumber& lhs, const DualNumber& rhs) {
  	auto res = lhs;
  	res -= rhs;
  	return res;
  }

  
  DualNumber operator-(const DualNumber& lhs, DualNumber&& rhs) {
  	auto res = std::move(rhs);
  	res *= -1.0;
  	res += lhs;

  	return res;
  }

  
  DualNumber operator-(DualNumber&& lhs, const DualNumber& rhs) {
  	auto res = std::move(lhs);
  	res -= rhs;

  	return res;
  }

  
  DualNumber operator-(DualNumber&& lhs, DualNumber&& rhs) {
  	return std::move(lhs) - rhs;
  }

  
  DualNumber operator-(const DualNumber& lhs, double rhs) {
  	auto res = lhs;
  	res -= rhs;

  	return res;
  }

  
  DualNumber operator-(DualNumber&& lhs, double rhs) {
  	auto res = std::move(lhs);
  	res -= rhs;

  	return res;
  }

  
  DualNumber operator-(double lhs, const DualNumber& rhs) {
  	auto res = rhs;
  	res *= -1;
  	res += lhs;

  	return res;
  }

  
  DualNumber operator-(double lhs, DualNumber&& rhs) {
  	auto res = rhs;
  	res *= -1;
  	res += lhs;

  	return res;
  }


  // overload multiply operator
  
  DualNumber operator*(const DualNumber& lhs, const DualNumber& rhs) {
  	auto res = lhs;
  	res *= rhs;
  	return res;
  }

  
  DualNumber operator*(const DualNumber& lhs, DualNumber&& rhs) {
  	auto res = std::move(rhs);
  	res *= lhs;
  	return res;
  }

  
  DualNumber operator*(DualNumber&& lhs, const DualNumber& rhs) {
  	return rhs * lhs;
  }

  
  DualNumber operator*(DualNumber&& lhs, DualNumber&& rhs) {
  	return std::move(lhs) * rhs;
  }

  
  DualNumber operator*(const DualNumber& lhs, double rhs) {
  	auto res = lhs;
  	res *= rhs;

  	return res;
  }

  
  DualNumber operator*(DualNumber&& lhs, double rhs) {
  	auto res = std::move(lhs);
  	res *= rhs;

  	return res;
  }

  
  DualNumber operator*(double lhs, const DualNumber& rhs) {
  	return rhs * lhs;
  }

  
  DualNumber operator*(double lhs, DualNumber&& rhs) {
  	return std::move(rhs) * lhs;
  }


  // overload division operator
  DualNumber operator/(const DualNumber& lhs, const DualNumber& rhs) {
  	auto res = lhs;
  	res /= rhs;

  	return res;
  }


  
  DualNumber operator/(DualNumber&& lhs, const DualNumber& rhs) {
  	auto res = std::move(lhs);
  	res /= rhs;
  
  	return res;
  }

  
  DualNumber operator/(const DualNumber& lhs, double rhs) {
  	auto res = lhs;
  	res /= rhs;

  	return res;
  }

  
  DualNumber operator/(DualNumber&& lhs, double rhs) {
  	auto res = std::move(lhs);
  	res /= rhs;

  	return res;
  }

  
  DualNumber operator/(double lhs, const DualNumber& rhs) {
  	auto res = DualNumber(lhs);
  	res /= rhs;

  	return res;
  }

}

#endif