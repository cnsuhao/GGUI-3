//-----------------------------------------------------------------------------
// (C) oil
// 2013-03-30
//-----------------------------------------------------------------------------
#include "GGUIBaseDefine.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	//-----------------------------------------------------------------------------
	ImagesetID Help_GetImagesetIDByImageID(ImageID theImageID)
	{
		return (theImageID / ImageID_ImagesetID);
	}
	//-----------------------------------------------------------------------------
	SoUInt32 Help_GenerateColor32(const stColor& theColor)
	{
		SoUInt32 ColorA = theColor.byColorA;
		SoUInt32 ColorR = theColor.byColorR;
		SoUInt32 ColorG = theColor.byColorG;
		SoUInt32 ColorB = theColor.byColorB;
		return (((ColorA&0xff)<<24)|((ColorR&0xff)<<16)|((ColorG&0xff)<<8)|(ColorB&0xff));
	}
}
//-----------------------------------------------------------------------------
