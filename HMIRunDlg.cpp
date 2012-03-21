// HMIRunDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HMI.h"
#include "HMIRunDlg.h"
#include "CfgFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHMIRunDlg dialog


CHMIRunDlg::CHMIRunDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHMIRunDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHMIRunDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CHMIRunDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHMIRunDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHMIRunDlg, CDialog)
	//{{AFX_MSG_MAP(CHMIRunDlg)
	ON_BN_CLICKED(IDC_BUTTON_RUN, OnButtonRun)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHMIRunDlg message handlers

void CHMIRunDlg::OnButtonRun() 
{
	// TODO: Add your control notification handler code here
	m_cfgFile.SaveCfgFile();
	m_cfgFile.LoadCfgFile();
}

BOOL CHMIRunDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CCfgFile cfgfile;
	cfgfile.LoadCfgFile();
	int number = cfgfile.getNumber();
	CComboBox *pCombo = (CComboBox *)GetDlgItem(IDC_COMBO_RUN);
	pCombo->InsertString(0, "Ëþ»ù");

	CString str;
	for(int i=0; i<number; i++)
	{
		str.Format("·ç»ú%d", i);
		pCombo->InsertString(i + 1, str);
	}
	pCombo->SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
