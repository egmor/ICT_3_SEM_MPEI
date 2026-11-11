namespace Lab7
{
    public class HDD
    {
        private uint capacityMB; // емкость в МБ
        private uint dataRateMBps; // скорость передачи данных в МБ/с
        private uint price; // цена в долларах США

        public HDD()
        {
            capacityMB = 1024 * 1024; // по умолчанию 1 ТБ
            dataRateMBps = 100; // по умолчанию 100 МБ/с
            price = 25;
        }
        public HDD(uint capacityMB, uint dataRateMBps, uint price)
        {
            if (!CheckCapacity(capacityMB))
                throw new ArgumentException("HDD capacity must be between 512000 and 31457280 MB.");
            if (!CheckDataRate(dataRateMBps))
                throw new ArgumentException("HDD data rate must be between 10 and 300 MB/s.");
            if (!CheckPrice(price))
                throw new ArgumentException("HDD price must be between 13 and 250 dollars.");
            this.capacityMB = capacityMB;
            this.dataRateMBps = dataRateMBps;
            this.price = price;
        }

        public uint CapacityMB
        {
            get => capacityMB;
            set
            {
                if (!CheckCapacity(value))
                    throw new ArgumentException("HDD capacity must be between 512000 and 31457280 MB.");
                capacityMB = value;
            }
        }

        public uint DataRateMBps
        {
            get => dataRateMBps;
            set
            {
                if (!CheckDataRate(value))
                    throw new ArgumentException("HDD data rate must be between 10 and 300 MB/s.");
                dataRateMBps = value;
            }
        }

        public uint Price
        {
            get => price;
            set
            {
                if (!CheckPrice(value))
                    throw new ArgumentException("HDD price must be between 13 and 250 dollars.");
                price = value;
            }
        }

        private static bool CheckCapacity(uint capacityMB)
        {
            return capacityMB >= 512000 && capacityMB <= 31457280;
        }

        private static bool CheckDataRate(uint dataRateMBps)
        {
            return dataRateMBps >= 10 && dataRateMBps <= 300;
        }

        private static bool CheckPrice(uint price)
        {
            return price >= 13 && price <= 250;
        }

        public void PrintInfo()
        {
            Console.WriteLine($"HDD Capacity: {capacityMB} MB | {capacityMB / 1024} GB | {capacityMB / (1024 * 1024)} TB, Data Rate: {dataRateMBps} MB/s, Price: ${price}");
        }
    }

    public class GraphicsCard
    {
        private uint memoryGB; // объем памяти в ГБ
        private uint price; // цена в долларах США
        public GraphicsCard()
        {
            memoryGB = 8; // по умолчанию 8 ГБ
            price = 100; // по умолчанию 100 долларов США
        }
        public GraphicsCard(uint memoryGB, uint price)
        {
            if (!CheckMemory(memoryGB))
                throw new ArgumentException("Graphics card memory must be between 4 and 24 GB.");
            if (!CheckPrice(price))
                throw new ArgumentException("Graphics card price must be between 50 and 2000 dollars.");
            this.memoryGB = memoryGB;
            this.price = price;
        }
        public uint MemoryGB
        {
            get => memoryGB;
            set
            {
                if (!CheckMemory(value))
                    throw new ArgumentException("Graphics card memory must be between 4 and 24 GB.");
                memoryGB = value;
            }
        }
        public uint Price   
        {
            get => price;
            set
            {
                if (!CheckPrice(value))
                    throw new ArgumentException("Graphics card price must be between 50 and 2000 dollars.");
                price = value;
            }
        }
        private static bool CheckMemory(uint memoryGB)
        {
            return memoryGB >= 4 && memoryGB <= 24;
        }
        private static bool CheckPrice(uint price)
        {
            return price >= 50 && price <= 2000;
        }

        public void PrintInfo()
        {
            Console.WriteLine($"Graphics Card Memory: {memoryGB} GB, Price: ${price}");
        }
    }

    public class Computer
    {
        private HDD hdd;
        private GraphicsCard gpu;
        private string brand;
        private uint price;

        public Computer()
        {
            hdd = new HDD();
            gpu = new GraphicsCard();
            brand = "Generic";
            price = 500;
        }
        public Computer(uint capacityHDD, uint dataRateHDD, uint priceHDD, uint memoryGPU, uint priceGPU, string brand, uint price)
        {
            this.hdd = new HDD(capacityHDD, dataRateHDD, priceHDD);
            this.gpu = new GraphicsCard(memoryGPU, priceGPU);
            if (!CheckBrand(brand))
                throw new ArgumentException("Brand name must be 2 and up to 31 characters.");
            if (!CheckPrice(price))
                throw new ArgumentException($"Computer price must be between {hdd.Price + gpu.Price + 100} and 5000 dollars.");
            this.brand = brand;
            this.price = price;
        }
        public HDD Hdd
        {
            get => hdd;
            set => hdd = value;
        }

        public GraphicsCard Gpu
        {
            get => gpu;
            set => gpu = value;
        }
        public string Brand
        {
            get => brand;
            set
            {
                if (!CheckBrand(value))
                    throw new ArgumentException("Brand name must be non-empty and up to 100 characters.");
                brand = value;
            }
        }
        public uint Price 
        {
            get => price;
            set
            {
                if (!CheckPrice(value))
                    throw new ArgumentException("Computer price must be between 300 and 5000 dollars.");
                price = value;
            }
        }

        private bool CheckPrice(uint price)
        {
            return price >= hdd.Price + gpu.Price + 100 && price <= 5000;
        }

        private static bool CheckBrand(string brand)
        {
            return brand.Length >= 2 && brand.Length <= 31;
        }

        public void PrintInfo()
        {
            Console.WriteLine($"Brand: {brand}, Price: ${price}");
            hdd.PrintInfo();
            gpu.PrintInfo();
        }

    }

    public class ComputerWithMonitor : Computer
    {
        private double monitorSize;
        private uint monitorPrice;
        public ComputerWithMonitor() : base()
        {
            monitorSize = 24;
            monitorPrice = 100;
        }
        public ComputerWithMonitor(uint capacityHDD, uint dataRateHDD, uint priceHDD, uint memoryGPU, uint priceGPU, string brand, uint price, double monitorSize, uint monitorPrice)
            : base(capacityHDD, dataRateHDD, priceHDD, memoryGPU, priceGPU, brand, price)
        {
            if (!CheckMonitorSize(monitorSize))
                throw new ArgumentException("Monitor size must be between 19 and 50 inches.");
            if (!CheckMonitorPrice(monitorPrice))
                throw new ArgumentException("Monitor price must be between 50 and 2000 dollars.");
            this.monitorPrice = monitorPrice;
            this.monitorSize = monitorSize;
        }

        public double MonitorSize
        {
            get => monitorSize;
            set
            {
                if (!CheckMonitorSize(value))
                    throw new ArgumentException("Monitor size must be between 19 and 50 inches.");
                monitorSize = value;
            }
        }
        public uint MonitorPrice
        {
            get => monitorPrice;
            set
            {
                if (!CheckMonitorPrice(value))
                    throw new ArgumentException("Monitor price must be between 50 and 2000 dollars.");
                monitorPrice = value;
            }
        }

        private static bool CheckMonitorSize(double size)
        {
            return size >= 19 && size <= 50;
        }
        private static bool CheckMonitorPrice(uint price)
        {
            return price >= 50 && price <= 2000;
        }

        public new void PrintInfo()
        {
            base.PrintInfo();
            Console.WriteLine($"Monitor Size: {monitorSize} inches, Monitor Price: ${monitorPrice}");
        }
    }


}