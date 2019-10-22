#include "stdafx.h"
#include "EnemyHard.h"
#include "Game.h"


EnemyHard::EnemyHard(const Point2f & pos, float angle, float swingBoundaries, std::shared_ptr<Player> player)
	:m_EnemyPos{pos}
	,m_Angle{angle}
	,m_SwingBoundaries{swingBoundaries}
	,m_pPlayer{player}
	,m_EnemyHeadOffset{ 550,120 }
	,m_LowerBodyEnemy{ "Resources/Sprites/Enemy/Hard/Enemy01.png" }
	,m_UpperBodyEnemy{ "Resources/Sprites/Enemy/Hard/Enemy02.png" }
	,m_UpperBodyEnemyDamaged{ "Resources/Sprites/Enemy/Hard/Enemy03.png" }
	,m_UpperBodyEnemyDamagedFinal{ "Resources/Sprites/Enemy/Hard/Enemy04.png" }
	,m_EyeSize{ 30 }
	,m_IsLaserEyesOn{false}
	,m_Laser01{"Resources/Sprites/Enemy/Hard/Laser01.png"}
	,m_Laser02{"Resources/Sprites/Enemy/Hard/Laser02.png"}
	,m_Laser03{"Resources/Sprites/Enemy/Hard/Laser03.png"}
	,m_LeftEyeHP{200}
	,m_RightEyeHP{ 200 }
	,m_MouthHP{5000}
	,m_HeadHP{ 8000 }
	,m_IsLeftEyeDestroyed{false}
	,m_IsRightEyeDestroyed{false}
	,m_IsMouthDestroyed{false}
	,m_IsMouthHit{false}
	,m_IsHeadHit{false}
{
	m_IsAttacking = true;
	m_MouthRect = Rectf({ m_EnemyPos.x + 500,m_EnemyPos.y + 170,200,100 });
	m_HeadRect = Rectf({ m_EnemyPos.x  + 350, m_EnemyPos.y + 300, 500,400 });

	//inladen lasers
	for (int i = 0; i < 15; i++)
	{
		m_LaserBeamPos01.push_back({ static_cast<float>(m_EnemyPos.x + m_LowerBodyEnemy.GetWidth() - (i * 130)) + 100,  static_cast<float>((i * (-20))) });
	}
	for (int i = 0; i < 15; i++)
	{
		m_LaserBeamPos02.push_back({ static_cast<float>(m_EnemyPos.x - (i * 300)) + 100,  80 });
	}

	//box for player
	m_AttackRange = (Rectf{ m_EnemyPos.x - 500,m_EnemyPos.y,m_LowerBodyEnemy.GetWidth() + 800,m_LowerBodyEnemy.GetHeight() }); 
	m_EyePositionLeft = { Ellipsef({ m_EnemyPos.x + 450,m_EnemyPos.y + 595 },m_EyeSize,m_EyeSize) };
	m_EyePositionRight = { Ellipsef({ m_EnemyPos.x + 745,m_EnemyPos.y + 595 },m_EyeSize,m_EyeSize) };
}

void EnemyHard::Draw() const
{
	DrawEnemy();
	DrawEnemyAttacks();
}

void EnemyHard::Update(float elapsedSec)
{
	if (!(m_CurrentPhase == Phase::final))
	{
		for (size_t i = 0; i < m_LaserBeamPos01.size(); i++)
		{
			if (utils::IsPointInRect(m_LaserBeamPos01[i], m_pPlayer->GetShape()))
			{
				AddDamage(elapsedSec);
			}
		}

		for (size_t i = 0; i < m_LaserBeamPos02.size(); i++)
		{
			if (utils::IsPointInRect(m_LaserBeamPos02[i], m_pPlayer->GetShape()))
			{
				AddDamage(elapsedSec);
			}
		}
		UpdateEnemySwings();
		UpdateEnemyAttacks(elapsedSec);
	}


}

void EnemyHard::PlayerCollision(const Rectf & playerShape)
{
	if (utils::IsOverlapping(playerShape,m_AttackRange))
	{
		m_IsPlayerReachable = true;
	}
	else
	{
		m_IsPlayerReachable = false;
	}
}

