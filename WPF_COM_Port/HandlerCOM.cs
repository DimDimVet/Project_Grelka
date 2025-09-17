using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO.Ports;
using System.Linq;
using System.Security.Policy;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using WPF_COM_Port;


namespace WPF_COM_Port
{
    public partial class HandlerCOM
    {
        private ViewModel vm;
        public HandlerCOM(ViewModel _vm)
        {
            vm = _vm;
            InitSerialPort();
        }

        SerialPort port;
        /**/
        private ObservableCollection<string> PortCombo;
        private ObservableCollection<int> BaudCombo;
        private ObservableCollection<Parity> ParityCombo;
        private ObservableCollection<int> DataBitsCombo;
        private ObservableCollection<StopBits> StopBitsCombo;
        private ObservableCollection<Handshake> HandshakeCombo;

        public void InitSerialPort()
        {
            port = new SerialPort();
            SetPort();

            vm.CloseBtnIsEnable = false;
            vm.SendBtnIsEnable = false;

            vm.RefreshBtnIsEnable = true;
            vm.OpenBtnIsEnable = true;
            vm.ClearBtnIsEnable = true;
        }

        public void SetPort() 
        {
            string[] ports = SerialPort.GetPortNames().OrderBy(n => n).ToArray();
            PortCombo = new ObservableCollection<string>(ports);
            vm.PortCombo = PortCombo;
            if (ports.Length > 0) 
            { 
                vm.PortComboSelectIndex = 0; 
            }

            int[] listBaund = new int[] { 300, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200 };
            BaudCombo = new ObservableCollection<int>(listBaund);
            vm.BaudCombo = BaudCombo;
            vm.BaudComboSelectItem = 9600;

            IEnumerable<Parity> parity = Enum.GetValues(typeof(Parity)).Cast<Parity>();
            ParityCombo = new ObservableCollection<Parity>(parity);
            vm.ParityCombo = ParityCombo;
            vm.ParityComboSelectItem = Parity.None;

            int[] listBits = new int[] { 5, 6, 7, 8 };
            DataBitsCombo = new ObservableCollection<int>(listBits);
            vm.DataBitsCombo = DataBitsCombo;
            vm.DataBitsComboSelectItem = 8;

            IEnumerable<StopBits> stopBits = Enum.GetValues(typeof(StopBits)).Cast<StopBits>();
            StopBitsCombo = new ObservableCollection<StopBits> (stopBits);
            vm.StopBitsCombo = StopBitsCombo;
            vm.StopBitsComboSelectItem = StopBits.One;

            IEnumerable<Handshake> handshake = Enum.GetValues(typeof(Handshake)).Cast<Handshake>();
            HandshakeCombo = new ObservableCollection<Handshake> (handshake);
            vm.HandshakeCombo = HandshakeCombo;
            vm.HandshakeComboSelectItem = Handshake.None;
        }
        public void RefreshBtnClick()
        {
            int selint = vm.PortComboSelectIndex;
            string sel = selint.ToString();
            string[] ports = SerialPort.GetPortNames().OrderBy(n => n).ToArray();
            PortCombo = new ObservableCollection<string>(ports);
            vm.PortCombo = PortCombo;
            if (!string.IsNullOrEmpty(sel) && ports.Contains(sel))
            {
                vm.PortComboSelectItem = sel;
            }
            else if (ports.Length > 0)
            {
                vm.PortComboSelectIndex = 0;
            }
        }

