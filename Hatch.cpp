#include "stdafx.h"
#include "Hatch.h"

Hatch::Hatch(const Point2f & posHatch, const Point2f & posMeter, const Point2f & posButtonBlue)
	:m_PosHatch{posHatch}
	,m_PosMeter{posMeter}
	,m_PosButton{ posButtonBlue }
	,m_Hatch{"Resources/Sprites/Environment/Hatch/hatch.png"}
	,m_Meter{"Resources/Sprites/Environment/Hatch/damageMeter.png"}
	,m_Buttons{"Resources/Sprites/Environment/Hatch/buttons.png"}
	,m_ButtonOffset{17.0f}
	,m_MeterAdderCount{195}
	,m_MeterAdder{ 0.0f }
	,m_HatchSlider{ 0.0f }
	,m_IsPressed{ false }
	,m_IsHatchOpen{ false }
{
}

void Hatch::DrawFront() const
{
	//draws the meter with the filler
	m_Meter.Draw(m_PosMeter);
	utils::SetColor(Colors::Yellowish);
	utils::FillRect(m_MeterFiller);
}

void Hatch::DrawBack() const
{
	// draws the hatch & buttons ( depends on the state )
	m_Hatch.Draw({ m_PosHatch.x - m_HatchSlider,m_PosHatch.y });
	if (m_MeterAdder <= m_MeterAdderCount - 1)
	{
		if (m_IsPressed == true)
		{
			m_Buttons.Draw({ m_PosButton.x + m_ButtonOffset,m_PosButton.y }, { 0,0,m_Buttons.GetWidth(),m_Buttons.GetHeight() });
		}
		else
		{
			m_Buttons.Draw({ m_PosButton.x + m_ButtonOffset,m_PosButton.y }, { m_Buttons.GetWidth() / 3,0,m_Buttons.GetWidth(),m_Buttons.GetHeight() });
		}
	}
	if (m_MeterAdder == m_MeterAdderCount)
	{
		m_Buttons.Draw({ m_PosButton.x + m_ButtonOffset,m_PosButton.y }, { (m_Buttons.GetWidth() / 3) * 2 ,0,m_Buttons.GetWidth(),m_Buttons.GetHeight() });
	}
	
}

void Hatch::Update(float elapsedSec)
{
	//sets the meter filler
	m_MeterFiller = { m_PosMeter.x + 8 ,m_PosMeter.y + 10 ,m_Meter.GetWidth() - 18, m_MeterAdder };

	// slides the hatch open
	if (m_MeterAdder >= m_MeterAdderCount)
	{
		if (m_HatchSlider >= -250)
		{
			m_HatchSlider -= 100 * elapsedSec;
		}
		m_IsHatchOpen = true;
	}
}

Rectf Hatch::GetButtonRect() const
{
	//gets the button possition
	return Rectf{ m_PosButton.x,m_PosButton.y,m_Buttons.GetWidth() / 3, m_Buttons.GetHeight() };
}

bool Hatch::BulletCollision(const Rectf & bullet, const Rectf & hatched)
{
	//checks if player hits the button 
	//fills the meter with +5 each hit
	if (utils::IsOverlapping(bullet, hatched))
	{
		if (m_MeterAdder < m_MeterAdderCount)
		{
			m_IsPressed = true;
			m_MeterAdder += 5;
		}
		return true;
	}
	m_IsPressed = false;
	return false;
}

bool Hatch::IsHatchedOpen()
{
	return m_IsHatchOpen;
}
