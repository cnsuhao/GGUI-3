//-----------------------------------------------------------------------------
// (C) oil
// 2012-10-20
//-----------------------------------------------------------------------------
#include "GGUIImagesetManager.h"
#include "GGUISystem.h"
#include "GGUILog.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	GGUIImagesetManager* GGUIImagesetManager::ms_pInstance = SoNULL;
	//-----------------------------------------------------------------------------
	GGUIImagesetManager::GGUIImagesetManager()
	{
		ms_pInstance = this;
	}
	//-----------------------------------------------------------------------------
	GGUIImagesetManager::~GGUIImagesetManager()
	{
		ReleaseImagesetManager();
		ms_pInstance = SoNULL;
	}
	//-----------------------------------------------------------------------------
	bool GGUIImagesetManager::InitImagesetManager()
	{
		//注意，预分配的元素空间尽量大，GGUIImageset对象内有stl容器，如果发生对象
		//拷贝的话，会比较耗时。
		m_arrayImageset.reserve(20);
		return true;
	}
	//-----------------------------------------------------------------------------
	void GGUIImagesetManager::ReleaseImagesetManager()
	{
		m_mapImagesetName2ID.clear();
		m_arrayImageset.clear();
	}
	//-----------------------------------------------------------------------------
	bool GGUIImagesetManager::CreateImagesetByTextureFile(const tchar* pszTextureFile, const GGUITinyString& strImagesetName, ImagesetID* pImagesetID, ImageID* pImageID)
	{
		IDirect3DTexture9* pDXTexture = LoadTextureFromDisk(pszTextureFile);
		if (pDXTexture == SoNULL)
		{
			return false;
		}
		ImagesetID newImagesetID = (ImagesetID)m_arrayImageset.size();
		GGUIImageset kImageset;
		kImageset.SetImagesetID(newImagesetID);
		kImageset.SetImagesetName(strImagesetName.GetValue());
		kImageset.SetDXTexture(pDXTexture);
		m_arrayImageset.push_back(kImageset);
		//维护在map中。
		m_mapImagesetName2ID.insert(std::make_pair(strImagesetName, newImagesetID));
		//
		GGUIImageset* pNewImageset = GetImageset(newImagesetID);
		if (pNewImageset == NULL)
		{
			return false;
		}
		ImageID newImageID = pNewImageset->AddImage(GGUITinyString(TEXT("default")), 0.0f, 1.0f, 0.0f, 1.0f);
		if (pImagesetID)
		{
			*pImagesetID = newImagesetID;
		}
		if (pImageID)
		{
			*pImageID = newImageID;
		}
		return true;
	}
	//-----------------------------------------------------------------------------
	void GGUIImagesetManager::ReleaseImageset(ImagesetID theImagesetID)
	{
		for (vecImageset::iterator it_image = m_arrayImageset.begin();
			it_image != m_arrayImageset.end();
			++it_image)
		{
			if (it_image->GetImagesetID() == theImagesetID)
			{
				//注意，只把对象清零，不要把对象删除。
				it_image->ReleaseImageset();
				break;
			}
		}
		//
		for (mapImagesetName2ImagesetID::iterator it = m_mapImagesetName2ID.begin();
			it != m_mapImagesetName2ID.end();
			++it)
		{
			if (it->second == theImagesetID)
			{
				m_mapImagesetName2ID.erase(it);
				break;
			}
		}
	}
	//-----------------------------------------------------------------------------
	IDirect3DTexture9* GGUIImagesetManager::LoadTextureFromDisk(const tchar* pszFileName) const
	{
		IDirect3DTexture9* pNewDXTexture = NULL;
		//宽高使用图片的宽高，并且不要调整到2的幂。
		SoUInt uiWidth = D3DX_DEFAULT_NONPOW2;
		SoUInt uiHeight = D3DX_DEFAULT_NONPOW2;
		//不应该使用MipMap。
		SoUInt uiMipLevels = 1;
		//用途，使用默认值。
		SoUInt uiUsage = 0;
		//像素格式。
		D3DFORMAT eFormat = D3DFMT_UNKNOWN;
		//使用托管内存池，因为贴图的数据不会被频繁改变（甚至不会改变），用托管内存池的好处是设备丢失后不必重新创建。
		D3DPOOL ePool = D3DPOOL_MANAGED;
		//图片过滤方式。
		SoUInt uiFilter = D3DX_FILTER_LINEAR;
		SoUInt uiMipFilter = D3DX_FILTER_NONE;
		//不使用关键色替换。
		D3DCOLOR dwColorKey = 0;
		HRESULT hr = D3DXCreateTextureFromFileEx(GGUISystem::GetInstance()->GetD3DDevice(), pszFileName,
			uiWidth, uiHeight, uiMipLevels, uiUsage, eFormat, ePool, uiFilter, uiMipFilter, dwColorKey,
			NULL, NULL, &pNewDXTexture);
		if (FAILED(hr))
		{
			LOG_ERROR(TEXT("GGUIImagesetManager::LoadTextureFromDisk : D3DXCreateTextureFromFileEx Fail [%s]"), pszFileName);
		}
		return pNewDXTexture;
	}
} //namespace GGUI
//-----------------------------------------------------------------------------
