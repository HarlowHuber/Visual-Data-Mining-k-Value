#if !defined(AFX_INPUTCFG_T_H__592CE70A_E63F_4758_9094_5172BAB2E22C__INCLUDED_)
#define AFX_INPUTCFG_T_H__592CE70A_E63F_4758_9094_5172BAB2E22C__INCLUDED_

#include "pch.h"
#include "resource.h"
#include <nvinput.h>
#include <nvinput_math.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// inputcfg_t.h : header file
//
//I think this is the pop up windows when you click new file.
//It asks you for a data file or formula.
//LR
/////////////////////////////////////////////////////////////////////////////
// inputcfg_t dialog

class inputcfg_t : public CDialog
{
	// Construction
public:
	inputcfg_t(CWnd* pParent = NULL);   // standard constructor

	nvinput_t* the_input;

	char title[256];
	int vector_size;
	// Dialog Data
	//{{AFX_DATA(inputcfg_t)
	enum { IDD = IDD_FORMULA_CONFIG };
	CStatic	m_size_txt;
	CEdit	m_size_edit;
	CStatic	m_formula_lbl;
	CComboBox	m_file_type;
	CStatic	m_file_txt;
	CStatic	m_data_txt;
	CButton	m_random_check;
	CButton	m_partia_check;
	CEdit	m_nb_data_edit;
	CEdit	m_filename_edit;
	CEdit	m_equation_edit;
	CButton	m_browse_button;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(inputcfg_t)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(inputcfg_t)
	afx_msg void OnPartial();
	virtual void OnOK();
	afx_msg void OnMath();
	afx_msg void OnInputFile();
	afx_msg void OnBrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTCFG_T_H__592CE70A_E63F_4758_9094_5172BAB2E22C__INCLUDED_)

