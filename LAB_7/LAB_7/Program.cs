
using Lab7;

internal class Program
{

    public static HDD[] hdds = new HDD[]
    {
        new HDD(512000, 60, 15),           // ~500 ГБ
        new HDD(1024 * 1024, 80, 25),      // 1 ТБ
        new HDD(1024 * 1024, 120, 35),     // 1 ТБ
        new HDD(2048 * 1024, 100, 45),     // 2 ТБ
        new HDD(2048 * 1024, 150, 55),     // 2 ТБ
        new HDD(3072 * 1024, 110, 60),     // 3 ТБ
        new HDD(4096 * 1024, 130, 75),     // 4 ТБ
        new HDD(4096 * 1024, 180, 90),     // 4 ТБ
        new HDD(5120 * 1024, 140, 95),     // 5 ТБ
        new HDD(6144 * 1024, 160, 110),    // 6 ТБ
        new HDD(6144 * 1024, 200, 125),    // 6 ТБ
        new HDD(8192 * 1024, 170, 135),    // 8 ТБ
        new HDD(8192 * 1024, 220, 150),    // 8 ТБ
        new HDD(10240 * 1024, 190, 165),   // 10 ТБ
        new HDD(10240 * 1024, 240, 180),   // 10 ТБ
        new HDD(12288 * 1024, 210, 190),   // 12 ТБ
        new HDD(14336 * 1024, 225, 200),   // 14 ТБ
        new HDD(16384 * 1024, 230, 210),   // 16 ТБ
        new HDD(16384 * 1024, 260, 220),   // 16 ТБ
        new HDD(18432 * 1024, 245, 225),   // 18 ТБ
        new HDD(20480 * 1024, 250, 230),   // 20 ТБ
        new HDD(22528 * 1024, 265, 235),   // 22 ТБ
        new HDD(24576 * 1024, 270, 240),   // 24 ТБ
        new HDD(26624 * 1024, 285, 245),   // 26 ТБ
        new HDD(30720 * 1024, 300, 250)    // 30 ТБ
    };

    public static GraphicsCard[] gpus = new GraphicsCard[]
    {
        new GraphicsCard(4, 60),
        new GraphicsCard(4, 95),
        new GraphicsCard(4, 130),
        new GraphicsCard(6, 160),
        new GraphicsCard(6, 210),
        new GraphicsCard(8, 250),
        new GraphicsCard(8, 310),
        new GraphicsCard(8, 380),
        new GraphicsCard(10, 420),
        new GraphicsCard(10, 490),
        new GraphicsCard(12, 520),
        new GraphicsCard(12, 600),
        new GraphicsCard(12, 680),
        new GraphicsCard(12, 750),
        new GraphicsCard(16, 820),
        new GraphicsCard(16, 950),
        new GraphicsCard(16, 1100),
        new GraphicsCard(16, 1250),
        new GraphicsCard(20, 1350),
        new GraphicsCard(20, 1480),
        new GraphicsCard(24, 1600),
        new GraphicsCard(24, 1720),
        new GraphicsCard(24, 1850),
        new GraphicsCard(24, 1950),
        new GraphicsCard(24, 2000)
    };

    public static (double Size, uint Price)[] monitors = new (double Size, uint Price)[]
    {
        (19.0, 55),
        (19.5, 70),
        (20.0, 85),
        (21.5, 100),
        (22.0, 120),
        (23.0, 140),
        (23.8, 165),
        (24.0, 190),
        (24.5, 230),
        (25.0, 270),
        (27.0, 310),
        (27.0, 420),
        (27.0, 550),
        (28.0, 480),
        (29.0, 350),
        (31.5, 520),
        (32.0, 680),
        (32.0, 890),
        (34.0, 750),
        (34.0, 1050),
        (38.0, 1200),
        (40.0, 1350),
        (42.0, 1500),
        (45.0, 1750),
        (49.0, 1990)
    };