void EnemyHard::BulletCollision(const Rectf & bullet)
{
	if (m_CurrentPhase == Phase::one)
	{
		if (utils::IsPointInRect(m_EyePositionLeft.center, bullet))
		{
			m_LeftEyeHP -= 10;
			m_IsLeftEyeHit = !m_IsLeftEyeHit;
		}
		if (m_LeftEyeHP <= 0)
		{
			m_IsLeftEyeDestroyed = true;
		}
		if (utils::IsPointInRect(m_EyePositionRight.center, bullet))
		{
			m_RightEyeHP -= 10;
			m_IsRightEyeHit = !m_IsRightEyeHit;
		}
		if (m_RightEyeHP <= 0)
		{
			m_IsRightEyeDestroyed = true;
		}
	}
	else if (m_CurrentPhase == Phase::two)
	{
		if (utils::IsOverlapping(m_MouthRect, bullet))
		{
			m_MouthHP -= 15;
			m_IsMouthHit = !m_IsMouthHit;
		}
		if (m_MouthHP <= 0)
		{
			m_IsMouthDestroyed = true;
		}
	}
	else if (m_CurrentPhase == Phase::three)
	{
		if (utils::IsOverlapping(m_HeadRect, bullet))
		{
			m_HeadHP -= 15;
			m_IsHeadHit = !m_IsHeadHit;
		}
		if (m_HeadHP <= 0)
		{
			m_IsHeadHit = true;
		}
	}
}

bool EnemyHard::GetEnemyLifeState()
{
	return m_IsEnemeyCompletlyDead;
}

void EnemyHard::DrawEnemy() const
{

	glPushMatrix();
	m_LowerBodyEnemy.Draw(Rectf{ m_EnemyPos.x,m_EnemyPos.y,1280,720 });
	glTranslatef(m_EnemyPos.x + m_EnemyHeadOffset.x, m_EnemyPos.y + m_EnemyHeadOffset.y, 0);
	glRotatef(m_Angle, 0.0f, 0.0f, 1.0f);
	glScalef(1, 1, 1.0f);
	glTranslatef(-m_UpperBodyEnemy.GetWidth() / 2, 0, 0.0f);
	if (!m_IsMouthHit)
	{
		m_UpperBodyEnemy.Draw({ 0.0f,0.0f });
	}
	else if (m_IsMouthHit)
	{
		m_UpperBodyEnemyDamaged.Draw({ 0.0f,0.0f });
	}
	if (m_IsHeadHit)
	{
		m_UpperBodyEnemyDamagedFinal.Draw({ 0.0f,0.0f });
	}
	glPopMatrix();

	if (m_IsAttacking)
	{
		if (!m_IsLeftEyeDestroyed)
		{
			if (m_IsLeftEyeHit)
			{
				utils::SetColor({ 137.0f / 255.0f,0,0,0.90f });
			}
			else
			{
				utils::SetColor({ 0,0,0,0.90f });
			}
			utils::FillEllipse(m_EyePositionLeft);
		}
		if (!m_IsRightEyeDestroyed)
		{
			if (m_IsRightEyeHit)
			{
				utils::SetColor({ 137.0f / 255.0f,0,0,0.90f });
			}
			else
			{
				utils::SetColor({ 0,0,0,0.90f });
			}
			utils::FillEllipse(m_EyePositionRight);
		}
	}
}

void EnemyHard::DrawEnemyAttacks() const
{
	if (m_IsPlayerReachable && !(m_CurrentPhase == Phase::final))
	{
		if (m_CurrentPhase == Phase::one)
		{
			if (m_LaserCounterPhase01 < 3)
			{
				for (int i = 0; i < m_LaserBeamPos01.size(); i++)
				{
					m_Laser01.Draw({ m_LaserBeamPos01[i].x,m_LaserBeamPos01[i].y });
				}
			}
			if (m_IsLaserEyesOn)
			{
				if (!m_IsRightEyeDestroyed)
				{
					utils::DrawLine({ m_EyePositionRight.center }, {m_pPlayer->GetShape().left +m_pPlayer->GetShape().width / 2,m_pPlayer->GetShape().bottom +m_pPlayer->GetShape().height }, 10);
				}
				if (!m_IsLeftEyeDestroyed)
				{
					utils::DrawLine({ m_EyePositionLeft.center }, {m_pPlayer->GetShape().left +m_pPlayer->GetShape().width / 2,m_pPlayer->GetShape().bottom +m_pPlayer->GetShape().height }, 10);
				}
			}
		}
		else if (m_CurrentPhase == Phase::two)
		{
			for (int i = 0; i < m_LaserBeamPos02.size(); i++)
			{
				m_Laser02.Draw({ m_LaserBeamPos02[i].x,m_LaserBeamPos02[i].y });
			}
		}
		else if (m_CurrentPhase == Phase::three)
		{
			for (int i = 0; i < m_LaserBeamPos01.size(); i++)
			{
				m_Laser01.Draw({ m_LaserBeamPos01[i].x,m_LaserBeamPos01[i].y });
			}
			for (int i = 0; i < m_LaserBeamPos02.size(); i++)
			{
				m_Laser02.Draw({ m_LaserBeamPos02[i].x,m_LaserBeamPos02[i].y });
			}
		}
	}
}

