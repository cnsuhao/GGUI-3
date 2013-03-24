//-----------------------------------------------------------------------------
// (C) oil
// 2012-10-19
//-----------------------------------------------------------------------------
#ifndef _GGUIImageset_h_
#define _GGUIImageset_h_
//-----------------------------------------------------------------------------
#include <vector>
#include <map>
#include "GGUIBaseDefine.h"
#include "GGUITinyString.h"
#include "GGUIArray.h"
#include "SoD3DDefine.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	class GGUIImage
	{
	public:
		GGUIImage()
		:m_MyImageID(Invalid_ImageID), m_fLeft(0.0f), m_fRight(0.0f)
		,m_fTop(0.0f), m_fBottom(0.0f) { }
	public:
		//记录自己的ImageID。
		//如果为无效值，表示本对象是无效值。
		ImageID m_MyImageID;
		//记录纹理坐标。
		float m_fLeft;
		float m_fRight;
		float m_fTop;
		float m_fBottom;
	};
	//-----------------------------------------------------------------------------
	class GGUIImageset
	{
		friend class GGUIImagesetManager;
	public:
		GGUIImageset();
		~GGUIImageset();

		ImagesetID GetImagesetID() const;
		//获取本Imageset的名字。
		const GGUITinyString& GetImagesetName() const;
		//获取DXTexture指针。
		const IDirect3DTexture9* GetDXTexture() const;

		//新增一个Image。
		//--strImageName Image的名字。
		//--fLeft,fRight,fTop,fBottom 纹理坐标。
		//返回新Image的ImageID。
		//如果已经存在名字为strImageName的Image，则新值覆盖旧值。
		ImageID AddImage(const GGUITinyString& strImageName, float fLeft, float fRight, float fTop, float fBottom);
		void RemoveImage(ImageID theImageID);
		const GGUIImage* GetImage(ImageID theImageID) const;
		ImageID GetImageIDByName(const GGUITinyString& strImageName) const;
		const GGUITinyString* GetImageNameByID(ImageID theImageID) const;
		//ImageRect中存储的是纹理UV坐标。这个函数用于获取ImageRect的像素坐标。
		bool GetImageRectPixel(ImageID theImageID, float& fLeft, float& fRight, float& fTop, float& fBottom) const;

	protected:
		void SetImagesetID(ImagesetID theID);
		//设置本Imageset的名字。
		//注意，pszName字符串的size（包括结束符）不能大于MaxCharCount_TinyString；
		//如果大于的话，会被截断。
		void SetImagesetName(const tchar* pszName);
		//
		void SetDXTexture(IDirect3DTexture9* pTexture);
		//
		void ReleaseImageset();
		//根据规则，生成一个ImageID。
		ImageID GenerateImageID() const;
		SoInt GenerateIndex(ImageID theImageID) const;

	private:
		typedef std::vector<GGUIImage> vecImage;
		typedef std::map<GGUITinyString, ImageID> mapImageName2ImageID;

	private:
		//
		ImagesetID m_MyImagesetID;
		GGUITinyString m_MyImagesetName;
		IDirect3DTexture9* m_pDXTexture;
		//记录DX贴图资源的宽高。
		int m_nDXTextureWidth;
		int m_nDXTextureHeight;
		//存储GGUIImage的数组。
		vecImage m_vecImageList;
		//存储从ImageName到ImageID的映射。
		mapImageName2ImageID m_mapName2ID;

	};
	//-----------------------------------------------------------------------------
	inline ImagesetID GGUIImageset::GetImagesetID() const
	{
		return m_MyImagesetID;
	}
	//-----------------------------------------------------------------------------
	inline const GGUITinyString& GGUIImageset::GetImagesetName() const
	{
		return m_MyImagesetName;
	}
	//-----------------------------------------------------------------------------
	inline const IDirect3DTexture9* GGUIImageset::GetDXTexture() const
	{
		return m_pDXTexture;
	}
	//-----------------------------------------------------------------------------
	inline ImageID GGUIImageset::GetImageIDByName(const GGUITinyString& strImageName) const
	{
		mapImageName2ImageID::const_iterator it = m_mapName2ID.find(strImageName);
		if (it == m_mapName2ID.end())
		{
			return Invalid_ImageID;
		}
		else
		{
			return (it->second);
		}
	}
	//-----------------------------------------------------------------------------
	inline void GGUIImageset::SetImagesetID(ImagesetID theID)
	{
		m_MyImagesetID = theID;
	}
	//-----------------------------------------------------------------------------
	inline ImageID GGUIImageset::GenerateImageID() const
	{
		ImageID theResult = (ImageID)m_vecImageList.size();
		theResult += m_MyImagesetID * ImageID_ImagesetID;
		return theResult;
	}
	//-----------------------------------------------------------------------------
	inline SoInt GGUIImageset::GenerateIndex(ImageID theImageID) const
	{
		return (theImageID % ImageID_ImagesetID);
	}
} //namespace GGUI
//-----------------------------------------------------------------------------
#endif //_GGUIImageset_h_
//-----------------------------------------------------------------------------
