// inputcfg_t.cpp : implementation file
//

#include "pch.h"
#include "vdatmin.h"
#include "inputcfg_t.h"
#include <nvinput.h>
#include <nvinput_math.h>
#include <nvinput_ascii.h>
#include <winuser.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// inputcfg_t dialog
//**********************************************************************************************
// constructor
//**********************************************************************************************

inputcfg_t::inputcfg_t(CWnd* pParent /*=NULL*/)
	: CDialog(inputcfg_t::IDD, pParent)
{
	//{{AFX_DATA_INIT(inputcfg_t)
	//}}AFX_DATA_INIT

	the_input = NULL;
}

//**********************************************************************************************
// data exchange
//**********************************************************************************************

void inputcfg_t::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(inputcfg_t)
	DDX_Control(pDX, IDC_SIZE_LABEL, m_size_txt);
	DDX_Control(pDX, IDC_SIZE_EDITBOX, m_size_edit);
	DDX_Control(pDX, IDC_STATIC_LABEL, m_formula_lbl);
	DDX_Control(pDX, FILE_TYPE, m_file_type);
	DDX_Control(pDX, IDC_FILE_TXT, m_file_txt);
	DDX_Control(pDX, IDC_DATA_TXT, m_data_txt);
	DDX_Control(pDX, IDC_RANDOMIZE, m_random_check);
	DDX_Control(pDX, IDC_PARTIAL, m_partia_check);
	DDX_Control(pDX, IDC_NBDATA, m_nb_data_edit);
	DDX_Control(pDX, IDC_FILENAME, m_filename_edit);
	DDX_Control(pDX, IDC_EQUATION, m_equation_edit);
	DDX_Control(pDX, IDC_BROWSE, m_browse_button);
	//}}AFX_DATA_MAP
	m_file_type.SetCurSel(0);
	CheckRadioButton(IDC_MATH, IDC_INPUT_FILE, IDC_MATH);
	CheckRadioButton(IDC_2DOBJ, IDC_3DOBJ, IDC_2DOBJ);
}


BEGIN_MESSAGE_MAP(inputcfg_t, CDialog)
	//{{AFX_MSG_MAP(inputcfg_t)
	ON_BN_CLICKED(IDC_PARTIAL, OnPartial)
	ON_BN_CLICKED(IDC_MATH, OnMath)
	ON_BN_CLICKED(IDC_INPUT_FILE, OnInputFile)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// inputcfg_t message handlers
//**********************************************************************************************
// On Partial
//**********************************************************************************************

void inputcfg_t::OnPartial()
{
	if (m_partia_check.GetCheck())
	{
		m_random_check.EnableWindow(true);
		m_data_txt.EnableWindow(true);
		m_nb_data_edit.EnableWindow(true);
	}
	else {
		m_random_check.EnableWindow(false);
		m_data_txt.EnableWindow(false);
		m_nb_data_edit.EnableWindow(false);
	}
}

//**********************************************************************************************
// OnOK
//**********************************************************************************************


