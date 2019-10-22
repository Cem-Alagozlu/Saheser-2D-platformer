#include "stdafx.h"
#include "Lever.h"


Lever::Lever(const Point2f& pos, float angle, float scale)
	: m_Pos{ pos }
	, m_Angle{ angle }
	, m_Scale{ scale }
	, m_Lever{"Resources/Sprites/Environment/Lever/lever.png"}
{
}

void Lever::Draw() const
{
	//draws lever
	if (m_IsLeverPulled)
	{
		glPushMatrix();
		glTranslatef(m_Pos.x, m_Pos.y, 0);
		glRotatef(m_Angle, 0.0f, 0.0f, 1.0f);
		glScalef(m_Scale, m_Scale, 1.0f);
		m_Lever.Draw({ 0,0 }, {}, true);
		glPopMatrix();
	}
	//draws lever but other side
	else
	{
		glPushMatrix();
		glTranslatef(m_Pos.x, m_Pos.y, 0);
		glRotatef(m_Angle, 0.0f, 0.0f, 1.0f);
		glScalef(m_Scale, m_Scale, 1.0f);
		m_Lever.Draw({ 0,0 });
		glPopMatrix();
	}


}

bool Lever::Collision(Rectf& actorShape) const
{
	//checks if there is collision between player & lever
	Rectf LeverRect{ m_Pos.x + 10, m_Pos.y + 40,160,200 };

	//if lever pulled -> play soundeffect
	if (utils::IsOverlapping(LeverRect, actorShape))
	{
		if (!m_IsLeverPulled)
		{
			PlayLeverSound();
		}
		return true;
	}
	return false;
}

bool Lever::SetLeverPull(bool isPulled)
{
	//sets lever state
	return m_IsLeverPulled = isPulled;
}

bool Lever::GetLeverState()
{
	//gets lever state
	return m_IsLeverPulled;
}

void Lever::PlayLeverSound() const
{
	SoundManager::PlaySoundEffect("Lever", false, false);
}
