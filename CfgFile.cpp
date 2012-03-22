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
	nTjNum = DEFAULT_NUMBER;
}

CCfgFile::~CCfgFile()
{

}

bool CCfgFile::LoadCfgFile()
{
	CFile cfgFile;
	
	if(!cfgFile.Open(__T("HMICfg.txt"), CFile::modeRead))
	{
		AfxMessageBox(__T("打开配置属性文件失败"), MB_OK | MB_ICONERROR);
		return false;
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
			int nTjNum = atoi(numStr);
			if(sscanf(valueStr, "%d.%d.%d.%d", &ipAddr[0], &ipAddr[1], &ipAddr[2], &ipAddr[3]) != 4)
			{
				continue;
			}
			if(nTjNum < 1000)
			{
				m_tjip[nTjNum] = (ipAddr[0] << 24) | (ipAddr[1] << 16) | (ipAddr[1] << 8) | (ipAddr[1] << 0);
			}
			TRACE("TJNUM: %d\r\n", nTjNum);
			TRACE("IP: %d.%d.%d.%d\r\n", ipAddr[0], ipAddr[1], ipAddr[2], ipAddr[3]);
		}
		else if(strLine.Find(__T("JCIP")) != -1)	// 查找机舱IP
		{
			if(sscanf(valueStr, "%d.%d.%d.%d", &ipAddr[0], &ipAddr[1], &ipAddr[2], &ipAddr[3]) != 4)
			{
				continue;
			}
			m_jcip = (ipAddr[0] << 24) | (ipAddr[1] << 16) | (ipAddr[1] << 8) | (ipAddr[1] << 0);
		}
		else if(strLine.Find(__T("number")) != -1)
		{
			nTjNum = atoi(valueStr);
		}
		else if(strLine.Find(__T("batFileName")) != -1)
		{
			batFileName = valueStr;
		}
	}
	return 0;
}

bool CCfgFile::SaveCfgFile()
{
	CFile file;
	CString strLine;

	if(!file.Open("HMICfg.txt", CFile::modeWrite | CFile::modeCreate))
	{
		AfxMessageBox(__T("打开HMI配置文件失败"));
		return false;
	}

	try
	{
		CArchive arch(&file, CArchive::store);
		strLine = "# 风机数量\r\n";
		arch.WriteString(strLine);
		strLine.Format("number = %d\r\n", DEFAULT_NUMBER);
		arch.WriteString(strLine);
	}
	catch (...)
	{
		AfxMessageBox("写入文件失败", MB_OK | MB_ICONERROR);
		return false;
	}

	return true;
}

int CCfgFile::getNumber()
{
	return nTjNum;
}