        public void OpenBtnClick()
        {
            if (port != null && port.IsOpen)
            {
                return;
            }

            if (vm.PortComboSelectItem == null)
            {
                MessageBox.Show("Select port", "Error", MessageBoxButton.OK, MessageBoxImage.Warning);
                return;
            }

            try
            {
                string portName = vm.PortComboSelectItem.ToString();
                int baud = Convert.ToInt32(vm.BaudComboSelectItem);
                Parity parity = vm.ParityComboSelectItem;
                int dataBits = Convert.ToInt32(vm.DataBitsComboSelectItem);
                StopBits stopBits = (StopBits)vm.StopBitsComboSelectItem;
                Handshake handshake = (Handshake)vm.HandshakeComboSelectItem;

                port = new SerialPort(portName, baud, parity, dataBits, stopBits)
                {
                    Encoding = Encoding.UTF8,
                    Handshake = handshake,
                    ReadTimeout = 500,
                    WriteTimeout = 500,
                    DtrEnable = vm.DtrCheckClick == true,
                    RtsEnable = vm.RtsCheckClick == true,
                    NewLine = "\n"
                };

                port.DataReceived += PortDataReceived;
                port.ErrorReceived += PortErrorReceived; 
                port.Open();

               vm.LogText=string.Format("Opened {0} @ {1}", portName, baud);
               vm.OpenBtnIsEnable = false;
               vm.CloseBtnIsEnable = true;
               vm.SendBtnIsEnable = true;

            }
            catch (Exception ex)
            {
                MessageBox.Show("Open error: " + ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void PortDataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            try
            {
                if (port == null)
                {
                    return;
                }

                string data = port.ReadExisting();
                AppendReceived(data);
            }
            catch (Exception ex)
            {
                vm.LogText = ("Read error: " + ex.Message);
            }
        }

        private void PortErrorReceived(object sender, SerialErrorReceivedEventArgs e)
        {
            vm.LogText = ("Serial error: " + e.EventType);
        }

        private void AppendReceived(string data)
        {
            vm.LogText = data;
        }

        public void CloseBtnClick()
        {
            ClosePort();
        }

        private void ClosePort()
        {
            if (port == null)
            {
                return;
            }
            try
            {
                port.DataReceived -= PortDataReceived;
                port.ErrorReceived -= PortErrorReceived;

                if (port.IsOpen)
                {
                    port.Close();
                }

                port.Dispose();
                vm.LogText="Closed port";
            }
            catch (Exception ex)
            {
                vm.LogText = "Close error: " + ex.Message;
            }
            finally
            {
                port = null;
                vm.OpenBtnIsEnable = true;
                vm.CloseBtnIsEnable = false;
                vm.SendBtnIsEnable = false;

            }
        }

        public void SendBtnClick()
        {
            if (port == null || !port.IsOpen)
            {
                MessageBox.Show("Port is not open", "Error", MessageBoxButton.OK, MessageBoxImage.Warning);
                return;
            }

            var text = vm.SendBox ?? string.Empty;
            try
            {
                port.WriteLine(text);
                vm.LogText = "> " + text;
            }
            catch (Exception ex)
            {
                vm.LogText = "Write error: " + ex.Message;
            }
        }

        public void ClearBtnClick()
        {
            vm.LogText = "";
        }

        public void Closed(bool flag)
        {
            ClosePort();
        }
    }
}



/*namespace UartWpfApp
{
    public partial class MainWindow : Window
    {
        private SerialPort port;
        private readonly Dispatcher ui;

        public MainWindow()
        {
            InitializeComponent();
            ui = Dispatcher.CurrentDispatcher;
            PopulateControls();
        }

        private void PopulateControls()
        {
            try
            {
                var ports = SerialPort.GetPortNames().OrderBy(n => n).ToArray();
                PortCombo.ItemsSource = ports;
                if (ports.Length > 0) PortCombo.SelectedIndex = 0;
            }
            catch { }

            BaudCombo.ItemsSource = new int[] { 300, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200 };
            BaudCombo.SelectedItem = 115200;

            ParityCombo.ItemsSource = Enum.GetValues(typeof(Parity)).Cast<Parity>();
            ParityCombo.SelectedItem = Parity.None;

            DataBitsCombo.ItemsSource = new int[] { 5, 6, 7, 8 };
            DataBitsCombo.SelectedItem = 8;

            StopBitsCombo.ItemsSource = Enum.GetValues(typeof(StopBits)).Cast<StopBits>();
            StopBitsCombo.SelectedItem = StopBits.One;

            HandshakeCombo.ItemsSource = Enum.GetValues(typeof(Handshake)).Cast<Handshake>();
            HandshakeCombo.SelectedItem = Handshake.None;
        }

        private void RefreshBtnClick(object sender, RoutedEventArgs e)
        {
            var sel = PortCombo.SelectedItem as string;
            var ports = SerialPort.GetPortNames().OrderBy(n => n).ToArray();
            PortCombo.ItemsSource = ports;
            if (!string.IsNullOrEmpty(sel) && ports.Contains(sel)) PortCombo.SelectedItem = sel;
            else if (ports.Length > 0) PortCombo.SelectedIndex = 0;
        }

        private void OpenBtnClick(object sender, RoutedEventArgs e)
        {
            if (port != null && port.IsOpen) return;

            if (PortCombo.SelectedItem == null)
            {
                MessageBox.Show("Select port", "Error", MessageBoxButton.OK, MessageBoxImage.Warning);
                return;
            }

            try
            {
                var portName = PortCombo.SelectedItem.ToString();
                var baud = Convert.ToInt32(BaudCombo.SelectedItem);
                var parity = (Parity)ParityCombo.SelectedItem;
                var dataBits = Convert.ToInt32(DataBitsCombo.SelectedItem);
                var stopBits = (StopBits)StopBitsCombo.SelectedItem;
                var handshake = (Handshake)HandshakeCombo.SelectedItem;

                port = new SerialPort(portName, baud, parity, dataBits, stopBits)
                {
                    Encoding = Encoding.UTF8,
                    Handshake = handshake,
                    ReadTimeout = 500,
                    WriteTimeout = 500,
                    DtrEnable = DtrCheck.IsChecked == true,
                    RtsEnable = RtsCheck.IsChecked == true,
                    NewLine = "\n"
                };

                port.DataReceived += Port_DataReceived;
                port.ErrorReceived += Port_ErrorReceived;
                port.Open();

                Log(string.Format("Opened {0} @ {1}", portName, baud));
                OpenBtn.IsEnabled = false;
                CloseBtn.IsEnabled = true;
                SendBtn.IsEnabled = true;
            }
            catch (Exception ex)
            {
                MessageBox.Show("Open error: " + ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void CloseBtnClick(object sender, RoutedEventArgs e)
        {
            ClosePort();
        }

private void ClosePort()
        {
            if (_port == null) return;
            try
            {
                _port.DataReceived -= Port_DataReceived;
                _port.ErrorReceived -= Port_ErrorReceived;
                if (_port.IsOpen) _port.Close();
                _port.Dispose();
                Log("Closed port");
            }
            catch (Exception ex)
            {
                Log("Close error: " + ex.Message);
            }
            finally
            {
                _port = null;
                OpenBtn.IsEnabled = true;
                CloseBtn.IsEnabled = false;
                SendBtn.IsEnabled = false;
            }
        }

        private void SendBtnClick(object sender, RoutedEventArgs e)
        {
            if (_port == null || !_port.IsOpen)
            {
                MessageBox.Show("Port is not open", "Error", MessageBoxButton.OK, MessageBoxImage.Warning);
                return;
            }

            var text = SendBox.Text ?? string.Empty;
            try
            {
                _port.WriteLine(text);
                Log("> " + text);
            }
            catch (Exception ex)
            {
                Log("Write error: " + ex.Message);
            }
        }

        private void ClearBtn_Click(object sender, RoutedEventArgs e)
        {
            LogBox.Clear();
        }

        private void Port_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            try
            {
                if (_port == null) return;
                var data = _port.ReadExisting();
                _ui.BeginInvoke(new Action(() => AppendReceived(data)));
            }
            catch (Exception ex)
            {
                _ui.BeginInvoke(new Action(() => Log("Read error: " + ex.Message)));
            }
        }

        private void Port_ErrorReceived(object sender, SerialErrorReceivedEventArgs e)
        {
            _ui.BeginInvoke(new Action(() => Log("Serial error: " + e.EventType)));
        }

        private void AppendReceived(string data)
        {
            // Добавляем без таймстампа (частями)
            LogBox.AppendText(data);
            LogBox.ScrollToEnd();
        }

        private void Log(string text)
        {
            LogBox.AppendText("[" + DateTime.Now.ToString("HH:mm:ss") + "] " + text + Environment.NewLine);
            LogBox.ScrollToEnd();
        }

        protected override void OnClosed(EventArgs e)
        {
            base.OnClosed(e);
            ClosePort();
        }
    }

    // Простая версия BeginInvoke-расширения для Dispatcher
    internal static class DispatcherExtensions
    {
        public static void BeginInvoke(this Dispatcher d, Action a)
        {
            if (d == null) return;
            d.BeginInvoke(a, DispatcherPriority.Background);
        }
    }
}
```
*/