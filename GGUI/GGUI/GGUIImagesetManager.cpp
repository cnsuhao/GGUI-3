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
		//ע�⣬Ԥ�����Ԫ�ؿռ価����GGUIImageset��������stl�����������������
		//�����Ļ�����ȽϺ�ʱ��
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
		//ά����map�С�
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
				//ע�⣬ֻ�Ѷ������㣬��Ҫ�Ѷ���ɾ����
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
		//���ʹ��ͼƬ�Ŀ�ߣ����Ҳ�Ҫ������2���ݡ�
		SoUInt uiWidth = D3DX_DEFAULT_NONPOW2;
		SoUInt uiHeight = D3DX_DEFAULT_NONPOW2;
		//��Ӧ��ʹ��MipMap��
		SoUInt uiMipLevels = 1;
		//��;��ʹ��Ĭ��ֵ��
		SoUInt uiUsage = 0;
		//���ظ�ʽ��
		D3DFORMAT eFormat = D3DFMT_UNKNOWN;
		//ʹ���й��ڴ�أ���Ϊ��ͼ�����ݲ��ᱻƵ���ı䣨��������ı䣩�����й��ڴ�صĺô����豸��ʧ�󲻱����´�����
		D3DPOOL ePool = D3DPOOL_MANAGED;
		//ͼƬ���˷�ʽ��
		SoUInt uiFilter = D3DX_FILTER_LINEAR;
		SoUInt uiMipFilter = D3DX_FILTER_NONE;
		//��ʹ�ùؼ�ɫ�滻��
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
