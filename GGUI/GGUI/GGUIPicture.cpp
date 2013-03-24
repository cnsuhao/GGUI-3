//-----------------------------------------------------------------------------
// GGUI Button控件
// (C) oil
// 2012-09-30
//-----------------------------------------------------------------------------
#include "GGUIPicture.h"
#include "GGUIImagesetManager.h"
#include "GGUIImageset.h"
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
			const GGUIImageset* pImageset = GGUIImagesetManager::GetInstance()->GetImageset(m_nMyImagesetID);
			if (pImageset)
			{
				GGUIRect kImageRectPixel;
				if (pImageset->GetImageRectPixel(m_nMyImageRectID, kImageRectPixel))
				{
					float fTextureSourceWidth = kImageRectPixel.m_fRight - kImageRectPixel.m_fLeft;
					float fTextureSourceHeight = kImageRectPixel.m_fBottom - kImageRectPixel.m_fTop;
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
			theRenderUnit.theImagesetID = m_nMyImagesetID;
			theRenderUnit.theImageRectID = m_nMyImageRectID;
		}
	}
}
//-----------------------------------------------------------------------------
