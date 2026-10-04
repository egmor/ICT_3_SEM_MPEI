/* =============ПОСТАНОВКА ЗАДАЧИ===================
Цель работы — разработать консольную программу на языке C++, которая обрабатывает сведения о пациентах поликлиники. Данные должны считываться из текстового файла, проверяться на корректность, выводиться в табличном виде, сортироваться и обрабатываться в соответствии с условием варианта 26.
Задание 26ого варианта:
Имеются сведения о пациентах поликлиники: ФИО, год рождения, адрес, основное заболевание, дата последнего посещения лечащего врача.
Определить количество больных диабетом и вывести сведения о больных диабетом, не посещавших лечащего врача более трёх месяцев.

В программе используется 4 структуры:
    1. Структура даты последнего посещения (день, месяц, год) (все данные unsigned int, так как дата не может быть отрицательной)
    2. Структура адреса (город, район, улица, дом, квартира) (все данные std::string)
    3. Структура ФИО (все данные std::string)
    4. Структура мед. книжки (структура ФИО, стуктура адреса, структура д.п.п., unsigned int год рождения, std::string болезнь)

Реализация работы с файлом происходит через std::vector<Medical_Record> - вектор состоящий из структур мед. книжки


    •	в начале работы пользователю предлагается выбрать входной файл для работы из 4х вариантов (текстовые файлы в формате ANSI):
            1. patients.txt - файл с 12 корректными записями
            2. empty_file_test.txt - пустой файл для тестирования
		    3. uncorrect_entry_file_test.txt - файл с 14 некорректными записями
            4. file_with_DiAbEt.txt - файл с 8 записями о диабете в различных регистрах
    •	при пустом файле программа полностью завершает свою работу с выводом сообщения об этом
    •	считывает записи о пациентах из файла в std::vector в формате:
            Фамилия, имя, отчество, адрес, дата последнего посещения (дд.мм.гггг), год рождения (гггг);
    •	проверяет данные о последнем посещение на корректность, а именно:
            1.	дата не может быть позже 21.09.2026
            2.	год не может быть раньше 2000
            3.	в феврале не может быть больше 28 или 29 дней (если висакосный год)
            4.	в месяце не может быть больше 30/31 дня, в зависимости от месяца
            5.	месяц и день не могут быть < 1, а месяц и > 12
    •	проверяет данные об адресе на корректность, а именно:
    .	    1.  количество символов в названии города не может быть меньше 2 и больше 15
            2.	количество символов в названии района не может быть меньше 2 и больше 10
            3.  количество символов в названии улицы не может быть меньше 2 и больше 15
            4.  номер дома и квартиры не може состоять только из букв
            5.	номер дома не может быть меньше 1 и больше 150
            6.  номер квартиры не может быть меньше 1 и больше 1000 
    •	проверяет данные об ФИО на корректность, а именно:
    .	    1.  количество символов в имени не может быть меньше 2 и больше 10
            2.	количество символов в фамилии не может быть меньше 2 и больше 10
            3.  количество символов в отчестве не может быть меньше 5 и больше 15
    •	записи, которые не прошли проверку не попадают в std::vector, кол-во неккоретных записей выводится на экран
    •	затем пользователю предлагается 14 вариантов работы программы:
            1. Сортировка по ФИО
            2. Сортировка по году рождения 
            3. Сортировка по адресу
            4. Сортировка по заболеванию
            5. Сортировка по дате посещения
            6. Ручной ввод данных в начало
            7. Ручной ввод данных в конец
            8. Ручной ввод данных по индексу
            9. Удаление записи (начало списка)
            10. Удаление записи (конец списка)
            11. Удаление записи (по индексу)
			12. Изменение существующей записи
			13. Отобразить актуальный список
            0. Завершить работу
        (при выборе несуществующего варианта программа завершает свою работу с выводом сообщения об этом)
    •	после выполнения вариантов работы программы с 6 по 13 пользователя повторно просят выбрать один из вариантов работы программы 
    •	std::vector сортируется выбранным способом и затем выводятся в консоль 2 списка:
            1. Отсортированный список пациентов
            2. Список диабетиков, которых не было в больнице более 3х месяцев
*/

#include "sorting.h"
#include "correct.h"

namespace Current_Date {
    constexpr unsigned int day{ 28 };
    constexpr unsigned int month{ 9 };
    constexpr unsigned int year{ 2026 };
}

std::string to_lower(std::string str) {
    for (char& ch : str) {
        unsigned char uc = static_cast<unsigned char>(ch);
        if (uc >= 192 && uc <= 223) ch = static_cast<char>(uc + 32); //Ё
        else if (uc == 168)  ch = static_cast<char>(184); //ё
    }
    return str;
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
        << std::format("{:^11}", ((sick_man.date.day < 10) ? "0" : "") + (std::to_string(sick_man.date.day) + "." + ((sick_man.date.month < 10) ? "0" : "") + std::to_string(sick_man.date.month) + "." + std::to_string(sick_man.date.year))) << "|"
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

void file_to_vector(const std::string& filename, std::vector<Medical_Record>& records) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Ошибка открытия файла: " << filename << '\n';
		return;
	}

	Medical_Record temp;
	while (file >> temp.SNL.name >> temp.SNL.surname >> temp.SNL.last_name
		>> temp.address.city >> temp.address.district >> temp.address.street
		>> temp.address.building >> temp.address.apartment
		>> temp.date.day >> temp.date.month >> temp.date.year
		>> temp.birth_year >> temp.illness) {
		if (correct_date(temp) && correct_address(temp.address) && correct_name(temp.SNL)) {
			records.push_back(temp);
		}
	}
	file.close();
}

