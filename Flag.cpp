#include "stdafx.h"
#include "Flag.h"


Flag::Flag(const Point2f & pos)
	:m_Pos{pos}
	,m_FlagSprite{ "Resources/Sprites/Environment/Flag/FlagSprite.png", 0.0f, 0.0f, 256.0f, 128.0f, 2,1,5 }
{
	//sets flag texture && flag rect (for collision)
	m_FlagTexture = { std::make_unique<Texture>("Resources/Sprites/Environment/Flag/Flag.png") };
	m_FlagRect = { m_Pos.x,m_Pos.y,m_FlagTexture->GetWidth(),m_FlagTexture->GetHeight() };
}

void Flag::Draw() const
{
	//draws flag checked & unchecked (after collision) 
	glPushMatrix();
	glTranslatef(m_Pos.x, m_Pos.y, 1);
	glScalef(0.55f, 0.55f, 1.0f);
	if (m_IsFlagTouched)
	{
		m_FlagSprite.Draw();
	}
	else
	{
		m_FlagTexture->Draw({0,0});
	}
	glPopMatrix();
}

void Flag::Update(float elapsedSec)
{
	//updates flag anim
	m_FlagSprite.Update(elapsedSec);
}

bool Flag::CollisionFlag(Rectf & actorShape) 
{
	//checks if player has collision with flag
	if (utils::IsOverlapping(actorShape,m_FlagRect))
	{
		m_IsFlagTouched = true;
		return true;
	}
	return false;
}
