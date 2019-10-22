#include "stdafx.h"
#include "TrapCircleSaw.h"

TrapCircleSaw::TrapCircleSaw(const Point2f& position, float scale)
	: Trap{position,"Resources/Sprites/Environment/Traps/Saw.png",m_Angle,scale,"Resources/Sprites/Environment/Traps/saw.svg"}
{
	//sets the shape and radius for the circle saw
	m_Shape.center.x = m_Pos.x + m_Texure.GetWidth() / 2;
	m_Shape.center.y = m_Pos.y + m_Texure.GetHeight() / 2;
	m_Shape.radius = 100 * m_Scale;
}

void TrapCircleSaw::Draw() const
{
	//draws the circle saw
	glPushMatrix();
	glTranslatef(m_Shape.center.x, m_Shape.center.y, 0);
	glRotatef(m_Angle, 0, 0, 1);
	glScalef(m_Scale, m_Scale, 1.0f);
	glTranslatef(-m_Texure.GetWidth() / 2, -m_Texure.GetHeight() / 2, 0);
	m_Texure.Draw({0,0});
	glPopMatrix();
}

void TrapCircleSaw::Update(float elapsedSec, const Vector2f& player)
{
	//updates the circle saw angle
	m_Angle += 2;
}

bool TrapCircleSaw::CircleCollision(const Rectf& rect) const
{
	//checks if there is collision
	if (utils::IsOverlapping(rect, m_Shape))
	{
		return true;
	}
	return false;
}