    static void Main()
    {
        Console.WriteLine("========== Computer Class Test ==========");

        Console.WriteLine("\nDefault Computer:");
        Computer computer1 = new Computer();
        computer1.PrintInfo();

        Console.WriteLine("\nCustom Computer:");
        HDD hdd = new HDD(2048 * 1024, 150, 100);
        GraphicsCard gpu = new GraphicsCard(16, 500);
        Computer computer2 = new Computer(hdd.CapacityMB, hdd.DataRateMBps, hdd.Price, gpu.MemoryGB, gpu.Price, "DELL", hdd.Price + gpu.Price + 200);
        computer2.PrintInfo();

        Console.WriteLine("\nWork with setters:");

        int choice;

        do
        {
            Console.WriteLine("\nMenu:" +
                "\n1. Change HDD capacity" +
                "\n2. Change HDD data rate" +
                "\n3. Change HDD price" +
                "\n4. Change GPU memory" +
                "\n5. Change GPU price" +
                "\n6. Change Computer brand" +
                "\n7. Change Computer price" +
                "\n0. Exit");

            choice = int.Parse(Console.ReadLine());
            switch (choice)
            {
                case 1:
                    Console.Write("Enter new HDD capacity (TB): ");
                    uint newCapacity = uint.Parse(Console.ReadLine());
                    computer2.Hdd.CapacityMB = newCapacity * 1024 * 1024;
                    break;
                case 2:
                    Console.Write("Enter new HDD data rate (MB/s): ");
                    uint newDataRate = uint.Parse(Console.ReadLine());
                    computer2.Hdd.DataRateMBps = newDataRate;
                    break;
                case 3:
                    Console.Write("Enter new HDD price ($): ");
                    uint newHDDPrice = uint.Parse(Console.ReadLine());
                    computer2.Hdd.Price = newHDDPrice;
                    break;
                case 4:
                    Console.Write("Enter new GPU memory (GB): ");
                    uint newGPUMemory = uint.Parse(Console.ReadLine());
                    computer2.Gpu.MemoryGB = newGPUMemory;
                    break;
                case 5:
                    Console.Write("Enter new GPU price ($): ");
                    uint newGPUPrice = uint.Parse(Console.ReadLine());
                    computer2.Gpu.Price = newGPUPrice;
                    break;
                case 6:
                    Console.Write("Enter new Computer brand: ");
                    string newBrand = Console.ReadLine();
                    computer2.Brand = newBrand;
                    break;
                case 7:
                    Console.Write("Enter new Computer price ($): ");
                    uint newComputerPrice = uint.Parse(Console.ReadLine());
                    computer2.Price = newComputerPrice;
                    break;
                case 0:
                    Console.WriteLine("Exiting...");
                    break;
                default:
                    Console.WriteLine("Invalid choice. Please try again.");
                    break;
            }
            Console.WriteLine("\nUpdated Computer Info:");
            computer2.PrintInfo();
        }
        while (choice != 0);


        Console.WriteLine("\n========== ComputerWithMonitor Class Test ==========");

        Console.WriteLine("\nDefault ComputerWithMonitor:");
        ComputerWithMonitor computerWithMonitor1 = new ComputerWithMonitor();
        computerWithMonitor1.PrintInfo();

        Console.WriteLine("\nComputerWithMonitor Computer:");
        HDD hdd1 = new HDD(2048 * 1024, 150, 100);
        GraphicsCard gpu1 = new GraphicsCard(16, 500);
        ComputerWithMonitor computerWithMonitor2 = new ComputerWithMonitor(hdd1.CapacityMB, hdd1.DataRateMBps, hdd1.Price, gpu1.MemoryGB, gpu1.Price, "DELL", hdd1.Price + gpu1.Price + 500, 24, 150);
        computerWithMonitor2.PrintInfo();

        Console.WriteLine("\nWork with setters:");

        int choice2;

        do
        {
            Console.WriteLine("\nMenu:" +
                "\n1. Change HDD capacity" +
                "\n2. Change HDD data rate" +
                "\n3. Change HDD price" +
                "\n4. Change GPU memory" +
                "\n5. Change GPU price" +
                "\n6. Change Computer brand" +
                "\n7. Change Computer price" +
                "\n8. Change Monitor size" +
                "\n9. Change Monitor price" +
                "\n0. Exit");

            choice2 = int.Parse(Console.ReadLine());
            switch (choice2)
            {
                case 1:
                    Console.Write("Enter new HDD capacity (TB): ");
                    uint newCapacity = uint.Parse(Console.ReadLine());
                    computerWithMonitor2.Hdd.CapacityMB = newCapacity * 1024 * 1024;
                    break;
                case 2:
                    Console.Write("Enter new HDD data rate (MB/s): ");
                    uint newDataRate = uint.Parse(Console.ReadLine());
                    computerWithMonitor2.Hdd.DataRateMBps = newDataRate;
                    break;
                case 3:
                    Console.Write("Enter new HDD price ($): ");
                    uint newHDDPrice = uint.Parse(Console.ReadLine());
                    computerWithMonitor2.Hdd.Price = newHDDPrice;
                    break;
                case 4:
                    Console.Write("Enter new GPU memory (GB): ");
                    uint newGPUMemory = uint.Parse(Console.ReadLine());
                    computerWithMonitor2.Gpu.MemoryGB = newGPUMemory;
                    break;
                case 5:
                    Console.Write("Enter new GPU price ($): ");
                    uint newGPUPrice = uint.Parse(Console.ReadLine());
                    computerWithMonitor2.Gpu.Price = newGPUPrice;
                    break;
                case 6:
                    Console.Write("Enter new Computer brand: ");
                    string newBrand = Console.ReadLine();
                    computerWithMonitor2.Brand = newBrand;
                    break;
                case 7:
                    Console.Write("Enter new Computer price ($): ");
                    uint newComputerPrice = uint.Parse(Console.ReadLine());
                    computerWithMonitor2.Price = newComputerPrice;
                    break;
                case 8:
                    Console.Write("Enter new Monitor size (inches): ");
                    uint newMonitorSize = uint.Parse(Console.ReadLine());
                    computerWithMonitor2.MonitorSize = newMonitorSize;
                    break;
                case 9:
                    Console.Write("Enter new Monitor price ($): ");
                    uint newMonitorPrice = uint.Parse(Console.ReadLine());
                    computerWithMonitor2.MonitorPrice = newMonitorPrice;
                    break;
                case 0:
                    Console.WriteLine("Exiting...");
                    break;
                default:
                    Console.WriteLine("Invalid choice. Please try again.");
                    break;
            }
            Console.WriteLine("\nUpdated Computer Info:");
            computerWithMonitor2.PrintInfo();
        }
        while (choice2 != 0);

        Console.WriteLine("\n==============Additional Task==================");

        Console.WriteLine("\nEnter PC budget ($): ");
        uint budget = uint.Parse(Console.ReadLine());

        Console.WriteLine("\nEnter minimum HDD capacity (TB): ");
        uint minHDDCapacity = uint.Parse(Console.ReadLine());

        Console.WriteLine("\nEnter minimum GPU memory (GB): ");
        uint minGPUMemory = uint.Parse(Console.ReadLine());

        Console.WriteLine("\nEnter minimum monitor size (inches): ");
        double minMonitorSize = double.Parse(Console.ReadLine());

        List<ComputerWithMonitor> suitableComputers = new List<ComputerWithMonitor>();
        foreach (var hDD in hdds)
        {
            foreach (var gPU in gpus)
            {
                foreach (var monitor in monitors)
                {
                    uint totalPrice = hDD.Price + gPU.Price + monitor.Price;
                    if (totalPrice <= budget && hDD.CapacityMB >= minHDDCapacity * 1024 * 1024 && gPU.MemoryGB >= minGPUMemory && monitor.Size >= minMonitorSize)
                    {
                        suitableComputers.Add(new ComputerWithMonitor(hDD.CapacityMB, hDD.DataRateMBps, hDD.Price, gPU.MemoryGB, gPU.Price, "Custom", totalPrice, monitor.Size, monitor.Price));
                    }
                }
            }
        }

        Console.WriteLine($"\nFound {suitableComputers.Count} suitable computers within the budget of {budget}$:");
        if (suitableComputers.Count == 0)
        {
            Console.WriteLine("No suitable computers found.");
        }
        else
        {
            Top10BestComputers(suitableComputers);
        }



    }

