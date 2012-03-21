; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CHMIRunDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "HMI.h"

ClassCount=5
Class1=CHMIApp
Class2=CHMIDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_DIALOG_RUN
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class4=CHMIRunDlg
Resource4=IDD_HMI_DIALOG
Class5=CHMISettingDlg
Resource5=IDD_DIALOG_SETTING

[CLS:CHMIApp]
Type=0
HeaderFile=HMI.h
ImplementationFile=HMI.cpp
Filter=N

[CLS:CHMIDlg]
Type=0
HeaderFile=HMIDlg.h
ImplementationFile=HMIDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CHMIDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=HMIDlg.h
ImplementationFile=HMIDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_HMI_DIALOG]
Type=1
Class=CHMIDlg
ControlCount=3
Control1=IDC_TAB,SysTabControl32,1342178304
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC_TIP,static,1342308352

[DLG:IDD_DIALOG_RUN]
Type=1
Class=CHMIRunDlg
ControlCount=3
Control1=IDC_STATIC,static,1342308352
Control2=IDC_COMBO_RUN,combobox,1344340227
Control3=IDC_BUTTON_RUN,button,1342242816

[CLS:CHMIRunDlg]
Type=0
HeaderFile=HMIRunDlg.h
ImplementationFile=HMIRunDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CHMIRunDlg

[DLG:IDD_DIALOG_SETTING]
Type=1
Class=CHMISettingDlg
ControlCount=9
Control1=IDC_STATIC,static,1342308352
Control2=IDC_IPADDRESS_CABIN_IP,SysIPAddress32,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,static,1342308352
Control6=IDC_COMBO_TOWER,combobox,1344340227
Control7=IDC_STATIC,static,1342308352
Control8=IDC_IPADDRESS_TOWER_IP,SysIPAddress32,1342242816
Control9=IDC_BUTTON_SET,button,1342242816

[CLS:CHMISettingDlg]
Type=0
HeaderFile=hmisettingdlg.h
ImplementationFile=hmisettingdlg.cpp
BaseClass=CDialog
LastObject=IDC_BUTTON_SET
Filter=D
VirtualFilter=dWC

