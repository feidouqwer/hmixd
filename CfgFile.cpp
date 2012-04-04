// CfgFile.cpp: implementation of the CCfgFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HMI.h"
#include "CfgFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


#define DEFAULT_NUMBER 24

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCfgFile::CCfgFile()
{
	TCHAR tchar[256];

	m_nTowerNum = DEFAULT_NUMBER;
	m_CabinIp = 0;
	memset(&m_TowerIP, 0, sizeof(m_TowerIP));
	GetCurrentDirectory(sizeof(tchar), tchar);
	CString strTmp = tchar;
	int nPos = strTmp.ReverseFind('\\');
	if(nPos != -1)
		m_batFileName = strTmp.Mid(nPos + 1, strTmp.GetLength() - nPos - 1) + ".bat";
	m_proFileName = "hmi.properties";
}

CCfgFile::~CCfgFile()
{

}

bool CCfgFile::LoadCfgFile()
{
	CFile cfgFile;
	
	if(!cfgFile.Open(__T("HMICfg.cfg"), CFile::modeRead))
	{
		AfxMessageBox(__T("打开配置属性文件失败"), MB_OK | MB_ICONERROR);
		return SaveDefaultCfgFile();
	}
	CArchive arch(&cfgFile, CArchive::load);
	
	CString strLine;
	CString valueStr;
	int nIndex = 0;
	int ipAddr[4];
	while(arch.ReadString(strLine))
	{
		strLine.TrimLeft();
		if(strLine.Left(1) == "#")
			continue;

		int equalPos = strLine.Find("=");
		if(equalPos < 0)
			continue;
		
		valueStr = strLine.Mid(equalPos + 1, strLine.GetLength() - equalPos - 1);
		valueStr.TrimLeft();
		valueStr.TrimRight();
		if(valueStr.IsEmpty())
			continue;
		
		int nTjPos;
		if((nTjPos = strLine.Find(__T("TJIP"))) != -1)	// 查找塔基IP
		{
			CString numStr = strLine.Mid(nTjPos + 4, equalPos - nTjPos - 4);
			if(numStr.IsEmpty())
				continue;
			int m_nTowerNum = atoi(numStr);
			if(sscanf(valueStr, "%d.%d.%d.%d", &ipAddr[0], &ipAddr[1], &ipAddr[2], &ipAddr[3]) != 4)
			{
				continue;
			}
			if(m_nTowerNum > 0 && m_nTowerNum < 1000)
			{
				m_TowerIP[m_nTowerNum - 1] = (ipAddr[0] << 24) | (ipAddr[1] << 16) | (ipAddr[2] << 8) | (ipAddr[3] << 0);
			}
			TRACE("TJNUM: %d\r\n", m_nTowerNum);
			TRACE("IP: %d.%d.%d.%d\r\n", ipAddr[0], ipAddr[1], ipAddr[2], ipAddr[3]);
		}
		else if(strLine.Find(__T("JCIP")) != -1)	// 查找机舱IP
		{
			if(sscanf(valueStr, "%d.%d.%d.%d", &ipAddr[0], &ipAddr[1], &ipAddr[2], &ipAddr[3]) != 4)
			{
				continue;
			}
			m_CabinIp = (ipAddr[0] << 24) | (ipAddr[1] << 16) | (ipAddr[2] << 8) | (ipAddr[3] << 0);
		}
		else if(strLine.Find(__T("number")) != -1)
		{
			m_nTowerNum = atoi(valueStr);
			if(m_nTowerNum < 0 || m_nTowerNum > MAX_TOWER_NUM)
				m_nTowerNum = MAX_TOWER_NUM;
		}
		else if(strLine.Find(__T("BatFileName")) != -1)
		{
			m_batFileName = valueStr;
		}
		else if(strLine.Find(__T("ProFileName")) != -1)
		{
			m_proFileName = valueStr;
		}
	}
	return 0;
}

