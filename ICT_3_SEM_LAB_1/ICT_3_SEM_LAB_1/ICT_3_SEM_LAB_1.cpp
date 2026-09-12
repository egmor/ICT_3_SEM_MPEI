#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <windows.h>
#include <format>

namespace Current_Date {
    constexpr int day{ 7 };
    constexpr int month{ 9 };
    constexpr int year{ 2026 };
}

struct Patient {
    std::string name{};
    std::string surname{};
    std::string last_name{};
};

struct Address {
    std::string city{};
    std::string district{};
    std::string street{};
    std::string building{};
    std::string apartment{};
};

struct Date_Last_Visit {
    int day{};
    int month{};
    int year{};
};

struct Medical_Record {
    Patient SNL{};
    Address address{};
    Date_Last_Visit date{};
    int birth_year{};
    std::string illness{};
};

bool correct_day(int day, int month, int year) {
    if (day > 31 || day < 1) return false;
    else if (day > 30 && (month == 4 || month == 6 || month == 9 || month == 11)) return false;
    else if (day > 29 && month == 2 && (year % 4 == 0)) return false;
    else if (day > 28 && month == 2 && (year % 4 != 0)) return false;
    else { return true; }
}

bool correct_date(Date_Last_Visit& date) {
    if (date.year <= 2000 || date.year > 2026) return false;
    if (date.month > 12 || date.month < 1) return false;
    if (!correct_day(date.day, date.month, date.year)) return false;
    else { return true; }
}

std::string to_lower(std::string str) {
    for (char& ch : str) {
        unsigned char uc = static_cast<unsigned char>(ch);
        if (uc >= 192 && uc <= 223) {
            ch = static_cast<char>(uc + 32);
        }
        else if (uc == 168) { // 'Ё'
            ch = static_cast<char>(184); // 'ё'
        }
    }
    return str;
}

bool text_to_file(const std::string& file_name, Medical_Record*& sick_mans, int& count) {
    std::ifstream inFile(file_name);
    if (!inFile.is_open()) return false;

    count = 0;
    int skippedCount = 0;
    Medical_Record temp;

    while (inFile >> temp.SNL.name >> temp.SNL.surname >> temp.SNL.last_name
        >> temp.address.city >> temp.address.district >> temp.address.street
        >> temp.address.building >> temp.address.apartment
        >> temp.date.day >> temp.date.month >> temp.date.year
        >> temp.birth_year >> temp.illness) {

        if (correct_date(temp.date)) {
            count++;
        }
        else {
            skippedCount++;
        }
    }

    if (count == 0) {
        if (skippedCount > 0) std::cout << "[Инфо] Всего пропущено некорректных записей: " << skippedCount << "\n\n";
        inFile.close();
        return false;
    }

    sick_mans = new Medical_Record[count];

    inFile.clear();
    inFile.seekg(0, std::ios::beg);

    int i = 0;
    while (inFile >> temp.SNL.name >> temp.SNL.surname >> temp.SNL.last_name
        >> temp.address.city >> temp.address.district >> temp.address.street
        >> temp.address.building >> temp.address.apartment
        >> temp.date.day >> temp.date.month >> temp.date.year
        >> temp.birth_year >> temp.illness) {

        if (correct_date(temp.date)) {
            sick_mans[i++] = temp;
        }
    }

    inFile.close();
    if (skippedCount > 0) std::cout << "[Инфо] Всего пропущено некорректных записей: " << skippedCount << "\n\n";

    return true;
}

int count_diabet(const Medical_Record* sick_man, int size) {
    int diabet_count{ 0 };
    for (int i{ 0 }; i < size; ++i) {
        if (to_lower(sick_man[i].illness) == "диабет") ++diabet_count;
    }
    return diabet_count;
}

