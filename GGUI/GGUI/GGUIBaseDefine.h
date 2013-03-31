//-----------------------------------------------------------------------------
// (C) oil
// 2013-03-24
//-----------------------------------------------------------------------------
#ifndef _GGUIBaseDefine_h_
#define _GGUIBaseDefine_h_
//-----------------------------------------------------------------------------
#include <string>
#include "FastDelegate.h"
#include "FastDelegateBind.h"
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
	//���������������ImageID��210045�����ʾImagesetIDΪ21������ֵΪ45��
	static const SoInt ImageID_ImagesetID = 10000;

	typedef SoInt WindowID;
	static const WindowID Invalid_WindowID = -1;
	//
	typedef SoInt DelegateID;
	static const DelegateID Invalid_DelegateID = -1;
	//
	static const float MaxZValue = 1000.0f;

	//���ڵĸ������͡�
	enum eWindowType
	{
		WindowType_Invalid = -1, 
		WindowType_Base = 0, //GGUIWindow����
		WindowType_Button, //GGUIButton����
		WindowType_Picture, //GGUIPicture����
		WindowType_Frame, //GGUIFrame����
		WindowType_Max,
	};

	//�����ܹ�������Щ��Ϣ�¼���
	enum eWindowEvent
	{
		//��Чֵ��
		WindowEvent_Invalid = -1,
		//�������˴��ڵľ�������
		//�������������ڿɼ��������봰�ھ��������ڡ�
		//ע�⣺�����Ǵ����Ƿ񱻽��á���������ص��Ļ��������ͬһʱ����괦�ڶ�����ڵľ��������ڡ�
		WindowEvent_MouseEnterWindowArea = 0,
		//����뿪�˴��ڵľ�������
		//�������������ڿɼ�������뿪���ھ��������ڡ�
		//ע�⣺�����Ǵ����Ƿ񱻽��á�����괦�ڴ��ھ���������ʱ�������ɿɼ���Ϊ���ɼ�����Ҳ�ᴥ������¼���
		WindowEvent_MouseLeaveWindowArea,
		//�������ڴ����ϰ����ˡ�
		//��������������û�б����ã�����ڴ��ڵľ��������ڣ����������¡�
		WindowEvent_MouseLeftButtonClickDown,
		//�������ڴ�����̧���ˡ�
		//��������������û�б����ã�����ڴ��ڵľ��������ڣ�������̧��
		WindowEvent_MouseLeftButtonClickUp,
		//���ֵ��
		WindowEvent_Max,
	};

	//�����¼���delegate������
	//--WindowID ��������¼���Window��
	//--int �����Ĳ�����
	typedef fastdelegate::FastDelegate2<WindowID, int> DelegateForWindowEvent;
	//
	struct stWindowEventDelegate
	{
		DelegateForWindowEvent theFunction[WindowEvent_Max];
	};

	//��������
	struct stRect
	{
		SoInt nLeft;
		SoInt nRight;
		SoInt nTop;
		SoInt nBottom;
		stRect():nLeft(0),nRight(0),nTop(0),nBottom(0) { }
	};

	//��ɫ��
	struct stColor
	{
		SoUInt8 byColorA;
		SoUInt8 byColorR;
		SoUInt8 byColorG;
		SoUInt8 byColorB;
		stColor():byColorA(255),byColorR(255),byColorG(255),byColorB(255) { }
	};

	//���ڵĻ��Ʋ�����
	struct stRenderUnit
	{
		stRect theWindowRect;
		float fZValue;
		SoUInt32 uiColor32;
		ImageID theImageID;
	};

	//-----------------------------------------------------------------------------
	ImagesetID Help_GetImagesetIDByImageID(ImageID theImageID);
	SoUInt32 Help_GenerateColor32(const stColor& theColor);

} //namespace GGUI
//-----------------------------------------------------------------------------
#endif //_GGUIBaseDefine_h_
//-----------------------------------------------------------------------------
