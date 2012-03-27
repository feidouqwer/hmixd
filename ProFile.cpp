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

CProFile::CProFile()
{
}

CProFile::~CProFile()
{

}

BOOL CProFile::MakeBakFile(LPCSTR lpstrPath, LPCSTR lpstrBakPath)
{	
	if(lpstrPath == NULL || lpstrBakPath == NULL)
		return FALSE;

	return CopyFile(lpstrPath, lpstrBakPath, FALSE);
}


BOOL CProFile::SetNetIP(DWORD dwNetIP)
{
	CFile proFile, proBakFile;
	CString proFileName = "hmi.properties";
	CString proBakFileName = proFileName + ".bak";
	
	if(!MakeBakFile(proFileName, proBakFileName))
	{
		AfxMessageBox(__T("制作备份文件失败!"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	if(!proFile.Open(proFileName, CFile::modeWrite))
	{
		AfxMessageBox(__T("打开属性文件失败!"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	if(!proBakFile.Open(proBakFileName, CFile::modeRead))
	{
		AfxMessageBox(__T("打开备份属性文件失败!"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	CString strLine;
	CArchive fileArch(&proFile, CArchive::store);
	CArchive bakFileArch(&proBakFile, CArchive::load);
	while(bakFileArch.ReadString(strLine))
	{
		if(strLine.Left(1) != "#" && strLine.Find("NetIP") != -1)
		{
			strLine.Format("NetIP = %d.%d.%d.%d", 
							(dwNetIP >> 24) & 0xff,
							(dwNetIP >> 16) & 0xff,
							(dwNetIP >> 8) & 0xff,
							(dwNetIP >> 0) & 0xff);
		}
		fileArch.WriteString(strLine + "\r\n");
	}
	return TRUE;
}
