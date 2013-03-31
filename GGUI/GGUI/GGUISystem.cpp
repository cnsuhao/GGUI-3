//-----------------------------------------------------------------------------
// GGUI系统类
// (C) oil
// 2012-09-08
//-----------------------------------------------------------------------------
#include "GGUISystem.h"
#include "GGUIScreenParam.h"
#include "GGUIWindowManager.h"
#include "GGUIInputProcess.h"
#include "GGUIDXRenderManager.h"
#include "GGUIImagesetManager.h"
#include "GGUILog.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	GGUISystem* GGUISystem::ms_pInstance = NULL;
	//-----------------------------------------------------------------------------
	GGUISystem::GGUISystem()
	:m_pD3DDevice(NULL)
	{
		ms_pInstance = this;
	}
	//-----------------------------------------------------------------------------
	GGUISystem::~GGUISystem()
	{
		ReleaseUISystem();
		ms_pInstance = NULL;
	}
	//-----------------------------------------------------------------------------
	bool GGUISystem::InitUISystem(IDirect3DDevice9* pDevice, SoInt nScreenWidth, SoInt nScreenHeight)
	{
		//首先为m_pD3DDevice赋值。
		m_pD3DDevice = pDevice;
		GGUIScreenParam::ms_nScreenWidth = nScreenWidth;
		GGUIScreenParam::ms_nScreenHeight = nScreenHeight;
		//
		new GGUIWindowManager;
		if (!GGUIWindowManager::GetInstance()->InitWindowManager())
		{
			return false;
		}
		//
		new GGUIInputProcess;
		if (!GGUIInputProcess::GetInstance()->InitInputProcess())
		{
			return false;
		}
		//
		new GGUIDXRenderManager;
		if (!GGUIDXRenderManager::GetInstance()->InitDXRenderManager())
		{
			return false;
		}
		//
		new GGUIImagesetManager;
		if (!GGUIImagesetManager::GetInstance()->InitImagesetManager())
		{
			return false;
		}
		//
		return true;
	}
	//-----------------------------------------------------------------------------
	void GGUISystem::ReleaseUISystem()
	{
		delete GGUIImagesetManager::GetInstance();
		delete GGUIDXRenderManager::GetInstance();
		delete GGUIInputProcess::GetInstance();
		delete GGUIWindowManager::GetInstance();
		//最后尝试释放GGUILog。
		if (GGUILog::GetInstance())
		{
			GGUILog::GetInstance()->ReleaseLog();
			delete GGUILog::GetInstance();
		}
		m_pD3DDevice = NULL;
	}
	//-----------------------------------------------------------------------------
	void GGUISystem::UpdateGGUI(float fFrameTime)
	{
		GGUIWindowManager::GetInstance()->UpdateWindowManager(fFrameTime);
	}
	//-----------------------------------------------------------------------------
	void GGUISystem::RenderGGUI()
	{
		GGUIWindowManager::GetInstance()->RenderWindowManager();
	}
	//-----------------------------------------------------------------------------
	bool GGUISystem::InjectKeyEvent(eInputEvent theEvent, eKeyButton theKey)
	{
		bool bResult = false;
		switch (theEvent)
		{
		case ButtonDown:
			{
				
			}
			break;
		case ButtonUp:
			{

			}
		default:
			break;
		}
		return bResult;
	}
	//-----------------------------------------------------------------------------
	bool GGUISystem::InjectMouseEvent(eInputEvent theEvent, eMouseButton theButton, SoInt nParamA, SoInt nParamB)
	{
		bool bResult = false;
		switch (theEvent)
		{
		case ButtonDown:
			{
				switch (theButton)
				{
				case LeftMouse:
					GGUIInputProcess::GetInstance()->OnMouseLeftButtonDown();
					break;
				default:
					break;
				}
			}
			break;
		case ButtonUp:
			{
				switch (theButton)
				{
				case LeftMouse:
					GGUIInputProcess::GetInstance()->OnMouseLeftButtonUp();
					break;
				default:
					break;
				}
			}
			break;
		case MouseMove:
			{
				bResult = GGUIInputProcess::GetInstance()->OnMouseMove(nParamA, nParamB);
			}
			break;
		default:
			break;
		}
		return bResult;
	}
} //namespace GGUI
//-----------------------------------------------------------------------------
