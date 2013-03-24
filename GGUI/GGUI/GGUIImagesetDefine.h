//-----------------------------------------------------------------------------
// (C) oil
// 2012-10-19
//-----------------------------------------------------------------------------
#ifndef _GGUIImagesetDefine_h_
#define _GGUIImagesetDefine_h_
//-----------------------------------------------------------------------------
namespace GGUI
{
	typedef int ImagesetID;
	static const ImagesetID Invalid_ImagesetID = -1;

	typedef int ImageRectID;
	static const ImageRectID Invalid_ImageRectID = -1;

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
		ImageRectID theImageRectID;
	};

} //namespace GGUI
//-----------------------------------------------------------------------------
#endif //_GGUIImagesetDefine_h_
//-----------------------------------------------------------------------------
