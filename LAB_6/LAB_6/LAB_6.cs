using System.Text;

// ===================== Типы =====================

struct Patient { public string Name = "", Surname = "", LastName = ""; public Patient() { } }
struct Address { public string City = "", District = "", Street = "", Building = "", Apartment = ""; public Address() { } }
struct DateLastVisit { public int Day, Month, Year; }
struct MedicalRecord
{
    public Patient Snl = new();
    public Address Address = new();
    public DateLastVisit Date = new();
    public int BirthYear;
    public string Illness = "";
    public double IBW;
    public double Hemoglobin;
    public MedicalRecord() { }
}

static class Menu
{
    public const string Ask = "\n Введите номер: ";

    public const string Files = """
        Выберите вариант входного файла:
         1. patients.txt - файл с 13 корректными записями
         2. empty_file_test.txt - пустой файл для тестирования
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
         13. Вывести актуальную таблицу
         14. Дополнительно: Вывести список больных с указанием степени заболевания диабетом
         15. Основной функционал
         0. Завершить работу
        """;

    public const string Change = """
        Выберите параметр который хотите изменить:
        1. ФИО
        2. Год рождения
        3. Адрес проживания
        4. Болезнь
        5. Дата последнего посещения
        6. ИМТ
        7. Гемоглобин
        8. Все параметры
        0. Ничего
        """;
}



class Program
{
    // «Текущая» дата для задания (раньше была локальной переменной верхнего уровня)
    static readonly DateTime Today = new DateTime(2026, 9, 28);

    private static ReadOnlySpan<string> TypesDiabet =>
    new string[]
    {
        "Норма",
        "Преддиабет",
        "Лёгкая степень диабета",
        "Средняя степень диабета",
        "Тяжёлая степень диабета (с ожирением)",
        "Тяжёлая степень диабета (с истощением)"
    };
    static int Main()
    {
        Console.OutputEncoding = Console.InputEncoding = Encoding.UTF8;

        string[] files = { "patients.txt", "empty_file_test.txt", "uncorrect_entry_file_test.txt", "file_with_DiAbEt.txt", "patients_diabetes_types.txt" };
        Console.Write(Menu.Files + Menu.Ask);
        int fileChoice = ReadInt();
        if (fileChoice < 1 || fileChoice > 5)
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

            // Удалять и изменять нечего, если список пуст
            if (InRange(choice, 9, 12) && records.Count == 0)
            {
                Console.Error.WriteLine("\nСписок пуст.");
                continue;
            }

            switch (choice)
            {
                case 1:
                    records = records.OrderBy(r => (r.Snl.Surname, r.Snl.Name, r.Snl.LastName)).ToList();
                    Console.WriteLine("\n=== ОТСОРТИРОВАННЫЙ СПИСОК (по ФИО) ===");
                    PrintTable(records);
                    break;
                case 2:
                    records = records.OrderBy(r => r.BirthYear).ToList();
                    Console.WriteLine("\n=== ОТСОРТИРОВАННЫЙ СПИСОК (по году рождения) ===");
                    PrintTable(records);
                    break;
                case 3:
                    records = records.OrderBy(r => (r.Address.City, r.Address.District, r.Address.Street, r.Address.Building, r.Address.Apartment)).ToList();
                    Console.WriteLine("\n=== ОТСОРТИРОВАННЫЙ СПИСОК (по адресу) ===");
                    PrintTable(records);
                    break;
                case 4:
                    records = records.OrderBy(r => r.Illness).ToList();
                    Console.WriteLine("\n=== ОТСОРТИРОВАННЫЙ СПИСОК (по заболеванию) ===");
                    PrintTable(records);
                    break;
                case 5:
                    records = records.OrderBy(r => (r.Date.Year, r.Date.Month, r.Date.Day)).ToList();
                    Console.WriteLine("\n=== ОТСОРТИРОВАННЫЙ СПИСОК (по дате посещения) ===");
                    PrintTable(records);
                    break;

                case 6:   // в конец / в начало / по индексу (новая запись встанет на позицию idx)
                case 7:
                case 8:
                    {
                        int idx = choice == 6 ? records.Count : choice == 7 ? 0 : ReadIndex("для вставки", records.Count + 1) - 1;
                        var rec = Fill(new MedicalRecord(), 8);
                        records.Insert(idx, rec);
                        Console.WriteLine("\nДобавленная строка:");
                        PrintRecord(rec);
                        break;
                    }

                case 9:   // конец / начало / по индексу
                case 10:
                case 11:
                    {
                        int idx = choice == 9 ? records.Count - 1 : choice == 10 ? 0 : ReadIndex("удаляемой записи", records.Count) - 1;
                        Console.WriteLine("\nУдаление записи:");
                        PrintRecord(records[idx]);
                        records.RemoveAt(idx);
                        break;
                    }

                case 12:
                    {
                        int idx = ReadIndex("изменяемой записи", records.Count) - 1;
                        var target = records[idx];   // копия структуры
                        Console.WriteLine("\nИзменение записи:");
                        PrintRecord(target);
                        Console.Write("\n" + Menu.Change + "\nВаш выбор: ");
                        int part;
                        while ((part = ReadInt()) < 0 || part > 8) Console.Write("Неверный выбор. Попробуйте снова: ");
                        target = Fill(target, part);   // 0 — ничего не менять
                        records[idx] = target;         // записываем изменённую копию обратно
                        if (part != 0) { Console.WriteLine("\nИзменённая строка:"); PrintRecord(target); }
                        break;
                    }

                case 13:
                    Console.WriteLine("\n=== АКТУАЛЬНЫЙ СПИСОК ===");
                    PrintTable(records);
                    break;

                case 14:
                    Console.WriteLine("\n=== СПИСОК БОЛЬНЫХ С УКАЗАНИЕМ СТЕПЕНИ ЗАБОЛЕВАНИЯ ДИАБЕТОМ ===");
                    PrintTableDiabetType(records);
                    break;

                case 15:
                    Console.WriteLine("\nОсновной функционал");
                    break;

                case 0:
                    Console.WriteLine("\nРабота программы завершена");
                    return 0;

                default:
                    Console.Error.WriteLine("\n[Ошибка] Неверный выбор!\nПовторите попытку ввода:");
                    break;
            }
        } while (choice != 0 && choice != 15);

