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
	BOOL SaveProFile(LPCSTR lpcstrPath);
	BOOL MakeBakFile(LPCSTR lpstrPath);
	BOOL LoadProFile(LPCSTR lpstrPath);
	CProFile(int nTjNum);
	virtual ~CProFile();

private:
	int nTjNum;
	DWORD m_jcip;
	DWORD m_tjip[1000];
};

#endif // !defined(AFX_PROFILE_H__960D11FB_156B_44CF_8C33_14073EACBBA2__INCLUDED_)
