#include <iostream>

class HardDisk {
private:
	unsigned int capacityMB;

public:
	HardDisk(unsigned int capacity = 4194304) {setCapacity(capacity);} // Стандартный объём HDD в 4 TB (4.194.304 MB)

	void setCapacity(unsigned int capacity) {
		if (capacity > 31457280) { // Максимальный объём HDD в 30 TB (31.457.280 MB)
			throw std::invalid_argument("Capacity exceeds maximum limit of 30 TB.");
		}
		capacityMB = capacity;
	}

	unsigned int getCapacity() const { return capacityMB; }
};

//=================================================================================================================

class Computer {
private:
	HardDisk HDD;
	char* brand;
	double price; //Цена в рублях

public:
	Computer(unsigned int hddCapacity = 1048576, const char* brandName = "Acer", double priceValue = 250000.0)
		: HDD(hddCapacity), brand(nullptr), price(priceValue) {
		setBrand(brandName);
		setPrice(priceValue);
	}

	Computer(const Computer& other)
		: HDD(other.HDD), brand(nullptr), price(other.price) {
		setBrand(other.brand);
		setPrice(other.price);
	}

	Computer& operator=(const Computer& other) {
		if (this != &other) {
			HDD = other.HDD;
			setBrand(other.brand);
			setPrice(other.price);
		}
		return *this;
	}

	void setBrand(const char* brandName) {
		delete[] brand;
		if (!brandName || strlen(brandName) == 0) { throw std::invalid_argument("Brand name cannot be empty.");}
		else if (strlen(brandName) > 31) { throw std::invalid_argument("Brand name cannot exceed 30 characters."); }
		else {
			brand = new char[strlen(brandName) + 1];
			strcpy_s(brand, strlen(brandName) + 1, brandName);
		}
	}

	void setPrice(double priceValue) {
		if (priceValue < 30000) { throw std::invalid_argument("Price cannot be less than 30,000 rub."); }
		else if (priceValue > 900000) { throw std::invalid_argument("Price cannot exceed 900,000 rub."); }
		price = priceValue;
	}

	unsigned int getHDDCapacity() const { return HDD.getCapacity(); }
	char* getBrand() const { return brand; }
	double getPrice() const { return price; }

	void print() const {
		std::cout << "\nBrand: " << brand;
		std::cout << "\nPrice: " << price << " rub";
		std::cout << "\nHDD Capacity: " << HDD.getCapacity() << " MB | " << HDD.getCapacity() / 1024 << " GB | " << HDD.getCapacity() / pow(1024.0, 2.0) << " TB";
	}

	~Computer() {
		delete[] brand;
	}
};

//=================================================================================================================

class PublicComputerMonitor : public Computer {
private:
	double monitorSize; // Диагональ монитора в дюймах

public:
	PublicComputerMonitor(unsigned int hddCapacity = 1048576, const char* brandName = "Lenovo", double priceValue = 100000.0, double monitorSizeValue = 27)
		: Computer(hddCapacity, brandName, priceValue), monitorSize(monitorSizeValue) {
		setMonitorSize(monitorSizeValue);
	}

	~PublicComputerMonitor() = default;

	void setMonitorSize(double size) {
		if (size <= 19) { throw std::invalid_argument("Monitor size must be >= 19 inches."); }
		else if (size > 50) { throw std::invalid_argument("Monitor size must be <= 50 inches."); }
		monitorSize = size;
	}

	double getMonitorSize() const { return monitorSize; }

	void print() const {
		Computer::print();
		std::cout << "\nMonitor Size: " << monitorSize << " inches";
	}
};

//=================================================================================================================

class PrivateComputerMonitor : private Computer {
private:
	double monitorSize; // Диагональ монитора в дюймах

public:
	PrivateComputerMonitor(unsigned int hddCapacity = 1048576, const char* brandName = "MSI", double priceValue = 100000.0, double monitorSizeValue = 27)
		: Computer(hddCapacity, brandName, priceValue), monitorSize(monitorSizeValue) {
		setMonitorSize(monitorSizeValue);
	}

	~PrivateComputerMonitor() = default;

	void setMonitorSize(double size) {
		if (size <= 19) { throw std::invalid_argument("Monitor size must be >= 19 inches."); }
		else if (size > 50) { throw std::invalid_argument("Monitor size must be <= 50 inches."); }
		monitorSize = size;
	}

	double getMonitorSize() const { return monitorSize; }

	void print() const {
		Computer::print();
		std::cout << "\nMonitor Size: " << monitorSize << " inches";
	}
};

//=================================================================================================================

int main() {
	std::cout << "Correct data for PC (public and private) monitors:\n";
	try {
		std::cout << "PUBLIC:";
		PublicComputerMonitor pc1(2097152, "Hewlett-Packard", 220000.00, 27.0);
		pc1.print();
		std::cout << "\n\n";

		std::cout << "PRIVATE:";
		PrivateComputerMonitor pc2(524288, "International Business Machines", 85000.00, 23.8);
		pc2.print();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}

	std::cout << "\n\nExceptions: \n";

	// Ошибка диска
	try {
		std::cout << "1. Invalid HDD capacity (> 30 TB): \n";
		HardDisk badHdd(32000000);
	}
	catch (const std::exception& e) {
		std::cout << "Catch exceptions: " << e.what() << "\n\n";
	}

	// Ошибка цены
	try {
		std::cout << "2. Invalid price (< 30.000 rub): \n";
		Computer badPc(512000, "Dell", -100.0);
	}
	catch (const std::exception& e) {
		std::cout << "Catch exceptions: " << e.what() << "\n\n";
	}

	try {
		std::cout << "3. Invalid price (> 900.000 rub): \n";
		Computer badPc(512000, "Dell", 1000000.0);
	}
	catch (const std::exception& e) {
		std::cout << "Catch exceptions: " << e.what() << "\n\n";
	}

	// Ошибка монитора
	try {
		std::cout << "4. Invalid monitor size (<= 19 inches): \n";
		PublicComputerMonitor badMonitor(512000, "Hewlett-Packard", 60000.0, 15.0);
	}
	catch (const std::exception& e) {
		std::cout << "Catch exceptions: " << e.what() << "\n\n";
	}

	try {
		std::cout << "5. Invalid monitor size (> 50 inches): \n";
		PublicComputerMonitor badMonitor(512000, "Hewlett-Packard", 60000.0, 55.0);
	}
	catch (const std::exception& e) {
		std::cout << "Catch exceptions: " << e.what() << "\n\n";
	}

	return 0;
}