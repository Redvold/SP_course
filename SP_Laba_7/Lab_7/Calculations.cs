using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_7
{
    public class Calculations
    {
        static int number_1;
        static int number_2;

        public Calculations()
        {
            number_1 = 0;
            number_2 = 0;
        }
        public Calculations(int num_1)
        {
            number_1 = num_1;
        }
        public Calculations(int num_1, int num_2)
        {
            number_1 = num_1;
            number_2 = num_2;
        }
        #region Trigonometry
        public string Sin()
        {
            return Math.Round(Math.Sin(number_1), 2).ToString();
        }
        public string Cos()
        {
            return Math.Round(Math.Cos(number_1), 2).ToString();
        }
        public string Tan()
        {
            return Math.Round(Math.Atan(number_1), 2).ToString();
        }
        #endregion
        #region Algebra
        public string Pow()
        {
            return Math.Round(Math.Pow(number_1, 2), 2).ToString();
        }
        public string Sqrt()
        {
            return Math.Round(Math.Sqrt(number_1), 2).ToString();
        }
        public string Log()
        {
            return Math.Round(Math.Log10(number_1), 2).ToString();
        }
        #endregion
        #region Arithmetic
        public string Add()
        {
            return (number_1 + number_2).ToString();
        }
        public string Sub()
        {
            return (number_1 - number_2).ToString();
        }
        public string Mul()
        {
            return (number_1 * number_2).ToString();
        }
        public string Div()
        {
            return Math.Round(((double)number_1 / (double)number_2), 2).ToString();
        }
        #endregion
    }
}
