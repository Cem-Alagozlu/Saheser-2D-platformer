#include "stdafx.h"
#include "TrapSwingBlade.h"
#include "SVGParser.h"
#include "SoundManager.h"

TrapSwingBlade::TrapSwingBlade(const Point2f& position, float angle, float scale, float swingBound)
	: Trap{position,"Resources/Sprites/Environment/Traps/blade_swing01.png",angle,scale,"Resources/Sprites/Environment/Traps/blade_swing01.svg"}
	  , m_SwingBounderies{swingBound}
{
}

void TrapSwingBlade::Draw() const
{
	//draws the blade
	glPushMatrix();
	glTranslatef(m_Pos.x, m_Pos.y, 0);
	glRotatef(m_Angle, 0.0f, 0.0f, 1.0f);
	glScalef(m_Scale, m_Scale, 1.0f);
	glTranslatef(-m_Texure.GetWidth() / 2, -m_Texure.GetHeight(), 0.0f);
	m_Texure.Draw({0.0f,0.0f});
	glPopMatrix();
}

void TrapSwingBlade::Update(float elapsedSec, const Vector2f& player)
{
	//updates the vertices for the blade
	UpdateVertices(Vector2f(-m_Texure.GetWidth() / 2.0f, -m_Texure.GetHeight()));

	//blade swings from left to right (depends on the angle)
	if (m_IsPositive == true)
	{
		++m_Angle;
	}
	else if (m_IsPositive == false)
	{
		--m_Angle;
	}

	if (m_Angle == -m_SwingBounderies)
	{
		m_IsPositive = true;
	}
	if (m_Angle >= m_SwingBounderies)
	{
		m_IsPositive = false;
	}

	SoundManager::PlaySoundEffectTraps(player, m_Pos, "Blade", true, true);
	SoundManager::Update(player, m_Pos, "Blade");
}

bool TrapSwingBlade::BladeCollision(const Rectf& player) const
{
	//check if the blade hits the plyer
	return utils::IsOverlapping(m_VerticesWorld, player);
}