void enter_SNL(Medical_Record& record) {
    std::cout << "Введите ФИО: ";
    std::cin >> record.SNL.surname >> record.SNL.name >> record.SNL.last_name;
    while (!correct_name(record.SNL)) {
        std::cout << "\nНеккоретный ввод ФИО. Введите ещё раз: ";
        std::cin >> record.SNL.surname >> record.SNL.name >> record.SNL.last_name;
    }
}

void enter_address(Medical_Record& record) {
    std::cout << "Введите название адрес проживания (город район улица дом квартира): ";
    std::cin >> record.address.city >> record.address.district >> record.address.street >> record.address.building >> record.address.apartment;
    while (!correct_address(record.address)) {
        std::cout << "Некорретный ввод адреса. Введите ещё раз: ";
        std::cin >> record.address.city >> record.address.district >> record.address.street >> record.address.building >> record.address.apartment;
    }
}

void hand_enter(Medical_Record& record) {
    //ФИО
    enter_SNL(record);
    //Год рождения
    std::cout << "Введите год рождения (совершеннолетний, но моложе 100 лет): ";
    std::cin >> record.birth_year;
    while (Current_Date::year - record.birth_year < 18 || Current_Date::year - record.birth_year >= 100) {
        std::cout << "Некорректный ввод года рождения. Введите ещё раз: ";
        std::cin >> record.birth_year;
    }
    //Адрес
    enter_address(record);
    //Болезнь
    std::cout << "Введите болезнь: ";
    std::cin >> record.illness;
    //Дата последнего посещения
    std::cout << "Введите дату последнего посещения больницы (дд мм гггг) \n(дата последнего посещения должна быть не раньше, чем через 18 лет после года рождения): ";
    std::cin >> record.date.day >> record.date.month >> record.date.year;
    while (!correct_date(record)) {
        std::cout << "Некорректный ввод даты. Введите ещё раз: ";
        std::cin >> record.date.day >> record.date.month >> record.date.year;
    }
}

