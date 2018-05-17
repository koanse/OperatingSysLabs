using System;
using System.Collections.Generic;
using System.Collections;
using System.Windows.Forms;

namespace Lab2Cs
{
    static class Program
    {
        [STAThread]
        static void Main()
        {
            SinFunction sf1 = new SinFunction(1, 3);
            SinFunction sf2 = new SinFunction(3, 4);
            LnFunction lf1 = new LnFunction(6, 4, 4);
            LnFunction lf2 = new LnFunction(5, 2, 5);
            Function[] arrFunc = new Function[] { sf1, lf1, sf2, lf2 };
            VectorFunction vf = new VectorFunction(arrFunc);
            double[] res = vf.GetValue(1.1);

            SinFunction[] arrSf = new SinFunction[] { sf1, sf2 };
            GenericVectorFunction<SinFunction> gvf =
                new GenericVectorFunction<SinFunction>(new SinFunction[] { sf1, sf2 });
            res = gvf.GetValue(4.7);
        }
    }
    public class Function
    {
        public virtual double GetValue(double x)
        {
            return x;
        }
    }
    public class SinFunction : Function
    {
        double a, b;
        public SinFunction(double a, double b)
        {
            this.a = a;
            this.b = b;
        }
        public override double GetValue(double x)
        {
            return a * Math.Sin(b * x);
        }
    }
    public class LnFunction : Function
    {
        double a, b, c;
        public LnFunction(double a, double b, double c)
        {
            this.a = a;
            this.b = b;
            this.c = c;
        }
        public override double GetValue(double x)
        {
            return a * Math.Log(b * x) + c;
        }
    }
    public class VectorFunction
    {
        Function[] functions;
        public VectorFunction(Function[] functions)
        {
            this.functions = functions;
        }
        public double[] GetValue(double x)
        {
            double[] res = new double[functions.Length];
            for (int i = 0; i < functions.Length; i++)
            {
                Function f = functions[i] as Function;
                res[i] = f.GetValue(x);
            }
            return res;
        }
    }
    public class GenericVectorFunction<FuncType> where FuncType : Function
    {
        FuncType[] functions;
        public GenericVectorFunction(FuncType[] functions)
        {
            this.functions = functions;
        }
        public double[] GetValue(double x)
        {
            double[] res = new double[functions.Length];
            for (int i = 0; i < functions.Length; i++)
            {
                Function f = functions[i] as Function;
                res[i] = f.GetValue(x);
            }
            return res;
        }
    }
}