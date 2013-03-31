//-----------------------------------------------------------------------------
// GGUI Frame控件
// (C) oil
// 2013-03-31
//-----------------------------------------------------------------------------
#ifndef _GGUIFrame_h_
#define _GGUIFrame_h_
//-----------------------------------------------------------------------------
#include <vector>
#include "GGUIWindow.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	class GGUIFrame : public GGUIWindow
	{
		friend class GGUIWindowManager;
	public:
		void AddChild(WindowID theChildWindowID);
		void RemoveChild(WindowID theChildWindowID);

		void SetDragRect(const stRect& newDragRect);

	protected:
		GGUIFrame();
		virtual ~GGUIFrame();

	protected:
		typedef std::vector<WindowID> vecWindowID;

	protected:
		//本窗口允许拖动。记录允许触发拖动的矩形区域。相对坐标。
		stRect m_DragRect;
		//存储子窗口。
		vecWindowID m_vecChildWindowList;
	};
}
//-----------------------------------------------------------------------------
#endif //_GGUIFrame_h_
//-----------------------------------------------------------------------------
