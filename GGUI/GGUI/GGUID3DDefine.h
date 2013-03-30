//-----------------------------------------------------------------------------
// (C) oil
// 2013-03-30
//-----------------------------------------------------------------------------
#ifndef _GGUID3DDefine_h_
#define _GGUID3DDefine_h_
//-----------------------------------------------------------------------------
#include <d3d9.h>
#include <d3dx9.h>
#include <D3dx9mesh.h>
//����exe�ļ��Ĺ���Ҫ���DX�Ŀ��ļ�"d3d9.lib""d3dx9.lib"
//-----------------------------------------------------------------------------
namespace GGUI
{
	typedef D3DXVECTOR2 SoPoint2;
	typedef D3DXVECTOR3 SoPoint3;
	typedef D3DX_ALIGN16 _D3DXMATRIXA16 SoMatrix4;
	typedef D3DXQUATERNION SoQuaternion;

	//-----------------------------------------------------------------------------
	//��ȫ���ͷ�Windows COM�ӿڶ���
	#define SAFE_D3D_RELEASE(p)   { if(p) { (p)->Release(); (p)=NULL; } } 
	//-----------------------------------------------------------------------------
	//Color���������;���DWORD SoUInt32
	#define SoMakeColorRGBA_UInt(r,g,b,a) ((DWORD)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
	#define SoMakeColorRGBA(r,g,b,a) SoMakeColorRGBA_UInt((DWORD)((r)*255.0f),(DWORD)((g)*255.0f),(DWORD)((b)*255.0f),(DWORD)((a)*255.0f))

	//-----------------------------------------------------------------------------
	//�Զ��������������Ľṹ��,����ֵһ��Ϊ16λ
	struct SoIndexBufferUnit
	{
		unsigned short _0;
		unsigned short _1;
		unsigned short _2;
	};

} //namespace GGUI
//-----------------------------------------------------------------------------
#endif //_GGUID3DDefine_h_
//-----------------------------------------------------------------------------
