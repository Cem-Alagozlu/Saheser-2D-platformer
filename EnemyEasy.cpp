#include "stdafx.h"
#include "EnemyEasy.h"

EnemyEasy::EnemyEasy(const Point2f& actorPos, const Point2f& endPoint, const std::string & type, const Point2f& offset, float dmg,float waitTime)
	: Enemy{ offset }
	, m_EnemyTypeString{ type }
	, m_EasyEnemySlimy{ "Resources/Sprites/Enemy/Easy/easy01.png" }
	, m_EasyEnemyFlying{ "Resources/Sprites/Enemy/Easy/easy02.png" }
	, m_BulletTexture{ "Resources/Sprites/Enemy/Easy/bullet01.png" }
	, m_ActorPos{ actorPos }
	, m_EndPos(endPoint)
	, m_WaitTime{ waitTime }
	, m_MovementSpeed{100.0f}
{
	m_BeginPos = m_ActorPos;
	m_EnemyDamage = dmg;
}

void EnemyEasy::Draw() const
{
	if (m_EnemyTypeString == "SlimyEasy"&& !m_IsDespawning)
	{
		glPushMatrix();
		glTranslatef(m_ActorPos.x , m_ActorPos.y, 0);
		DrawHealthBar();
		glScaled(0.45f, 1.2f, 1.0f);
		if (m_IsMoving && !m_IsEnemyDead)
		{
		m_EasyEnemySlimy.Draw({ 0,0 }, { 0,0,m_EasyEnemySlimy.GetWidth() / 3,m_EasyEnemySlimy.GetHeight() }, !m_IsMovingLeft);
		}
		else if(!m_IsMoving && !m_IsEnemyDead)
		{
			m_EasyEnemySlimy.Draw({ 0,0 }, { m_EasyEnemySlimy.GetWidth() / 3,0,m_EasyEnemySlimy.GetWidth() / 3,m_EasyEnemySlimy.GetHeight() }, !m_IsMovingLeft);
		}
		if (m_IsEnemyDead)
		{
			m_EasyEnemySlimy.Draw({ 0,0 }, { m_EasyEnemySlimy.GetWidth() - m_EasyEnemySlimy.GetWidth() / 3,0,m_EasyEnemySlimy.GetWidth() / 3,m_EasyEnemySlimy.GetHeight() }, !m_IsMovingLeft);
		}
		glPopMatrix();
	}
	if (m_EnemyTypeString == "FlyingEasy"&& !m_IsDespawning)
	{
		glPushMatrix();
		glTranslatef(m_ActorPos.x, m_ActorPos.y, 0);
		DrawHealthBar();
		if (!m_IsEnemyDead && m_IsMoving)
		{
			m_EasyEnemyFlying.Draw({ 0,0 }, { 0,0,m_EasyEnemyFlying.GetWidth() ,m_EasyEnemyFlying.GetHeight() }, !m_IsMovingLeft);
		}
		if (!m_IsMoving)
		{
			m_EasyEnemyFlying.Draw({ 0,0 }, { 0,0,m_EasyEnemyFlying.GetWidth() ,m_EasyEnemyFlying.GetHeight() }, !m_IsMovingLeft);
		}

		if (m_IsEnemyDead)
		{

		}
		glPopMatrix();
		if (!m_IsEnemyDead)
		{
			for (int i = 0; i < m_BulletPos.size(); i++)
			{
				m_BulletTexture.Draw({ m_BulletPos[i].x,m_BulletPos[i].y });
			}
		}
	}
}