void EnemyHard::UpdateEnemySwings()
{
	if (!m_IsAttacking)
	{
		if (m_IsPositive)
		{
			m_Angle = m_Angle + 0.2f;
		}
		else if (m_IsPositive == false)
		{
			m_Angle = m_Angle - 0.2f;
		}
		if (m_Angle <= -m_SwingBoundaries)
		{
			m_IsPositive = true;
		}
		if (m_Angle >= m_SwingBoundaries)
		{
			m_IsPositive = false;
		}
	}
	else
	{
		m_Angle = 0;
	}

}

void EnemyHard::UpdateEnemyAttacks(float elapsedSec)
{
	if (m_CurrentPhase == Phase::one)
	{
		if (m_LaserCounterPhase01 < 3)
		{
			for (int i = 0; i < m_LaserBeamPos01.size(); i++)
			{
				m_LaserBeamPos01[i].y += elapsedSec * 100;
				if (m_LaserBeamPos01[i].y >= m_LowerBodyEnemy.GetHeight() + m_LowerBodyEnemy.GetHeight() / 2)
				{
					m_LaserBeamPos01[i].y = -30.0f;
				}
			}
			if (m_LaserBeamPos01[0].y == -30.0f)
			{
				++m_LaserCounterPhase01;
			}
			if (m_LaserCounterPhase01 == 1)
			{
				m_IsLaserEyesOn = false;
			}
		}
		if (m_LaserCounterPhase01 >= 3 )
		{
			while (m_Amounts == 0)
			{
				m_IsLaserEyesOn = true;
				if (!m_IsLeftEyeDestroyed || !m_IsRightEyeDestroyed)
				{
					m_pPlayer->GetPlayerManager().SetHealth((m_pPlayer->GetPlayerManager().GetHealth()) - 3);
				}
				++m_Amounts;
			}

		}

		if (m_Amounts == 1)
		{
			m_LaserCounterPhase01 = 0;
			m_Amounts = 0;
		}

		if (m_IsLeftEyeDestroyed && m_IsRightEyeDestroyed && m_LaserCounterPhase01 == 2)
		{
			m_IsAttacking = false;
			m_CurrentPhase = Phase::two;
		}


		Game::m_Cam.x = float(rand() % 2);
		Game::m_Cam.y = float(rand() % 2);
	}
	if (m_CurrentPhase == Phase::two)
	{
		for (int i = 0; i < m_LaserBeamPos01.size(); i++)
		{
			m_LaserBeamPos02[i].x += elapsedSec * 200;
			if (m_LaserBeamPos02[i].x >= m_LowerBodyEnemy.GetWidth() + m_EnemyPos.x +  m_LowerBodyEnemy.GetWidth()/2)
			{
				m_LaserBeamPos02[i].x = -30.0f;
			}
		}
		if (m_IsMouthDestroyed)
		{
			m_CurrentPhase = Phase::three;
		}
		Game::m_Cam.x = float(rand() % 5);
		Game::m_Cam.y = float(rand() % 3);
	}
	if (m_CurrentPhase == Phase::three)
	{
		for (int i = 0; i < m_LaserBeamPos01.size(); i++)
		{
			m_LaserBeamPos02[i].x += elapsedSec * 200;
			if (m_LaserBeamPos02[i].x >= m_LowerBodyEnemy.GetWidth() + m_EnemyPos.x + m_LowerBodyEnemy.GetWidth() / 2)
			{
				m_LaserBeamPos02[i].x = -30.0f;
			}
		}

		for (int i = 0; i < m_LaserBeamPos01.size(); i++)
		{
			m_LaserBeamPos01[i].y += elapsedSec * 100;

			if (m_LaserBeamPos01[i].y >= m_LowerBodyEnemy.GetHeight() + m_LowerBodyEnemy.GetHeight() / 2)
			{
				m_LaserBeamPos01[i].y = -30.0f;
			}
		}
		if (m_LaserBeamPos01[0].y == -30.0f)
		{
			++m_LaserCounterPhase01;
		}
		if (m_HeadHP <= 0.0f)
		{
			m_CurrentPhase = Phase::final;
		}
		Game::m_Cam.x = float(rand() % 7);
		Game::m_Cam.y = float(rand() % 3);
	}
	if (m_CurrentPhase == Phase::final)
	{
		m_IsEnemeyCompletlyDead = true;
	}
}

void EnemyHard::AddDamage(float elapsedSec)
{
	m_Timer += elapsedSec;
	if (m_Timer <= 0.02f)
	{
		m_pPlayer->AddHealth(1);
	}
	if (m_Timer >= 0.5f)
	{
		m_Timer = 0.0f;
	}
}
