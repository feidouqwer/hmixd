// CfgFile.h: interface for the CCfgFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CFGFILE_H__3D013421_0823_47BF_9215_9F4ACBBB3AE2__INCLUDED_)
#define AFX_CFGFILE_H__3D013421_0823_47BF_9215_9F4ACBBB3AE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCfgFile  
{
public:
	int getNumber();
	bool SaveCfgFile();
	bool LoadCfgFile();
	CCfgFile();
	virtual ~CCfgFile();

private:
	int nTjNum;
	DWORD m_jcip;
	DWORD m_tjip[1000];
	CString batFileName;
};

#endif // !defined(AFX_CFGFILE_H__3D013421_0823_47BF_9215_9F4ACBBB3AE2__INCLUDED_)
