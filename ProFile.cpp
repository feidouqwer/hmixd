// ProFile.cpp: implementation of the CProFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HMI.h"
#include "ProFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProFile::CProFile(int nTjNum)
{
	this->nTjNum = nTjNum;
	memset(m_tjip, 0, sizeof(m_tjip));
}

CProFile::~CProFile()
{

}

BOOL CProFile::LoadProFile(LPCSTR lpstrPath)
{
	CFile proFile;
	
	if(!proFile.Open(lpstrPath, CFile::modeRead))
	{
		AfxMessageBox(__T("打开配置属性文件失败"), MB_OK | MB_ICONERROR);
		return false;
	}
	CArchive arch(&proFile, CArchive::load);
	
	CString strLine;
	CString ipStr;
	int nIndex = 0;
	int ipAddr[4];
	while(arch.ReadString(strLine))
	{
		strLine.TrimLeft();
		if(strLine.Left(2) == "#!")
		{
			int equalPos = strLine.Find("=");
			if(equalPos < 0)
				continue;
			int nTjPos;
			if((nTjPos = strLine.Find(__T("TJIP"))) != -1)
			{
				CString numStr = strLine.Mid(nTjPos + 4, equalPos - nTjPos - 4);
				if(numStr.IsEmpty())
					continue;
				int nTjNum = atoi(numStr);
				ipStr = strLine.Mid(equalPos + 1, strLine.GetLength() - equalPos - 1);
				ipStr.TrimLeft();
				ipStr.TrimRight();
				if(sscanf(ipStr, "%d.%d.%d.%d", &ipAddr[0], &ipAddr[1], &ipAddr[2], &ipAddr[3]) != 4)
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
			else if(strLine.Find(__T("JCIP")) != -1)
			{
				ipStr = strLine.Mid(equalPos + 1, strLine.GetLength() - equalPos - 1);
				ipStr.TrimLeft();
				ipStr.TrimRight();
				if(sscanf(ipStr, "%d.%d.%d.%d", &ipAddr[0], &ipAddr[1], &ipAddr[2], &ipAddr[3]) != 4)
				{
					continue;
				}
				m_jcip = (ipAddr[0] << 24) | (ipAddr[1] << 16) | (ipAddr[1] << 8) | (ipAddr[1] << 0);
			}
		}
	}
	return 0;
}

BOOL CProFile::SaveProFile(LPCSTR lpcstrPath)
{
	CFile file;
	CString strLine;

	if(!file.Open(lpcstrPath, CFile::modeWrite))
	{
		AfxMessageBox(__T("打开保存文件失败"),  MB_OK | MB_ICONERROR);
		return false;
	}
	CArchive arch(&file, CArchive::store);
	arch.WriteString(__T("# HMI配置文件, 手动修改请确保格式正确"));
	arch.WriteString(__T("# JCIP代表基舱IP, TJIP代表塔基IP\r\n"));
	arch.WriteString(__T("#  机航IP\r\n"));
	strLine.Format("JCIP = %d.%d.%d.%d", 
		(m_jcip&0xff), (m_jcip>>8)&0xff, (m_jcip>>16)&0xff, (m_jcip>>24)&0xff);
	arch.WriteString(strLine);
	for(int i=0; i<nTjNum; i++)
	{
		strLine.Format("TJIP = %d.%d.%d.%d", 
			(m_tjip[i]&0xff), (m_tjip[i]>>8)&0xff, (m_tjip[i]>>16)&0xff, (m_tjip[i]>>24)&0xff);
		arch.WriteString(strLine);
	}
	return true;
}

BOOL CProFile::MakeBakFile(LPCSTR lpstrPath)
{
	CFile file;
	CFile bakFile;
	CString bakPathStr(lpstrPath);

	if(!file.Open(lpstrPath, CFile::modeRead))
	{
		AfxMessageBox(__T("制作备份文件失败:无法打开需要备份的文件!!!"), MB_OK | MB_ICONERROR);
		return false;
	}

	bakPathStr += ".bak";
	if(!bakFile.Open(bakPathStr, CFile::modeWrite))
	{
		AfxMessageBox(__T("打开备份文件失败"), MB_OK | MB_ICONERROR);
		return false;
	}
	
	CString strLine;
	CArchive archFile(&file, CArchive::load);
	CArchive archFileBak(&bakFile, CArchive::store);
	while(archFile.ReadString(strLine))
	{
		if(strLine.Find("#!") < 0)
		{
			continue;
		}
		archFileBak.WriteString(strLine);
	}
	return true;
}


