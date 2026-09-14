#include "doublelinkedlist.h"
#include "sorting.h"
#include "queue.h"

namespace Current_Date {
    constexpr int day{ 14 };
    constexpr int month{ 9 };
    constexpr int year{ 2026 };
}

bool correct_day(int day, int month, int year) {
    if (day > 31 || day < 1) return false;
    else if (day > 30 && (month == 4 || month == 6 || month == 9 || month == 11)) return false;
    else if (day > 29 && month == 2 && (year % 4 == 0)) return false;
    else if (day > 28 && month == 2 && (year % 4 != 0)) return false;
    else return true;
}

bool correct_date(Date_Last_Visit& date) {
    if (date.year <= 2000 || date.year > 2026) return false;
    if (date.month > 12 || date.month < 1) return false;
    if (!correct_day(date.day, date.month, date.year)) return false;
    else return true;
}

bool correct_address(Address& data) {
    if (data.city.size() < 2 || data.city.size() > 10) return false;
    if (data.district.size() < 2 || data.district.size() > 10) return false;
    if (data.street.size() < 2 || data.street.size() > 15) return false;
    if (std::stoi(data.building) < 1 || std::stoi(data.building) > 150) return false;
    if (std::stoi(data.apartment) < 1 || std::stoi(data.apartment) > 1000) return false;
    else return true;
}

bool correct_name(Patient& data) {
    if (data.name.size() < 2 || data.name.size() > 10) return false;
    if (data.surname.size() < 2 || data.surname.size() > 10) return false;
    if (data.last_name.size() < 5 || data.last_name.size() > 15) return false;
    else return true;
}

std::string to_lower(std::string str) {
    for (char& ch : str) {
        unsigned char uc = static_cast<unsigned char>(ch);
        if (uc >= 192 && uc <= 223) ch = static_cast<char>(uc + 32); //Ё
        else if (uc == 168)  ch = static_cast<char>(184); //ё
    }
    return str;
}

