//-----------------------------------------------------------------------------
// (C) oil
// 2012-12-02
//
// 本类允许用户定义派生类。通过调用GGUILog::SetInstance()把派生类对象的指针告知
// 给GGUI。派生类对象的释放由GGUI负责。
//
// 工程选项中用户可以设置使用ANSI字符集还是Unicode字符集。如果是Unicode字符集，
// 输出log过程中会吧Unicode字符串转换为ANSI字符串。
//-----------------------------------------------------------------------------
#include <Windows.h>
#include <tchar.h>
#include <strsafe.h>
#include "GGUILog.h"
#include "GGUIStringHelp.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	GGUILog* GGUILog::ms_pInstance = SoNULL;
	//-----------------------------------------------------------------------------
	GGUILog::GGUILog()
	:m_fp(SoNULL)
	,m_bOutputDebugString(false)
	,m_bFlushImmediately(false)
	{

	}
	//-----------------------------------------------------------------------------
	GGUILog::~GGUILog()
	{
		ms_pInstance = SoNULL;
	}
	//-----------------------------------------------------------------------------
	void GGUILog::SetInstance(GGUILog* pLog)
	{
		ms_pInstance = pLog;
	}
	//-----------------------------------------------------------------------------
	GGUILog* GGUILog::GetInstance()
	{
		return ms_pInstance;
	}
	//-----------------------------------------------------------------------------
	bool GGUILog::InitLog(const tchar* pszDiskFileName, bool bOutputDebugString, bool bFlushImmediately)
	{
		bool br = true;
		if (pszDiskFileName)
		{
			br = OpenDiskFile(pszDiskFileName);
		}
		m_bOutputDebugString = bOutputDebugString;
		m_bFlushImmediately = bFlushImmediately;
		return br;
	}
	//-----------------------------------------------------------------------------
	void GGUILog::ReleaseLog()
	{
		CloseDiskFile();
	}
	//-----------------------------------------------------------------------------
	void GGUILog::OutputDebug(const tchar* pFormat, ...)
	{
		AddLogHead("DEBUG");
		//
		va_list marker;
		va_start(marker, pFormat);
		AddLogBody(pFormat, marker);
		va_end(marker);
	}
	//-----------------------------------------------------------------------------
	void GGUILog::OutputWaring(const tchar* pFormat, ...)
	{
		AddLogHead("WARING");
		//
		va_list marker;
		va_start(marker, pFormat);
		AddLogBody(pFormat, marker);
		va_end(marker);
	}
	//-----------------------------------------------------------------------------
	void GGUILog::OutputError(const tchar* pFormat, ...)
	{
		AddLogHead("ERROR");
		//
		va_list marker;
		va_start(marker, pFormat);
		AddLogBody(pFormat, marker);
		va_end(marker);
	}
	//-----------------------------------------------------------------------------
	void GGUILog::AddLogHead(char* pType)
	{
		char szBuff[128] = {0};
		SYSTEMTIME stTime;
		GetSystemTime(&stTime);
		StringCbPrintfA(szBuff, sizeof(szBuff), 
			"%02u:%02u:%02u:%03u [%s] ",
			stTime.wHour+8, stTime.wMinute, stTime.wSecond, stTime.wMilliseconds, pType);
		if (m_fp)
		{
			size_t theBuffLength = 0;
			StringCbLengthA(szBuff, sizeof(szBuff), &theBuffLength);
			fwrite(szBuff, theBuffLength, 1, m_fp);
		}
		if (m_bOutputDebugString)
		{
			OutputDebugStringA(szBuff);
		}
	}
	//-----------------------------------------------------------------------------
	void GGUILog::AddLogBody(const tchar* pFormat, const va_list& kVaList)
	{
		tchar szBuff[2048] = {0};
		HRESULT	hr = StringCbVPrintf(szBuff, sizeof(szBuff), pFormat, kVaList);
		if (SUCCEEDED(hr))
		{
			if (m_fp)
			{
				size_t theBuffLength = 0;
				StringCbLength(szBuff, sizeof(szBuff), &theBuffLength);
				//添加换行符
				if (sizeof(tchar) == 1)
				{
					szBuff[theBuffLength] = TEXT('\n');
					++theBuffLength;
					szBuff[theBuffLength] = 0;
				}
				else
				{
					size_t theCharCount = theBuffLength / 2;
					szBuff[theCharCount] = TEXT('\n');
					szBuff[theCharCount+1] = TEXT('\0');
					theBuffLength += 2;
				}
				//
				if (sizeof(tchar) == 1)
				{
					fwrite(szBuff, theBuffLength, 1, m_fp);
				}
				else
				{
					int nNewStringLength = 0;
					char* pAnsi = UnicodeToAnsi(szBuff, &nNewStringLength);
					fwrite(pAnsi, nNewStringLength, 1, m_fp);
				}
				if (m_bFlushImmediately)
				{
					fflush(m_fp);
				}
			}
			if (m_bOutputDebugString)
			{
				OutputDebugString(szBuff);
			}
		}
		else
		{
			if (STRSAFE_E_INVALID_PARAMETER == hr)
			{
				::MessageBox(SoNULL, TEXT("STRSAFE_E_INVALID_PARAMETER"), TEXT("GGUILog Error"), MB_OK);
			}
			else if (STRSAFE_E_INSUFFICIENT_BUFFER == hr)
			{
				::MessageBox(SoNULL, TEXT("STRSAFE_E_INSUFFICIENT_BUFFER"), TEXT("GGUILog Error"), MB_OK);
			}
		}
	}
	//-----------------------------------------------------------------------------
	bool GGUILog::OpenDiskFile(const tchar* pszDiskFileName)
	{
		if (_tfopen_s(&m_fp, pszDiskFileName, TEXT("at+")) != 0)
		{
			//打开文件失败。
			m_fp = SoNULL;
			return false;
		}
		//
		char szBuff[1024] = {0};
		SYSTEMTIME stTime;
		GetSystemTime(&stTime);
		StringCbPrintfA(szBuff, sizeof(szBuff), 
			"========%04u:%02u:%02u %02u:%02u:%02u begin========\n",
			stTime.wYear, stTime.wMonth, stTime.wDay, stTime.wHour+8, stTime.wMinute, stTime.wSecond);
		size_t theBuffLength = 0;
		StringCbLengthA(szBuff, sizeof(szBuff), &theBuffLength);
		fwrite(szBuff, theBuffLength, 1, m_fp);
		return true;
	}
	//-----------------------------------------------------------------------------
	void GGUILog::CloseDiskFile()
	{
		if (m_fp)
		{
			char szBuff[1024] = {0};
			SYSTEMTIME stTime;
			GetSystemTime(&stTime);
			StringCbPrintfA(szBuff, sizeof(szBuff), 
				"========%4u:%2u:%2u %2u%2u%2u end========\n",
				stTime.wYear, stTime.wMonth, stTime.wDay, stTime.wHour, stTime.wMinute, stTime.wSecond);
			size_t theBuffLength = 0;
			StringCbLengthA(szBuff, sizeof(szBuff), &theBuffLength);
			fwrite(szBuff, theBuffLength, 1, m_fp);
			fflush(m_fp);
			fclose(m_fp);
			m_fp = SoNULL;
		}
	}
}
//-----------------------------------------------------------------------------
