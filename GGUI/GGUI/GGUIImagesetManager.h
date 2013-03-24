//-----------------------------------------------------------------------------
// (C) oil
// 2012-10-20
//-----------------------------------------------------------------------------
#ifndef _GGUIImagesetManager_h_
#define _GGUIImagesetManager_h_
//-----------------------------------------------------------------------------
#include "GGUIImageset.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	class GGUIImagesetManager
	{
	public:
		GGUIImagesetManager();
		~GGUIImagesetManager();
		static GGUIImagesetManager* GetInstance();

		bool InitImagesetManager();
		void ReleaseImagesetManager();

		//临时函数。
		bool CreateImagesetByTextureFile(const tchar* pszTextureFile, const GGUITinyString& strImagesetName, ImagesetID* pImagesetID, ImageID* pImageID);
		//删除一个GGUIImageset对象。
		void ReleaseImageset(ImagesetID theImagesetID);
		//获取一个GGUIImageset对象。
		GGUIImageset* GetImageset(ImagesetID theImagesetID);
		ImagesetID GetImagesetIDByName(const GGUITinyString& strImagesetName) const;

	private:
		IDirect3DTexture9* LoadTextureFromDisk(const tchar* pszFileName) const;


	private:
		typedef std::vector<GGUIImageset> vecImageset;
		typedef std::map<GGUITinyString, ImagesetID> mapImagesetName2ImagesetID;

	private:
		static GGUIImagesetManager* ms_pInstance;
	private:
		//GGUIImageset数组。
		vecImageset m_arrayImageset;
		//维护从ImagesetName到ImagesetID的映射。
		mapImagesetName2ImagesetID m_mapImagesetName2ID;

	};
	//-----------------------------------------------------------------------------
	inline GGUIImagesetManager* GGUIImagesetManager::GetInstance()
	{
		return ms_pInstance;
	}
	//-----------------------------------------------------------------------------
	inline GGUIImageset* GGUIImagesetManager::GetImageset(ImagesetID theImagesetID)
	{
		if (theImagesetID < (ImagesetID)m_arrayImageset.size())
		{
			return &(m_arrayImageset[theImagesetID]);
		}
		else
		{
			return SoNULL;
		}
	}
	//-----------------------------------------------------------------------------
	inline ImagesetID GGUIImagesetManager::GetImagesetIDByName(const GGUITinyString& strImagesetName) const
	{
		mapImagesetName2ImagesetID::const_iterator it = m_mapImagesetName2ID.find(strImagesetName);
		if (it == m_mapImagesetName2ID.end())
		{
			return Invalid_ImagesetID;
		}
		else
		{
			return (it->second);
		}
	}
} //namespace GGUI
//-----------------------------------------------------------------------------
#endif //_GGUIImagesetManager_h_
//-----------------------------------------------------------------------------
