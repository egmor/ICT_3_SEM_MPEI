#include <iostream>
#include <climits>
#include <stdexcept>

class Double {
private:
	double value;

	void checkOverflow(double val) {
		if (val > 1e308 || val < -1e308) {
			throw std::overflow_error("Overflow error: value is too large or too small.");
		}
	}

public:
	Double() : value(0.0) {}
	// Конструктор (0 если неверные данные (буквы и т.п.)
	Double(double val = 0.0) {
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
	if (res > 1e308 || res < -1e308) {
		throw std::overflow_error("Overflow error: result is too large or too small.");
	}
	return Double(res);
}


class Integ {
private:
	int number;

	void checkOverflow(long long val) {
		if (val > INT_MAX || val < INT_MIN) {
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

	Integ& operator+(const Integ& other) {
		long long res = static_cast<long long>(number) + other.number;
		checkOverflow(res);
		number += other.number;
		return *this;
	}

	friend Integ operator-(const Integ& l1, const Integ& l2);

	void print() const {
		std::cout << number << "\n";
	}
};

Integ operator-(const Integ& l1, const Integ& l2) {
	long long res = static_cast<long long>(l1.number) - l2.number;
	if (res > INT_MAX || res < INT_MIN) {
		throw std::overflow_error("Overflow error: result is too large or too small.");
	}
	return Integ(static_cast<int>(res));
}


int main() {
	try {
		double value1{};
		double value2{};

		std::cout << "Enter two double values (two numbers after dot): ";
		std::cin >> value1 >> value2;

		Double d1(value1);
		Double d2(value2);
		Double d3 = d1 * d2;

		std::cout << "\nd1 = ";
		d1.print();
		std::cout << "d2 = ";
		d2.print();

		std::cout << "\nd3 = d1 * d2 = ";
		d3.print();

		std::cout << "\nd1++ = ";
		d1++;
		d1.print();

		std::cout << "++d2 = ";
		++d2;
		d2.print();

		// Тест для Integ
		std::cout << "\nEnter two integer values: ";
		int val1, val2;
		std::cin >> val1 >> val2;

		Integ i1(val1);
		Integ i2(val2);

		std::cout << "\ni1 = ";
		i1.print();
		std::cout << "i2 = ";
		i2.print();

		Integ i3 = i1 - i2;
		std::cout << "\ni1 - i2 = ";
		i3.print();

		Integ i4 = i1 + i2;
		std::cout << "i1 + i2 = ";
		i4.print();

	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}

	return 0;
}