        Console.Write($"\n\nКоличество больных диабетом: {records.Count(IsDiabetes)} чел.");

        Console.WriteLine("\n\n=== СПИСОК БОЛЬНЫХ ДИАБЕТОМ, НЕ ПОСЕЩАВШИХ ПОЛИКЛИНИКУ БОЛЕЕ 3х МЕСЯЦЕВ ===");
        PrintTable(records.Where(r => IsDiabetes(r) && new DateTime(r.Date.Year, r.Date.Month, r.Date.Day).AddMonths(3) < Today));
        return 0;
    }


    // ===================== Проверка данных =====================

    static bool InRange(int value, int lo, int hi) => value >= lo && value <= hi;

    static bool IsDiabetes(MedicalRecord r) => r.Illness.Equals("диабет", StringComparison.OrdinalIgnoreCase);

    static bool CorrectName(Patient p) =>
        InRange(p.Name.Length, 2, 10) && InRange(p.Surname.Length, 2, 10) && InRange(p.LastName.Length, 5, 15);

    static int LeadingNum(string s)
    {
        int i = 0;
        while (i < s.Length && s[i] >= '0' && s[i] <= '9') i++;   // сколько цифр в начале строки
        return i > 0 && int.TryParse(s.Substring(0, i), out int n) ? n : -1;
    }

    static bool CorrectAddress(Address a) =>
        InRange(a.City.Length, 2, 15) && InRange(a.District.Length, 2, 10) && InRange(a.Street.Length, 2, 15) &&
        InRange(LeadingNum(a.Building), 1, 150) && InRange(LeadingNum(a.Apartment), 1, 1000);

    static bool CorrectDate(MedicalRecord r) =>
        InRange(r.Date.Year, 2000, 2026) && InRange(r.Date.Month, 1, 12) &&
        r.Date.Day >= 1 && r.Date.Day <= DateTime.DaysInMonth(r.Date.Year, r.Date.Month) &&
        r.Date.Year - r.BirthYear >= 18;

    static bool CorrectHemoglobin(MedicalRecord r) => r.Hemoglobin >= 3.0 && r.Hemoglobin <= 20.0;

    static bool CorrectIBW(MedicalRecord r) => r.IBW >= 6.0 && r.IBW <= 100.0;


    // ===================== Ввод =====================

    static string ReadLine() => Console.ReadLine() ?? throw new EndOfStreamException("Ввод завершён");

    static string[] Words(string s) => s.Split((char[]?)null, StringSplitOptions.RemoveEmptyEntries);

    static int Num(string s) => int.TryParse(s, out int v) ? v : -1;   // не число -> -1 (не пройдёт проверки)

    static int ReadInt() => Num(ReadLine());

    // Строка из ровно n слов; иначе просим повторить
    static string[] ReadWords(int n)
    {
        string[] w;
        while ((w = Words(ReadLine())).Length != n) Console.Write($"Нужно ввести слов: {n}. Попробуйте снова: ");
        return w;
    }

    static int ReadIndex(string what, int max)
    {
        Console.Write($"\nВведите индекс {what} (1-{max}): ");
        int i;
        while ((i = ReadInt()) < 1 || i > max) Console.Write("Некорректный индекс. Попробуйте снова: ");
        return i;
    }

    // Выводит приглашение, читает значение и повторяет, пока оно не пройдёт проверку
    static void Enter(string prompt, Action read, Func<bool> ok)
    {
        Console.Write(prompt);
        read();
        while (!ok())
        {
            Console.Write("Некорректный ввод. Введите ещё раз: ");
            read();
        }
    }

    // Ввод полей записи: 1 ФИО, 2 год рождения, 3 адрес, 4 болезнь, 5 дата, 6 ИМТ, 7 гемоглобин, 8 — все сразу.
    static MedicalRecord Fill(MedicalRecord r, int part)
    {
        if (part == 1 || part == 8)
            Enter("Введите ФИО (фамилия имя отчество): ",
                () => { var w = ReadWords(3); (r.Snl.Surname, r.Snl.Name, r.Snl.LastName) = (w[0], w[1], w[2]); },
                () => CorrectName(r.Snl));

        if (part == 2 || part == 8)
            Enter("Введите год рождения (совершеннолетний, но моложе 100 лет): ",
                () => r.BirthYear = Num(ReadLine()),
                () => InRange(Today.Year - r.BirthYear, 18, 99));

        if (part == 3 || part == 8)
            Enter("Введите адрес (город район улица дом квартира): ",
                () => { var w = ReadWords(5); (r.Address.City, r.Address.District, r.Address.Street, r.Address.Building, r.Address.Apartment) = (w[0], w[1], w[2], w[3], w[4]); },
                () => CorrectAddress(r.Address));

        if (part == 4 || part == 8)
        {
            Console.Write("Введите болезнь: ");
            r.Illness = ReadWords(1)[0];
        }

        if (part == 5 || part == 8)
            Enter("Введите дату последнего посещения (дд мм гггг; не раньше, чем через 18 лет после рождения): ",
                () => { var n = ReadWords(3).Select(Num).ToArray(); (r.Date.Day, r.Date.Month, r.Date.Year) = (n[0], n[1], n[2]); },
                () => CorrectDate(r));

        if (part == 6 || part == 8)
            Enter("Введите ИМТ (6-100): ",
                () => r.IBW = double.Parse(ReadLine()),
                () => CorrectIBW(r));

        if (part == 7 || part == 8)
            Enter("Введите гемоглобин (3.0-20.0): ",
                () => r.Hemoglobin = double.Parse(ReadLine()),
                () => CorrectHemoglobin(r));

        return r;
    }

    static List<MedicalRecord> LoadFile(string file)
    {
        var list = new List<MedicalRecord>();
        if (!File.Exists(file))
        {
            Console.Error.WriteLine($"Ошибка открытия файла: {file}");
            return list;
        }

        string text = File.ReadAllText(file, CodePagesEncodingProvider.Instance.GetEncoding(1251)!);   // файлы в ANSI
        foreach (var w in Words(text).Chunk(15))
        {
            if (w.Length < 15) break;
            var rec = new MedicalRecord
            {
                Snl = new() { Name = w[0], Surname = w[1], LastName = w[2] },
                Address = new() { City = w[3], District = w[4], Street = w[5], Building = w[6], Apartment = w[7] },
                Date = new() { Day = Num(w[8]), Month = Num(w[9]), Year = Num(w[10]) },
                BirthYear = Num(w[11]),
                Illness = w[12],
                IBW = double.Parse(w[13]),
                Hemoglobin = double.Parse(w[14])
            };
            if (CorrectDate(rec) && CorrectAddress(rec.Address) && CorrectName(rec.Snl) && CorrectIBW(rec) && CorrectHemoglobin(rec)) list.Add(rec);
        }
        return list;
    }


    // ===================== Вывод таблицы =====================

    static void PrintRow(params string[] cells) =>
        PrintRow(new int[] { 18, 16, 20, 6, 52, 25, 11 }, cells);

    static void PrintRow(int[] width, params string[] cells)
    {
        Console.WriteLine("|" + string.Join("|", cells.Select((s, i) =>
            s.PadLeft((width[i] + s.Length) / 2).PadRight(width[i]))) + "|");
    }

    static void PrintRecord(MedicalRecord r) => PrintRow(
        r.Snl.Surname, r.Snl.Name, r.Snl.LastName, r.BirthYear.ToString(),
        $"{r.Address.City}, {r.Address.District}, {r.Address.Street}, {r.Address.Building}, {r.Address.Apartment}",
        r.Illness, $"{r.Date.Day:D2}.{r.Date.Month:D2}.{r.Date.Year}");

    static void PrintTable(IEnumerable<MedicalRecord> list)
    {
        PrintRow("Фамилия", "Имя", "Отчество", "Год", "Адрес", "Основное заболевание", "Дата п.п.");
        Console.WriteLine(new string('-', 156));
        foreach (var r in list) PrintRecord(r);
    }

    static void PrintTableDiabetType(IEnumerable<MedicalRecord> list)
    {
        int[] width = { 18, 16, 20, 6, 10, 13, 48 };

        PrintRow(width, "Фамилия", "Имя", "Отчество", "Год",
                 "ИМТ", "Гемоглобин", "Тип диабета");

        Console.WriteLine(new string('-', width.Sum() + width.Length + 1));

        foreach (var r in list)
        {
            PrintRow(
                width,
                r.Snl.Surname,
                r.Snl.Name,
                r.Snl.LastName,
                r.BirthYear.ToString(),
                r.IBW.ToString("0.0"),
                r.Hemoglobin.ToString("0.0"),
                TypesDiabet[DiabetesType(r)]
            );
        }
    }

    //вычисление типа диабета и степени
    static int DiabetesType(MedicalRecord r)
    {
        if (r.Hemoglobin >= 5.7 && r.Hemoglobin <= 6.4 && (r.IBW > 25.0 && r.IBW <= 30.0)) return 1;   // преддиабет
        else if (r.Hemoglobin >= 6.5 && r.Hemoglobin <= 6.9 && (r.IBW > 18.5 && r.IBW <= 30.0)) return 2;   // лёгкая степень диабета
        else if (r.Hemoglobin >= 7.0 && r.Hemoglobin <= 8.0 && (r.IBW > 30.0 && r.IBW <= 40.0)) return 3;   // средняя степень диабета
        else if (r.Hemoglobin > 8.0 && r.IBW >= 40.0) return 4;   // тяжёлая степень диабета (с ожирением)
        else if (r.Hemoglobin >= 8.0 && r.IBW <= 18.5) return 5;   // тяжёлая степень диабета (с истощением)
        else return 0;   // норма при любых других значениях гемоглобина и ИМТ
    }
}
