// HMIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HMI.h"
#include "HMIDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CCfgFile gCfgFile;
/////////////////////////////////////////////////////////////////////////////
// CHMIDlg dialog

CHMIDlg::CHMIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHMIDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHMIDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHMIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHMIDlg)
	DDX_Control(pDX, IDC_TAB, m_tab);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHMIDlg, CDialog)
	//{{AFX_MSG_MAP(CHMIDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, OnSelchangeTab)
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHMIDlg message handlers

BOOL CHMIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	gCfgFile.LoadCfgFile();

	m_tab.InsertItem(0, __T("启动"));
	m_tab.InsertItem(1, __T("设置"));

	m_runDlg.Create(IDD_DIALOG_RUN, GetDlgItem(IDC_TAB));
	m_settingDlg.Create(IDD_DIALOG_SETTING, GetDlgItem(IDC_TAB));

	CRect rs;
	m_tab.GetClientRect(&rs);
	TRACE("top = %d\n", rs.top);
	rs.top += 20;
	rs.bottom -= 1;
	rs.left += 1;
	rs.right -= 2;
	m_runDlg.MoveWindow(&rs);
	m_settingDlg.MoveWindow(&rs);

	m_runDlg.ShowWindow(SW_SHOW);
	m_settingDlg.ShowWindow(SW_HIDE);

	m_tab.SetCurSel(0);
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//SetDlgItemText(IDC_STATIC_TIP, __T("设置成功"));
	SetStatusString(__T("设置成功"));
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHMIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHMIDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHMIDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CHMIDlg::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nCurSel = m_tab.GetCurSel();

	switch(nCurSel)
	{
	case 0:
		m_runDlg.ShowWindow(SW_SHOW);
		m_settingDlg.ShowWindow(SW_HIDE);
		break;
	case 1:
		m_runDlg.ShowWindow(SW_HIDE);
		m_settingDlg.ShowWindow(SW_SHOW);
		break;
	default:
		break;
	}
	*pResult = 0;
}


void CHMIDlg::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void CHMIDlg::SetStatusString(CString strText)
{
	SetDlgItemText(IDC_STATIC_TIP, strText);
}
