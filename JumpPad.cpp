#include "stdafx.h"
#include "JumpPad.h"


JumpPad::JumpPad(const Point2f & pos)
	:m_Pos{pos}
{
	//sets the pos for your jump pad & texure
	m_JumpPadTexture = (std::make_unique<Texture>("Resources/Sprites/Environment/JumpPad/JumpPad.png"));
	m_JumpPadRect = { m_Pos.x, m_Pos.y, 120, 40 };
}

void JumpPad::Draw() const
{
	//draws the jumppad
	glPushMatrix();
	glTranslatef(m_Pos.x, m_Pos.y, 1);
	glScalef(0.5f, 0.75f, 1.0f);
	if (m_IsJumping)
	{
		m_JumpPadTexture->Draw({ 0,0 }, { m_JumpPadTexture->GetWidth() / 2,0,m_JumpPadTexture->GetWidth() /2,m_JumpPadTexture->GetHeight() });
	}
	else
	{
		m_JumpPadTexture->Draw({ 0,0 }, { 0,0,m_JumpPadTexture->GetWidth() / 2,m_JumpPadTexture->GetHeight() });
	}
	glPopMatrix();
}


bool JumpPad::CollisionJumpPad(Rectf & actorShape)  const
{
	//checks if player is on the pad
	if (utils::IsOverlapping(actorShape,m_JumpPadRect))
	{
		return true;
	}
	return false;
}

void JumpPad::SetIsJumping( bool isJumping)
{
	//sets to player to jumping
	m_IsJumping = isJumping;
}

bool JumpPad::GetIsJumping()
{
	//gets the player state
	return m_IsJumping;
}
