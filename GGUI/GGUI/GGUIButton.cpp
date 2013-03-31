//-----------------------------------------------------------------------------
// GGUI Button控件
// (C) oil
// 2012-09-30
//-----------------------------------------------------------------------------
#include "GGUIButton.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	GGUIButton::GGUIButton()
	:GGUIWindow()
	,m_eButtonState(ButtonState_Normal)
	{
		m_eMyWindowType = WindowType_Button;
	}
	//-----------------------------------------------------------------------------
	GGUIButton::~GGUIButton()
	{

	}
	//-----------------------------------------------------------------------------
	void GGUIButton::SetEnable(bool bEnable)
	{
		//把旧值保存下来。
		bool bOldValue = m_bEnable;
		__super::SetEnable(bEnable);
		//
		if (bOldValue != bEnable)
		{
			eButtonState eDestState = bEnable ? ButtonState_Normal : ButtonState_Disable;
			if (m_eButtonState != eDestState)
			{
				m_eButtonState = eDestState;
				m_bDirty = true;
			}
		}
	}
	//-----------------------------------------------------------------------------
	void GGUIButton::OnMouseEnterWindowArea()
	{
		if (m_bEnable)
		{
			if (m_eButtonState != ButtonState_Hover)
			{
				m_eButtonState = ButtonState_Hover;
				m_bDirty = true;
			}
		}
		__super::OnMouseEnterWindowArea();
	}
	//-----------------------------------------------------------------------------
	void GGUIButton::OnMouseLeaveWindowArea()
	{
		if (m_bEnable)
		{
			if (m_eButtonState != ButtonState_Normal)
			{
				m_eButtonState = ButtonState_Normal;
				m_bDirty = true;
			}
		}
		__super::OnMouseLeaveWindowArea();
	}
	//-----------------------------------------------------------------------------
	void GGUIButton::OnMouseLeftButtonClickDown()
	{
		if (m_bEnable)
		{
			if (m_eButtonState != ButtonState_PushDown)
			{
				m_eButtonState = ButtonState_PushDown;
				m_bDirty = true;
			}
		}
		__super::OnMouseLeftButtonClickDown();
	}
	//-----------------------------------------------------------------------------
	void GGUIButton::OnMouseLeftButtonClickUp()
	{
		if (m_bEnable)
		{
			if (m_bMouseInWindowArea)
			{
				if (m_eButtonState != ButtonState_Hover)
				{
					m_eButtonState = ButtonState_Hover;
					m_bDirty = true;
				}
			}
			else
			{
				if (m_eButtonState != ButtonState_Normal)
				{
					m_eButtonState = ButtonState_Normal;
					m_bDirty = true;
				}
			}
		}
		__super::OnMouseLeftButtonClickUp();
	}
	//-----------------------------------------------------------------------------
	void GGUIButton::GenerateRenderUnit(stRenderUnit& theRenderUnit)
	{
		static SoInt s_nDeltaX = 2;
		static SoInt s_nDeltaY = 2;
		static float s_fDisableColor = 0.5f;

		stRect destRect = m_WindowRect;
		stColor destColor = m_WindowColor;
		//
		switch (m_eButtonState)
		{
		case ButtonState_Normal:
			break;
		case ButtonState_Hover:
			{
				destRect.nLeft -= s_nDeltaX;
				destRect.nRight -= s_nDeltaX;
				destRect.nTop -= s_nDeltaY;
				destRect.nBottom -= s_nDeltaY;
			}
			break;
		case ButtonState_PushDown:
			{
				destRect.nLeft += s_nDeltaX;
				destRect.nRight += s_nDeltaX;
				destRect.nTop += s_nDeltaY;
				destRect.nBottom += s_nDeltaY;
			}
			break;
		case ButtonState_Disable:
			{
				destColor.byColorR = (SoUInt8)(destColor.byColorR * s_fDisableColor);
				destColor.byColorG = (SoUInt8)(destColor.byColorG * s_fDisableColor);
				destColor.byColorB = (SoUInt8)(destColor.byColorB * s_fDisableColor);
			}
			break;
		}
		theRenderUnit.theWindowRect = destRect;
		theRenderUnit.fZValue = ((float)m_nZValue) / MaxZValue;
		theRenderUnit.uiColor32 = Help_GenerateColor32(destColor);
		theRenderUnit.theImageID = m_nMyImageID;
	}
}
//-----------------------------------------------------------------------------
