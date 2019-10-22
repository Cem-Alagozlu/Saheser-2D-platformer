#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy(const Point2f& offSet)
	:m_HealthBarTexture{"Resources/Sprites/Enemy/Hud/healthbar.png"}
	,m_OffSetHealthBar{offSet}
	,m_LimitHealthBar{380}
	,m_HealthPoints{0.0f}
	,m_DespawnTime{0.45f}
	,m_DespawnCounterLimit{4}
	,m_IsEnemyDead{ false }
	,m_IsDespawning{ false }
	,m_CanBeRemoved{ false }
{
}

void Enemy::Update(float elapsedSec)
{
	m_CountTime += elapsedSec;

	// checks if enemy is killed
	// if yes, fade in/out X times, then remove
	if (m_DespawnCounter <= 4)
	{
		if (m_IsEnemyDead)
		{
			if (m_CountTime <= m_DespawnTime)
			{
				m_IsDespawning = false; // tekent
			}
			else
			{
				m_IsDespawning = true;
				if (m_CountTime >= m_DespawnTime * 2)
				{
					++m_DespawnCounter;
					m_CountTime = 0.0f;
				}
			}
		}
	}
	else
	{
		m_CanBeRemoved = true;
	}
}

void Enemy::DrawHealthBar() const
{
	//draws a blue health bar , if bellow 50% -> green
	// if below 25% -> red
	glPushMatrix();
	glTranslatef(m_OffSetHealthBar.x, m_OffSetHealthBar.y, 1);
	glScalef(0.3f, 0.3f, 1.0f);
	if (m_EnemyDamage >= m_HealthPoints)
	{
		if (m_HealthPoints >= -m_LimitHealthBar/2)
		{
			utils::SetColor(Colors::Green);
		}
		else
		{
			utils::SetColor(Colors::Red);
		}
		utils::FillRect({ m_OffSetHealthBar.x + 80,m_OffSetHealthBar.y + 20 }, m_HealthBarTexture.GetWidth() - 90 + m_HealthPoints, m_HealthBarTexture.GetHeight() - 30);
	}
	m_HealthBarTexture.Draw({ m_OffSetHealthBar.x ,m_OffSetHealthBar.y});
	glPopMatrix();
}

bool Enemy::IsEnemyDead() const
{
	return m_IsEnemyDead; // checks if enemy is dead
}



