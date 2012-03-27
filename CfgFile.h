// CfgFile.h: interface for the CCfgFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CFGFILE_H__3D013421_0823_47BF_9215_9F4ACBBB3AE2__INCLUDED_)
#define AFX_CFGFILE_H__3D013421_0823_47BF_9215_9F4ACBBB3AE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_TOWER_NUM 1000

class CCfgFile  
{
public:
	CString GetProFileName();
	void SetTowerIP(int nIndex, DWORD dwTowerIP);
	void SetCabinIP(DWORD dwCabinIP);
	DWORD GetTowerIP(int nIndex);
	DWORD GetCabinIP();
	bool SaveDefaultCfgFile();
	CString GetBatFileName();
	int GetTowerNumber();
	bool SaveCfgFile();
	bool LoadCfgFile();
	CCfgFile();
	virtual ~CCfgFile();

private:
	int m_nTowerNum;
	DWORD m_CabinIp;
	DWORD m_TowerIP[MAX_TOWER_NUM];
	CString m_batFileName;
	CString m_proFileName;
};

#endif // !defined(AFX_CFGFILE_H__3D013421_0823_47BF_9215_9F4ACBBB3AE2__INCLUDED_)
