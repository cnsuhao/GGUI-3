//-----------------------------------------------------------------------------
// (C) oil
// 2012-10-19
//-----------------------------------------------------------------------------
#include "GGUIImageset.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	//定义一个GGUIImage的无效对象。
	const GGUIImage Invalid_GGUIImage;
	//-----------------------------------------------------------------------------
	GGUIImageset::GGUIImageset()
	:m_MyImagesetID(Invalid_ImagesetID)
	,m_MyImagesetName()
	,m_pDXTexture(SoNULL)
	,m_nTextureWidth(0)
	,m_nTextureHeight(0)
	{
		m_vecImageList.reserve(10);
	}
	//-----------------------------------------------------------------------------
	GGUIImageset::~GGUIImageset()
	{
		ReleaseImageset();
	}
	//-----------------------------------------------------------------------------
	ImageID GGUIImageset::AddImage(const GGUITinyString& strImageName, float fLeft, float fRight, float fTop, float fBottom)
	{
		ImageID theImageID = GenerateImageID();
		GGUIImage theImage;
		theImage.m_MyImageID = theImageID;
		theImage.m_fLeft = fLeft;
		theImage.m_fRight = fRight;
		theImage.m_fTop = fTop;
		theImage.m_fBottom = fBottom;
		m_vecImageList.push_back(theImage);
		//
		m_mapName2ID.insert(std::make_pair(strImageName, theImageID));
		return theImageID;
	}
	//-----------------------------------------------------------------------------
	void GGUIImageset::RemoveImage(ImageID theImageID)
	{
		GGUIImage* theImage = GetImage(theImageID);
		if (theImage)
		{
			//元素不要从容器中移除，只是把其置为无效值。
			theImage->m_MyImageID = Invalid_ImageID;
		}
		//
		for (mapImageName2ImageID::iterator it_map = m_mapName2ID.begin();
			it_map != m_mapName2ID.end();
			++it_map)
		{
			if (it_map->second == theImageID)
			{
				m_mapName2ID.erase(it_map);
				break;
			}
		}
	}
	//-----------------------------------------------------------------------------
	GGUIImage* GGUIImageset::GetImage(ImageID theImageID)
	{
		SoInt theIndex = GetIndexByImageID(theImageID);
		if (theIndex >= 0 && theIndex < (SoInt)m_vecImageList.size()
			&& m_vecImageList[theIndex].m_MyImageID != Invalid_ImageID)
		{
			return &(m_vecImageList[theIndex]);
		}
		else
		{
			return SoNULL;
		}
	}
	//-----------------------------------------------------------------------------
	const GGUIImage* GGUIImageset::GetImage(ImageID theImageID) const
	{
		SoInt theIndex = GetIndexByImageID(theImageID);
		if (theIndex >= 0 && theIndex < (SoInt)m_vecImageList.size()
			&& m_vecImageList[theIndex].m_MyImageID != Invalid_ImageID)
		{
			return &(m_vecImageList[theIndex]);
		}
		else
		{
			return SoNULL;
		}
	}
	//-----------------------------------------------------------------------------
	const GGUITinyString* GGUIImageset::GetImageNameByID(ImageID theImageID) const
	{
		GGUITinyString* pResult = SoNULL;
		for (mapImageName2ImageID::const_iterator it = m_mapName2ID.begin();
			it != m_mapName2ID.end();
			++it)
		{
			if (it->second == theImageID)
			{
				//写成pResult = &(it->first);会报错。
				pResult = (GGUITinyString*)(&(it->first));
				break;
			}
		}
		return pResult;
	}
	//-----------------------------------------------------------------------------
	bool GGUIImageset::GetImageRectPixel(ImageID theImageID, SoInt& nLeft, SoInt& nRight, SoInt& nTop, SoInt& nBottom) const
	{
		const GGUIImage* pRect = GetImage(theImageID);
		if (pRect)
		{
			nLeft = (SoInt)(pRect->m_fLeft * (float)m_nTextureWidth + 0.5f);
			nRight = (SoInt)(pRect->m_fRight * (float)m_nTextureWidth + 0.5f);
			nTop = (SoInt)(pRect->m_fTop * (float)m_nTextureHeight + 0.5f);
			nBottom = (SoInt)(pRect->m_fBottom * (float)m_nTextureHeight + 0.5f);
			return true;
		}
		else
		{
			return false;
		}
	}
	//-----------------------------------------------------------------------------
	void GGUIImageset::SetImagesetName(const tchar* pszName)
	{
		m_MyImagesetName.SetValue(pszName);
	}
	//-----------------------------------------------------------------------------
	void GGUIImageset::SetDXTexture(IDirect3DTexture9* pTexture)
	{
		SAFE_D3D_RELEASE(m_pDXTexture);
		m_pDXTexture = pTexture;
	}
	//-----------------------------------------------------------------------------
	void GGUIImageset::SetTextureWidthHeight(int nWidth, int nHeight)
	{
		m_nTextureWidth = nWidth;
		m_nTextureHeight = nHeight;
	}
	//-----------------------------------------------------------------------------
	void GGUIImageset::ReleaseImageset()
	{
		m_MyImagesetID = Invalid_ImagesetID;
		m_MyImagesetName.SetValue(SoNULL);
		SAFE_D3D_RELEASE(m_pDXTexture);
		m_nTextureWidth = 0;
		m_nTextureHeight = 0;
		m_mapName2ID.clear();
		m_vecImageList.clear();
	}
	//-----------------------------------------------------------------------------
} //namespace GGUI
//-----------------------------------------------------------------------------
