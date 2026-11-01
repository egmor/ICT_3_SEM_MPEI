/* Вариант 26: сведения о пациентах поликлиники. Определить количество больных диабетом
   и вывести сведения о больных диабетом, не посещавших врача более трёх месяцев.
   Данные читаются из текстового файла (ANSI / Windows-1251), проверяются, выводятся таблицей,
   сортируются и обрабатываются через меню. */

using System.Text;
using System.Text.RegularExpressions;

var today = new DateTime(2026, 9, 28);   // «текущая» дата для задания
Console.OutputEncoding = Console.InputEncoding = Encoding.UTF8;

string[] files = { "patients.txt", "empty_file_test.txt", "uncorrect_entry_file_test.txt", "file_with_DiAbEt.txt" };
Console.Write(Menu.Files + Menu.Ask);
int fileChoice = ReadInt();
if (fileChoice < 1 || fileChoice > 4)
{
    Console.Error.WriteLine("[Ошибка] Неверный выбор файла! Завершение работы программы");
    return 2;
}

Console.WriteLine("\n1. Чтение данных из файла...");
var records = LoadFile(files[fileChoice - 1]);
if (records.Count == 0)
{
    Console.Error.WriteLine("Файл пуст! Программа завершает свою работу");
    return 2;
}

Console.WriteLine("\n=== ИЗНАЧАЛЬНЫЙ СПИСОК ===");
PrintTable(records);

int choice;
do
{
    Console.Write("\n" + Menu.Main + Menu.Ask);
    choice = ReadInt();

    switch (choice)
    {
        case 1:
            records = records.OrderBy(r => (r.Snl.Surname, r.Snl.Name, r.Snl.LastName)).ToList();
            Console.WriteLine("\n=== СПИСОК, ОТСОРТИРОВАННЫЙ ПО ФИО ===");
            PrintTable(records);
            break;
        case 2:
            records = records.OrderBy(r => r.BirthYear).ToList();
            Console.WriteLine("\n=== СПИСОК, ОТСОРТИРОВАННЫЙ ПО ГОДУ РОЖДЕНИЯ ===");
            PrintTable(records);
            break;
        case 3:
            records = records.OrderBy(r => (r.Address.City, r.Address.District, r.Address.Street, r.Address.Building, r.Address.Apartment)).ToList();
            Console.WriteLine("\n=== СПИСОК, ОТСОРТИРОВАННЫЙ ПО АДРЕСУ ===");
            PrintTable(records);
            break;
        case 4:
            records = records.OrderBy(r => r.Illness).ToList();
            Console.WriteLine("\n=== СПИСОК, ОТСОРТИРОВАННЫЙ ПО ЗАБОЛЕВАНИЮ ===");
            PrintTable(records);
            break;
        case 5:
            records = records.OrderBy(r => (r.Date.Year, r.Date.Month, r.Date.Day)).ToList();
            Console.WriteLine("\n=== СПИСОК, ОТСОРТИРОВАННЫЙ ПО ДАТЕ ПОСЛЕДНЕГО ПОСЕЩЕНИЯ ===");    
            PrintTable(records);
            break;

        case 6 or 7 or 8:   // в конец / в начало / по индексу (новая запись встанет на позицию idx)
            {
                int idx = choice == 6 ? records.Count : choice == 7 ? 0 : ReadIndex("для вставки", records.Count + 1) - 1;
                var rec = new MedicalRecord();
                Fill(rec, 6);
                records.Insert(idx, rec);
                Console.WriteLine("\nДобавленная строка:");
                PrintRecord(rec);
                break;
            }

        case >= 9 and <= 12 when records.Count == 0:
            Console.Error.WriteLine("\nСписок пуст.");
            break;

        case 9 or 10 or 11:   // конец / начало / по индексу
            {
                int idx = choice == 9 ? records.Count - 1 : choice == 10 ? 0 : ReadIndex("удаляемой записи", records.Count) - 1;
                Console.WriteLine("\nУдаление записи:");
                PrintRecord(records[idx]);
                records.RemoveAt(idx);
                break;
            }

        case 12:
            {
                var target = records[ReadIndex("изменяемой записи", records.Count) - 1];
                Console.WriteLine("\nИзменение записи:");
                PrintRecord(target);
                Console.Write("\n" + Menu.Change + "\nВаш выбор: ");
                int part;
                while ((part = ReadInt()) is < 0 or > 6) Console.Write("Неверный выбор. Попробуйте снова: ");
                Fill(target, part);   // 0 — ничего не менять
                if (part != 0) { Console.WriteLine("\nИзменённая строка:"); PrintRecord(target); }
                break;
            }

        case 13:
            Console.WriteLine("\nОсновной функционал");
            break;

        case 0:
            Console.WriteLine("\nРабота программы завершена");
            return 0;

        default:
            Console.Error.WriteLine("[Ошибка] Неверный выбор!");
            return 1;
    }
} while (choice != 0 && choice != 13);

