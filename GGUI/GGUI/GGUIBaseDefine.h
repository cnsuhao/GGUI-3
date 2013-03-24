//-----------------------------------------------------------------------------
// (C) oil
// 2013-03-24
//-----------------------------------------------------------------------------
#ifndef _GGUIBaseDefine_h_
#define _GGUIBaseDefine_h_
//-----------------------------------------------------------------------------
#include <string>
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
	//ImageID除以ImageID_ImagesetID，得到的商就是其所属的Imageset的ID。
	static const SoInt ImageID_ImagesetID = 10000;

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
		ImagesetID theImagesetID;
		ImageID theImageID;
	};
}
//-----------------------------------------------------------------------------
#endif //_GGUIBaseDefine_h_
//-----------------------------------------------------------------------------
