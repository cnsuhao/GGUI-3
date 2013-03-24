//-----------------------------------------------------------------------------
// (C) oil
// 2012-10-21
//-----------------------------------------------------------------------------
#include "GGUIDXTextureManager.h"
#include "GGUISystem.h"
#include "GGUILog.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	GGUIDXTextureManager* GGUIDXTextureManager::ms_pInstance = NULL;
	//-----------------------------------------------------------------------------
	GGUIDXTextureManager::GGUIDXTextureManager()
	:m_arrayDXTexture(NULL, 20)
	{
		ms_pInstance = this;
	}
	//-----------------------------------------------------------------------------
	GGUIDXTextureManager::~GGUIDXTextureManager()
	{
		int nValidCount = m_arrayDXTexture.GetWriteIndex();
		for (int i=0; i<nValidCount; ++i)
		{
			ReleaseDXTexture(i);
		}
		//
		ms_pInstance = NULL;
	}
	//-----------------------------------------------------------------------------
	bool GGUIDXTextureManager::InitDXTextureManager()
	{
		return true;
	}
	//-----------------------------------------------------------------------------
	DXTextureID GGUIDXTextureManager::LoadTextureFromDisk(const tchar* pszFileName)
	{
		DXTextureID theDXTextureID = Invalid_DXTextureID;
		if (!pszFileName)
		{
			LOG_ERROR(TEXT("GGUIDXTextureManager::LoadTextureFromDisk : invalid filename"));
			return theDXTextureID;
		}
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
			LOG_ERROR(TEXT("GGUIDXTextureManager::LoadTextureFromDisk : D3DXCreateTextureFromFileEx Fail [%s]"), pszFileName);
			return theDXTextureID;
		}
		//
		m_arrayDXTexture.AddElement(pNewDXTexture);
		theDXTextureID = m_arrayDXTexture.GetWriteIndex() - 1;
		LOG_DEBUG(TEXT("GGUIDXTextureManager::LoadTextureFromDisk : success FileName[%s] DXTextureID[%d]"), pszFileName, theDXTextureID);
		return theDXTextureID;
	}
	//-----------------------------------------------------------------------------
	void GGUIDXTextureManager::ReleaseDXTexture(DXTextureID theTextureID)
	{
		IDirect3DTexture9* pDXTexture = m_arrayDXTexture.GetElement(theTextureID);
		if (pDXTexture)
		{
			SAFE_D3D_RELEASE(pDXTexture);
			m_arrayDXTexture.RemoveElement(theTextureID);
			LOG_DEBUG(TEXT("GGUIDXTextureManager::ReleaseDXTexture : DXTextureID[%d]"), theTextureID);
		}
	}
} //namespace GGUI
//-----------------------------------------------------------------------------
