//-----------------------------------------------------------------------------
#include "MyApp.h"
#include "../GGUI/GGUIImagesetManager.h"
#include "../GGUI/GGUIStringHelp.h"
//-----------------------------------------------------------------------------
SoD3DApp* SoD3DApp::CreateInstance(void)
{
	return new MyApp;
}
//-----------------------------------------------------------------------------
MyApp::MyApp(void)
:SoD3DApp()
,m_pUIWindow(NULL)
,m_eTransformState(Transform_None)
,m_nTransformWindowID(Invalid_WindowID)
,m_fAccTimeForTransform(0.0f)
{

}
//-----------------------------------------------------------------------------
MyApp::~MyApp(void)
{

}
//-----------------------------------------------------------------------------
void MyApp::BeforeCreateWindow(void)
{
	m_strWinName = TEXT("TEST");
	m_bSizeAble = false;
	m_lClientW = 800;
	m_lClientH = 600;
	m_dwBgColor = RGB(188,188,188);
}

//-----------------------------------------------------------------------------
bool MyApp::InitResource(void)
{
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//创建GGUI系统
	new GGUISystem;
	GGUISystem::GetInstance()->InitUISystem(SoD3DApp::GetD3DDevice(), m_lClientW, m_lClientH);
	//
	GGUILog* pLog = new GGUILog;
	pLog->InitLog(TEXT("Log.txt"), true, true);
	GGUILog::SetInstance(pLog);
	//
	//CreateUIWindowA();
	CreateWindowList();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	return true;
}

//-----------------------------------------------------------------------------
void MyApp::ClearResource(void)
{
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//ReleaseWindowList();
	ReleaseUIWindowA();
	//释放GGUI系统
	delete GGUISystem::GetInstance();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
}

//-----------------------------------------------------------------------------
void MyApp::Update(float fAccTime, float fFrameTime)
{
	if (m_eTransformState != Transform_None)
	{
		m_fAccTimeForTransform += fFrameTime;
		if (m_fAccTimeForTransform >= TransformTime)
		{
			if (m_eTransformState == Transform_Large)
			{
				ForceLarge(m_nTransformWindowID);
				m_eTransformState = Transform_WaitForRestore;
			}
			else if (m_eTransformState == Transform_Restore)
			{
				ForceRestore(m_nTransformWindowID);
				m_eTransformState = Transform_None;
			}
			m_nTransformWindowID = Invalid_WindowID;
			m_fAccTimeForTransform = 0.0f;
		}
		else
		{
			float fDestPosLeft = 0.0f;
			float fDestPosRight = 0.0f;
			float fDestPosUp = 0.0f;
			float fDestPosDown = 0.0f;
			float fRemainTime = TransformTime - (m_fAccTimeForTransform-fFrameTime);
			//
			if (m_eTransformState == Transform_Large)
			{
				fDestPosLeft = 0.0f;
				fDestPosRight = (float)m_lClientW;
				fDestPosUp = 0.0f;
				fDestPosDown = (float)m_lClientH;
			}
			else if (m_eTransformState == Transform_Restore)
			{
				int x = m_nTransformWindowID % PictureCountX;
				int y = m_nTransformWindowID / PictureCountY;
				fDestPosLeft = MarginX + x*(MarginX+PictureWindowWidth);
				fDestPosRight = fDestPosLeft + PictureWindowWidth;
				fDestPosUp = MarginY + y*(MarginY+PictureWindowHeight);
				fDestPosDown = fDestPosUp + PictureWindowHeight;
			}
			//
			GGUIWindow* pWindow = GGUIWindowManager::GetInstance()->GetUIWindow(m_nTransformWindowID);
			if (pWindow)
			{
				float fCurrentPosLeft = pWindow->GetRectLeft();
				float fCurrentPosRight = fCurrentPosLeft + pWindow->GetWidth();
				float fCurrentPosUp = pWindow->GetRectTop();
				float fCurrentPosDown = fCurrentPosUp + pWindow->GetHeight();
				//求出矩形的四个顶点的移动速度，包含方向。
				//值为正表示Transform_Large，值为负表示Transform_Restore。
				float fSpeedLeft = (fDestPosLeft - fCurrentPosLeft) / fRemainTime;
				float fSpeedRight = (fDestPosRight - fCurrentPosRight) / fRemainTime;
				float fSpeedUp = (fDestPosUp - fCurrentPosUp) / fRemainTime;
				float fSpeedDown = (fDestPosDown - fCurrentPosDown) / fRemainTime;
				//
				float fNewPosLeft = fCurrentPosLeft + fSpeedLeft * fFrameTime;
				float fNewPosRight = fCurrentPosRight + fSpeedRight * fFrameTime;
				float fNewPosUp = fCurrentPosUp + fSpeedUp * fFrameTime;
				float fNewPosDown = fCurrentPosDown + fSpeedDown * fFrameTime;
				//
				pWindow->SetRectLeft(fNewPosLeft);
				pWindow->SetRectTop(fNewPosUp);
				pWindow->SetWidth(fNewPosRight - fNewPosLeft);
				pWindow->SetHeight(fNewPosDown - fNewPosUp);
				pWindow->SetZValue(300);
			}
		}
	}

	GGUISystem::GetInstance()->UpdateGGUI(fFrameTime);
}

