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
	,m_nMyImageID(Invalid_ImageID)
	,m_nMyDelegateID(Invalid_DelegateID)
	,m_nZValue(0)
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
	void GGUIWindow::SetRectLeft(SoInt nLeft)
	{
		m_WindowRect.nLeft = nLeft;
		m_bDirty = true;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetRectRight(SoInt nRight)
	{
		m_WindowRect.nRight = nRight;
		m_bDirty = true;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetRectTop(SoInt nTop)
	{
		m_WindowRect.nTop = nTop;
		m_bDirty = true;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetRectBottom(SoInt nBottom)
	{
		m_WindowRect.nBottom = nBottom;
		m_bDirty = true;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetZValue(SoInt nZValue)
	{
		m_nZValue = nZValue;
		m_bDirty = true;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetWidth(SoInt nWidth)
	{
		m_WindowRect.nRight = m_WindowRect.nLeft + nWidth;
		m_bDirty = true;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetHeight(SoInt nHeight)
	{
		m_WindowRect.nBottom = m_WindowRect.nTop + nHeight;
		m_bDirty = true;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetColor(SoUInt8 byColorR, SoUInt8 byColorG, SoUInt8 byColorB)
	{
		m_WindowColor.byColorR = byColorR;
		m_WindowColor.byColorG = byColorG;
		m_WindowColor.byColorB = byColorB;
		m_bDirty = true;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetAlpha(SoUInt8 byColorA)
	{
		m_WindowColor.byColorA = byColorA;
		m_bDirty = true;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetImageID(ImageID theID)
	{
		m_nMyImageID = theID;
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
	SoInt GGUIWindow::GetRectLeft() const
	{
		return m_WindowRect.nLeft;
	}
	//-----------------------------------------------------------------------------
	SoInt GGUIWindow::GetRectRight() const
	{
		return m_WindowRect.nRight;
	}
	//-----------------------------------------------------------------------------
	SoInt GGUIWindow::GetRectTop() const
	{
		return m_WindowRect.nTop;
	}
	//-----------------------------------------------------------------------------
	SoInt GGUIWindow::GetRectBottom() const
	{
		return m_WindowRect.nBottom;
	}
	//-----------------------------------------------------------------------------
	SoInt GGUIWindow::GetZValue() const
	{
		return m_nZValue;
	}
	//-----------------------------------------------------------------------------
	SoInt GGUIWindow::GetWidth() const
	{
		return m_WindowRect.nRight - m_WindowRect.nLeft;
	}
	//-----------------------------------------------------------------------------
	SoInt GGUIWindow::GetHeight() const
	{
		return m_WindowRect.nBottom - m_WindowRect.nTop;
	}
	//-----------------------------------------------------------------------------
	WindowID GGUIWindow::GetWindowID() const
	{
		return m_nMyWindowID;
	}
	//-----------------------------------------------------------------------------
	ImageID GGUIWindow::GetImageID() const
	{
		return m_nMyImageID;
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
		theRenderUnit.theWindowRect = m_WindowRect;
		theRenderUnit.fZValue = ((float)m_nZValue) / MaxZValue;
		theRenderUnit.uiColor32 = Help_GenerateColor32(m_WindowColor);
		theRenderUnit.theImageID = m_nMyImageID;
	}
}
//-----------------------------------------------------------------------------
