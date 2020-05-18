using System;
using System.Collections.Generic;
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



namespace Lab_7
{
    /// <summary>
    /// Пустая страница, которую можно использовать саму по себе или для перехода внутри фрейма.
    /// </summary>
    public sealed partial class Calc_Page : Page
    {
        private bool operation_mode;
        Calculations calc_module;
        public Calc_Page()
        {
            this.InitializeComponent();
            operation_mode = false;//where 'false' stands for sigle operand calculations
            calc_module = new Calculations();//class for calculations logic
        }
        private void RadioVisibleNot()
        {

            sin.Visibility = Visibility.Collapsed;
            cos.Visibility = Visibility.Collapsed;
            tg.Visibility = Visibility.Collapsed;

            plus.Visibility = Visibility.Collapsed;
            minus.Visibility = Visibility.Collapsed;
            divide.Visibility = Visibility.Collapsed;
            multiple.Visibility = Visibility.Collapsed;

            sqrt.Visibility = Visibility.Collapsed;
            power.Visibility = Visibility.Collapsed;
            log.Visibility = Visibility.Collapsed;
        }
        private void LayoutAlgebra()
        {
            sqrt.Visibility = Visibility.Visible;
            power.Visibility = Visibility.Visible;
            log.Visibility = Visibility.Visible;
            operand2.Visibility = Visibility.Collapsed;
            log.IsChecked = true;
            operation_mode = false;
        }
        private void LayoutTrig()
        {
            sin.Visibility = Visibility.Visible;
            cos.Visibility = Visibility.Visible;
            tg.Visibility = Visibility.Visible;
            operand2.Visibility = Visibility.Collapsed;
            sin.IsChecked = true;
            operation_mode = false;
        }
        private void LayoutArith()
        {
            plus.Visibility = Visibility.Visible;
            minus.Visibility = Visibility.Visible;
            divide.Visibility = Visibility.Visible;
            multiple.Visibility = Visibility.Visible;
            operand2.Visibility = Visibility.Visible;
            plus.IsChecked = true;
            operation_mode = true;
        }
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            RadioVisibleNot();
            if (e.Parameter is string && !string.IsNullOrWhiteSpace((string)e.Parameter))
            {
                if ((string)e.Parameter == "algebra")
                {
                    LayoutAlgebra();
                }
                else if ((string)e.Parameter == "trigo")
                {
                    LayoutTrig();
                }
                else
                {
                    LayoutArith();

                }
            }
            base.OnNavigatedTo(e);
        }
        private void operand2_BeforeTextChanging(TextBox sender, TextBoxBeforeTextChangingEventArgs args)
        {
            args.Cancel = args.NewText.Any(c => !char.IsDigit(c));
        }

        private void operand1_BeforeTextChanging(TextBox sender, TextBoxBeforeTextChangingEventArgs args)
        {
            args.Cancel = args.NewText.Any(c => !char.IsDigit(c));
        }

        private void Back_Click(object sender, RoutedEventArgs e)
        {
            this.Frame.Navigate(typeof(MainPage));
        }
        private bool IsValidNumber(string operand1, string operand2)
        {

            if (!string.IsNullOrWhiteSpace(operand1) && !string.IsNullOrWhiteSpace(operand2))
            {
                try
                {
                    Calculations cal_module = new Calculations(Convert.ToInt32(operand1), Convert.ToInt32(operand2));
                    return true;
                }
                catch (Exception)
                {
                    return false;
                }

            }
            else
            {
                return false;
            }
        }
        private bool IsValidNumber(string operand1)
        {

            if (!string.IsNullOrWhiteSpace(operand1))
            {
                try
                {
                    Calculations cal_module = new Calculations(Convert.ToInt32(operand1));
                    return true;
                }
                catch (Exception)
                {
                    return false;
                }

            }
            else
            {
                return false;
            }
        }
        void SwitchDoubleOperandOperations()
        {
            if (plus.IsChecked == true)
            {
                result.Text = calc_module.Add();
            }
            else if (minus.IsChecked == true)
            {
                result.Text = calc_module.Sub();
            }
            else if (divide.IsChecked == true)
            {
                result.Text = calc_module.Div();
            }
            else if (multiple.IsChecked == true)
            {
                result.Text = calc_module.Mul();
            }
            else
            {
                result.Text = "Error operation!";
            }
        }
        void SwitchSigleOperandOperations()
        {
            if (sin.IsChecked == true)
            {
                result.Text = calc_module.Sin();
            }
            else if (cos.IsChecked == true)
            {
                result.Text = calc_module.Cos();
            }
            else if (tg.IsChecked == true)
            {
                result.Text = calc_module.Tan();
            }

            else if (power.IsChecked == true)
            {
                result.Text = calc_module.Pow();
            }
            else if (log.IsChecked == true)
            {
                result.Text = calc_module.Log();
            }
            else if (sqrt.IsChecked == true)
            {
                result.Text = calc_module.Sqrt();
            }
            else
            {
                result.Text = "Error operation!";
            }
        }
        private void Compute_Click(object sender, RoutedEventArgs e)
        {
            if (operation_mode)
            {
                if (IsValidNumber(operand1.Text, operand2.Text))
                {
                    try
                    {
                        SwitchDoubleOperandOperations();
                    }
                    catch (Exception exep)
                    {

                        result.Text = exep.Message;
                    }
                }
                else
                {
                    operand1.Text = "Error input!";
                    operand2.Text = "Error input!";
                }
            }
            else
            {
                if (IsValidNumber(operand1.Text))
                {
                    try
                    {
                        SwitchSigleOperandOperations();
                    }
                    catch (Exception exep)
                    {

                        result.Text = exep.Message;
                    }
                }
                else
                {
                    operand1.Text = "Error input!";
                }
            }

        }
    }
}
