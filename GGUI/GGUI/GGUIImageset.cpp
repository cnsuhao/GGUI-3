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
	,m_nDXTextureWidth(0)
	,m_nDXTextureHeight(0)
	{

	}
	//-----------------------------------------------------------------------------
	GGUIImageset::~GGUIImageset()
	{
		ReleaseImageset();
	}
	//-----------------------------------------------------------------------------
	ImageID GGUIImageset::AddImage(const GGUITinyString& strImageName, float fLeft, float fRight, float fTop, float fBottom)
	{
		//如果是第一次添加Image元素，则预先分配内存。
		//之所以没有放到构造函数中去预分配内存，是为了减少本类对象的初始大小，
		//在GGUIImagesetManager中会为本类对象预先分配内存。
		if (m_vecImageList.empty())
		{
			m_vecImageList.reserve(10);
		}
		//
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
		for (vecImage::iterator it = m_vecImageList.begin();
			it != m_vecImageList.end();
			++it)
		{
			if (it->m_MyImageID == theImageID)
			{
				//注意，这里不能移除元素，只能把元素置为无效值。
				it->m_MyImageID = Invalid_ImageID;
				break;
			}
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
	const GGUIImage* GGUIImageset::GetImage(ImageID theImageID) const
	{
		SoInt theIndex = GenerateIndex(theImageID);
		if (theIndex < (SoInt)m_vecImageList.size())
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
	bool GGUIImageset::GetImageRectPixel(ImageID theImageID, float& fLeft, float& fRight, float& fTop, float& fBottom) const
	{
		const GGUIImage* pRect = GetImage(theImageID);
		if (pRect)
		{
			fLeft = pRect->m_fLeft * m_nDXTextureWidth;
			fRight = pRect->m_fRight * m_nDXTextureWidth;
			fTop = pRect->m_fTop * m_nDXTextureHeight;
			fBottom = pRect->m_fBottom * m_nDXTextureHeight;
			if (fLeft < 0.0f)
			{
				fLeft = 0.0f;
			}
			if (fRight > (float)m_nDXTextureWidth)
			{
				fRight = (float)m_nDXTextureWidth;
			}
			if (fTop < 0.0f)
			{
				fTop = 0.0f;
			}
			if (fBottom > (float)m_nDXTextureHeight)
			{
				fBottom = (float)m_nDXTextureHeight;
			}
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
	void GGUIImageset::ReleaseImageset()
	{
		SAFE_D3D_RELEASE(m_pDXTexture);
		m_mapName2ID.clear();
		m_vecImageList.clear();
		m_MyImagesetID = Invalid_ImagesetID;
	}
	//-----------------------------------------------------------------------------
} //namespace GGUI
//-----------------------------------------------------------------------------
