using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

using Modbus.Device;

namespace ModbusMaster
{
    public partial class Form1 : Form
    {
        private SerialPort serialPort;
        private IModbusSerialMaster master;

        public Form1()
        {
            InitializeComponent();
            LoadSerialPorts();
        }

        private void LoadSerialPorts()
        {
            comboBox_PortName.Items.Clear();
            string[] ports = SerialPort.GetPortNames();
            comboBox_PortName.Items.AddRange(ports);

            if (ports.Length > 0)
                comboBox_PortName.SelectedIndex = 0;
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button_Connect_Click(object sender, EventArgs e)
        {
            string portName = comboBox_PortName.SelectedItem.ToString();

            serialPort = new SerialPort(portName)
            {
                BaudRate = 115200,
                DataBits = 8,
                Parity = Parity.Even,
                StopBits = StopBits.One
            };
            serialPort.Open();

            master = ModbusSerialMaster.CreateRtu(serialPort);

            MessageBox.Show("Connected to " + portName);
        }

        private void button_Read_Click(object sender, EventArgs e)
        {
            if (master == null)
            {
                MessageBox.Show("Not connected.");
                return;
            }

            byte slaveId = 2;
            ushort startAddress = 0;
            ushort numRegisters = 10;

            ushort[] registers = master.ReadHoldingRegisters(slaveId, startAddress, numRegisters);

            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < registers.Length; i++)
            {
                sb.AppendLine($"Reg[{startAddress + i}] = {registers[i]}");
            }

            textBox_Result.Text = sb.ToString();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (serialPort != null && serialPort.IsOpen)
                serialPort.Close();
        }

    }
}
