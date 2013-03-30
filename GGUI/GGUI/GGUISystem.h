//-----------------------------------------------------------------------------
// GGUI系统类
// (C) oil
// 2012-09-08
//-----------------------------------------------------------------------------
#ifndef _GGUISystem_h_
#define _GGUISystem_h_
//-----------------------------------------------------------------------------
#include "GGUID3DDefine.h"
#include "GGUIInputDefine.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	class GGUISystem
	{
	public:
		GGUISystem();
		~GGUISystem();
		static GGUISystem* GetInstance();

		//初始化GGUI系统，创建必要的组件和资源。
		bool InitUISystem(IDirect3DDevice9* pDevice, float fScreenWidth, float fScreenHeight);
		//释放GGUI系统。
		void ReleaseUISystem();
		//获取D3D设备指针。
		IDirect3DDevice9* GetD3DDevice();

		//更新。
		void UpdateGGUI(float fFrameTime);
		//绘制。
		void RenderGGUI();

		//注入一个键盘按键事件。
		//返回ture表示这个按键事件被本系统响应并处理了；
		//返回false表示本系统不关心并没有处理这个事件。
		bool InjectKeyEvent(eInputEvent theEvent, eKeyButton theKey);
		//注入一个鼠标事件。
		//返回ture表示这个事件被本系统响应并处理了；
		//返回false表示本系统不关心并没有处理这个事件。
		bool InjectMouseEvent(eInputEvent theEvent, eMouseButton theButton, float fParamA, float fParamB);

	private:
		static GGUISystem* ms_pInstance;

	private:
		IDirect3DDevice9* m_pD3DDevice;
	};
	//-----------------------------------------------------------------------------
	inline GGUISystem* GGUISystem::GetInstance()
	{
		return ms_pInstance;
	}
	//-----------------------------------------------------------------------------
	inline IDirect3DDevice9* GGUISystem::GetD3DDevice()
	{
		return m_pD3DDevice;
	}
	//-----------------------------------------------------------------------------
} //namespace GGUI
//-----------------------------------------------------------------------------
#endif //_GGUISystem_h_
//-----------------------------------------------------------------------------
