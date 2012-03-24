// HMIDlg.h : header file
//

#if !defined(AFX_HMIDLG_H__9FDE32A9_D8AD_4AE2_8614_3C6E6B85052E__INCLUDED_)
#define AFX_HMIDLG_H__9FDE32A9_D8AD_4AE2_8614_3C6E6B85052E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CfgFile.h"
#include "HMIRunDlg.h"
#include "HMISettingDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CHMIDlg dialog

class CHMIDlg : public CDialog
{
// Construction
public:
	void SetStatusString(CString strText);
	CHMIDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHMIDlg)
	enum { IDD = IDD_HMI_DIALOG };
	CTabCtrl	m_tab;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHMIDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHMIDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCancelMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CHMIRunDlg m_runDlg;
	CHMISettingDlg m_settingDlg;
};

extern CCfgFile gCfgFile;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HMIDLG_H__9FDE32A9_D8AD_4AE2_8614_3C6E6B85052E__INCLUDED_)
