using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// Документацию по шаблону элемента "Пустая страница" см. по адресу https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x419

namespace Lab_7
{
    /// <summary>
    /// Пустая страница, которую можно использовать саму по себе или для перехода внутри фрейма.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        private const string ADD = "+";
        private const string MUL = "*";
        private const string DIV = "/";
        private const string SUB = "-";
        private const string SQRT = "sqrt";
        private const string COS = "cos";
        private const string SIN = "sin";
        private const string TAN = "tan";
        private const string CTAN = "ctan";
        private const string LOG = "log";
        private const string POW = "^";

        private string action;

        public MainPage()
        {
            this.InitializeComponent();
        }

        private void Info_Click(object sender, Windows.UI.Xaml.RoutedEventArgs e)
        {
            this.Frame.Navigate(typeof(About));
        }

        private void Trig_page(object sender, Windows.UI.Xaml.RoutedEventArgs e)
        {
            this.Frame.Navigate(typeof(Calc_Page), "trigo");
        }

        private void Arith_page(object sender, Windows.UI.Xaml.RoutedEventArgs e)
        {
            this.Frame.Navigate(typeof(Calc_Page), "arith");

        }

        private void Alg_page(object sender, Windows.UI.Xaml.RoutedEventArgs e)
        {
            this.Frame.Navigate(typeof(Calc_Page), "algebra");
        }
    }
}