//-----------------------------------------------------------------------------
void MyApp::Draw(void)
{
	GGUISystem::GetInstance()->RenderGGUI();
}

//-----------------------------------------------------------------------------
LRESULT MyApp::MsgProcess(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_MOUSEMOVE:
		{
			//本窗口处理了这个消息。
			int xPos = LOWORD(lParam);
			int yPos = HIWORD(lParam);
			GGUISystem::GetInstance()->InjectMouseEvent(MouseMove, Mouse_Invalid, xPos, yPos);
		}
		break;
	case WM_LBUTTONDOWN:
		{
			GGUISystem::GetInstance()->InjectMouseEvent(ButtonDown, LeftMouse, 0, 0);
		}
		break;
	case WM_LBUTTONUP:
		{
			GGUISystem::GetInstance()->InjectMouseEvent(ButtonUp, LeftMouse, 0, 0);
		}
		break;
	default:
		break;
	}
	//
	return __super::MsgProcess(uMsg, wParam, lParam);
}

//-----------------------------------------------------------------------------
void MyApp::OnMouseClick(WindowID theWindowID, int uiParam)
{

}
//-----------------------------------------------------------------------------
void MyApp::OnMouseClickWindowList(WindowID theWindowID, int uiParam)
{
	if (m_eTransformState == Transform_None)
	{
		m_eTransformState = Transform_Large;
		m_nTransformWindowID = theWindowID;
		m_fAccTimeForTransform = 0.0f;
	}
	else if (m_eTransformState == Transform_Large)
	{
		if (m_nTransformWindowID == theWindowID)
		{
			m_eTransformState = Transform_Restore;
			m_nTransformWindowID = theWindowID;
			m_fAccTimeForTransform = TransformTime - m_fAccTimeForTransform;
		}
		else
		{
			//立即恢复原状
			ForceRestore(m_nTransformWindowID);
			m_eTransformState = Transform_Large;
			m_nTransformWindowID = theWindowID;
			m_fAccTimeForTransform = 0.0f;
		}
	}
	else if (m_eTransformState == Transform_WaitForRestore)
	{
		m_eTransformState = Transform_Restore;
		m_nTransformWindowID = theWindowID;
		m_fAccTimeForTransform = 0.0f;
	}
	else if (m_eTransformState == Transform_Restore)
	{
		if (m_nTransformWindowID == theWindowID)
		{
			m_eTransformState = Transform_Large;
			m_nTransformWindowID = theWindowID;
			m_fAccTimeForTransform = TransformTime - m_fAccTimeForTransform;
		}
		else
		{
			//立即恢复原状
			ForceRestore(m_nTransformWindowID);
			m_eTransformState = Transform_Large;
			m_nTransformWindowID = theWindowID;
			m_fAccTimeForTransform = 0.0f;
		}
	}
}
//-----------------------------------------------------------------------------
void MyApp::CreateUIWindowA()
{
	m_pUIWindow = GGUIWindowManager::GetInstance()->CreateUIWindow(WindowType_Picture);
	m_pUIWindow->SetRectLeft(0);
	m_pUIWindow->SetRectTop(0);
	m_pUIWindow->SetZValue(500);
	m_pUIWindow->SetWidth(600);
	m_pUIWindow->SetHeight(403);

	ImagesetID theImagesetID = Invalid_ImagesetID;
	ImageID theImageID = Invalid_ImageID;
	GGUIImagesetManager::GetInstance()->CreateImagesetByTextureFile(TEXT("A.jpg"), GGUITinyString(TEXT("Ajpg")), &theImagesetID, &theImageID);
	m_pUIWindow->SetImageID(theImageID);
	//m_pUIWindow->SetImageByFileName(TEXT("B.tga"));
	m_pUIWindow->UpdateWindow(0.0f);

	RegisterWindowEventB(m_pUIWindow->GetWindowID(), WindowEvent_MouseEnterWindowArea, this, &MyApp::OnMouseClick);
}
//-----------------------------------------------------------------------------
void MyApp::ReleaseUIWindowA()
{
	if (m_pUIWindow)
	{
		GGUIWindowManager::GetInstance()->ReleaseUIWindow(m_pUIWindow->GetWindowID());
	}
}
//-----------------------------------------------------------------------------
void MyApp::CreateWindowList()
{
	tchar szBuff[56] = {0};
	//
	for (int y=0; y<PictureCountY; ++y)
	{
		for (int x=0; x<PictureCountX; ++x)
		{
			GGUIWindow* pWindow = GGUIWindowManager::GetInstance()->CreateUIWindow(WindowType_Picture);
			pWindow->SetRectLeft(MarginX + x*(MarginX+PictureWindowWidth));
			pWindow->SetRectTop(MarginY + y*(MarginY+PictureWindowHeight));
			pWindow->SetZValue(500);
			pWindow->SetWidth(PictureWindowWidth);
			pWindow->SetHeight(PictureWindowHeight);
			SoPrintf(szBuff, sizeof(szBuff), TEXT("Pic/%d.bmp"), y*PictureCountX+x);
			ImagesetID theImagesetID = Invalid_ImagesetID;
			ImageID theImageID = Invalid_ImageID;
			GGUIImagesetManager::GetInstance()->CreateImagesetByTextureFile(szBuff, GGUITinyString(szBuff), &theImagesetID, &theImageID);
			pWindow->SetImageID(theImageID);
			RegisterWindowEventB(pWindow->GetWindowID(), WindowEvent_MouseLeftButtonClickDown, this, &MyApp::OnMouseClickWindowList);
			m_theWindowList.push_back(pWindow->GetWindowID());
		}
	}
}
//-----------------------------------------------------------------------------
void MyApp::ReleaseWindowList()
{

}
//-----------------------------------------------------------------------------
void MyApp::ForceRestore(WindowID theWindowID)
{
	GGUIWindow* pWindow = GGUIWindowManager::GetInstance()->GetUIWindow(theWindowID);
	if (pWindow == NULL)
	{
		return;
	}
	//
	int x = theWindowID % PictureCountX;
	int y = theWindowID / PictureCountY;
	pWindow->SetRectLeft(MarginX + x*(MarginX+PictureWindowWidth));
	pWindow->SetRectTop(MarginY + y*(MarginY+PictureWindowHeight));
	pWindow->SetZValue(500);
	pWindow->SetWidth(PictureWindowWidth);
	pWindow->SetHeight(PictureWindowHeight);
}
//-----------------------------------------------------------------------------
void MyApp::ForceLarge(WindowID theWindowID)
{
	GGUIWindow* pWindow = GGUIWindowManager::GetInstance()->GetUIWindow(theWindowID);
	if (pWindow == NULL)
	{
		return;
	}
	//
	pWindow->SetRectLeft(0);
	pWindow->SetRectTop(0);
	pWindow->SetZValue(300);
	pWindow->SetWidth(m_lClientW);
	pWindow->SetHeight(m_lClientH);
}
//-----------------------------------------------------------------------------
//  MyApp.cpp
//-----------------------------------------------------------------------------
