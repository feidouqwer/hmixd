; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CHMIDlg
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
Resource3=IDD_HMI_DIALOG
Class4=CHMIRunDlg
Resource4=IDD_ABOUTBOX
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
LastObject=IDC_TAB

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
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_TAB,SysTabControl32,1342178304

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

[DLG:IDD_DIALOG_SETTING]
Type=1
Class=CHMISettingDlg
ControlCount=8
Control1=IDC_STATIC,static,1342308352
Control2=IDC_IPADDRESS1,SysIPAddress32,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,static,1342308352
Control6=IDC_COMBO1,combobox,1344340226
Control7=IDC_STATIC,static,1342308352
Control8=IDC_IPADDRESS2,SysIPAddress32,1342242816

[CLS:CHMISettingDlg]
Type=0
HeaderFile=hmisettingdlg.h
ImplementationFile=hmisettingdlg.cpp
BaseClass=CDialog
LastObject=IDC_COMBO1

