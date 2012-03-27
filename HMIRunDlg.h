#if !defined(AFX_HMIRUNDLG_H__9689A114_802D_4976_B8E9_474D51DA276E__INCLUDED_)
#define AFX_HMIRUNDLG_H__9689A114_802D_4976_B8E9_474D51DA276E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HMIRunDlg.h : header file
//

#include "CfgFile.h"
/////////////////////////////////////////////////////////////////////////////
// CHMIRunDlg dialog

class CHMIRunDlg : public CDialog
{
// Construction
public:
	CHMIRunDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHMIRunDlg)
	enum { IDD = IDD_DIALOG_RUN };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHMIRunDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHMIRunDlg)
	afx_msg void OnButtonRun();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboRun();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HMIRUNDLG_H__9689A114_802D_4976_B8E9_474D51DA276E__INCLUDED_)
