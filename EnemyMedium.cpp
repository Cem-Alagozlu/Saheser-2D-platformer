#include "stdafx.h"
#include "EnemyMedium.h"
#include "LevelBase.h"

EnemyMedium::EnemyMedium()
	: m_Idle{ "Resources/Sprites/Enemy/Medium/idle.png", 0.0f, 0.0f, 5882, 1794, 4, 1, 6 }
	, m_Walking{ "Resources/Sprites/Enemy/Medium/walk.png", 0.0f, 0.0f, 5882, 1794, 4, 1, 6 }
	, m_Shooting{ "Resources/Sprites/Enemy/Medium/shooting.png", 0.0f, 0.0f, 3988, 1772, 3, 1, 6 }
	, m_Dead{ "Resources/Sprites/Enemy/Medium/death.png", 0.0f, 0.0f, 8000, 1794, 8, 1, 6 }
	, m_pCurrentSprite(&m_Idle)
	, m_BulletTexture("Resources/Sprites/Enemy/Medium/bullet01.png")
	, m_Life{ 100 }
{
	m_WaitTime = { 1.0f }; // wait time to shoot
	m_Scale = 0.1f; // texture scaling
	//setting up his shape for rect
	m_Shape = { 0,0,(m_Idle.GetWidth()  + m_BeginPosition.x) * m_Scale, (m_Idle.GetHeight()  + m_BeginPosition.y) * m_Scale };
	m_ActionState = ActionState::idle;// his begin state
}

void EnemyMedium::Draw() const
{
	//draws enemy and checks if he stands left or right
	glPushMatrix();
	glTranslatef(m_Shape.left, m_Shape.bottom, 0);
	glScalef(m_Scale, m_Scale, 1);
	if (m_Direction == Direction::left)
	{
		m_pCurrentSprite->Draw(true);
	}
	if (m_Direction == Direction::right)
	{
		m_pCurrentSprite->Draw(false);
	}
	glPopMatrix();

	//draws the enemy bullets
	for (int i = 0; i < m_BulletPos.size(); i++)
		{
			m_BulletTexture.Draw({ m_BulletPos[i].x,m_BulletPos[i].y });
		}
}

void EnemyMedium::Update(float elapsedSec, LevelManager& level, Rectf& playerShape)
{
	m_AccumSec += elapsedSec;

	//creates a player rect shape ( to track ) ) 
	m_PlayerCollisionRect = (Rectf{ m_Shape.left - 200 ,m_Shape.bottom - 200,600,600 });

	//stops updating if player == dead
	if (!m_Dead.HasEnded())
	{
		UpdateSprite(elapsedSec);
	}
	else
	{
		m_IsDead = true;
	}

	// updates the level collision (vertices)
	UpdateCollision(level.GetCurrentLevel());

	//checks if player is not dead
	if (m_Life  > 0)
	{
		//if velocity.x && y == 0, his state will be put into idle
		if (m_Velocity.x == 0 && m_Velocity.y == 0)
		{
			if (!m_IsMoving)
			{
				m_ActionState = ActionState::idle;
			}
		}
		
		else
		{
			m_ActionState = ActionState::walking;//if not, he will be walking
		}
		
		UpdatePosition(elapsedSec);//updates his position
		if (m_IsMoving)
		{
			if (m_IsGoingLeft) // left velocity 
			{
				m_Direction = Direction::left;
				m_Velocity.x = -300;
			}
			else  // right velocity 
			{
				m_Direction = Direction::right;
				m_Velocity.x = 300;
			}

		}

		// wait time for shooting (delay)
		if (m_AccumSec >= m_WaitTime)
		{
			m_IsMoving = !m_IsMoving;
			m_AccumSec = 0;
			m_Amounts = 0;
		}

		//checks if player is in detection zone
		//if yes, enemy will stop, and start shooting
		if (utils::IsOverlapping(playerShape, m_PlayerCollisionRect))
		{
			m_ActionState = ActionState::shooting;
			m_Velocity.x = 0;

			// adds bullets into vector
			while (m_Amounts == 0)
			{
				m_CollisionCalculation.push_back({ (playerShape.left - m_Shape.left),(playerShape.bottom - m_Shape.bottom) });
				m_BulletPos.push_back({ m_Shape.left + m_Shape.width - 50 ,m_Shape.bottom + m_Shape.height / 2 - 50 });
				m_BulletRect.push_back({ m_Shape.left + m_Shape.width - 50,m_Shape.bottom + m_Shape.height / 2 - 50,m_BulletTexture.GetWidth(),m_BulletTexture.GetHeight() });
				++m_Amounts;
			}
		}

		//checks in which direction the enemy has to shoot
		if (m_ActionState == ActionState::shooting)
		{
			if (m_IsShootingLeft)
			{
				m_Direction = Direction::left;
			}
			else
			{
				m_Direction = Direction::right;
			}
		}
		else
		{
			if (m_IsGoingLeft)
			{
				m_Direction = Direction::left;

			}
			else
			{
				m_Direction = Direction::right;

			}

		}
	}
	else
	{
	 m_ActionState = ActionState::dying;
	}


	//caclculates the direction of the bullets 
	for (int i = 0; i < m_CollisionCalculation.size(); i++)
	{
		if (m_CollisionCalculation[i].x > -2.0f)
		{
			m_IsShootingLeft = false;
			m_BulletPos[i].x += 10.0f;
			m_BulletRect[i].left += 10.0f;
		}
		if (m_CollisionCalculation[i].x < 2.0f)
		{
			m_IsShootingLeft = true;
			m_BulletPos[i].x -= 10.0f;
			m_BulletRect[i].left -= 10.0f;
		}


		if (m_CollisionCalculation[i].y >  -2.0f)
		{
			m_BulletPos[i].y += 4.0f;
			m_BulletRect[i].bottom += 4.0f;
		}
		if (m_CollisionCalculation[i].y < 2.0f)
		{
			m_BulletPos[i].y -= 4.0f;
			m_BulletRect[i].bottom -= 4.0f;
		}
		if (m_CollisionCalculation[i].y > -1.0f && m_CollisionCalculation[i].y < 2.0f)
		{
			m_BulletPos[i].y -= 0.0f;
			m_BulletRect[i].bottom -= 0.0f;
		}
	}

	if (m_BulletPos.size() >= 20)
	{
		for (int i = 0; i < 19; i++)
		{
			m_BulletRect.pop_front();
			m_BulletPos.pop_front();
			m_CollisionCalculation.pop_front();
		}
	}

	m_Velocity.y += m_Acceleration.y;
}

