// CHMISettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HMI.h"
#include "HMISettingDlg.h"
#include "CfgFile.h"

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
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHMISettingDlg message handlers

BOOL CHMISettingDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CCfgFile cfgFile;

	cfgFile.LoadCfgFile();

	CString str;
	int number = cfgFile.getNumber();
	CComboBox *pComBox = (CComboBox *)GetDlgItem(IDC_COMBO_TOWER);
	for(int i=0; i<number; i++)
	{
		str.Format("·ç»ú%d", i + 1);
		pComBox->InsertString(i, str);
	}
	pComBox->SetCurSel(0);

	CIPAddressCtrl *pCabinIpCtrl = (CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS_CABIN_IP);
	pCabinIpCtrl->SetAddress(192, 168, 1, 2);

	CIPAddressCtrl *pTowerIpCtrl = (CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS_TOWER_IP);
	pTowerIpCtrl->SetAddress(192, 168, 1, 2);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CHMISettingDlg::OnButtonSet() 
{
	// TODO: Add your control notification handler code here
	
}
