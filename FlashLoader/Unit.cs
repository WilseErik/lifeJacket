using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.IO.Ports;
using System.Globalization;
using System.Threading;
using System.ComponentModel;

namespace FlashLoader
{
    class Unit
    {
        private SerialPort LpuartInterface = null;
        private int BAUD_RATE = 38400;
        private bool open = false;
        private int CONFIG_SIZE = 8388608;
        private int PAGE_SIZE = 256;
        private BackgroundWorker worker;





        /**
         * @brief Initialize the computer interface
         */
        public Unit(string PortName, BackgroundWorker worker)
        {
            string retVal = "";
            this.worker = worker;

            try
            {
                LpuartInterface = new SerialPort(PortName, BAUD_RATE);
                LpuartInterface.ReadTimeout = 5000;  // ms
                LpuartInterface.Open();
                LpuartInterface.NewLine = "\r\n";
                LpuartInterface.WriteLine("set sleep allowed off");
                retVal = LpuartInterface.ReadLine();
                retVal = LpuartInterface.ReadLine();
                open = retVal.Contains("ok") || retVal.Contains("Invalid syntax");

                if (!open)
                {
                    LpuartInterface.Close();
                }
                else
                {
                    LpuartInterface.WriteLine("set debug log enable off");
                    retVal = LpuartInterface.ReadLine();
                    retVal = LpuartInterface.ReadLine();
                }
            }
            catch (Exception)
            {
                try
                {
                    LpuartInterface.Close();
                }
                catch (Exception)
                { }

                open = false;
            }
        }

        ~Unit()
        {
            try
            {
                LpuartInterface.Close();
            }
            catch (Exception)
            { }
        }

        public void Close()
        {
            open = false;

            try
            {
                LpuartInterface.Close();
            }
            catch (Exception)
            { }
        }

        /**
         * @brief Checks if the comunication to the PCB is opened.
         */
        public bool isOpen()
        {
            return open;
        }

        /**
         * @brief Reads the configuration.
         * @param FileName - where to store the read config.
         */
        public void ReadConfig(string FileName)
        {
            List<byte> config = new List<byte>();
            int reportInterval = 4;
            int nextProgressReport = reportInterval;
            worker.ReportProgress(0);

            try
            {
                using (FileStream stream = File.Open(FileName, FileMode.Create))
                using (BinaryWriter writer = new BinaryWriter(stream))
                {
                    for (int i = 0; i != CONFIG_SIZE; ++i)
                    {
                        Byte readVal = 0;
                        string returnVal;
                        LpuartInterface.WriteLine("get flash " + String.Format("{0:X}", i));
                        returnVal = LpuartInterface.ReadLine();
                        returnVal = LpuartInterface.ReadLine();
                        Byte.TryParse(returnVal, NumberStyles.HexNumber, null as IFormatProvider, out readVal);
                        writer.Write(readVal);
                        returnVal = LpuartInterface.ReadLine(); // "ok"

                        if (i == nextProgressReport)
                        {
                            worker.ReportProgress((i * 100) / CONFIG_SIZE);
                            nextProgressReport += reportInterval;
                        }
                    }
                }
            }
            catch (TimeoutException)
            {
                Close();
            }
        }

        private bool send_ef_sbp_command(int address, UInt16 value)
        {
            int tryNumber = 0;
            bool commandDone = false;
            
            while (!commandDone && (tryNumber++ < 10))
            {
                try
                {
                    string dummy;
                    LpuartInterface.WriteLine("ef spb " + String.Format("{0:X} {1:X}", address, value));
                    dummy = LpuartInterface.ReadLine();
                    dummy = LpuartInterface.ReadLine();
                    commandDone = true;
                }
                catch
                {
                        ;
                }

                if (!commandDone)
                {
                    string dummy;
                    LpuartInterface.WriteLine("restart uart");
                    dummy = LpuartInterface.ReadLine();
                    dummy = LpuartInterface.ReadLine();
                }
            }

            return commandDone;
        }

        private bool send_ef_wp_command(int address)
        {
            int tryNumber = 0;
            bool commandDone = false;

            while (!commandDone && (tryNumber++ < 10))
            {
                try
                {
                    string dummy;
                    LpuartInterface.WriteLine("ef wp " + String.Format("{0:X}", address));
                    dummy = LpuartInterface.ReadLine();
                    dummy = LpuartInterface.ReadLine();
                    commandDone = true;
                }
                catch
                {
                    ;
                }

                if (!commandDone)
                {
                    string dummy;
                    LpuartInterface.WriteLine("restart uart");
                    dummy = LpuartInterface.ReadLine();
                    dummy = LpuartInterface.ReadLine();
                }
            }

            return commandDone;
        }

        /**
         * @brief Writes a configuration to the PCB.
         * @param FileName - the configuration to be written.
         */
        public void WriteConfig(string FileName)
        {
            byte[] config;
            string dummy;
            int reportInterval = 4;
            int nextProgressReport = reportInterval;
            int chip_erase_progress = 10;
            worker.ReportProgress(0);

            try
            {

                using (FileStream stream = File.Open(FileName, FileMode.Open))
                using (BinaryReader reader = new BinaryReader(stream))
                {
                    config = reader.ReadBytes(CONFIG_SIZE);
                }

                LpuartInterface.WriteLine("ext flash chip erase\r\n");

                bool chip_erase_done = false;

                while (!chip_erase_done)
                {
                    try
                    {
                    chip_erase_done = LpuartInterface.ReadLine().Contains("ok");
                    } catch (Exception) {;};
                }

                worker.ReportProgress(chip_erase_progress);

                for (int i = 0; i < CONFIG_SIZE; i += PAGE_SIZE)
                {
                    for (int k = 0; k != PAGE_SIZE; k += 2)
                    {
                        UInt32 address = (UInt32)(i + k);

                        UInt16 value = (UInt16)(((UInt16)config[address]) * 256);
                        value += (UInt16)config[address + 1];


                        if (!send_ef_sbp_command(k / 2, value))
                        {
                            throw new TimeoutException();
                        }
                    }

                    if (!send_ef_wp_command(i))
                    {
                        throw new TimeoutException();
                    }
                    
                    
                    worker.ReportProgress(chip_erase_progress + (i * 100) / CONFIG_SIZE);
                }
            }
            catch (TimeoutException)
            {
                Close();
            }
        }
    }
}
