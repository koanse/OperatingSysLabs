// L1.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "L1.h"
#include "L1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


class Matrix
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

// CL1App

BEGIN_MESSAGE_MAP(CL1App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CL1App construction

CL1App::CL1App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CL1App object

CL1App theApp;


// CL1App initialization

BOOL CL1App::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CL1Dlg dlg;
	m_pMainWnd = &dlg;
	
	Matrix A(3, 4), B(4, 3);
	A.Populate(1, 3);
	B.Populate(4, 1);
	Matrix C1(A);
	Matrix C2(A, B);
	Matrix C3 = A * B;
	
	//dlg.SetDlgItemTextW(IDC_EDIT1, L"SsS");
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

