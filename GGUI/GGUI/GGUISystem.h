//-----------------------------------------------------------------------------
// GGUIϵͳ��
// (C) oil
// 2012-09-08
//-----------------------------------------------------------------------------
#ifndef _GGUISystem_h_
#define _GGUISystem_h_
//-----------------------------------------------------------------------------
#include "SoD3DDefine.h"
#include "GGUIInputDefine.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	class GGUISystem
	{
	public:
		GGUISystem();
		~GGUISystem();
		static GGUISystem* GetInstance();

		//��ʼ��GGUIϵͳ��������Ҫ���������Դ��
		bool InitUISystem(IDirect3DDevice9* pDevice, float fScreenWidth, float fScreenHeight);
		//�ͷ�GGUIϵͳ��
		void ReleaseUISystem();
		//��ȡD3D�豸ָ�롣
		IDirect3DDevice9* GetD3DDevice();

		//���¡�
		void UpdateGGUI(float fFrameTime);
		//���ơ�
		void RenderGGUI();

		//ע��һ�����̰����¼���
		//����ture��ʾ��������¼�����ϵͳ��Ӧ�������ˣ�
		//����false��ʾ��ϵͳ�����Ĳ�û�д�������¼���
		bool InjectKeyEvent(eInputEvent theEvent, eKeyButton theKey);
		//ע��һ������¼���
		//����ture��ʾ����¼�����ϵͳ��Ӧ�������ˣ�
		//����false��ʾ��ϵͳ�����Ĳ�û�д�������¼���
		bool InjectMouseEvent(eInputEvent theEvent, eMouseButton theButton, float fParamA, float fParamB);

	private:
		static GGUISystem* ms_pInstance;

	private:
		IDirect3DDevice9* m_pD3DDevice;
	};
	//-----------------------------------------------------------------------------
	inline GGUISystem* GGUISystem::GetInstance()
	{
		return ms_pInstance;
	}
	//-----------------------------------------------------------------------------
	inline IDirect3DDevice9* GGUISystem::GetD3DDevice()
	{
		return m_pD3DDevice;
	}
	//-----------------------------------------------------------------------------
} //namespace GGUI
//-----------------------------------------------------------------------------
#endif //_GGUISystem_h_
//-----------------------------------------------------------------------------