Console.Write($"\n\nКоличество больных диабетом: {records.Count(IsDiabetes)} чел.");

Console.WriteLine("\n\n=== СПИСОК БОЛЬНЫХ ДИАБЕТОМ, НЕ ПОСЕЩАВШИХ ПОЛИКЛИНИКУ БОЛЕЕ 3х МЕСЯЦЕВ ===");
PrintTable(records.Where(r => IsDiabetes(r) && new DateTime(r.Date.Year, r.Date.Month, r.Date.Day).AddMonths(3) < today));
return 0;


// ===================== Проверка данных =====================

bool IsDiabetes(MedicalRecord r) => r.Illness.Equals("диабет", StringComparison.OrdinalIgnoreCase);

bool CorrectName(Patient p) =>
    p.Name.Length is >= 2 and <= 10 && p.Surname.Length is >= 2 and <= 10 && p.LastName.Length is >= 5 and <= 15;

// Ведущее число в строке ("12а" -> 12), как std::stoi; нет цифр — -1
int LeadingNum(string s) => int.TryParse(Regex.Match(s, @"^\d+").Value, out int n) ? n : -1;

bool CorrectAddress(Address a) =>
    a.City.Length is >= 2 and <= 15 && a.District.Length is >= 2 and <= 10 && a.Street.Length is >= 2 and <= 15 &&
    LeadingNum(a.Building) is >= 1 and <= 150 && LeadingNum(a.Apartment) is >= 1 and <= 1000;

// DaysInMonth сам учитывает 28/29/30/31 дней и високосные годы
bool CorrectDate(MedicalRecord r) =>
    r.Date.Year is >= 2000 and <= 2026 && r.Date.Month is >= 1 and <= 12 &&
    r.Date.Day >= 1 && r.Date.Day <= DateTime.DaysInMonth(r.Date.Year, r.Date.Month) &&
    r.Date.Year - r.BirthYear >= 18;


// ===================== Ввод =====================

string ReadLine() => Console.ReadLine() ?? throw new EndOfStreamException("Ввод завершён");

string[] Words(string s) => s.Split((char[]?)null, StringSplitOptions.RemoveEmptyEntries);

int Num(string s) => int.TryParse(s, out int v) ? v : -1;   // не число -> -1 (не пройдёт проверки)

int ReadInt() => Num(ReadLine());

// Строка из ровно n слов; иначе просим повторить
string[] ReadWords(int n)
{
    string[] w;
    while ((w = Words(ReadLine())).Length != n) Console.Write($"Нужно ввести слов: {n}. Попробуйте снова: ");
    return w;
}

int ReadIndex(string what, int max)
{
    Console.Write($"\nВведите индекс {what} (1-{max}): ");
    int i;
    while ((i = ReadInt()) < 1 || i > max) Console.Write("Некорректный индекс. Попробуйте снова: ");
    return i;
}

// Выводит приглашение, читает значение и повторяет, пока оно не пройдёт проверку
void Enter(string prompt, Action read, Func<bool> ok)
{
    Console.Write(prompt);
    read();
    while (!ok())
    {
        Console.Write("Некорректный ввод. Введите ещё раз: ");
        read();
    }
}

// Ввод полей записи: 1 ФИО, 2 год рождения, 3 адрес, 4 болезнь, 5 дата, 6 — все сразу
void Fill(MedicalRecord r, int part)
{
    if (part is 1 or 6)
        Enter("Введите ФИО (фамилия имя отчество): ",
            () => { var w = ReadWords(3); (r.Snl.Surname, r.Snl.Name, r.Snl.LastName) = (w[0], w[1], w[2]); },
            () => CorrectName(r.Snl));

    if (part is 2 or 6)
        Enter("Введите год рождения (совершеннолетний, но моложе 100 лет): ",
            () => r.BirthYear = Num(ReadLine()),
            () => today.Year - r.BirthYear is >= 18 and < 100);

    if (part is 3 or 6)
        Enter("Введите адрес (город район улица дом квартира): ",
            () => { var w = ReadWords(5); var a = r.Address; (a.City, a.District, a.Street, a.Building, a.Apartment) = (w[0], w[1], w[2], w[3], w[4]); },
            () => CorrectAddress(r.Address));

    if (part is 4 or 6)
    {
        Console.Write("Введите болезнь: ");
        r.Illness = ReadWords(1)[0];
    }

    if (part is 5 or 6)
        Enter("Введите дату последнего посещения (дд мм гггг; не раньше, чем через 18 лет после рождения): ",
            () => { var n = ReadWords(3).Select(Num).ToArray(); (r.Date.Day, r.Date.Month, r.Date.Year) = (n[0], n[1], n[2]); },
            () => CorrectDate(r));
}

