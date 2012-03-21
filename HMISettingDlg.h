#if !defined(AFX_CHMISettingDlg_H__2AB84B3B_A2A3_4BEC_9DFB_8EE5BD29A115__INCLUDED_)
#define AFX_CHMISettingDlg_H__2AB84B3B_A2A3_4BEC_9DFB_8EE5BD29A115__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CHMISettingDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHMISettingDlg dialog

class CHMISettingDlg : public CDialog
{
// Construction
public:
	CHMISettingDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHMISettingDlg)
	enum { IDD = IDD_DIALOG_SETTING };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHMISettingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHMISettingDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHMISettingDlg_H__2AB84B3B_A2A3_4BEC_9DFB_8EE5BD29A115__INCLUDED_)
