//-----------------------------------------------------------------------------
// (C) oil
// 2013-03-24
//-----------------------------------------------------------------------------
#ifndef _GGUIBaseDefine_h_
#define _GGUIBaseDefine_h_
//-----------------------------------------------------------------------------
#include <string>
//-----------------------------------------------------------------------------
namespace GGUI
{
	typedef __int8  SoInt8;
	typedef __int16 SoInt16;
	typedef __int32 SoInt32;
	typedef __int64 SoInt64;
	typedef __int32 SoInt;
	//
	typedef unsigned __int8  SoUInt8;
	typedef unsigned __int16 SoUInt16;
	typedef unsigned __int32 SoUInt32;
	typedef unsigned __int64 SoUInt64;
	typedef unsigned __int32 SoUInt;
	//
	typedef float SoFloat; //32λ�ĸ���������ȷ��6λ��Ч���֡�
	typedef double SoDouble; //64λ�ĸ���������ȷ��16λ��Ч���֡�
	//ָ�����Чֵ��
#define SoNULL 0

	//-----------------------------------------------------------------------------
#if defined(_UNICODE) || defined(UNICODE)
	typedef wchar_t tchar;
	typedef std::wstring tstring;
#else
	typedef char tchar;
	typedef std::string tstring;
#endif

	//-----------------------------------------------------------------------------
	//��ȫ��ɾ��һ������
#define SAFE_DELETE(p);  { if(p) { delete (p); (p)=0; } }
	//��ȫ��ɾ��һ���������顣
#define SAFE_DELETE_ARRAY(p);  { if(p) { delete [] (p); (p)=0; } }

	//-----------------------------------------------------------------------------
	typedef SoInt ImagesetID;
	static const ImagesetID Invalid_ImagesetID = -1;
	typedef SoInt ImageID;
	static const ImageID Invalid_ImageID = -1;
	//ImagesetID����Сֵ��0�����ֵ��(ImageID_ImagesetID-1)��
	//ImageID����Сֵ��ImageID_ImagesetID��
	//ImageID����ImageID_ImagesetID���õ����̾�����������Imageset��ID��
	static const SoInt ImageID_ImagesetID = 10000;

	//���ڵĻ��Ʋ�����
	struct stRenderUnit
	{
		float fPositionX;
		float fPositionY;
		float fPositionZ;
		float fWidth;
		float fHeight;
		float fColorR;
		float fColorG;
		float fColorB;
		float fColorA;
		ImagesetID theImagesetID;
		ImageID theImageID;
	};
}
//-----------------------------------------------------------------------------
#endif //_GGUIBaseDefine_h_
//-----------------------------------------------------------------------------
