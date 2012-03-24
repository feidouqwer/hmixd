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

BOOL CProFile::SaveProFile(LPCSTR lpcstrPath)
{
	CFile file;
	CString strLine;

	if(!file.Open(lpcstrPath, CFile::modeWrite))
	{
		AfxMessageBox(__T("�򿪱����ļ�ʧ��"),  MB_OK | MB_ICONERROR);
		return false;
	}
	CArchive arch(&file, CArchive::store);
	arch.WriteString(__T("# HMI�����ļ�, �ֶ��޸���ȷ����ʽ��ȷ"));
	arch.WriteString(__T("# JCIP�������IP, TJIP��������IP\r\n"));
	arch.WriteString(__T("#  ����IP\r\n"));
	strLine.Format("JCIP = %d.%d.%d.%d", 
		(m_CabinIp&0xff), (m_CabinIp>>8)&0xff, (m_CabinIp>>16)&0xff, (m_CabinIp>>24)&0xff);
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
		AfxMessageBox(__T("���������ļ�ʧ��:�޷�����Ҫ���ݵ��ļ�!!!"), MB_OK | MB_ICONERROR);
		return false;
	}

	bakPathStr += ".bak";
	if(!bakFile.Open(bakPathStr, CFile::modeWrite))
	{
		AfxMessageBox(__T("�򿪱����ļ�ʧ��"), MB_OK | MB_ICONERROR);
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