void change_record(Medical_Record& record) {
    std::cout << "\nВыберите параметр который хотите изменить: \n"
        << "1. ФИО\n"
        << "2. Год рождения\n"
        << "3. Адрес проживания\n"
        << "4. Болезнь\n"
        << "5. Дата последнего посещения\n"
        << "6. Все параметры\n"
        << "0. Ничего\nВаш выбор: ";
    unsigned int choice{ 0 };
    std::cin >> choice;
    do {
        switch (choice) {
        case 1: enter_SNL(record); std::cout << "\nИзменённая строка: \n"; table_sick_man(record); break;
        case 2: {
            std::cout << "Введите год рождения (совершеннолетний, но моложе 100 лет): ";
            std::cin >> record.birth_year;
            while (Current_Date::year - record.birth_year < 18 || Current_Date::year - record.birth_year >= 100) {
                std::cout << "Некорректный ввод года рождения. Введите ещё раз: ";
                std::cin >> record.birth_year;
            }
            std::cout << "\nИзменённая строка: \n";
            table_sick_man(record);
            break;
        }
        case 3: enter_address(record); std::cout << "\nИзменённая строка: \n"; table_sick_man(record); break;
        case 4: std::cout << "Введите болезнь: "; std::cin >> record.illness; break;
        case 5: {
            std::cout << "Введите дату последнего посещения (дд.мм.гггг): ";
            std::cin >> record.date.day >> record.date.month >> record.date.year;
            while (!correct_date(record)) {
                std::cout << "Некорректный ввод даты. Введите ещё раз: ";
                std::cin >> record.date.day >> record.date.month >> record.date.year;
            }
            std::cout << "\nИзменённая строка: \n";
            table_sick_man(record);
            break;
        }
        case 6: hand_enter(record); std::cout << "\nИзменённая строка: \n"; table_sick_man(record); break;
        case 0: break;
        default: std::cerr << "[Ошибка] Неверный выбор! Пожалуйста, попробуйте снова.\n"; break;
        }
    } while (choice > 6);
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

    std::vector<Medical_Record> records;

    std::cout << "\n1. Чтение данных из файла в первичную очередь...\n";
    file_to_vector(filename, records);
    if (records.empty()) {
        std::cerr << "Файл пуст! Программа завершает свою работу\n";
        return 2;
    }

    std::cout << "\n=== ИЗНАЧАЛЬНЫЙ СПИСОК ===\n";
    up_table();
    for (int i{ 0 }; i < records.size(); ++i) {
        table_sick_man(records[i]);
    }

    int choice{ 0 };
    do {
        std::cout << "\nВыберите вариант работы программы:\n"
            << " 1. Сортировка по ФИО\n"
            << " 2. Сортировка по году рождения\n"
            << " 3. Сортировка по адресу\n"
            << " 4. Сортировка по заболеванию\n"
            << " 5. Сортировка по дате посещения\n"
            << " 6. Ручной ввод данных в конец\n"
            << " 7. Ручной ввод данных в начало\n"
            << " 8. Ручной ввод данных по индексу\n"
            << " 9. Удаление записи (конец списка)\n"
            << " 10. Удаление записи (начало списка)\n"
            << " 11. Удаление записи (по индексу)\n"
			<< " 12. Изменение существующей записи\n"
			<< " 13. Отобразить актуальный список\n"
            << " 0. Завершить работу\n"
            << " Введите номер: ";
        std::cin >> choice;

        Medical_Record temp{};

        switch (choice) {
        case 1: sort_by_fio(records); break;
        case 2: std::sort(records.begin(), records.end(), [](const Medical_Record& a, const Medical_Record& b) {return a.birth_year < b.birth_year;}); break;
        case 3: sort_by_address(records); break;
        case 4: std::sort(records.begin(), records.end(), [](const Medical_Record& a, const Medical_Record& b) {return a.illness < b.illness;}); break;
        case 5: sort_by_date(records); break;
        case 6: hand_enter(temp); records.push_back(temp); std::cout << "\nДобавленная строка: \n"; table_sick_man(temp); break;
        case 7: hand_enter(temp); records.insert(records.begin(), temp); std::cout << "\nДобавленная строка: \n"; table_sick_man(temp);  break;
        case 8: {
            int index{};
            std::cout << "\nВведите индекс в который хотите добавить запись (1-" << records.size() << "): ";
            std::cin >> index;
            while (index < 1 || index > records.size()) {
                std::cout << "\nВведён неккоретный индекс. Попробуйте снова: ";
                std::cin >> index;
            }
            hand_enter(temp);
            records.insert(records.begin() + index, temp);
            std::cout << "\nДобавленная строка: \n";
            table_sick_man(temp);
            break;
        }
		case 9: std::cout << "\nУдаление записи:\n"; table_sick_man(records[records.size() - 1]); records.pop_back(); break;
		case 10: std::cout << "\nУдаление записи:\n"; table_sick_man(records[0]); records.erase(records.begin()); break;
		case 11: {
			int index{};
			std::cout << "\nВведите индекс записи для удаления (1-" << records.size() << "): ";
			std::cin >> index;
            while (index < 1 || index > records.size()) {
                std::cout << "\nВведён неккоретный индекс. Попробуйте снова: ";
                std::cin >> index;
            }
            std::cout << "\nУдаление записи:\n";
			table_sick_man(records[index - 1]);
            records.erase(records.begin() + index);
			break;
		}
        case 12: {
            int index{};
            std::cout << "\nВведите индекс записи для изменения (1-" << records.size() << "): ";
            std::cin >> index;
            while (index < 1 || index > records.size()) {
                std::cout << "\nВведён неккоретный индекс. Попробуйте снова: ";
                std::cin >> index;
            }
            std::cout << "\nИзменение записи:\n";
            table_sick_man(records[index - 1]);
            change_record(records[index - 1]);
            break;
        }
		case 13: std::cout << "\n=== АКТУАЛЬНЫЙ СПИСОК (БЕЗ СОРТИРОВКИ) ===\n"; up_table(); {
            for (int i{ 0 }; i < records.size(); ++i) {
                table_sick_man(records[i]);
            }
            break;
		}
        case 0: std::cout << "\nРабота программы завершена\n"; return 0;
        default:
            std::cerr << "[Ошибка] Неверный выбор!\n";
            return 1;
        }
    } while (choice == 6 || choice == 7 || choice == 8 || choice == 9 || choice == 10 || choice == 11 || choice == 12 || choice == 13);

	std::cout << "\n\n=== ОТСОРТИРОВАННЫЙ СПИСОК ===\n";
    up_table();
	for (int i{ 0 }; i < records.size(); ++i) {
		table_sick_man(records[i]);
	}

	int count{ 0 };

	for (int i{ 0 }; i < records.size(); ++i) {
		if (to_lower(records[i].illness) == "диабет") {
			++count;
		}
	}

	std::cout << "\n\nКоличество больых диабетом: " << count << " чел.";

	std::cout << "\n\n=== СПИСОК БОЛЬНЫХ ДИАБЕТОМ, НЕ ПОСЕЩАВШИХ ПОЛИКЛИНИКУ БОЛЕЕ 3х МЕСЯЦЕВ ===\n";
    up_table();
	for (int i{ 0 }; i < records.size(); ++i) {
		if (to_lower(records[i].illness) == "диабет" && over_3_months(records[i].date)) {
			table_sick_man(records[i]);
		}
	}
    return 0;
}