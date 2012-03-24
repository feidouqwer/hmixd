// CHMISettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HMI.h"
#include "HMIDlg.h"
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
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	ON_CBN_SELCHANGE(IDC_COMBO_TOWER, OnSelchangeComboTower)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHMISettingDlg message handlers

BOOL CHMISettingDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	CString str;
	int number = gCfgFile.GetTowerNumber();
	CComboBox *pComBox = (CComboBox *)GetDlgItem(IDC_COMBO_TOWER);
	for(int i=0; i<number; i++)
	{
		str.Format("·ç»ú%d", i + 1);
		pComBox->InsertString(i, str);
	}
	pComBox->SetCurSel(0);

	CIPAddressCtrl *pCabinIpCtrl = (CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS_CABIN_IP);
	//pCabinIpCtrl->SetAddress(192, 168, 1, 2);
	pCabinIpCtrl->SetAddress(gCfgFile.GetCabinIP());

	CIPAddressCtrl *pTowerIpCtrl = (CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS_TOWER_IP);
	//pTowerIpCtrl->SetAddress(192, 168, 1, 2);
	pTowerIpCtrl->SetAddress(gCfgFile.GetTowerIP(0));
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CHMISettingDlg::OnButtonSet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwCabinIP, dwTowerIP;
	int nIndex;
	CIPAddressCtrl *pIPCtrl = (CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS_CABIN_IP);
	pIPCtrl->GetAddress(dwCabinIP);
	
	pIPCtrl = (CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS_TOWER_IP);
	pIPCtrl->GetAddress(dwTowerIP);
	
	CComboBox *pComboTower = (CComboBox *)GetDlgItem(IDC_COMBO_TOWER);
	nIndex = pComboTower->GetCurSel();

	gCfgFile.SetCabinIP(dwCabinIP);
	gCfgFile.SetTowerIP(nIndex, dwTowerIP);
	
	gCfgFile.SaveCfgFile();
}

void CHMISettingDlg::OnSelchangeComboTower() 
{
	// TODO: Add your control notification handler code here
	int nIndex;
	CComboBox *pComboTower = (CComboBox *)GetDlgItem(IDC_COMBO_TOWER);
	nIndex = pComboTower->GetCurSel();

	DWORD dwTowerIP = gCfgFile.GetTowerIP(nIndex);
	CIPAddressCtrl *pIPCtrl = (CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS_TOWER_IP);
	pIPCtrl->SetAddress(dwTowerIP);
}