void EnemyEasy::Update(float elapsedSec)
{
	Enemy::Update(elapsedSec);
	m_AccumSec +=  elapsedSec;
	
	if (m_EnemyTypeString == "SlimyEasy")
	{
			if (m_IsMoving && !m_IsEnemyDead)
			{
				if (m_IsMovingLeft)
				{
					m_ActorPos.x -= m_MovementSpeed * elapsedSec;
					if (m_ActorPos.x <= m_BeginPos.x)
					{
						m_IsMovingLeft = false;
					}
				}
				else
				{
					m_ActorPos.x += m_MovementSpeed * elapsedSec;
					if (m_ActorPos.x >= m_EndPos.x)
					{
						m_IsMovingLeft = true;
					}
				}
			}
			if (m_AccumSec >= m_WaitTime)
			{
				m_IsMoving = !m_IsMoving;
				m_AccumSec = 0;
			}
	}
	if (m_EnemyTypeString == "FlyingEasy")
	{
		if (m_IsMoving && !m_IsEnemyDead)
		{
			if (m_IsMovingLeft)
			{
				m_ActorPos.x -= m_MovementSpeed * elapsedSec;
				if (m_ActorPos.x <= m_BeginPos.x)
				{
					m_IsMovingLeft = false;
				}
			}
			else
			{
				m_ActorPos.x += m_MovementSpeed * elapsedSec;
				if (m_ActorPos.x >= m_EndPos.x)
				{
					m_IsMovingLeft = true;
				}
			}
		}
		if (m_AccumSec >= m_WaitTime)
		{
			m_IsMoving = !m_IsMoving;
			m_AccumSec = 0;
			m_Amounts = 0;
		}
		
		if (!m_IsMoving && !m_IsEnemyDead)
		{
			while (m_Amounts == 0)
			{
				m_BulletPos.push_back({ m_ActorPos.x + (m_EasyEnemyFlying.GetWidth() / 2 - 8),m_ActorPos.y });
				m_BulletRect.push_back({ m_ActorPos.x + (m_EasyEnemyFlying.GetWidth() / 2 - 8),m_ActorPos.y,m_BulletTexture.GetWidth(),m_BulletTexture.GetHeight() });
				++m_Amounts;
			}
		}

	}
	if (m_HealthPoints <= -m_LimitHealthBar)
	{
		m_IsEnemyDead = true;
	}
	for (int i = 0; i < m_BulletPos.size(); i++)
	{
		m_BulletPos[i].y -= 1.0f;
		m_BulletRect[i].bottom -= 1.0f;

		if ((m_BulletPos[i].y + m_BulletTexture.GetHeight()) <= 0.0f 
			&& (m_BulletRect[i].bottom + m_BulletRect[i].height) <= 0.0f)
		{
			m_BulletPos.pop_front();
			m_BulletRect.pop_front();
		}
	}
}

void EnemyEasy::BulletCollision(const Rectf & bullet, const Rectf & enemy)
{
	//checks bullet collision between enemy & player bullet
	if (utils::IsOverlapping(bullet, enemy))
	{
		if (-m_LimitHealthBar <= m_HealthPoints )
		{
			m_HealthPoints -= m_EnemyDamage;
		}
	}
}

Rectf EnemyEasy::GetPosition() const
{
	if (m_EnemyTypeString == "SlimyEasy")
	{
		return { m_ActorPos.x,m_ActorPos.y, m_EasyEnemySlimy.GetWidth() / 3, m_EasyEnemySlimy.GetHeight() };
	}
	else if(m_EnemyTypeString == "FlyingEasy")
	{
		return { m_ActorPos.x,m_ActorPos.y, m_EasyEnemyFlying.GetWidth(), m_EasyEnemyFlying.GetHeight() };
	}
	return Rectf{}; 
	// returns the enemy position
}

bool EnemyEasy::IsEnemyDestroyed() const
{
	return m_CanBeRemoved; // checks if enemy can be deleted ( after he died ) 
}

bool EnemyEasy::PlayerCollisionBullet(const Rectf & player)
{
	//checks if bullet collides with player
	for (int i = 0; i < m_BulletRect.size(); i++)
	{
		if (utils::IsOverlapping(m_BulletRect[i], player))
		{
			return true;
		}
	}
	return false;
}


