using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.IO.Ports;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace WPF_COM_Port
{
    public class ViewModel : INotifyPropertyChanged
    {
        /*модель*/
        HandlerCOM handlerCOM;
        /*кнопки*/
        public ICommand RefreshBtnClick { get; set; }
        public ICommand OpenBtnClick { get; set; }
        public ICommand CloseBtnClick { get; set; }
        public ICommand SendBtnClick { get; set; }
        public ICommand ClearBtnClick { get; set; }

        /*списки*/
        public ObservableCollection<string> PortCombo { get; set; } = new ObservableCollection<string>();
        public ObservableCollection<int> BaudCombo { get; set; } = new ObservableCollection<int>();
        public ObservableCollection<Parity> ParityCombo { get; set; } = new ObservableCollection<Parity>();
        public ObservableCollection<int> DataBitsCombo { get; set; } = new ObservableCollection<int>();
        public ObservableCollection<StopBits> StopBitsCombo { get; set; } = new ObservableCollection<StopBits>();
        public ObservableCollection<Handshake> HandshakeCombo { get; set; } = new ObservableCollection<Handshake>();

        /*тексты*/
        private string _logText;
        public string LogText
        {
            get => _logText;
            set
            {
                if (_logText == value) return;
                _logText = value;
                OnPropertyChanged();
            }
        }
        private string _sendBox;
        public string SendBox
        {
            get => _sendBox;
            set
            {
                if (_sendBox == value) return;
                _sendBox = value;
                OnPropertyChanged();
            }
        }

        /*вход*/
        public ViewModel()
        {
            InitButtons();
            // Для теста добавим элемент по умолчанию
            //Items.Add("Первый элемент");
            //LogText = "[eqyz";
            //PortCombo.Add(LogText);
            handlerCOM = new HandlerCOM(this);
        }
        private void InitButtons()
        {
            RefreshBtnClick = new RelayCommand(OnRefreshBtnClick, CanRefreshBtnClick);
            OpenBtnClick = new RelayCommand(OnOpenBtnClick, CanOpenBtnClick);
            CloseBtnClick = new RelayCommand(OnCloseBtnClick, CanCloseBtnClick);
            SendBtnClick = new RelayCommand(OnSendBtnClick, CanSendBtnClick);
            ClearBtnClick = new RelayCommand(OnClearBtnClick, CanClearBtnClick);
        }
        /*обработка кнопок*/
        public void OnRefreshBtnClick(object parameter)
        {
            //Items.Add(string.IsNullOrWhiteSpace(Text1) ? "(пусто)" : Text1);
            // LogText = string.Empty;
            //LogText = LogText + 1;
            //PortCombo.Add(LogText);
        }
        private bool CanRefreshBtnClick(object parameter)
        {
            return true;
        }

        public void OnOpenBtnClick(object parameter)
        {

        }
        private bool CanOpenBtnClick(object parameter)
        {
            return true;
        }

        public void OnCloseBtnClick(object parameter)
        {

        }
        private bool CanCloseBtnClick(object parameter)
        {
            return true;
        }
        public void OnSendBtnClick(object parameter)
        {

        }
        private bool CanSendBtnClick(object parameter)
        {
            return true;
        }
        public void OnClearBtnClick(object parameter)
        {

        }
        private bool CanClearBtnClick(object parameter)
        {
            return true;
        }

        /*обработка текстов - евенты*/
        public event PropertyChangedEventHandler PropertyChanged;
        protected void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