void inputcfg_t::OnOK()
{
	// formula
	if (GetCheckedRadioButton(IDC_MATH, IDC_INPUT_FILE) == IDC_MATH)
	{
		MessageBox(NULL, L"Formulas not yet implemented.", MB_OK);

		//char buffer1[256], buffer2[256];
		//	replace getwindowtext with cstrings
		//	convert cstring to char buffer and pass to constructors
		/*CString c1, c2;
		LPTSTR buffer1, buffer2;
		nvinput_math_t* myinput = NULL;

		//buffer1[0] = 0;
		m_equation_edit.GetWindowText(c1);
		buffer1 = c1.GetBuffer(256);
		myinput = new nvinput_math_t((char*)buffer1);

		m_nb_data_edit.GetWindowText(c2);
		buffer2 = c2.GetBuffer(256);
		myinput->set_max_number(atoi((char*)buffer2));


		if (m_partia_check.GetCheck())
		{
			if (m_random_check.GetCheck())
			{
				sprintf_s(title, sizeof(title), "%s Partial Random %s samples", (char*)buffer1, (char*)buffer2);
			}
			else {
				sprintf_s(title, sizeof(title), "%s Partial %s samples", (char*)buffer1, (char*)buffer2);
			}
		}
		else sprintf_s(title, sizeof(title), "%s full sample", (char*)buffer1);

		myinput->set_partial((m_partia_check.GetCheck() != 0) ? true : false);
		myinput->set_randomize((m_random_check.GetCheck() != 0) ? true : false);
		the_input = myinput;
		m_size_edit.GetWindowText(buffer1, 255);

		myinput->set_size((vector_size = atoi((char*)buffer1)));*/

	}
	else if (GetCheckedRadioButton(IDC_MATH, IDC_INPUT_FILE) == IDC_INPUT_FILE) {
		CString c;
		m_filename_edit.GetWindowText(c);
		CStringA c2(c);
		const char* buffer = c2;

		if (m_file_type.GetCurSel() == 0){ // group files are unneeded
			nvinput_groupfile_t* myinput;
			myinput = new nvinput_groupfile_t((char*)buffer);
			sprintf_s(title, sizeof(title), "Group File : %s", buffer);
			myinput->init();
			vector_size = myinput->read_vector_size();
			myinput->rewind();
			the_input = myinput;
		}
		else {
			nvinput_vectfile_t* myinput;
			myinput = new nvinput_vectfile_t((char*)buffer); // NEED TO delete
			sprintf_s(title, sizeof(title), "Vector File : %s", buffer);
			myinput->init();
			vector_size = myinput->read_vector_size();
			myinput->rewind();
			the_input = myinput;
		}

	}
	CDialog::OnOK();
}

//**********************************************************************************************
// OnMath functions
//**********************************************************************************************


void inputcfg_t::OnMath()
{
	if (GetCheckedRadioButton(IDC_MATH, IDC_INPUT_FILE) == IDC_MATH)
	{
		m_file_txt.EnableWindow(false);
		m_file_type.EnableWindow(false);
		m_filename_edit.EnableWindow(false);
		m_browse_button.EnableWindow(false);

		m_formula_lbl.EnableWindow(true);
		m_equation_edit.EnableWindow(true);
		m_partia_check.EnableWindow(true);

		m_size_edit.EnableWindow(true);
		m_size_txt.EnableWindow(true);

		if (m_partia_check.GetCheck())
		{
			m_random_check.EnableWindow(true);
			m_data_txt.EnableWindow(true);
			m_nb_data_edit.EnableWindow(true);
		}
		else {
			m_random_check.EnableWindow(false);
			m_data_txt.EnableWindow(false);
			m_nb_data_edit.EnableWindow(false);
		}
	}
	else if (GetCheckedRadioButton(IDC_MATH, IDC_INPUT_FILE) == IDC_INPUT_FILE) {

		m_formula_lbl.EnableWindow(false);
		m_equation_edit.EnableWindow(false);
		m_partia_check.EnableWindow(false);
		m_random_check.EnableWindow(false);
		m_data_txt.EnableWindow(false);
		m_nb_data_edit.EnableWindow(false);

		m_file_txt.EnableWindow(true);
		m_file_type.EnableWindow(true);
		m_filename_edit.EnableWindow(true);
		m_browse_button.EnableWindow(true);

		m_size_edit.EnableWindow(false);
		m_size_txt.EnableWindow(false);

	}

}

void inputcfg_t::OnInputFile()
{
	OnMath();
}

//**********************************************************************************************
// On browse
//**********************************************************************************************

void inputcfg_t::OnBrowse()
{
	CFileDialog chooser(true, NULL, NULL, OFN_FILEMUSTEXIST, NULL);


	chooser.m_ofn.nFilterIndex = m_file_type.GetCurSel();
	switch (m_file_type.GetCurSel())
	{
	case 0:
		chooser.m_ofn.lpstrFilter = L"Group File (*.bgrp )\0*.bgrp\0Vector File (*.bvect)\0*.bvect\0Generic Text File (*.txt)\0*.txt\0All Files\0*.*\0";
		break;
	case 1:
		chooser.m_ofn.lpstrFilter = L"Vector File (*.bvect)\0*.bvect\0Group File (*.bgrp )\0*.bgrp\0Generic Text File (*.txt)\0*.txt\0All Files\0*.*\0";
		break;
	default:
		break;
	}

	if (chooser.DoModal() == IDOK)
	{
		m_filename_edit.SetWindowText(chooser.GetPathName());
	}
}
