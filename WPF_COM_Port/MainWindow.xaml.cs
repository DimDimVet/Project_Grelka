using System;
using System.Windows;


namespace WPF_COM_Port
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        protected override void OnClosed(EventArgs e) //в маин
        {
            base.OnClosed(e);
            IsClosed(true);
        }

        public static Action<bool> OnIsClosed;
        public static void IsClosed(bool flag)
        {
            OnIsClosed?.Invoke(flag);
        }
    }
}
