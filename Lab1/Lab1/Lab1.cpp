#include "stdafx.h"
#include "Form1.h"

using namespace Lab1;

public class Matrix
{
private:
	int m, n;
	float **elements;

public:
	Matrix()
	{
		m = 0;
		n = 0;
		elements = 0;
	}
	Matrix(Matrix &A, Matrix &B)
	{
		if (A.elements == 0 || B.elements == 0 ||
			A.m != B.n || A.n != B.m)
		{
			m = 0;
			n = 0;
			elements = 0;
			throw "Argument exception";
		}
		m = A.m;
		n = B.n;
		elements = new float*[m];
		for (int i = 0; i < m; i++)
		{
			elements[i] = new float[n];
			for (int j = 0; j < n; j++)
			{
				float sum = 0;
				for (int k = 0; k < A.n; k++)
					sum += A.elements[i][k] * B.elements[k][j];
				elements[i][j] = sum;
			}
		}
	}
	Matrix(Matrix &A)
	{
		m = A.m;
		n = A.n;
		elements = new float*[m];
		for (int i = 0; i < m; i++)
		{
			elements[i] = new float[n];
			for (int j = 0; j < n; j++)
				elements[i][j] = A.elements[i][j];
		}
	}
	Matrix(int m, int n)
	{
		this->m = m;
		this->n = n;
		elements = new float*[m];
		for (int i = 0; i < m; i++)
		{
			elements[i] = new float[n];
			for (int j = 0; j < n; j++)
				elements[i][j] = 0;
		}
	}
	Matrix operator *(Matrix &B)
	{
		return Matrix(*this, B);
	}
	void Populate(float seed, float step)
	{
		if (elements == 0)
			throw("Wrong matrix");
		float x = seed;
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
			{
				elements[i][j] = x;
				x += step;
			}
	}
	~Matrix()
	{
		if (elements != 0)
		{
			delete [] elements;
			elements = 0;
		}
	}
};

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 
	Matrix A(3, 5), B(4, 3);
	A.Populate(1, 3);
	B.Populate(4, 1);
	Matrix C1(A);
	Matrix C2(A, B);
	Matrix C3 = A * B;
	
	Form1 form1 = gcnew Form1();

	Application::Run(gcnew Form1());
	return 0;
}