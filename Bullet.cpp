#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(Point2f & pos, Vector2f & dir)
	: m_Pos{pos}
	, m_Speed{25.0f}
	, m_BulletTexture{"Resources/Sprites/Character/bullet1.png"}
	, m_Velocity{dir.Normalized() * m_Speed}

{
}

void Bullet::Update(float elapsedSec)
{
	m_Pos.x += m_Velocity.x;
	m_Pos.y += m_Velocity.y;
}

void Bullet::Draw() const
{
	m_BulletTexture.Draw(m_Pos);
}

Rectf Bullet::GetBulletLocation()
{
	return Rectf{ m_Pos.x,m_Pos.y,m_BulletTexture.GetWidth(),m_BulletTexture.GetHeight() };
}


