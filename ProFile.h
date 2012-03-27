// ProFile.h: interface for the CProFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROFILE_H__960D11FB_156B_44CF_8C33_14073EACBBA2__INCLUDED_)
#define AFX_PROFILE_H__960D11FB_156B_44CF_8C33_14073EACBBA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CProFile  
{
public:
	BOOL SetNetIP(DWORD dwNetIP);
	BOOL MakeBakFile(LPCSTR lpstrPath, LPCSTR lpstrBakPath);
	CProFile();
	virtual ~CProFile();
};

#endif // !defined(AFX_PROFILE_H__960D11FB_156B_44CF_8C33_14073EACBBA2__INCLUDED_)