bool text_to_queue(const std::string& file_name, Queue& q) {
    std::ifstream inFile(file_name);
    if (!inFile.is_open()) return false;

    int skippedCount{ 0 };
    Medical_Record temp;

    while (inFile >> temp.SNL.name >> temp.SNL.surname >> temp.SNL.last_name
        >> temp.address.city >> temp.address.district >> temp.address.street
        >> temp.address.building >> temp.address.apartment
        >> temp.date.day >> temp.date.month >> temp.date.year
        >> temp.birth_year >> temp.illness) {
        if (correct_date(temp.date) && correct_address(temp.address) && correct_name(temp.SNL)) push_queue(q, temp);
        else ++skippedCount;
    }

    inFile.close();
    if (skippedCount > 0) std::cout << "[Инфо] Пропущено некорректных записей: " << skippedCount << "\n";

    return q.size > 0;
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

bool over_3_months(const Date_Last_Visit& date) {
    int year_diff = Current_Date::year - date.year;
    int month_diff = Current_Date::month - date.month;
    int total_months = year_diff * 12 + month_diff;

    if (total_months > 3) return true;
    if (total_months == 3 && Current_Date::day > date.day) return true;

    return false;
}

void hand_enter(DoublyLinkedList& list) {
    Medical_Record temp{};
    //ФИО
    std::cout << "\nВведите ФИО пациента (Имя Фамилия Отчество: ";
    std::cin >> temp.SNL.name;
    std::cin >> temp.SNL.surname;
    std::cin >> temp.SNL.last_name;
    while (!correct_name(temp.SNL)) {
        std::cout << "\nНекорректный ввод ФИО пациента\n Введите ещё раз: ";
        std::cin >> temp.SNL.name;
        std::cin >> temp.SNL.surname;
        std::cin >> temp.SNL.last_name;
    }
    //Адрес
    std::cout << "\nВведите адрес проживания пациента (город, район, улица, дом, квартира): ";
    std::cin >> temp.address.city;
    std::cin >> temp.address.district;
    std::cin >> temp.address.street;
    std::cin >> temp.address.building;
    std::cin >> temp.address.apartment;
    while (!correct_address(temp.address)) {
        std::cout << "\nНекорректный ввод адрес прожвания пациента\n Введите ещё раз: ";
        std::cin >> temp.address.city;
        std::cin >> temp.address.district;
        std::cin >> temp.address.street;
        std::cin >> temp.address.building;
        std::cin >> temp.address.apartment;
    }
    //Дата последнего посещения
    std::cout << "\nВведите дату последнего посещения пациента (дд мм гггг): ";
    std::cin >> temp.date.day;
    std::cin >> temp.date.month;
    std::cin >> temp.date.year;
    while (!correct_date(temp.date)) {
        std::cout << "\nНекорректный ввод дату последнего посещения пациента\n Введите ещё раз: ";
        std::cin >> temp.date.day;
        std::cin >> temp.date.month;
        std::cin >> temp.date.year;
    }
    //Год рождения
    std::cout << "\nВведите год рождения пациента: ";
    std::cin >> temp.birth_year;
    while (temp.birth_year < 1926 || temp.birth_year > 2026) {
        std::cout << "\nНекорректный ввод года рождения пациента\n Введите ещё раз: ";
        std::cin >> temp.birth_year;
    }
    //Болезнь
    std::cout << "\nВведите болезнь пациента: ";
    std::cin >> temp.illness;

    push_back(list, temp);

    Node* last_record = list.tail;

    table_sick_man(last_record->data);
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    std::string filename = "patients.txt";

    Queue input_queue;
    std::cout << "1. Чтение данных из файла в первичную очередь...\n";
    if (!text_to_queue(filename, input_queue)) {
        std::cerr << "[Ошибка] Не удалось загрузить данные в очередь!\n";
        return 1;
    }

    DoublyLinkedList list;
    Medical_Record temp_record;

    std::cout << "\n=== ИСХОДНЫЕ ДАННЫЕ ИЗ ОЧЕРЕДИ (БЕЗ СОРТИРОВКИ) ===\n";
    up_table();

    while (pop_queue(input_queue, temp_record)) {
        table_sick_man(temp_record);
        push_back(list, temp_record);
    }

    int choice{ 0 };
    do {
        std::cout << "\nВыберите вариант работы программы:\n"
            << " 1. По ФИО\n"
            << " 2. По году рождения\n"
            << " 3. По адресу\n"
            << " 4. По заболеванию\n"
            << " 5. По дате посещения\n"
            << " 6. Ручной ввод данных\n"
            << " 0. Завершить работу\n"
            << " Введите номер: ";
        std::cin >> choice;

        switch (choice) {
        case 1: sort_by_fio(list); break;
        case 2: sort_by_birth_year(list); break;
        case 3: sort_by_address(list); break;
        case 4: sort_by_illness(list); break;
        case 5: sort_by_date(list); break;
        case 6: hand_enter(list); break;
        case 0: std::cout << "\nРабота программы завершена\n"; return 0;
        default:
            std::cerr << "[Ошибка] Неверный выбор!\n";
            clear_list(list);
            return 1;
        }
    } while (choice == 6);

    Queue output_queue;
    Queue diabet_queue;

    Node* current = list.head;
    while (current != nullptr) {
        push_queue(output_queue, current->data);

        if (to_lower(current->data.illness) == "диабет" && over_3_months(current->data.date)) {
            push_queue(diabet_queue, current->data);
        }

        current = current->next;
    }
    clear_list(list);

    std::cout << "\n=== ОТСОРТИРОВАННЫЙ СПИСОК (ИЗ ВЫХОДНОЙ ОЧЕРЕДИ) ===\n";
    up_table();

    Medical_Record printed_record;
    while (pop_queue(output_queue, printed_record)) {
        table_sick_man(printed_record);
    }

    std::cout << "\n=== ПАЦИЕНТЫ С ДИАБЕТОМ (НЕ БЫЛИ БОЛЕЕ 3 МЕСЯЦЕВ) ===\n";
    if (diabet_queue.size == 0) {
        std::cout << "Таких пациентов не найдено.\n";
    }
    else {
        up_table();
        while (pop_queue(diabet_queue, printed_record)) {
            table_sick_man(printed_record);
        }
    }

    return 0;
}