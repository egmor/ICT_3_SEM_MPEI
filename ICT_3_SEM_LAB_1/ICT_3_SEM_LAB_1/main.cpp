#include "doublelinkedlist.h"
#include "sorting.h"
#include "queue.h"
#include "correct.h"

namespace Current_Date {
    constexpr int day{ 14 };
    constexpr int month{ 9 };
    constexpr int year{ 2026 };
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
    std::cout << "|" << std::format("{:^18}", "Фамилия") << "|"
        << std::format("{:^16}", "Имя") << "|"
        << std::format("{:^20}", "Отчество") << "|"
        << std::format("{:^6}", "Год") << "|"
        << std::format("{:^52}", "Адрес") << "|"
        << std::format("{:^25}", "Основное заболевание") << "|"
        << std::format("{:^11}", "Дата п.п.") << "|"
        << "\n"
        << "------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
}

void table_sick_man(const Medical_Record& sick_man) {
    std::cout << "|" << std::format("{:^18}", sick_man.SNL.surname) << "|"
        << std::format("{:^16}", sick_man.SNL.name) << "|"
        << std::format("{:^20}", sick_man.SNL.last_name) << "|"
        << std::format("{:^6}", std::to_string(sick_man.birth_year)) << "|"
        << std::format("{:^52}", (sick_man.address.city + ", " + sick_man.address.district + ", " + sick_man.address.street + ", " + sick_man.address.building + ", " + sick_man.address.apartment)) << "|"
        << std::format("{:^25}", sick_man.illness) << "|"
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

void hand_enter(DoublyLinkedList& list, Medical_Record& temp) {
    //ФИО
    std::cout << "\nВведите ФИО пациента (Фамилия Имя Отчество): ";
    std::cin >> temp.SNL.surname;
    std::cin >> temp.SNL.name;
    std::cin >> temp.SNL.last_name;
    while (!correct_name(temp.SNL)) {
        std::cout << "\nНекорректный ввод ФИО пациента\n Введите ещё раз: ";
        std::cin >> temp.SNL.surname;
        std::cin >> temp.SNL.name;
        std::cin >> temp.SNL.last_name;
    }
    //Адрес
    std::cout << "Введите адрес проживания пациента (город, район, улица, дом, квартира): ";
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
    std::cout << "Введите дату последнего посещения пациента (дд мм гггг): ";
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
    std::cout << "Введите год рождения пациента (совершеннолетний, не старше 100 лет): ";
    std::cin >> temp.birth_year;
    while (temp.birth_year < 1926 || temp.birth_year > 2008 || temp.birth_year > temp.date.year - 18) {
        std::cout << "\nНекорректный ввод года рождения пациента\n Введите ещё раз (совершеннолетний, не старше 100 лет): ";
        std::cin >> temp.birth_year;
    }
    //Болезнь
    std::cout << "Введите болезнь пациента: ";
    std::cin >> temp.illness;
}

void change_record(DoublyLinkedList& list) {
    int index{};
    std::cout << "\nВведите индекс записи для изменения (1-" << list.size<< "): ";
    std::cin >> index;
    Node* node_to_edit = get_node(list, index - 1);
    if (node_to_edit) {
        std::cout << "\nТекущая запись:\n";
        table_sick_man(node_to_edit->data);
        hand_enter(list, node_to_edit->data);
        std::cout << "\nИзменённая запись:\n";
        table_sick_man(node_to_edit->data);
    }
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    std::cout << "Выберите вариант входного файла:\n"
        << " 1. patients.txt - файл с 12 корректными записями\n"
        << " 2. empty_file_test.txt - пустой файл для тестирования\n"
		<< " 3. uncorrect_entry_file_test.txt - файл с 14 некорректными записями\n"
        << " 4. file_with_DiAbEt.txt - файл с 8 записями о диабете в различных регистрах\n"
        << " Введите номер: ";
    int file_choice{};
    std::cin >> file_choice;

    std::string filename;
    switch (file_choice) {
        case 1: filename = "patients.txt"; break;
        case 2: filename = "empty_file_test.txt"; break;
        case 3: filename = "uncorrect_entry_file_test.txt"; break;
		case 4: filename = "file_with_DiAbEt.txt"; break;
        default: std::cerr << "[Ошибка] Неверный выбор файла! Завершение работы программы\n"; return 2;
    }

    Queue input_queue;
    std::cout << "\n1. Чтение данных из файла в первичную очередь...\n";
    if (!text_to_queue(filename, input_queue)) {
        std::cerr << "========== Файл пуст! Заполните его перед началом работы!!! Или завершите работу программы ==========\n";
    }

    DoublyLinkedList list;
    Medical_Record temp_record;


    while (pop_queue(input_queue, temp_record)) {
        push_back(list, temp_record);
    }

    int choice{ 0 };
    do {
        std::cout << "\nВыберите вариант работы программы:\n"
            << " 1. Сортировка по ФИО\n"
            << " 2. Сортировка по году рождения\n"
            << " 3. Сортировка по адресу\n"
            << " 4. Сортировка по заболеванию\n"
            << " 5. Сортировка по дате посещения\n"
            << " 6. Ручной ввод данных\n"
            << " 7. Удаление записи (начало списка)\n"
            << " 8. Удаление записи (конец списка)\n"
            << " 9. Удаление записи (по индексу)\n"
			<< " 10. Изменение существующей записи\n"
			<< " 11. Отобразить актуальный список\n"
            << " 0. Завершить работу\n"
            << " Введите номер: ";
        std::cin >> choice;

        Medical_Record temp{};

        switch (choice) {
        case 1: sort_by_fio(list); break;
        case 2: sort_by_birth_year(list); break;
        case 3: sort_by_address(list); break;
        case 4: sort_by_illness(list); break;
        case 5: sort_by_date(list); break;
        case 6: hand_enter(list, temp); push_back(list, temp); break;
		case 7: std::cout << "\nУдаление записи:\n"; table_sick_man(list.head->data); pop_front(list); break;
		case 8: std::cout << "\nУдаление записи:\n"; table_sick_man(list.tail->data); pop_back(list); break;
		case 9: {
			int index{};
			std::cout << "\nВведите индекс записи для удаления (1-" << list.size << "): ";
			std::cin >> index;
            std::cout << "\nУдаление записи:\n";
			table_sick_man(get_node(list, index - 1)->data);
			pop_index(list, index - 1);
			break;
		}
		case 10: change_record(list); break;
		case 11: std::cout << "\n=== АКТУАЛЬНЫЙ СПИСОК (БЕЗ СОРТИРОВКИ) ===\n"; up_table(); {
			Node* current = list.head;
			while (current != nullptr) {
				table_sick_man(current->data);
				current = current->next;
			}
		} break;
        case 0: std::cout << "\nРабота программы завершена\n"; return 0;
        default:
            std::cerr << "[Ошибка] Неверный выбор!\n";
            clear_list(list);
            return 1;
        }
    } while (choice == 6 || choice == 7 || choice == 8 || choice == 9 || choice == 10 || choice == 11);

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