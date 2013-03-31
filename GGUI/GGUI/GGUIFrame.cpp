//-----------------------------------------------------------------------------
// GGUI Frame控件
// (C) oil
// 2013-03-31
//-----------------------------------------------------------------------------
#include <algorithm> //std::find
#include "GGUIFrame.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	//-----------------------------------------------------------------------------
	void GGUIFrame::AddChild(WindowID theChildWindowID)
	{
		//判断这个WindowID是否已经存在了。
		vecWindowID::iterator it = std::find(m_vecChildWindowList.begin(), m_vecChildWindowList.end(), theChildWindowID);
		if (it != m_vecChildWindowList.end())
		{
			//已经存在了。
			return;
		}
		//
		m_vecChildWindowList.push_back(theChildWindowID);
	}
	//-----------------------------------------------------------------------------
	void GGUIFrame::RemoveChild(WindowID theChildWindowID)
	{
		vecWindowID::iterator it = std::find(m_vecChildWindowList.begin(), m_vecChildWindowList.end(), theChildWindowID);
		if (it == m_vecChildWindowList.end())
		{
			//没有找到这个子窗口。
			return;
		}
		//
		m_vecChildWindowList.erase(it);
	}
	//-----------------------------------------------------------------------------
	void GGUIFrame::SetDragRect(const stRect& newDragRect)
	{
		m_DragRect = newDragRect;
		//调整m_DragRect的矩形范围，不能超出窗口的矩形范围。
		if (m_DragRect.nLeft < m_WindowRect.nLeft)
		{
			m_DragRect.nLeft = m_WindowRect.nLeft;
		}
		else if (m_DragRect.nLeft > m_WindowRect.nRight)
		{
			m_DragRect.nLeft = m_WindowRect.nRight;
		}
		if (m_DragRect.nRight < m_DragRect.nLeft)
		{
			m_DragRect.nRight = m_DragRect.nLeft;
		}
		else if (m_DragRect.nRight > m_WindowRect.nRight)
		{
			m_DragRect.nRight = m_WindowRect.nRight;
		}
		if (m_DragRect.nTop < m_WindowRect.nTop)
		{
			m_DragRect.nTop = m_WindowRect.nTop;
		}
		else if (m_DragRect.nTop > m_WindowRect.nBottom)
		{
			m_DragRect.nTop = m_WindowRect.nBottom;
		}
		if (m_DragRect.nBottom < m_DragRect.nTop)
		{
			m_DragRect.nBottom = m_DragRect.nTop;
		}
		else if (m_DragRect.nBottom > m_WindowRect.nBottom)
		{
			m_DragRect.nBottom = m_WindowRect.nBottom;
		}
	}
	//-----------------------------------------------------------------------------
	GGUIFrame::GGUIFrame()
	{
		m_eMyWindowType = WindowType_Frame;
		m_vecChildWindowList.reserve(10);
	}
	//-----------------------------------------------------------------------------
	GGUIFrame::~GGUIFrame()
	{

	}
}
//-----------------------------------------------------------------------------