// Одна запись в файле = 13 слов (порядок как в исходной программе: имя, фамилия, отчество, ...)
List<MedicalRecord> LoadFile(string file)
{
    var list = new List<MedicalRecord>();
    if (!File.Exists(file))
    {
        Console.Error.WriteLine($"Ошибка открытия файла: {file}");
        return list;
    }

    string text = File.ReadAllText(file, CodePagesEncodingProvider.Instance.GetEncoding(1251)!);   // файлы в ANSI
    foreach (var w in Words(text).Chunk(13))
    {
        if (w.Length < 13) break;
        var rec = new MedicalRecord
        {
            Snl = new() { Name = w[0], Surname = w[1], LastName = w[2] },
            Address = new() { City = w[3], District = w[4], Street = w[5], Building = w[6], Apartment = w[7] },
            Date = new() { Day = Num(w[8]), Month = Num(w[9]), Year = Num(w[10]) },
            BirthYear = Num(w[11]),
            Illness = w[12]
        };
        if (CorrectDate(rec) && CorrectAddress(rec.Address) && CorrectName(rec.Snl)) list.Add(rec);
    }
    return list;
}


// ===================== Вывод таблицы =====================

void PrintRow(params string[] cells)
{
    int[] width = { 18, 16, 20, 6, 52, 25, 11 };
    // PadLeft + PadRight = центрирование как в std::format("{:^N}")
    Console.WriteLine("|" + string.Join("|", cells.Select((s, i) => s.PadLeft((width[i] + s.Length) / 2).PadRight(width[i]))) + "|");
}

void PrintRecord(MedicalRecord r) => PrintRow(
    r.Snl.Surname, r.Snl.Name, r.Snl.LastName, r.BirthYear.ToString(),
    $"{r.Address.City}, {r.Address.District}, {r.Address.Street}, {r.Address.Building}, {r.Address.Apartment}",
    r.Illness, $"{r.Date.Day:D2}.{r.Date.Month:D2}.{r.Date.Year}");

void PrintTable(IEnumerable<MedicalRecord> list)
{
    PrintRow("Фамилия", "Имя", "Отчество", "Год", "Адрес", "Основное заболевание", "Дата п.п.");
    Console.WriteLine(new string('-', 156));
    foreach (var r in list) PrintRecord(r);
}


// ===================== Типы =====================

class Patient { public string Name = "", Surname = "", LastName = ""; }
class Address { public string City = "", District = "", Street = "", Building = "", Apartment = ""; }
class DateLastVisit { public int Day, Month, Year; }
class MedicalRecord
{
    public Patient Snl = new();
    public Address Address = new();
    public DateLastVisit Date = new();
    public int BirthYear;
    public string Illness = "";
}

static class Menu
{
    public const string Ask = "\n Введите номер: ";

    public const string Files = """
        Выберите вариант входного файла:
         1. patients.txt - файл с 12 корректными записями
         2. empty_file_test.txt - пустой файл для тестирования
         3. uncorrect_entry_file_test.txt - файл с 14 некорректными записями
         4. file_with_DiAbEt.txt - файл с 8 записями о диабете в различных регистрах
        """;

    public const string Main = """
        Выберите вариант работы программы:
         1. Сортировка по ФИО
         2. Сортировка по году рождения
         3. Сортировка по адресу
         4. Сортировка по заболеванию
         5. Сортировка по дате посещения
         6. Ручной ввод данных в конец
         7. Ручной ввод данных в начало
         8. Ручной ввод данных по индексу
         9. Удаление записи (конец списка)
         10. Удаление записи (начало списка)
         11. Удаление записи (по индексу)
         12. Изменение существующей записи
         13. Основной функционал (подсчёт диабетиков и вывод списка диабетиков, не посещавших поликлинику более 3х месяцев)
         0. Завершить работу
        """;

    public const string Change = """
        Выберите параметр который хотите изменить:
        1. ФИО
        2. Год рождения
        3. Адрес проживания
        4. Болезнь
        5. Дата последнего посещения
        6. Все параметры
        0. Ничего
        """;
}