    static void Top10BestComputers(List<ComputerWithMonitor> computers)
    {
        int choice;

        List<ComputerWithMonitor> sortedComputers = new List<ComputerWithMonitor>(computers);

        do
        {
            Console.WriteLine("\nChoose the criteria for the top 10 best computers:" +
            "\n1. Best HDD capacity" +
            "\n2. Best GPU memory" +
            "\n3. Best Monitor size" +
            "\n4. Best overall performance (HDD + GPU + Monitor)" +
            "\n5. Price" +
            "\n0. Exit");

            choice = int.Parse(Console.ReadLine());

            switch (choice)
            {
                case 1:
                    sortedComputers.Sort((c1, c2) => c2.Hdd.CapacityMB.CompareTo(c1.Hdd.CapacityMB));
                    break;
                case 2:
                    sortedComputers.Sort((c1, c2) => c2.Gpu.MemoryGB.CompareTo(c1.Gpu.MemoryGB));
                    break;
                case 3:
                    sortedComputers.Sort((c1, c2) => c2.MonitorSize.CompareTo(c1.MonitorSize));
                    break;
                case 4:
                    sortedComputers.Sort((c1, c2) =>
                    {
                        int hddComparison = c2.Hdd.CapacityMB.CompareTo(c1.Hdd.CapacityMB);
                        if (hddComparison != 0) return hddComparison;
                        int gpuComparison = c2.Gpu.MemoryGB.CompareTo(c1.Gpu.MemoryGB);
                        if (gpuComparison != 0) return gpuComparison;
                        return c2.MonitorSize.CompareTo(c1.MonitorSize);
                    });
                    break;
                case 5:
                    sortedComputers.Sort((c1, c2) => c1.Price.CompareTo(c2.Price));
                    break;
                case 0:
                    Console.WriteLine("Exiting...");
                    break;
                default:
                    Console.WriteLine("Invalid choice. Please try again.");
                    continue;
            }

            Console.WriteLine("\nTop 10 Best Computers:");
            for (int i = 0; i < Math.Min(10, sortedComputers.Count); i++)
            {
                Console.WriteLine($"{i + 1}. ");
                sortedComputers[i].PrintInfo();
                Console.WriteLine("\n-----------------------------");
            }
        } while (choice != 0);

        
    }

}
