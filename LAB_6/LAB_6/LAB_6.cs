using System.Text;
using System.Globalization;

struct Patient
{
    public string Name = "", Surname = "", LastName = "";
    public Patient() { }
}

struct Address
{
    public string City = "", District = "", Street = "", Building = "", Apartment = "";
    public Address() { }
}

struct DateLastVisit
{
    public int Day, Month, Year;
}

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
    public const string Ask = "\nВведите номер: ";

    public const string Files = """
        Выберите вариант входного файла:
         1. patients.txt - основной набор данных
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
         14. Дополнительно: определить риск/степень диабета
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
    // Дата фиксирована для воспроизводимости результатов лабораторной работы.
    static readonly DateTime Today = new DateTime(2026, 11, 9);
    static readonly CultureInfo NumberCulture = CultureInfo.InvariantCulture;

    static readonly string[] TypesDiabet =
    {
        "Норма",
        "Преддиабет (риск заболевания)",
        "Лёгкая степень диабета",
        "Средняя степень диабета",
        "Тяжёлая степень диабета (с ожирением)",
        "Тяжёлая степень диабета (с истощением)",
        "Степень не определена по заданным критериям"
    };

    static int Main()
    {
        Console.OutputEncoding = Encoding.UTF8;
        Console.InputEncoding = Encoding.UTF8;
        Encoding.RegisterProvider(CodePagesEncodingProvider.Instance);

        string[] files =
        {
            "patients.txt", "empty_file_test.txt"
        };

        Console.Write(Menu.Files + Menu.Ask);
        int fileChoice = ReadInt();
        if (fileChoice < 1 || fileChoice > files.Length)
        {
            Console.Error.WriteLine("[Ошибка] Неверный выбор файла! Завершение работы программы.");
            return 2;
        }

        Console.WriteLine("\nЧтение данных из файла...");
        List<MedicalRecord> records = LoadFile(files[fileChoice - 1]);
        if (records.Count == 0)
        {
            Console.Error.WriteLine("Файл не содержит корректных записей. Программа завершает работу.");
            return 2;
        }

        Console.WriteLine("\n=== ИЗНАЧАЛЬНЫЙ СПИСОК ===");
        PrintTable(records);

        int choice;
        do
        {
            Console.Write("\n" + Menu.Main + Menu.Ask);
            choice = ReadInt();

            if (InRange(choice, 9, 12) && records.Count == 0)
            {
                Console.Error.WriteLine("\nСписок пуст.");
                continue;
            }

            switch (choice)
            {
                case 1:
                    records = records.OrderBy(r => r.Snl.Surname)
                        .ThenBy(r => r.Snl.Name).ThenBy(r => r.Snl.LastName).ToList();
                    Console.WriteLine("\n=== ОТСОРТИРОВАННЫЙ СПИСОК (по ФИО) ===");
                    PrintTable(records);
                    break;
                case 2:
                    records = records.OrderBy(r => r.BirthYear).ToList();
                    Console.WriteLine("\n=== ОТСОРТИРОВАННЫЙ СПИСОК (по году рождения) ===");
                    PrintTable(records);
                    break;
                case 3:
                    records = records.OrderBy(r => r.Address.City).ThenBy(r => r.Address.District)
                        .ThenBy(r => r.Address.Street).ThenBy(r => r.Address.Building)
                        .ThenBy(r => r.Address.Apartment).ToList();
                    Console.WriteLine("\n=== ОТСОРТИРОВАННЫЙ СПИСОК (по адресу) ===");
                    PrintTable(records);
                    break;
                case 4:
                    records = records.OrderBy(r => r.Illness).ToList();
                    Console.WriteLine("\n=== ОТСОРТИРОВАННЫЙ СПИСОК (по заболеванию) ===");
                    PrintTable(records);
                    break;
                case 5:
                    records = records.OrderBy(r => r.Date.Year).ThenBy(r => r.Date.Month)
                        .ThenBy(r => r.Date.Day).ToList();
                    Console.WriteLine("\n=== ОТСОРТИРОВАННЫЙ СПИСОК (по дате посещения) ===");
                    PrintTable(records);
                    break;
                case 6:
                case 7:
                case 8:
                    {
                        int idx = choice == 6 ? records.Count : choice == 7 ? 0 : ReadIndex("для вставки", records.Count + 1) - 1;
                        MedicalRecord rec = Fill(new MedicalRecord(), 8);
                        records.Insert(idx, rec);
                        Console.WriteLine("\nДобавленная строка:");
                        PrintRecord(rec);
                        break;
                    }
                case 9:
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
                        MedicalRecord target = records[idx];
                        Console.WriteLine("\nИзменение записи:");
                        PrintRecord(target);
                        Console.Write("\n" + Menu.Change + "\nВаш выбор: ");
                        int part;
                        while ((part = ReadInt()) < 0 || part > 8)
                            Console.Write("Неверный выбор. Попробуйте снова: ");
                        target = Fill(target, part);
                        records[idx] = target;
                        if (part != 0)
                        {
                            Console.WriteLine("\nИзменённая строка:");
                            PrintRecord(target);
                        }
                        break;
                    }
                case 13:
                    Console.WriteLine("\n=== АКТУАЛЬНЫЙ СПИСОК ===");
                    PrintTable(records);
                    break;
                case 14:
                    Console.WriteLine("\n=== РИСК ДИАБЕТА И СТЕПЕНЬ ЗАБОЛЕВАНИЯ ===");
                    PrintTableDiabetType(records);
                    break;
                case 15:
                    Console.WriteLine("\nОсновной функционал");
                    break;
                case 0:
                    Console.WriteLine("\nРабота программы завершена.");
                    return 0;
                default:
                    Console.Error.WriteLine("\n[Ошибка] Неверный выбор! Повторите ввод.");
                    break;
            }
        } while (choice != 0 && choice != 15);

        Console.WriteLine($"\nКоличество больных диабетом: {records.Count(IsDiabetes)} чел.");
        Console.WriteLine("\n=== БОЛЬНЫЕ ДИАБЕТОМ, НЕ ПОСЕЩАВШИЕ ПОЛИКЛИНИКУ БОЛЕЕ ТРЁХ МЕСЯЦЕВ ===");
        IEnumerable<MedicalRecord> overdue = records.Where(r => IsDiabetes(r) &&
            new DateTime(r.Date.Year, r.Date.Month, r.Date.Day).AddMonths(3) < Today);
        PrintTable(overdue);
        return 0;
    }

    static bool InRange(int value, int min, int max) => value >= min && value <= max;
    static bool IsDiabetes(MedicalRecord r) => r.Illness.Equals("диабет", StringComparison.OrdinalIgnoreCase);
    static bool CorrectName(Patient p) => InRange(p.Name.Length, 2, 10) &&
        InRange(p.Surname.Length, 2, 10) && InRange(p.LastName.Length, 5, 15);

    static int LeadingNum(string value)
    {
        int i = 0;
        while (i < value.Length && char.IsDigit(value[i])) i++;
        return i > 0 && int.TryParse(value.Substring(0, i), out int number) ? number : -1;
    }

    static bool CorrectAddress(Address a) =>
        InRange(a.City.Length, 2, 15) && InRange(a.District.Length, 2, 10) &&
        InRange(a.Street.Length, 2, 15) && InRange(LeadingNum(a.Building), 1, 150) &&
        InRange(LeadingNum(a.Apartment), 1, 1000);

    static bool CorrectDate(MedicalRecord r)
    {
        if (!InRange(r.Date.Year, 2000, Today.Year) || !InRange(r.Date.Month, 1, 12)) return false;
        if (r.Date.Day < 1 || r.Date.Day > DateTime.DaysInMonth(r.Date.Year, r.Date.Month)) return false;
        int ageAtVisit = r.Date.Year - r.BirthYear;
        return InRange(ageAtVisit, 18, 99);
    }

    static bool CorrectHemoglobin(MedicalRecord r) => r.Hemoglobin >= 3.0 && r.Hemoglobin <= 20.0;
    static bool CorrectIBW(MedicalRecord r) => r.IBW >= 6.0 && r.IBW <= 100.0;

    static string ReadLine() => Console.ReadLine() ?? throw new EndOfStreamException("Ввод завершён.");
    static string[] Words(string s) => s.Split((char[]?)null, StringSplitOptions.RemoveEmptyEntries);
    static int Num(string s) => int.TryParse(s, NumberStyles.Integer, CultureInfo.InvariantCulture, out int v) ? v : -1;
    static int ReadInt() => Num(ReadLine());

    static bool TryReadDouble(string value, out double result)
    {
        // Принимаются и десятичная запятая, и точка независимо от системной локали.
        string normalized = value.Trim().Replace(',', '.');
        return double.TryParse(normalized, NumberStyles.Float, NumberCulture, out result) &&
               !double.IsNaN(result) && !double.IsInfinity(result);
    }

    static double ReadDouble()
    {
        while (true)
        {
            string input = ReadLine();
            if (TryReadDouble(input, out double value)) return value;
            Console.Write("Нужно ввести число (дробная часть через запятую или точку). Попробуйте снова: ");
        }
    }

    static string[] ReadWords(int count)
    {
        string[] words;
        while ((words = Words(ReadLine())).Length != count)
            Console.Write($"Нужно ввести слов: {count}. Попробуйте снова: ");
        return words;
    }

    static int ReadIndex(string what, int max)
    {
        Console.Write($"\nВведите индекс {what} (1-{max}): ");
        int index;
        while ((index = ReadInt()) < 1 || index > max)
            Console.Write("Некорректный индекс. Попробуйте снова: ");
        return index;
    }

    static void Enter(string prompt, Action read, Func<bool> valid)
    {
        Console.Write(prompt);
        read();
        while (!valid())
        {
            Console.Write("Некорректный ввод. Введите ещё раз: ");
            read();
        }
    }

    static MedicalRecord Fill(MedicalRecord r, int part)
    {
        if (part == 1 || part == 8)
            Enter("Введите ФИО (фамилия имя отчество): ",
                () => { string[] w = ReadWords(3); (r.Snl.Surname, r.Snl.Name, r.Snl.LastName) = (w[0], w[1], w[2]); },
                () => CorrectName(r.Snl));

        if (part == 2 || part == 8)
            Enter("Введите год рождения (возраст от 18 до 99 лет): ",
                () => r.BirthYear = Num(ReadLine()),
                () => InRange(Today.Year - r.BirthYear, 18, 99));

        if (part == 3 || part == 8)
            Enter("Введите адрес (город район улица дом квартира): ",
                () => { string[] w = ReadWords(5); (r.Address.City, r.Address.District, r.Address.Street, r.Address.Building, r.Address.Apartment) = (w[0], w[1], w[2], w[3], w[4]); },
                () => CorrectAddress(r.Address));

        if (part == 4 || part == 8)
        {
            Console.Write("Введите основное заболевание (одно слово): ");
            r.Illness = ReadWords(1)[0];
        }

        if (part == 5 || part == 8)
            Enter("Введите дату последнего посещения (дд мм гггг): ",
                () => { int[] n = ReadWords(3).Select(Num).ToArray(); (r.Date.Day, r.Date.Month, r.Date.Year) = (n[0], n[1], n[2]); },
                () => CorrectDate(r));

        if (part == 6 || part == 8)
            Enter("Введите ИМТ (6,0-100,0): ", () => r.IBW = ReadDouble(), () => CorrectIBW(r));

        if (part == 7 || part == 8)
            Enter("Введите гемоглобин (3,0-20,0): ", () => r.Hemoglobin = ReadDouble(), () => CorrectHemoglobin(r));

        return r;
    }

    static List<MedicalRecord> LoadFile(string file)
    {
        var records = new List<MedicalRecord>();
        if (!File.Exists(file))
        {
            Console.Error.WriteLine($"Ошибка открытия файла: {file}");
            return records;
        }

        try
        {
            string[] lines = File.ReadAllLines(file, Encoding.GetEncoding(1251));
            int lineNumber = 0;
            foreach (string line in lines)
            {
                lineNumber++;
                if (string.IsNullOrWhiteSpace(line)) continue;
                string[] w = Words(line);
                if (w.Length != 15)
                {
                    Console.Error.WriteLine($"Строка {lineNumber} пропущена: ожидалось 15 полей, получено {w.Length}.");
                    continue;
                }
                if (!TryReadDouble(w[13], out double bmi) || !TryReadDouble(w[14], out double hemoglobin))
                {
                    Console.Error.WriteLine($"Строка {lineNumber} пропущена: ИМТ или гемоглобин не является числом.");
                    continue;
                }

                var record = new MedicalRecord
                {
                    Snl = new Patient { Name = w[0], Surname = w[1], LastName = w[2] },
                    Address = new Address { City = w[3], District = w[4], Street = w[5], Building = w[6], Apartment = w[7] },
                    Date = new DateLastVisit { Day = Num(w[8]), Month = Num(w[9]), Year = Num(w[10]) },
                    BirthYear = Num(w[11]),
                    Illness = w[12],
                    IBW = bmi,
                    Hemoglobin = hemoglobin
                };

                if (CorrectDate(record) && CorrectAddress(record.Address) && CorrectName(record.Snl) &&
                    CorrectIBW(record) && CorrectHemoglobin(record))
                    records.Add(record);
                else
                    Console.Error.WriteLine($"Строка {lineNumber} пропущена: данные не прошли проверку.");
            }
        }
        catch (Exception ex) when (ex is IOException || ex is UnauthorizedAccessException || ex is ArgumentException)
        {
            Console.Error.WriteLine($"Ошибка чтения файла {file}: {ex.Message}");
        }

        Console.WriteLine($"Корректных записей загружено: {records.Count}.");
        return records;
    }

    static void PrintRow(params string[] cells) =>
        PrintRow(new[] { 18, 16, 20, 6, 52, 25, 11 }, cells);

    static void PrintRow(int[] widths, params string[] cells)
    {
        Console.WriteLine("|" + string.Join("|", cells.Select((s, i) =>
            s.PadLeft((widths[i] + s.Length) / 2).PadRight(widths[i]))) + "|");
    }

    static void PrintRecord(MedicalRecord r) => PrintRow(
        r.Snl.Surname, r.Snl.Name, r.Snl.LastName, r.BirthYear.ToString(CultureInfo.InvariantCulture),
        $"{r.Address.City}, {r.Address.District}, {r.Address.Street}, {r.Address.Building}, {r.Address.Apartment}",
        r.Illness, $"{r.Date.Day:D2}.{r.Date.Month:D2}.{r.Date.Year}");

    static void PrintTable(IEnumerable<MedicalRecord> list)
    {
        PrintRow("Фамилия", "Имя", "Отчество", "Год", "Адрес", "Основное заболевание", "Дата п.п.");
        Console.WriteLine(new string('-', 156));
        foreach (MedicalRecord record in list) PrintRecord(record);
    }

    static void PrintTableDiabetType(IEnumerable<MedicalRecord> list)
    {
        int[] widths = { 18, 16, 20, 6, 10, 13, 48 };
        PrintRow(widths, "Фамилия", "Имя", "Отчество", "Год", "ИМТ", "Гемоглобин", "Категория");
        Console.WriteLine(new string('-', widths.Sum() + widths.Length + 1));
        foreach (MedicalRecord r in list)
        {
            PrintRow(widths, r.Snl.Surname, r.Snl.Name, r.Snl.LastName,
                r.BirthYear.ToString(CultureInfo.InvariantCulture),
                r.IBW.ToString("0.0", CultureInfo.GetCultureInfo("ru-RU")),
                r.Hemoglobin.ToString("0.0", CultureInfo.GetCultureInfo("ru-RU")),
                TypesDiabet[DiabetesType(r)]);
        }
    }

    static int DiabetesType(MedicalRecord r)
    {
        if (!IsDiabetes(r))
        {
            if (r.Hemoglobin >= 5.7 && r.Hemoglobin <= 6.4 && r.IBW > 25.0 && r.IBW < 30.0)
                return 1;
            return 0;
        }

        if (r.Hemoglobin >= 6.5 && r.Hemoglobin <= 6.9 && r.IBW > 18.5 && r.IBW < 30.0) return 2;
        if (r.Hemoglobin >= 7.0 && r.Hemoglobin <= 8.0 && r.IBW > 30.0 && r.IBW < 40.0) return 3;
        if (r.Hemoglobin > 8.0 && r.IBW >= 40.0) return 4;
        if (r.Hemoglobin >= 8.0 && r.IBW < 18.5) return 5;
        return 6;
    }
}
