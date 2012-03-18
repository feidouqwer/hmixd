// CHMISettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HMI.h"
#include "HMISettingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHMISettingDlg dialog


CHMISettingDlg::CHMISettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHMISettingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHMISettingDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CHMISettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHMISettingDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHMISettingDlg, CDialog)
	//{{AFX_MSG_MAP(CHMISettingDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHMISettingDlg message handlers