void up_table() {
    std::cout << "|" << std::format("{:^19}", "Фамилия") << "|"
        << std::format("{:^16}", "Имя") << "|"
        << std::format("{:^20}", "Отчество") << "|"
        << std::format("{:^6}", "Год") << "|"
        << std::format("{:^40}", "Адрес") << "|"
        << std::format("{:^36}", "Основное заболевание") << "|"
        << std::format("{:^11}", "Дата п.п.") << "|"
        << "\n"
        << "------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
}

void table_sick_man(const Medical_Record& sick_man) {
    std::cout << "|" << std::format("{:^19}", sick_man.SNL.surname) << "|"
        << std::format("{:^16}", sick_man.SNL.name) << "|"
        << std::format("{:^20}", sick_man.SNL.last_name) << "|"
        << std::format("{:^6}", std::to_string(sick_man.birth_year)) << "|"
        << std::format("{:^40}", (sick_man.address.city + ", " + sick_man.address.district + ", " + sick_man.address.street + ", " + sick_man.address.building + ", " + sick_man.address.apartment)) << "|"
        << std::format("{:^36}", sick_man.illness) << "|"
        << std::format("{:^11}", (std::to_string(sick_man.date.day) + "." + std::to_string(sick_man.date.month) + "." + std::to_string(sick_man.date.year))) << "|"
        << "\n";
}

void output_table(const Medical_Record* sick_man, int size) {
    for (int i{ 0 }; i < size; ++i) table_sick_man(sick_man[i]);
}

void output_table_diabet(const Medical_Record* sick_man, int size) {
    for (int i{ 0 }; i < size; ++i) {
        if ((std::abs(Current_Date::year - sick_man[i].date.year) >= 0) && (std::abs(Current_Date::month - sick_man[i].date.month) >= 3) &&
            (std::abs(Current_Date::day - sick_man[i].date.day) > 0) && (to_lower(sick_man[i].illness) == "диабет")) {
            table_sick_man(sick_man[i]);
        }
    }
}

void sort_by_date(Medical_Record* sick_man, int size) {
	std::sort(sick_man, sick_man + size, [](const Medical_Record& a, const Medical_Record& b) {
		return a.date.year < b.date.year || (a.date.year == b.date.year && a.date.month < b.date.month) || (a.date.year == b.date.year && a.date.month == b.date.month && a.date.day < b.date.day);
	});
}

int main() {

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    Medical_Record* patients = nullptr;
    int patients_count = 0;
	std::string filename = "patients.txt"; // полностью корректный файл с данными пациентов
	// std::string filename = "empty_file_test.txt"; // тест пустым файлом
	// std::string filename = "uncorrect_entry_file_test.txt"; // тест файлом с некорректными данными
	// std::string filename = "file_with_DiAbEt.txt"; // проверка работа понижения регистра

    std::cout << "Загрузка данных из текстового файла " << filename << "...\n";
    if (!text_to_file(filename, patients, patients_count)) {
        std::cerr << "[Ошибка] Не удалось загрузить данные из файла!\n";
        return 1;
    }
    
    std::cout << "Успешно загружено корректных записей: " << patients_count << "\n\n";
    
    std::cout << "=== ИСХОДНЫЕ ДАННЫЕ ИЗ ФАЙЛА ===\n";
	up_table();
    output_table(patients, patients_count);
    
    std::cout << "\n\nСортировка данных по дате...";
    sort_by_date(patients, patients_count);
    
    std::cout << "\n=== ОТСОРТИРОВАННАЯ ТАБЛИЦА ===\n";
    up_table();
    output_table(patients, patients_count);

	int diabet_count = count_diabet(patients, patients_count);
	std::cout << "\n\n Количество больных диабетом: " << diabet_count;

	std::cout << "\n=== ПАЦИЕНТЫ С ДИАБЕТОМ, КОТОРЫХ НЕ БЫЛО > 3х МЕСЯЦЕВ ===\n";
    up_table();
	output_table_diabet(patients, patients_count);

    delete[] patients;

    return 0;
}