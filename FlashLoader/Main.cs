using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace FlashLoader
{
    public partial class Main : Form
    {
        enum UnitInterfaceWorkerState { OFF, READING, WRITING };

        private UnitInterfaceWorkerState interfaceWorkerState = UnitInterfaceWorkerState.OFF;
        private Unit Unit = null;



        public Main()
        {
            InitializeComponent();
        }

        private void closeButton_Click(object sender, EventArgs e)
        {
            if (null != Unit)
            {
                Unit.Close();
                Unit = null;
                StatusTextBox.Text += "Connection closed\r\n";
            }

            writeButton.Enabled = false;
            openButton.Enabled = true;
        }

        private void writeButton_Click(object sender, EventArgs e)
        {
            if (File.Exists(WriteFileTextBox.Text))
            {
                StatusTextBox.Text += "Starting write operation\r\n";
                openButton.Enabled = false;
                closeButton.Enabled = false;
                unitInterfaceWorker.RunWorkerAsync(UnitInterfaceWorkerState.WRITING);
            }
            else
            {
                StatusTextBox.Text += "Invalid file name\r\n";
            }
        }

        private void openButton_Click(object sender, EventArgs e)
        {
            bool alreadyOpen = false;

            if (null != Unit)
            {
                if (Unit.isOpen())
                {
                    alreadyOpen = true;
                    writeButton.Enabled = true;
                    openButton.Enabled = true;
                }
            }

            if (!alreadyOpen)
            {
                Unit = new Unit(ComPortTextBox.Text, unitInterfaceWorker);

                if (Unit.isOpen())
                {
                    StatusTextBox.Text += "Connection opened\r\n";
                    writeButton.Enabled = true;
                    openButton.Enabled = true;
                    closeButton.Enabled = true;
                }
                else
                {
                    StatusTextBox.Text += "Connection failed\r\n";
                }
            }
        }

        private void readButton_Click(object sender, EventArgs e)
        {
            if (File.Exists(ReadFileTextBox.Text))
            {
                StatusTextBox.Text += "Starting read operation\r\n";
                openButton.Enabled = false;
                closeButton.Enabled = false;
                unitInterfaceWorker.RunWorkerAsync(UnitInterfaceWorkerState.READING);
            }
            else
            {
                StatusTextBox.Text += "Invalid file name\r\n";
            }
        }

        private void unitInterfaceWorker_DoWork(object sender, DoWorkEventArgs e)
        {
            interfaceWorkerState = (UnitInterfaceWorkerState)e.Argument;

            switch (interfaceWorkerState)
            {
                case UnitInterfaceWorkerState.OFF:
                    break;

                case UnitInterfaceWorkerState.READING:
                    Unit.ReadConfig(ReadFileTextBox.Text);
                    break;

                case UnitInterfaceWorkerState.WRITING:
                    Unit.WriteConfig(WriteFileTextBox.Text);
                    break;

                default:
                    interfaceWorkerState = UnitInterfaceWorkerState.OFF;
                    break;
            }
        }

        private void unitInterfaceWorker_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            switch (interfaceWorkerState)
            {
                case UnitInterfaceWorkerState.READING:
                    openButton.Enabled = true;
                    closeButton.Enabled = true;
                    if (Unit.isOpen())
                    {
                        StatusTextBox.Text += "Configuration read\r\n";
                    }
                    else
                    {
                        StatusTextBox.Text += "Operation failed, port closed\r\n";
                        writeButton.Enabled = false;
                        openButton.Enabled = false;
                    }
                    break;

                case UnitInterfaceWorkerState.WRITING:
                    openButton.Enabled = true;
                    closeButton.Enabled = true;
                    if (Unit.isOpen())
                    {
                        StatusTextBox.Text += "Config written\r\n";
                    }
                    else
                    {
                        StatusTextBox.Text += "Operation failed, port closed\r\n";
                        writeButton.Enabled = false;
                        openButton.Enabled = false;
                    }
                    break;
            }
        }

        private void unitInterfaceWorker_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            progressBar.Value = e.ProgressPercentage;
        }

        private void label3_Click(object sender, EventArgs e)
        {

        }
    }
}
