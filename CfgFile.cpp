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
	number = DEFAULT_NUMBER;
}

CCfgFile::~CCfgFile()
{

}

bool CCfgFile::LoadCfgFile()
{
	CFile file;
	CString strLine;
	int nIndex;

	if(!file.Open("HMICfg.txt", CFile::modeRead))
	{
		return false;
	}
	CArchive arch(&file, CArchive::load);
	while(arch.ReadString(strLine))
	{
		TRACE("%s\n", strLine);
		strLine.TrimLeft();
		if(strLine.Find("#", 0) == 0)
		{
			continue;
		}
		nIndex = strLine.Find("=", 0);
		if(nIndex <= 0)
		{
			continue;
		}
		CString leftStr = strLine.Left(nIndex);
		CString rightStr = strLine.Right(strLine.GetLength() - nIndex - 1);
		leftStr.TrimLeft();
		leftStr.TrimRight();
		rightStr.TrimLeft();
		rightStr.TrimRight();
		TRACE("nIndex = %d", nIndex);
		TRACE("LeftStr = %s\r\n", leftStr);
		TRACE("RightStr = %s\r\n", rightStr);
		if(leftStr == "number")
		{
			number = atoi(rightStr);
			if(number < 0)
			{
				number = 0;
			}
			else if(number > 1000)
			{
				number = 1000;
			}
		}
	}
	return true;
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
	return number;
}
