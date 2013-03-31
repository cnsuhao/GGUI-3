//-----------------------------------------------------------------------------
// GGUI Button控件
// (C) oil
// 2012-09-30
//-----------------------------------------------------------------------------
#include "GGUIPicture.h"
#include "GGUIImagesetManager.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	//-----------------------------------------------------------------------------
	GGUIPicture::GGUIPicture()
	:GGUIWindow()
	,m_ePictureShow(PictureShow_Auto)
	{
		m_eMyWindowType = WindowType_Picture;
	}
	//-----------------------------------------------------------------------------
	GGUIPicture::~GGUIPicture()
	{

	}
	//-----------------------------------------------------------------------------
	void GGUIPicture::SetPictureShowType(ePictureShow theShowType)
	{
		m_ePictureShow = theShowType;
		m_bDirty = true;
	}
	//-----------------------------------------------------------------------------
	GGUIPicture::ePictureShow GGUIPicture::GetPictureShowType() const
	{
		return m_ePictureShow;
	}
	//-----------------------------------------------------------------------------
	void GGUIPicture::GenerateRenderUnit(stRenderUnit& theRenderUnit)
	{
		if (m_ePictureShow == PictureShow_Auto)
		{
			stRect destRect = m_WindowRect;
			//获取图片源文件的宽高。
			ImagesetID theImagesetID = Help_GetImagesetIDByImageID(m_nMyImageID);
			const GGUIImageset* pImageset = GGUIImagesetManager::GetInstance()->GetImageset(theImagesetID);
			if (pImageset)
			{
				SoInt nLeft = 0;
				SoInt nRight = 0;
				SoInt nTop = 0;
				SoInt nBottom = 0;
				if (pImageset->GetImageRectPixel(m_nMyImageID, nLeft, nRight, nTop, nBottom))
				{
					SoInt nTextureSourceWidth = nRight - nLeft;
					SoInt nTextureSourceHeight = nBottom - nTop;
					SoInt nWindowWidth = m_WindowRect.nRight - m_WindowRect.nLeft;
					SoInt nWindowHeight = m_WindowRect.nBottom - m_WindowRect.nTop;
					if (nTextureSourceWidth != 0 && nWindowWidth != 0)
					{
						float fWindowHeightWidth = (float)nWindowHeight / (float)nWindowWidth;
						float fTextureHeightWidth = (float)nTextureSourceHeight / (float)nTextureSourceWidth;
						if (fWindowHeightWidth > fTextureHeightWidth)
						{
							//宽度不变，对高度进行调整。
							SoInt nDestHeight = (SoInt)((float)nWindowWidth * fTextureHeightWidth + 0.5f);
							destRect.nTop += (SoInt)((float)(nWindowHeight - nDestHeight) * 0.5f + 0.5f);
							destRect.nBottom = destRect.nTop + nDestHeight;
						}
						else if (fWindowHeightWidth < fTextureHeightWidth)
						{
							SoInt nDestWidth = (SoInt)((float)nWindowHeight / fTextureHeightWidth + 0.5f);
							destRect.nLeft += (SoInt)((float)(nWindowWidth - nDestWidth) * 0.5f + 0.5f);
							destRect.nRight = destRect.nLeft + nDestWidth;
						}
						else
						{
							//什么都不做。
						}
					}
				}
			}
			theRenderUnit.theWindowRect = destRect;
			theRenderUnit.fZValue = ((float)m_nZValue) / MaxZValue;
			theRenderUnit.uiColor32 = Help_GenerateColor32(m_WindowColor);
			theRenderUnit.theImageID = m_nMyImageID;
		}
	}
}
//-----------------------------------------------------------------------------