bool CCfgFile::SaveCfgFile()
{
	CFile file;
	CString strLine;

	if(!file.Open("HMICfg.cfg", CFile::modeWrite | CFile::modeCreate))
	{
		AfxMessageBox(__T("打开HMI配置文件失败"));
		return false;
	}

	try
	{
		CArchive arch(&file, CArchive::store);	
		arch.WriteString(__T("# HMI配置文件, 手动修改请确保格式正确"));
		arch.WriteString(__T("# JCIP代表基舱IP, TJIP代表塔基IP\r\n\r\n"));
		arch.WriteString(__T("# 风机数量\r\n"));
		strLine.Format("number = %d\r\n\r\n", m_nTowerNum);
		arch.WriteString(strLine);
		arch.WriteString(__T("# 批处理文件名\r\n"));
		strLine = "BatFileName = ";
		arch.WriteString(strLine + m_batFileName + "\r\n\r\n");
		arch.WriteString(__T("# 属性文件名\r\n"));
		strLine = "ProFileName = ";
		arch.WriteString(strLine + m_proFileName + "\r\n\r\n");

		if(m_CabinIp != 0)
		{
			arch.WriteString(__T("# 机航IP地址\r\n"));
			strLine.Format("JCIP = %d.%d.%d.%d\r\n\r\n", 
					(m_CabinIp >> 24) & 0xff, 
					(m_CabinIp >> 16) & 0xff, 
					(m_CabinIp >> 8) & 0xff, 
					(m_CabinIp >> 0) & 0xff);
			arch.WriteString(strLine);
		}

		arch.WriteString(__T("# 塔基IP地址\r\n"));
		for(int i=0; i<m_nTowerNum; i++)
		{
			if(m_TowerIP[i] != 0)
			{
				strLine.Format("TJIP%d = %d.%d.%d.%d", i + 1, 
					(m_TowerIP[i] >> 24) & 0xff, 
					(m_TowerIP[i] >> 16) & 0xff, 
					(m_TowerIP[i] >> 8) & 0xff, 
					(m_TowerIP[i] >> 0) & 0xff);
				arch.WriteString(strLine + "\r\n");
			}
		}
	}
	catch (...)
	{
		AfxMessageBox("写入文件失败", MB_OK | MB_ICONERROR);
		return false;
	}

	return true;
}

bool CCfgFile::SaveDefaultCfgFile()
{
	CFile cfgFile;
	CString strLine, strTmp;
	TCHAR tchar[256];

	if(!cfgFile.Open("HMICfg.cfg", CFile::modeWrite | CFile::modeCreate))
	{
		AfxMessageBox(__T("打开HMI配置文件失败"));
		return false;
	}
	
	try
	{
		CArchive arch(&cfgFile, CArchive::store);

		arch.WriteString(__T("# 风机数量\r\n"));
		m_nTowerNum = DEFAULT_NUMBER;
		strLine.Format("number = %d\r\n\r\n", m_nTowerNum);
		arch.WriteString(strLine);

		arch.WriteString(__T("# 批处理文件名\r\n"));
		GetCurrentDirectory(sizeof(tchar), tchar);
		TRACE("CurrentDirectoroy: %s\r\n", tchar);
		strTmp = tchar;
		int nPos = strTmp.ReverseFind('\\');
		if(nPos != -1)
			m_batFileName = strTmp.Mid(nPos + 1, strTmp.GetLength() - nPos - 1) + ".bat";
		else
			m_batFileName = "";
		m_batFileName.MakeLower();
		strLine = "BatFileName = " + m_batFileName + "\r\n\r\n";
		arch.WriteString(strLine);
		
		arch.WriteString(__T("# 属性文件名\r\n"));
		m_proFileName = "hmi.properties";
		arch.WriteString("ProFileName = hmi.properties\r\n\r\n");
		
		arch.WriteString(__T("# 机航IP地址\r\n"));
		m_CabinIp = 1 + (1 << 8) + (168 << 16) + (192 << 24);
		arch.WriteString(__T("JCIP = 192.168.1.1\r\n\r\n"));

		arch.WriteString(__T("# 塔基IP地址\r\n"));
		for(int i=0; i<m_nTowerNum; i++)
		{
			m_TowerIP[i] = i + 1 + (1 << 8) + (168 << 16) + (192 << 24);
			strLine.Format("TJIP%d = 192.168.1.%d\r\n", i + 1, i + 1);
			arch.WriteString(strLine);
		}
	}
	catch (...)
	{
		AfxMessageBox("写入文件失败", MB_OK | MB_ICONERROR);
		return false;
	}
	return true;
}

int CCfgFile::GetTowerNumber()
{
	return m_nTowerNum;
}

CString CCfgFile::GetBatFileName()
{
	return m_batFileName;
}

DWORD CCfgFile::GetCabinIP()
{
	return m_CabinIp;
}

DWORD CCfgFile::GetTowerIP(int nIndex)
{
	if(nIndex >= MAX_TOWER_NUM)
		return ~0;
	
	return m_TowerIP[nIndex];
}

void CCfgFile::SetCabinIP(DWORD dwCabinIP)
{
	m_CabinIp = dwCabinIP;
}

void CCfgFile::SetTowerIP(int nIndex, DWORD dwTowerIP)
{
	if(nIndex >= 0 && nIndex < MAX_TOWER_NUM)
		m_TowerIP[nIndex] = dwTowerIP;
}

CString CCfgFile::GetProFileName()
{
	return m_proFileName;
}
