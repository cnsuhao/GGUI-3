//-----------------------------------------------------------------------------
// GGUI窗口的容器类
// (C) oil
// 2012-09-16
//-----------------------------------------------------------------------------
#include "GGUIWindowManager.h"
#include "GGUIDXRenderManager.h"
#include "GGUIButton.h"
#include "GGUIPicture.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	GGUIWindowManager* GGUIWindowManager::ms_pInstance = SoNULL;
	//-----------------------------------------------------------------------------
	GGUIWindowManager::GGUIWindowManager()
	{
		ms_pInstance = this;
	}
	//-----------------------------------------------------------------------------
	GGUIWindowManager::~GGUIWindowManager()
	{
		ReleaseWindowManager();
		ms_pInstance = SoNULL;
	}
	//-----------------------------------------------------------------------------
	bool GGUIWindowManager::InitWindowManager()
	{
		m_vecWindowList.reserve(100);
		m_vecDelegateList.reserve(20);
		return true;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindowManager::ReleaseWindowManager()
	{
		int nWindowCount = (int)m_vecWindowList.size();
		for (int i=0; i<nWindowCount; ++i)
		{
			if (m_vecWindowList[i])
			{
				SAFE_DELETE(m_vecWindowList[i]);
			}
		}
		m_vecWindowList.clear();
		//
		int nDelegateCount = (int)m_vecDelegateList.size();
		for (int i=0; i<nDelegateCount; ++i)
		{
			if (m_vecDelegateList[i])
			{
				SAFE_DELETE(m_vecDelegateList[i]);
			}
		}
		m_vecDelegateList.clear();
	}
	//-----------------------------------------------------------------------------
	void GGUIWindowManager::UpdateWindowManager(float fFrameTime)
	{
		int nWindowCount = (int)m_vecWindowList.size();
		for (int i=0; i<nWindowCount; ++i)
		{
			if (m_vecWindowList[i])
			{
				m_vecWindowList[i]->UpdateWindow(fFrameTime);
			}
		}
	}
	//-----------------------------------------------------------------------------
	void GGUIWindowManager::RenderWindowManager()
	{
		//绘制之前，对每个窗口的Mesh顶点做最后的更新。
		PostUpdateWindowManager();
		//
		GGUIDXRenderManager* pDXRenderMgr = GGUIDXRenderManager::GetInstance();
		stRenderUnit theRenderUnit;
		int nWindowCount = (int)m_vecWindowList.size();
		for (int i=0; i<nWindowCount; ++i)
		{
			GGUIWindow* theWindow = m_vecWindowList[i];
			if (theWindow && theWindow->GetVisible())
			{
				pDXRenderMgr->PreRender();
				theWindow->GenerateRenderUnit(theRenderUnit);
				pDXRenderMgr->AddRnederUnit(theRenderUnit);
				pDXRenderMgr->DoRender();
				pDXRenderMgr->PostRender();
			}
		}
	}
	//-----------------------------------------------------------------------------
	GGUIWindow* GGUIWindowManager::CreateUIWindow(eWindowType theType)
	{
		GGUIWindow* pNewWindow = SoNULL;
		switch (theType)
		{
		case WindowType_Base:
			pNewWindow = new GGUIWindow;
			break;
		case WindowType_Button:
			pNewWindow = new GGUIButton;
			break;
		case WindowType_Picture:
			pNewWindow = new GGUIPicture;
			break;
		default:
			break;
		}
		if (pNewWindow)
		{
			WindowID newWindowID = (WindowID)m_vecWindowList.size();
			pNewWindow->SetWindowID(newWindowID);
			m_vecWindowList.push_back(pNewWindow);
		}
		return pNewWindow;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindowManager::ReleaseUIWindow(WindowID theWindowID)
	{
		if (theWindowID >= 0 && theWindowID < (WindowID)m_vecWindowList.size())
		{
			SAFE_DELETE(m_vecWindowList[theWindowID]);
		}
		else
		{
			//Wait for add log
		}
	}
	//-----------------------------------------------------------------------------
	stWindowEventDelegate* GGUIWindowManager::GetWindowEventDelegate(WindowID theWindowID)
	{
		stWindowEventDelegate* pDelegate = SoNULL;
		GGUIWindow* pTheWindow = GetUIWindow(theWindowID);
		if (pTheWindow)
		{
			DelegateID theDelegateID = pTheWindow->GetDelegateID();
			if (theDelegateID == Invalid_DelegateID)
			{
				theDelegateID = CreateDelegate();
				pTheWindow->SetDelegateID(theDelegateID);
			}
			if (theDelegateID >= 0 && theDelegateID < (DelegateID)m_vecDelegateList.size())
			{
				pDelegate = m_vecDelegateList[theDelegateID];
			}
		}
		return pDelegate;
	}
	//-----------------------------------------------------------------------------
	bool GGUIWindowManager::Next(int& nIndex, GGUIWindow*& pWindow)
	{
		if (nIndex >= 0 && nIndex < (int)m_vecWindowList.size())
		{
			if (m_vecWindowList[nIndex])
			{
				pWindow = m_vecWindowList[nIndex];
				++nIndex;
				return true;
			}
			else
			{
				++nIndex;
				return Next(nIndex, pWindow);
			}
		}
		else
		{
			pWindow = SoNULL;
			return false;
		}
	}
	//-----------------------------------------------------------------------------
	void GGUIWindowManager::PostUpdateWindowManager()
	{
		int nWindowCount = (int)m_vecWindowList.size();
		for (int i=0; i<nWindowCount; ++i)
		{
			if (m_vecWindowList[i])
			{
				m_vecWindowList[i]->PostUpdateWindow();
			}
		}
	}
	//-----------------------------------------------------------------------------
	DelegateID GGUIWindowManager::CreateDelegate()
	{
		DelegateID newDelegateID = (DelegateID)m_vecDelegateList.size();
		stWindowEventDelegate* pDelegate = new stWindowEventDelegate;
		m_vecDelegateList.push_back(pDelegate);
		return newDelegateID;
	}
}
//-----------------------------------------------------------------------------
