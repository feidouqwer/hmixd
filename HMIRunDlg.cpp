// HMIRunDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HMI.h"
#include "HMIRunDlg.h"
#include "HMIDlg.h"
#include "ProFile.h"

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
	ON_CBN_SELCHANGE(IDC_COMBO_RUN, OnSelchangeComboRun)
	ON_WM_SETCURSOR()
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
	pCombo->InsertString(row, "机舱");
	pCombo->SetCurSel(0);
	
	CIPAddressCtrl *pIPAddr = (CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS_RUN);
	pIPAddr->SetAddress(gCfgFile.GetTowerIP(0));

	CHMIDlg *pDlg = (CHMIDlg *)(GetParent()->GetParent());
	pDlg->SetTipString(__T("加载配置文件成功!"));

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

	CProFile proFile;
	proFile.SetNetIP(dwIpAddr);
	CString batFileName = gCfgFile.GetBatFileName();
	if(batFileName.IsEmpty())
	{
		AfxMessageBox(__T("请先设备批处理程序名再点击运行!"), MB_OK | MB_ICONERROR);
		return;
	}
	batFileName.MakeLower();
	
	CFile batFile;
	if(!batFile.Open(batFileName, CFile::modeRead))
	{
		AfxMessageBox(__T("打开执行文件失败!"), MB_OK | MB_ICONERROR);
		return;
	}

	TCHAR curDir[512];
	CString appPath;
	GetCurrentDirectory(sizeof(curDir), curDir);
	appPath = "cmd.exe /c ";
	appPath = appPath + curDir;
	appPath = appPath + "\\" + batFileName;
//	AfxMessageBox(appPath, MB_OK);
	HINSTANCE Instance = ShellExecute(NULL,"open", "cmd.exe", appPath, NULL, SW_SHOWNORMAL);
	if((int)Instance <= 32)
	{
		AfxMessageBox(__T("打开程序失败!"), MB_OK | MB_ICONERROR);
		return;
	}
	CHMIDlg *pDlg = (CHMIDlg *)(GetParent()->GetParent());
	pDlg->SetTipString(batFileName + __T("开始运行"));
}

void CHMIRunDlg::OnSelchangeComboRun() 
{
	// TODO: Add your control notification handler code here
	int nCurSel;
	int nTowerNum;
	DWORD dwIP;

	CComboBox *pCombo = (CComboBox *)GetDlgItem(IDC_COMBO_RUN);
	nCurSel = pCombo->GetCurSel();
	
	nTowerNum = gCfgFile.GetTowerNumber();
	if(nCurSel < nTowerNum)
	{
		dwIP = gCfgFile.GetTowerIP(nCurSel);
	}
	else if(nCurSel == nTowerNum)
	{
		dwIP = gCfgFile.GetCabinIP();
	}

	CIPAddressCtrl *pIPCtrl = (CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS_RUN);
	pIPCtrl->SetAddress(dwIP);
}

BOOL CHMIRunDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	OnSelchangeComboRun();
	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}
