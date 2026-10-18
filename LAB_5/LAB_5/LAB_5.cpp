#include <iostream>
#include <limits>
#include <iomanip>

class Double {
private:
	double value;

	bool checkOverflow(double val) {
		if (val > std::numeric_limits<double>::max() || val < -std::numeric_limits<double>::max()) {
			return false;
		}
		return true;
	}

public:
	Double() : value(0.0) {}//По умолчанию

	// Конструктор (0 если неверные данные (буквы и т.п.))
	Double(double val = 0.0) : value(val) {
		if (!checkOverflow(val)) {
			throw std::overflow_error("\nOverflow error: value is too large or too small.");
		}
	}

	void setValue(double val) {
		if (!checkOverflow(val)) {
			throw std::overflow_error("\nOverflow error: value is too large or too small.");
		}
		else value = val;
	}

	double getValue() const {
		return value;
	}

	Double& operator++() {//++a
		if (!checkOverflow(value + 1.0)) {
			throw std::overflow_error("\nOverflow error: value is too large or too small.");
		}
		value += 1.0;
		return *this;
	}

	Double operator++(int) {//a++
		Double temp = *this;
		if (!checkOverflow(value + 1.0)) {
			throw std::overflow_error("\nOverflow error: value is too large or too small.");
		}
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

	bool checkOverflow(int val) {
		if (val > std::numeric_limits<int>::max() || val < std::numeric_limits<int>::min()) {
			return false;
		}
		return true;
	}

public:
	Integ() : number(0) {}//По умолчанию
	// Конструктор (0 если неверные данные (буквы и т.п.)
	Integ(int val = 0) : number(val) {
		if (!checkOverflow(val)) {
			throw std::overflow_error("Overflow error: value is too large or too small.");
		}
	}

	void setValue(int val) {
		if (!checkOverflow(val)) {
			throw std::overflow_error("Overflow error: value is too large or too small.");
		}
		else number = val;
	}

	int getValue() const {
		return number;
	}

	Integ operator+(const Integ& other) {
		long long res = static_cast<long long>(number) + other.number;
		if (!checkOverflow(res)) {
			throw std::overflow_error("Overflow error: value is too large or too small.");
		}
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

	std::cout << std::fixed << std::setprecision(5);

	try {
		double value1{};
		double value2{};

		std::cout << "Enter two double values ([-10^10; 10^10] and 5 number after dot):\nValue 1: ";
		while (!(std::cin >> value1) || value1 > LIMIT_DOUBLE || value1 < -LIMIT_DOUBLE) {
			std::cout << "Uncorrent enter value1. Try again: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		std::cout << "Value 2: ";
		while (!(std::cin >> value2) || value2 > LIMIT_DOUBLE || value2 < -LIMIT_DOUBLE) {
			std::cout << "Uncorrent enter value2. Try again: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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

		std::cout << "\n d1++ = ";
		//d1++;
		(d1++).print();

		std::cout << "++d2 = ";
		//++d2;
		(++d2).print();

		
		std::cout << "\nEnter two integer values [-10^9; 10^9]:\nValue 1: ";
		double val1{};
		double val2{};

		while (!(std::cin >> val1) || static_cast<int>(round(val1)) > LIMIT_INT || static_cast<int>(round(val1) < -LIMIT_INT)) {
			std::cout << "Uncorrent enter val1. Try again: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		int int_val1{ static_cast<int>(round(val1)) };

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::cout << "Value 2: ";
		while (!(std::cin >> val2) || static_cast<int>(round(val2)) > LIMIT_INT || static_cast<int>(round(val2) < -LIMIT_INT)) {
			std::cout << "Uncorrent enter val2. Try again: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		int int_val2{ static_cast<int>(round(val2)) };

		Integ i1(int_val1);
		Integ i2(int_val2);

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