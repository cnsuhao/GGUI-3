//-----------------------------------------------------------------------------
// (C) oil
// 2013-03-24
//-----------------------------------------------------------------------------
#ifndef _GGUIBaseDefine_h_
#define _GGUIBaseDefine_h_
//-----------------------------------------------------------------------------
#include <string>
#include "FastDelegate.h"
#include "FastDelegateBind.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	typedef __int8  SoInt8;
	typedef __int16 SoInt16;
	typedef __int32 SoInt32;
	typedef __int64 SoInt64;
	typedef __int32 SoInt;
	//
	typedef unsigned __int8  SoUInt8;
	typedef unsigned __int16 SoUInt16;
	typedef unsigned __int32 SoUInt32;
	typedef unsigned __int64 SoUInt64;
	typedef unsigned __int32 SoUInt;
	//
	typedef float SoFloat; //32位的浮点数，精确到6位有效数字。
	typedef double SoDouble; //64位的浮点数，精确到16位有效数字。
	//指针的无效值。
#define SoNULL 0

	//-----------------------------------------------------------------------------
#if defined(_UNICODE) || defined(UNICODE)
	typedef wchar_t tchar;
	typedef std::wstring tstring;
#else
	typedef char tchar;
	typedef std::string tstring;
#endif

	//-----------------------------------------------------------------------------
	//安全的删除一个对象。
#define SAFE_DELETE(p);  { if(p) { delete (p); (p)=0; } }
	//安全的删除一个对象数组。
#define SAFE_DELETE_ARRAY(p);  { if(p) { delete [] (p); (p)=0; } }

	//-----------------------------------------------------------------------------
	typedef SoInt ImagesetID;
	static const ImagesetID Invalid_ImagesetID = -1;
	typedef SoInt ImageID;
	static const ImageID Invalid_ImageID = -1;
	//ImagesetID的最小值是0，最大值是(ImageID_ImagesetID-1)。
	//ImageID的最小值是ImageID_ImagesetID。
	//规则是这样，如果ImageID是210045，则表示ImagesetID为21，索引值为45。
	static const SoInt ImageID_ImagesetID = 10000;

	typedef SoInt WindowID;
	static const WindowID Invalid_WindowID = -1;
	//
	typedef SoInt DelegateID;
	static const DelegateID Invalid_DelegateID = -1;

	//窗口的各个类型。
	enum eWindowType
	{
		WindowType_Invalid = -1, 
		WindowType_Base = 0, //GGUIWindow类型
		WindowType_Button, //GGUIButton类型
		WindowType_Picture, //GGUIPicture类型
		WindowType_Max,
	};

	//窗口能够触发哪些消息事件。
	enum eWindowEvent
	{
		//无效值。
		WindowEvent_Invalid = -1,
		//鼠标进入了窗口的矩形区域。
		//触发条件：窗口可见，鼠标进入窗口矩形区域内。
		//注意：不考虑窗口是否被禁用。如果窗口重叠的话，会出现同一时刻鼠标处于多个窗口的矩形区域内。
		WindowEvent_MouseEnterWindowArea = 0,
		//鼠标离开了窗口的矩形区域。
		//触发条件：窗口可见，鼠标离开窗口矩形区域内。
		//注意：不考虑窗口是否被禁用。当鼠标处于窗口矩形区域内时，窗口由可见变为不可见，则也会触发这个事件。
		WindowEvent_MouseLeaveWindowArea,
		//鼠标左键在窗口上按下了。
		//触发条件：窗口没有被禁用，鼠标在窗口的矩形区域内，鼠标左键按下。
		WindowEvent_MouseLeftButtonClickDown,
		//鼠标左键在窗口上抬起了。
		//触发条件：窗口没有被禁用，鼠标在窗口的矩形区域内，鼠标左键抬起。
		WindowEvent_MouseLeftButtonClickUp,
		//最大值。
		WindowEvent_Max,
	};

	//窗口事件的delegate函数。
	//--WindowID 触发这个事件的Window。
	//--int 附带的参数。
	typedef fastdelegate::FastDelegate2<WindowID, int> DelegateForWindowEvent;
	//
	struct stWindowEventDelegate
	{
		DelegateForWindowEvent theFunction[WindowEvent_Max];
	};


	//窗口的绘制参数。
	struct stRenderUnit
	{
		float fPositionX;
		float fPositionY;
		float fPositionZ;
		float fWidth;
		float fHeight;
		float fColorR;
		float fColorG;
		float fColorB;
		float fColorA;
		ImageID theImageID;
	};

	//-----------------------------------------------------------------------------
	ImagesetID Help_GetImagesetIDByImageID(ImageID theImageID);

} //namespace GGUI
//-----------------------------------------------------------------------------
#endif //_GGUIBaseDefine_h_
//-----------------------------------------------------------------------------
