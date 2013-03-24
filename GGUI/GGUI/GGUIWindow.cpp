//-----------------------------------------------------------------------------
// GGUI窗口基类
// (C) oil
// 2012-09-16
//-----------------------------------------------------------------------------
#include "GGUIWindow.h"
#include "GGUIWindowManager.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	GGUIWindow::GGUIWindow()
	:m_eMyWindowType(WindowType_Base)
	,m_nMyWindowID(Invalid_WindowID)
	,m_nMyImagesetID(Invalid_ImagesetID)
	,m_nMyImageRectID(Invalid_ImageRectID)
	,m_nMyDelegateID(Invalid_DelegateID)
	,m_fPositionX(0.0f)
	,m_fPositionY(0.0f)
	,m_fPositionZ(0.0f)
	,m_fWidth(0.0f)
	,m_fHeight(0.0f)
	,m_fColorR(0.0f)
	,m_fColorG(0.0f)
	,m_fColorB(0.0f)
	,m_fColorA(0.0f)
	,m_bDirty(false)
	,m_bVisible(true)
	,m_bEnable(true)
	,m_bMouseInWindowArea(false)
	{

	}
	//-----------------------------------------------------------------------------
	GGUIWindow::~GGUIWindow()
	{

	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::UpdateWindow(float fFrameTime)
	{

	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::RenderWindow()
	{
		if (!m_bVisible)
		{
			return;
		}

	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetPositionX(float fPosX)
	{
		m_fPositionX = fPosX;
		m_bDirty = true;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetPositionY(float fPosY)
	{
		m_fPositionY = fPosY;
		m_bDirty = true;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetPositionZ(float fPosZ)
	{
		m_fPositionZ = fPosZ;
		m_bDirty = true;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetWidth(float fWidth)
	{
		m_fWidth = fWidth;
		m_bDirty = true;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetHeight(float fHeight)
	{
		m_fHeight = fHeight;
		m_bDirty = true;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetColor(float fR, float fG, float fB)
	{
		m_fColorR = fR;
		m_fColorG = fG;
		m_fColorB = fB;
		m_bDirty = true;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetAlpha(float fAlpha)
	{
		m_fColorA = fAlpha;
		m_bDirty = true;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetImagesetID(ImagesetID theID)
	{
		m_nMyImagesetID = theID;
		m_bDirty = true;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetImageRectID(ImageRectID theID)
	{
		m_nMyImageRectID = theID;
		m_bDirty = true;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetVisible(bool bVisible)
	{
		m_bVisible = bVisible;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetEnable(bool bEnable)
	{
		m_bEnable = bEnable;
	}
	//-----------------------------------------------------------------------------
	float GGUIWindow::GetPositionX() const
	{
		return m_fPositionX;
	}
	//-----------------------------------------------------------------------------
	float GGUIWindow::GetPositionY() const
	{
		return m_fPositionY;
	}
	//-----------------------------------------------------------------------------
	float GGUIWindow::GetPositionZ() const
	{
		return m_fPositionZ;
	}
	//-----------------------------------------------------------------------------
	float GGUIWindow::GetWidth() const
	{
		return m_fWidth;
	}
	//-----------------------------------------------------------------------------
	float GGUIWindow::GetHeight() const
	{
		return m_fHeight;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::GetColor(float& fR, float& fG, float& fB) const
	{
		fR = m_fColorR;
		fG = m_fColorG;
		fB = m_fColorB;
	}
	//-----------------------------------------------------------------------------
	float GGUIWindow::GetAlpha() const
	{
		return m_fColorA;
	}
	//-----------------------------------------------------------------------------
	WindowID GGUIWindow::GetWindowID() const
	{
		return m_nMyWindowID;
	}
	//-----------------------------------------------------------------------------
	ImagesetID GGUIWindow::GetImagesetID() const
	{
		return m_nMyImagesetID;
	}
	//-----------------------------------------------------------------------------
	ImageRectID GGUIWindow::GetImageRectID() const
	{
		return m_nMyImageRectID;
	}
	//-----------------------------------------------------------------------------
	DelegateID GGUIWindow::GetDelegateID() const
	{
		return m_nMyDelegateID;
	}
	//-----------------------------------------------------------------------------
	bool GGUIWindow::GetVisible() const
	{
		return m_bVisible;
	}
	//-----------------------------------------------------------------------------
	bool GGUIWindow::GetEnable() const
	{
		return m_bEnable;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::OnMouseEnterWindowArea()
	{
		m_bMouseInWindowArea = true;
		GGUIWindowManager::GetInstance()->RaiseWindowEvent(m_nMyWindowID, m_nMyDelegateID, WindowEvent_MouseEnterWindowArea, 0);
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::OnMouseLeaveWindowArea()
	{
		m_bMouseInWindowArea = false;
		GGUIWindowManager::GetInstance()->RaiseWindowEvent(m_nMyWindowID, m_nMyDelegateID, WindowEvent_MouseLeaveWindowArea, 0);
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::OnMouseLeftButtonClickDown()
	{
		GGUIWindowManager::GetInstance()->RaiseWindowEvent(m_nMyWindowID, m_nMyDelegateID, WindowEvent_MouseLeftButtonClickDown, 0);
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::OnMouseLeftButtonClickUp()
	{
		GGUIWindowManager::GetInstance()->RaiseWindowEvent(m_nMyWindowID, m_nMyDelegateID, WindowEvent_MouseLeftButtonClickUp, 0);
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetWindowID(WindowID theID)
	{
		m_nMyWindowID = theID;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetDelegateID(DelegateID theID)
	{
		m_nMyDelegateID = theID;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::PostUpdateWindow()
	{
		if (m_bDirty)
		{
			m_bDirty = false;
		}
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::GenerateRenderUnit(stRenderUnit& theRenderUnit)
	{
		theRenderUnit.fPositionX = m_fPositionX;
		theRenderUnit.fPositionY = m_fPositionY;
		theRenderUnit.fPositionZ = m_fPositionZ;
		theRenderUnit.fWidth = m_fWidth;
		theRenderUnit.fHeight = m_fHeight;
		theRenderUnit.fColorR = m_fColorR;
		theRenderUnit.fColorG = m_fColorG;
		theRenderUnit.fColorB = m_fColorB;
		theRenderUnit.fColorA = m_fColorA;
		theRenderUnit.theImagesetID = m_nMyImagesetID;
		theRenderUnit.theImageRectID = m_nMyImageRectID;
	}
}
//-----------------------------------------------------------------------------
