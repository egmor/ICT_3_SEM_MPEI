#include <iostream>
#include <limits>
#include <stdexcept>
#include <cmath>
#include <iomanip>

class Double {
private:
	double value;

	void checkOverflow(double val) {
		if (val > std::numeric_limits<double>::max() || val < -std::numeric_limits<double>::max()) {
			throw std::overflow_error("\nOverflow error: value is too large or too small.");
		}
	}

public:
	// Конструктор (0 если неверные данные (буквы и т.п.)
	Double(double val = 0.0) : value(val) {
		setValue(val);
	}

	void setValue(double val) {
		checkOverflow(val);
		value = val;
	}

	double getValue() const {
		return value;
	}

	Double& operator++() {//++a
		checkOverflow(value + 1.0);
		value += 1.0;
		return *this;
	}

	Double operator++(int) {//a++
		Double temp = *this;
		checkOverflow(value + 1.0);
		value += 1.0;
		return temp;
	}

	friend Double operator*(const Double& f1, const Double& f2);

	void print() const {
		std::cout << value << "\n";
	}
};

Double operator*(const Double& f1, const Double& f2) {
	double res = f1.value * f2.value;
	if (res > std::numeric_limits<double>::max() || res < -std::numeric_limits<double>::max()) {
		throw std::overflow_error("Overflow error: result is too large or too small.");
	}
	return Double(res);
}


class Integ {
private:
	int number;

	void checkOverflow(int val) {
		if (val > std::numeric_limits<int>::max() || val < std::numeric_limits<int>::min()) {
			throw std::overflow_error("Overflow error: value is too large or too small.");
		}
	}

public:
	Integ() : number(0) {}
	// Конструктор (0 если неверные данные (буквы и т.п.)
	Integ(int val = 0) {
		setValue(val);
	}

	void setValue(int val) {
		checkOverflow(val);
		number = val;
	}

	int getValue() const {
		return number;
	}

	Integ operator+(const Integ& other) {
		long long res = static_cast<long long>(number) + other.number;
		checkOverflow(res);
		return Integ(static_cast<int>(res));
	}

	friend Integ operator-(const Integ& l1, const Integ& l2);

	void print() const {
		std::cout << number << "\n";
	}
};

Integ operator-(const Integ& l1, const Integ& l2) {
	long long res = static_cast<long long>(l1.number) - l2.number;
	if (res > std::numeric_limits<int>::max() || res < std::numeric_limits<int>::min()) {
		throw std::overflow_error("Overflow error: result is too large or too small.");
	}
	return Integ(static_cast<int>(res));
}


int main() {
	constexpr int LIMIT_INT{ 1000000000 };
	constexpr double LIMIT_DOUBLE{ 10000000000.0 };

	std::cout << std::fixed << std::setprecision(6);

	try {
		double value1{};
		double value2{};

		std::cout << "Enter two double values ((-10^10; 10^10) and 6 number after dot):\nValue 1: ";
		std::cin >> value1;
		while (value1 > LIMIT_DOUBLE || value1 < -LIMIT_DOUBLE) {
			std::cout << "Uncorrent enter value1. Try again: ";
			std::cin >> value1;
		}

		std::cout << "Value 2: ";
		std::cin >> value2;
		while (value2 > LIMIT_DOUBLE || value2 < -LIMIT_DOUBLE) {
			std::cout << "Uncorrent enter value2. Try again: ";
			std::cin >> value2;
		}

		Double d1(value1);
		Double d2(value2);

		std::cout << "\nd1 = ";
		d1.print();
		std::cout << "d2 = ";
		d2.print();

		Double d3 = d1 * d2;
		std::cout << "\nd3 = d1 * d2 = ";
		d3.print();

		std::cout << "\nd1++ = ";
		d1++;
		d1.print();

		std::cout << "++d2 = ";
		++d2;
		d2.print();

		// Тест для Integ


		std::cout << "\nEnter two integer values:\nValue 1: ";
		int val1{};
		int val2{};

		std::cin >> val1;
		while (val1 > LIMIT_INT || val1 < -LIMIT_INT) {
			std::cout << "Uncorrent enter val1. Try again: ";
			std::cin >> val1;
		}

		std::cout << "Value 2: ";
		std::cin >> val2;
		while (val2 > LIMIT_INT || val2 < -LIMIT_INT) {
			std::cout << "Uncorrent enter val2. Try again: ";
			std::cin >> val2;
		}

		Integ i1(val1);
		Integ i2(val2);

		std::cout << "\ni1 = ";
		i1.print();
		std::cout << "i2 = ";
		i2.print();

		Integ i3 = i1 - i2;
		std::cout << "\ni3 = i1 - i2 = ";
		i3.print();

		Integ i4 = i1 + i2;
		std::cout << "i4 = i1 + i2 = ";
		i4.print();

	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}

	return 0;
}


