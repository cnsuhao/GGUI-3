//-----------------------------------------------------------------------------
// (C) oil
// 2012-10-19
//-----------------------------------------------------------------------------
#ifndef _GGUIRect_h_
#define _GGUIRect_h_
//-----------------------------------------------------------------------------
namespace GGUI
{
	//-----------------------------------------------------------------------------
	class GGUIRect
	{
	public:
		GGUIRect()
		:m_fLeft(0.0f), m_fRight(0.0f), m_fTop(0.0f), m_fBottom(0.0f)
		{

		}
		GGUIRect(float fLeft, float fRight, float fTop, float fBottom)
		:m_fLeft(fLeft), m_fRight(fRight), m_fTop(fTop), m_fBottom(fBottom)
		{

		}

	public:
		float m_fLeft;
		float m_fRight;
		float m_fTop;
		float m_fBottom;
	};
} //namespace GGUI
//-----------------------------------------------------------------------------
#endif //_GGUIRect_h_
//-----------------------------------------------------------------------------
