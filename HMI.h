// HMI.h : main header file for the HMI application
//

#if !defined(AFX_HMI_H__CBE6CB23_5385_40E1_9829_46DBA46474C1__INCLUDED_)
#define AFX_HMI_H__CBE6CB23_5385_40E1_9829_46DBA46474C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHMIApp:
// See HMI.cpp for the implementation of this class
//

class CHMIApp : public CWinApp
{
public:
	CHMIApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHMIApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHMIApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HMI_H__CBE6CB23_5385_40E1_9829_46DBA46474C1__INCLUDED_)
