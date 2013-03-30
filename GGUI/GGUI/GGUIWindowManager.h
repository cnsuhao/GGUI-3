//-----------------------------------------------------------------------------
// GGUI窗口的管理类
// (C) oil
// 2012-09-16
//-----------------------------------------------------------------------------
#ifndef _GGUIWindowManager_h_
#define _GGUIWindowManager_h_
//-----------------------------------------------------------------------------
#include <vector>
#include "GGUIWindow.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	//-----------------------------------------------------------------------------
	class GGUIWindowManager
	{
	public:
		GGUIWindowManager();
		~GGUIWindowManager();
		static GGUIWindowManager* GetInstance();

		bool InitWindowManager();
		void ReleaseWindowManager();
		void UpdateWindowManager(float fFrameTime);
		void RenderWindowManager();

		GGUIWindow* CreateUIWindow(eWindowType theType);
		void ReleaseUIWindow(WindowID theWindowID);
		GGUIWindow* GetUIWindow(WindowID theWindowID);

		//根据WindowID获取这个窗口所对应的Delegate结构体。
		//如果这个窗口没有对应的Delegate，则为其申请一个。
		stWindowEventDelegate* GetWindowEventDelegate(WindowID theWindowID);
		void RaiseWindowEvent(WindowID theWindowID, DelegateID theDelegateID, eWindowEvent theEvent, unsigned int uiParam);

		//如果nIndex索引号的元素为有效值，则返回该元素；
		//如果是无效值，则使nIndex自增，当找到有效元素时，返回该元素和nIndex；
		//如果遍历数组完毕也没有找到有效元素，则返回NULL。
		//--nIndex [In][Out]
		//--pWindow [Out]
		bool Next(int& nIndex, GGUIWindow*& pWindow);

	protected:
		void PostUpdateWindowManager();
		//创建一个stWindowEventDelegate对象。返回该对象在数组中的索引值。
		//目前看来不需要删除一个stWindowEventDelegate对象，所以没有删除函数。
		DelegateID CreateDelegate();

	private:
		typedef std::vector<GGUIWindow*> vecWindow;
		typedef std::vector<stWindowEventDelegate*> vecDelegate;

	private:
		static GGUIWindowManager* ms_pInstance;
	private:
		//一个WindowID对应着一个GGUIWindow对象。
		//WindowID也即数组的索引号（下标）。
		//目前，数组中的元素还没有实现重复利用。一个窗口被delete后，其对应的数组
		//元素就被置为NULL，之后不会再次被使用。数组中有空洞，有空元素。
		vecWindow m_vecWindowList;
		//如果用户为一个窗口注册了事件响应函数，则这个窗口就拥有一个有效的DelegateID，
		//这个ID就是事件响应结构体stWindowEventDelegate在数组中的索引号。
		//如果一个窗口没有注册任何事件响应函数，则它的DelegateID为无效值。
		vecDelegate m_vecDelegateList;
	};
	//-----------------------------------------------------------------------------
	inline GGUIWindowManager* GGUIWindowManager::GetInstance()
	{
		return ms_pInstance;
	}
	//-----------------------------------------------------------------------------
	inline GGUIWindow* GGUIWindowManager::GetUIWindow(WindowID theWindowID)
	{
		if (theWindowID >= 0 && theWindowID < (WindowID)m_vecWindowList.size())
		{
			return m_vecWindowList[theWindowID];
		}
		else
		{
			return SoNULL;
		}
	}
	//-----------------------------------------------------------------------------
	inline void GGUIWindowManager::RaiseWindowEvent(WindowID theWindowID, DelegateID theDelegateID, eWindowEvent theEvent, unsigned int uiParam)
	{
		if (theDelegateID >= 0 && theDelegateID < (DelegateID)m_vecDelegateList.size())
		{
			if (theEvent >= 0 && theEvent < WindowEvent_Max)
			{
				DelegateForWindowEvent& theDelegate = m_vecDelegateList[theDelegateID]->theFunction[theEvent];
				if (!theDelegate.empty())
				{
					theDelegate(theWindowID, uiParam);
				}
			}
		}
	}
	//-----------------------------------------------------------------------------
	#define RegisterWindowEventA(theWindowID, theWindowEventID, theFuncPointer) \
	{ \
		GGUI::stWindowEventDelegate* pDelegate = GGUI::GGUIWindowManager::GetInstance()->GetWindowEventDelegate(theWindowID); \
		if (pDelegate) \
		{ \
			if (theWindowEventID >= 0 && theWindowEventID < GGUI::WindowEvent_Max) \
			{ \
				pDelegate->theFunction[theWindowEventID].bind(theFuncPointer); \
			} \
		} \
	}
	//-----------------------------------------------------------------------------
	#define RegisterWindowEventB(theWindowID, theWindowEventID, theObjectPoint, theFuncPointer) \
	{ \
		GGUI::stWindowEventDelegate* pDelegate = GGUI::GGUIWindowManager::GetInstance()->GetWindowEventDelegate(theWindowID); \
		if (pDelegate) \
		{ \
			if (theWindowEventID >= 0 && theWindowEventID < GGUI::WindowEvent_Max) \
			{ \
				pDelegate->theFunction[theWindowEventID].bind(theObjectPoint, theFuncPointer); \
			} \
		} \
	}
}
//-----------------------------------------------------------------------------
#endif //_GGUIWindowManager_h_
//-----------------------------------------------------------------------------
