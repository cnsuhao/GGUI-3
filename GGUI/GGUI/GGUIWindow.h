//-----------------------------------------------------------------------------
// GGUI窗口基类
// (C) oil
// 2012-09-16
//-----------------------------------------------------------------------------
#ifndef _GGUIWindow_h_
#define _GGUIWindow_h_
//-----------------------------------------------------------------------------
#include "GGUIBaseDefine.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	class GGUIWindow
	{
		friend class GGUIWindowManager;
		friend class GGUIInputProcess;
	public:
		//更新函数
		virtual void UpdateWindow(float fFrameTime);
		//绘制函数
		virtual void RenderWindow();

		//设置属性函数
		void SetPositionX(float fPosX);
		void SetPositionY(float fPosY);
		void SetPositionZ(float fPosZ);
		void SetWidth(float fWidth);
		void SetHeight(float fHeight);
		void SetColor(float fR, float fG, float fB);
		void SetAlpha(float fAlpha);
		void SetImageID(ImageID theID);
		virtual void SetVisible(bool bVisible);
		virtual void SetEnable(bool bEnable);

		//获取属性函数
		float GetPositionX() const;
		float GetPositionY() const;
		float GetPositionZ() const;
		float GetWidth() const;
		float GetHeight() const;
		void GetColor(float& fR, float& fG, float& fB) const;
		float GetAlpha() const;
		WindowID GetWindowID() const;
		ImageID GetImageID() const;
		DelegateID GetDelegateID() const;
		bool GetVisible() const;
		bool GetEnable() const;

		//根据鼠标坐标和本窗口的矩形区域，判断鼠标是否落在本窗口内部。
		//单纯的位置判断，不考虑窗口是否可见，是否被禁用等等。
		bool CheckMouseInWindowArea(float fMousePosX, float fMousePosY) const;

	protected:
		//事件响应函数。在函数内部会执行用户注册的Delegate函数。
		//派生类如果要重写这些函数的话，应该先执行自己的逻辑，再调用基类的事件响应函数。
		virtual void OnMouseEnterWindowArea();
		virtual void OnMouseLeaveWindowArea();
		virtual void OnMouseLeftButtonClickDown();
		virtual void OnMouseLeftButtonClickUp();

	protected:
		GGUIWindow();
		virtual ~GGUIWindow();
		void SetWindowID(WindowID theID);
		void SetDelegateID(DelegateID theID);
		void PostUpdateWindow();
		virtual void GenerateRenderUnit(stRenderUnit& theRenderUnit);

	protected:
		//本窗口的类型。
		eWindowType m_eMyWindowType;
		//本窗口的ID。
		WindowID m_nMyWindowID;
		//本窗口的贴图。
		ImageID m_nMyImageID;
		//本窗口的Delegate事件响应函数的ID。
		DelegateID m_nMyDelegateID;
		//
		float m_fPositionX;
		float m_fPositionY;
		float m_fPositionZ;
		float m_fWidth;
		float m_fHeight;
		float m_fColorR;
		float m_fColorG;
		float m_fColorB;
		float m_fColorA;
		//记录窗口属性数据是否发生了变化。如果发生了变化，就应该重绘。
		bool m_bDirty;
		//记录窗口是否可见。
		bool m_bVisible;
		//记录窗口是否可用。
		bool m_bEnable;
		//记录鼠标的坐标是否落在本窗口的矩形区域内。
		bool m_bMouseInWindowArea;

	};
	//-----------------------------------------------------------------------------
	inline bool GGUIWindow::CheckMouseInWindowArea(float fMousePosX, float fMousePosY) const
	{
		if (fMousePosX > m_fPositionX && fMousePosX < m_fPositionX + m_fWidth)
		{
			if (fMousePosY > m_fPositionY && fMousePosY < m_fPositionY + m_fHeight)
			{
				return true;
			}
		}
		return false;
	}
}
//-----------------------------------------------------------------------------
#endif //_GGUIWindow_h_
//-----------------------------------------------------------------------------
