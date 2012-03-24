// HMIRunDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HMI.h"
#include "HMIRunDlg.h"
#include "HMIDlg.h"

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

BOOL CHMIRunDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	int number = gCfgFile.GetTowerNumber();
	CComboBox *pCombo = (CComboBox *)GetDlgItem(IDC_COMBO_RUN);

	int row;
	CString str;
	for(row=0; row<number; row++)
	{
		str.Format("风机%d", row + 1);
		pCombo->InsertString(row, str);
	}
	pCombo->InsertString(row, "塔基");
	pCombo->SetCurSel(0);
	
	CIPAddressCtrl *pIPAddr = (CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS_RUN);
	pIPAddr->SetAddress(gCfgFile.GetTowerIP(0));


	CHMIDlg *pDlg = (CHMIDlg *)GetParent();
	pDlg->SetStatusString(__T("加载配置文件成功!"));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CHMIRunDlg::OnButtonRun() 
{
	// TODO: Add your control notification handler code here
	CIPAddressCtrl *pIpAddr = (CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS_RUN);
	DWORD dwIpAddr;
	pIpAddr->GetAddress(dwIpAddr);
	if(dwIpAddr == 0)
	{
		AfxMessageBox(__T("请先设置IP地址!"), MB_OK | MB_ICONERROR);
		return;
	}
	// add the run application code here!!!
}