bool EnemyMedium::SetMovement(bool isMoving)
{
	//sets movement for enemy (if he can move)
	m_IsMoving = isMoving;  
	return m_IsMoving;
}

void EnemyMedium::SetPosition(const Point2f & enemyPos)
{
	//sets position for enemy
	m_Shape.left = enemyPos.x;
	m_Shape.bottom = enemyPos.y;
}

void EnemyMedium::SetActionState(ActionState actionState)
{
	//sets action state
	m_ActionState = actionState;
}

void EnemyMedium::SetLevelBeginPos(const Point2f & pos)
{
	//sets begin positions
	m_BeginPosition = pos;
}

void EnemyMedium::UpdateCollision(std::shared_ptr<LevelBase> level)
{
	//updates the collision for your level && checks if your enemy goes left
	level->HandleCollision(m_Shape, m_Velocity);
	m_IsGoingLeft = level->GetLeftBool();
}

void EnemyMedium::BulletCollision(const Rectf & bullet)
{
	//if bullet overlaps enemy, his life will be reduced 
	if (utils::IsOverlapping(bullet,m_Shape))
	{
		--m_Life;
	}
}

bool EnemyMedium::PlayerCollisionBullet(const Rectf & player)
{
	// checks if player got hit by bullet or not
	for (int i = 0; i < m_BulletRect.size(); i++)
	{
		if (utils::IsOverlapping(m_BulletRect[i], player))
		{
			return true;
		}
	}
	return false;
}

Point2f EnemyMedium::GetPosition() const
{
	//gets position of enemy
	return Point2f(m_Shape.left, m_Shape.bottom);
}

Rectf EnemyMedium::GetShape() const
{
	//gets enemy shape
	return m_Shape;
}

bool EnemyMedium::GetAliveState() const
{
	//checks if enemy is alive or not
	return m_IsDead;
}

void EnemyMedium::UpdatePosition(float elapsedSec)
{
	//updates player position
	m_Shape.left += m_Velocity.x * elapsedSec;
	m_Shape.bottom += m_Velocity.y * elapsedSec;
}

void EnemyMedium::UpdateSprite(float elapsedSec)
{
	//switches between states for enemy
	switch (m_ActionState)
	{
	case EnemyMedium::ActionState::idle:
		m_pCurrentSprite = &m_Idle;
		break;
	case EnemyMedium::ActionState::walking:
		m_pCurrentSprite = &m_Walking;
		break;
	case EnemyMedium::ActionState::shooting:
		m_pCurrentSprite = &m_Shooting;
		break;
	case EnemyMedium::ActionState::dying:
		m_pCurrentSprite = &m_Dead;
		break;
	default:
		break;
	}

	m_pCurrentSprite->Update(elapsedSec);
}
