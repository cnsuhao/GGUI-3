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
			float fDestPosX = m_fPositionX;
			float fDestPosY = m_fPositionY;
			float fDestWidth = m_fWidth;
			float fDestHeight = m_fHeight;
			//获取图片源文件的宽高。
			ImagesetID theImagesetID = Help_GetImagesetIDByImageID(m_nMyImageID);
			const GGUIImageset* pImageset = GGUIImagesetManager::GetInstance()->GetImageset(theImagesetID);
			if (pImageset)
			{
				float fLeft = 0.0f;
				float fRight = 0.0f;
				float fTop = 0.0f;
				float fBottom = 0.0f;
				if (pImageset->GetImageRectPixel(m_nMyImageID, fLeft, fRight, fTop, fBottom))
				{
					float fTextureSourceWidth = fRight - fLeft;
					float fTextureSourceHeight = fBottom - fTop;
					float fWindowHeightWidth = m_fHeight / m_fWidth;
					float fTextureHeightWidth = fTextureSourceHeight / fTextureSourceWidth;
					if (fWindowHeightWidth > fTextureHeightWidth)
					{
						//宽度不变，对高度进行调整。
						fDestHeight = m_fWidth * fTextureHeightWidth;
						fDestPosY += (m_fHeight - fDestHeight) * 0.5f;
					}
					else if (fWindowHeightWidth < fTextureHeightWidth)
					{
						fDestWidth = m_fHeight / fTextureHeightWidth;
						fDestPosX += (m_fWidth - fDestWidth) * 0.5f;
					}
					else
					{
						//什么都不做。
					}
				}
			}
			theRenderUnit.fPositionX = fDestPosX;
			theRenderUnit.fPositionY = fDestPosY;
			theRenderUnit.fPositionZ = m_fPositionZ;
			theRenderUnit.fWidth = fDestWidth;
			theRenderUnit.fHeight = fDestHeight;
			theRenderUnit.fColorR = m_fColorR;
			theRenderUnit.fColorG = m_fColorG;
			theRenderUnit.fColorB = m_fColorB;
			theRenderUnit.fColorA = m_fColorA;
			theRenderUnit.theImageID = m_nMyImageID;
		}
	}
}
//-----------------------------------------------------------------------------
