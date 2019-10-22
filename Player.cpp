#include "stdafx.h"
#include "Player.h"
#include "SoundManager.h"
#include "LevelBase.h"


Player::Player(const Camera& cam)
	: m_IsMoving(true)
	  , m_Camera{cam}
	  , m_Jump{ "Resources/Sprites/Character/jump.png", 0.0f, 0.0f, 2835 , 1112, 5, 2, 15 }
	  , m_Idle{"Resources/Sprites/Character/idle.png", 0.0f, 0.0f, 2835.0f, 1112.0f, 5, 2, 15 }
	  , m_Death{ "Resources/Sprites/Character/death.png", 0.0f, 0.0f, 2835.0f, 1112.0f, 5, 2, 10 }
	  , m_Run{"Resources/Sprites/Character/run.png", 0.0f, 0.0f, 2268, 1112, 4, 2, 15 }
	  , m_RunShoot{ "Resources/Sprites/Character/runshoot.png", 0.0f, 0.0f, 1701, 1668, 3,3, 15 }
	  , m_IdleShoot{ "Resources/Sprites/Character/shoot.png", 0.0f, 0.0f, 2268, 1112, 4,2, 10 }
	  , m_Melee{ "Resources/Sprites/Character/melee.png", 0.0f, 0.0f, 2268, 1112, 4,2, 15 }
	  , m_JumpShoot{ "Resources/Sprites/Character/jumpShoot.png", 0.0f, 0.0f, 2835 , 556, 5, 1, 8 }
	  , m_pCurrentSprite(nullptr)
	  , m_Scale{ 0.35f }
	  , m_PlayerHud(m_PlayerManager)
{
	m_CollisonBox.width = m_Idle.GetWidth() *m_Scale * 0.35f;
	m_CollisonBox.height = m_Idle.GetHeight() * m_Scale * 0.65f;
}


void Player::Update(float elapsedSec, std::shared_ptr<LevelBase> level)
{
	UpdateSprite(elapsedSec);
	UpdateCollision(level);
	if (m_Velocity.x == 0 && m_Velocity.y == 0 && !(m_Smovement == SecondaryMovement::death))
	{
		if (m_IsIdleShooting)
		{
			m_Smovement = SecondaryMovement::idleShoot;
		}
		else
		{
			m_Smovement = SecondaryMovement::idle;
		}
	}
	if (m_Velocity.y == 0)
	{
		m_IsJumping = false;
	}

	UpdatePosition(elapsedSec);
	HandleMoveKeysState(elapsedSec);
	UpdateReset(elapsedSec);

	UpdateAnimations();


	m_PlayerHud.Update(elapsedSec);
	
	for (size_t i = 0; i < m_Bullets.size(); i++)
	{
		m_Bullets[i].Update(elapsedSec);
	}

	
}

void Player::UpdateSprite(float elapsedSec)
{
	switch (m_Smovement)
	{
	case SecondaryMovement::idle:
		m_pCurrentSprite = &m_Idle;
		break;
	case SecondaryMovement::run:
		m_pCurrentSprite = &m_Run;
		break;
	case SecondaryMovement::jump:
		m_pCurrentSprite = &m_Jump;
		break;
	case SecondaryMovement::runShoot:
		m_pCurrentSprite = &m_RunShoot;
		break;
	case SecondaryMovement::idleShoot:
		m_pCurrentSprite = &m_IdleShoot;
		break;
	case SecondaryMovement::melee:
		m_pCurrentSprite = &m_Melee;
		break;
	case SecondaryMovement::jumpShoot:
		m_pCurrentSprite = &m_JumpShoot;
		break;
	case SecondaryMovement::death:
		m_pCurrentSprite = &m_Death;
		break;
	default:
		break;
	}

	if (m_IsIdleShooting || m_IsRunShooting || m_IsJumpShooting)
	{
		m_ShootTimer += elapsedSec;
	}
	m_pCurrentSprite->Update(elapsedSec);
}

void Player::UpdatePosition(float elapsedSec)
{
	m_CollisonBox.left += m_Velocity.x * elapsedSec;
	m_CollisonBox.bottom += m_Velocity.y * elapsedSec;
}

void Player::UpdateCollision(std::shared_ptr<LevelBase> level)
{
	level->HandleCollision(m_CollisonBox, m_Velocity);
}

void Player::UpdateReset(float elapsedSec)
{
	if (m_Smovement == SecondaryMovement::death)
	{
		if (!m_HasPlayedDeathSound)
		{
			SoundManager::PlaySoundEffect("Death", false, true);
			m_HasPlayedDeathSound = true;
		}
		AddHealth(1);
		if (m_pCurrentSprite->HasEnded())
		{
			SetMovement(false);
			m_pCurrentSprite->Lock();
			m_Velocity.y -= 50.0f;
			m_TotalAccum += elapsedSec;

			if (m_TotalAccum >= m_TotalTimerReset)
			{
				SetPosition(m_BeginPosition);
				m_pCurrentSprite->Unlock();
				SetMovement(true);
				m_Smovement = SecondaryMovement::idle;
				m_TotalAccum = 0.0f;
				m_PlayerManager.AddLives(-1);
				m_HasPlayedDeathSound = false;
				m_Run.Unlock();
				m_Jump.Unlock();
				m_Melee.Unlock();
				m_JumpShoot.Unlock();
				m_RunShoot.Unlock();
				m_Death.Unlock();
				m_Idle.Unlock();
				AddHealth(3);
			}
		
		}
	}

}

void Player::UpdateAnimations()
{
	if (m_TotalShootTime <= m_ShootTimer)
	{
		m_IsIdleShooting = false;
		m_IsJumpShooting = false;
		m_IsRunShooting = false;
	}
	if (m_IsMoving == false)
	{
		m_Velocity.y -= 10.0f;
	}
}

void Player::Draw() const
{
	Vector2f offset{ m_CollisonBox.width - m_pCurrentSprite->GetWidth() * m_Scale, m_CollisonBox.height - m_pCurrentSprite->GetHeight() * m_Scale };

	glPushMatrix();
	glTranslatef(m_CollisonBox.left + offset.x / 2, m_CollisonBox.bottom, 0);
	glScalef(m_Scale, m_Scale, 1);
	if (m_Pmovement == PrimaryMovement::left)
	{
		m_pCurrentSprite->Draw(true);
	}
	else if (m_Pmovement == PrimaryMovement::right)
	{
		m_pCurrentSprite->Draw(false);
	}
	glPopMatrix();
//	DrawDebugHelp();

	for (size_t i = 0; i < m_Bullets.size(); i++)
	{
		m_Bullets[i].Draw();
	}
}

void Player::DrawDebugHelp() const
{
	Point2f actorBottomPos{ GetShape().left + GetShape().width / 2, GetShape().bottom };
	Point2f actorTopPos{ GetShape().left + GetShape().width / 2, GetShape().bottom + GetShape().height };

	Point2f actorLeftPos{ GetShape().left , GetShape().bottom + GetShape().height / 2 };
	Point2f actorRightPos{ GetShape().left + GetShape().width , GetShape().bottom + GetShape().height / 2 };

	utils::SetColor({ 1,0,0,1 });
	utils::DrawLine(actorBottomPos, actorTopPos);
	utils::DrawLine(actorLeftPos, actorRightPos);
	utils::DrawRect(GetShape());

	//std::cout << int(m_Pmovement) << " primary " << int(m_Smovement) << " secondary" << std::endl;
	std::cout << GetShape().left << " x " << GetShape().bottom << " y" << GetShape().width << " " << GetShape().height << " " << std::endl;
}

void Player::DrawHud() const
{
	m_PlayerHud.Draw();
}

void Player::HandleMoveKeysState(float elapsedSec)
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	m_Velocity.x = 0.0f;

	if (m_IsMoving == true && m_Smovement != SecondaryMovement::death)
	{
		if (m_IsMeleeOn == false)
		{
			if (pStates[SDL_SCANCODE_RIGHT] || pStates[SDL_SCANCODE_D] )
			{
				m_Velocity.x += (m_HorSpeed + m_PlayerManager.GetSpeed());
				m_Pmovement = PrimaryMovement::right;
				if (m_IsRunShooting)
				{
					m_Smovement = SecondaryMovement::runShoot;
				}
				else
				{
					m_Smovement = SecondaryMovement::run;
				}
				
				m_IsMeleeOn = false;
			}
			if (pStates[SDL_SCANCODE_LEFT] || pStates[SDL_SCANCODE_A])
			{
				m_Velocity.x -= (m_HorSpeed + m_PlayerManager.GetSpeed());
				m_Pmovement = PrimaryMovement::left;
				if (m_IsRunShooting)
				{
					m_Smovement = SecondaryMovement::runShoot;
				}
				else
				{
					m_Smovement = SecondaryMovement::run;
				}
				m_IsMeleeOn = false;
			}
			if (pStates[SDL_SCANCODE_SPACE] && !m_IsJumping)
			{
				m_Velocity.y += m_JumpSpeed;
		
				if (m_IsJumpShooting)
				{
					m_Smovement = SecondaryMovement::jumpShoot;
				}
				else
				{
					m_Smovement = SecondaryMovement::jump;
				}
				m_IsJumping = true;
				m_IsMeleeOn = false;
			}
			if (m_IsJumping == true)
			{
				if (m_IsJumpShooting)
				{
					m_Smovement = SecondaryMovement::jumpShoot;
				}
				else
				{
					m_Smovement = SecondaryMovement::jump;
				}
				m_IsMeleeOn = false;
			}
			m_Velocity.y += m_Acceleration.y;
		}
		if (m_IsMeleeOn == true)
		{
			m_Smovement = SecondaryMovement::melee;
			if (m_Melee.HasEnded())
			{
				m_Melee.Unlock();
				m_IsMeleeOn = false;
			}
		}
	}

}

void Player::MouseMoved(const Point2f & mousePos)
{
	m_MousePos = mousePos;
}

void Player::MouseClick(const SDL_MouseButtonEvent & e) 
{
	if (e.button == SDL_BUTTON_LEFT)
	{
		SoundManager::PlaySoundEffect("Shooting", false, false);
		if (!(m_Smovement == SecondaryMovement::death))
		{
		m_ShootTimer = 0.0f;
			if (m_Pmovement == PrimaryMovement::left)
			{
				m_BulletPos = { m_CollisonBox.left - 40 , m_CollisonBox.bottom + m_CollisonBox.height / 3 };
				if (m_MousePos.x >= 640)
				{
					m_Pmovement = PrimaryMovement::right;
				}
			}
			if (m_Pmovement == PrimaryMovement::right)
			{
				m_BulletPos = { m_CollisonBox.left + m_CollisonBox.width, m_CollisonBox.bottom + m_CollisonBox.height / 3 };
				if (m_MousePos.x <= 640)
				{
					m_Pmovement = PrimaryMovement::left;
				}
			}

			// Animation activation based on current states
			if (m_IsJumping == false)
			{
				m_IsRunShooting = true;
				if (m_Velocity.x == 0)
				{
					m_IsIdleShooting = true;
				}
			}
			else
			{
				m_IsJumpShooting = true;
			}


		//creates a bullet
		Vector2f direction = m_MousePos + m_Camera.GetPosition() - m_BulletPos;
		direction = direction.Normalized();

		if (m_Bullets.size() >= 20)
		{
			for (int i = 0; i < 19; i++)
			{
				m_Bullets.pop_front();
			}
		}
		else
		{
			m_Bullets.push_back(Bullet(m_BulletPos, direction));
		}
			m_IsMeleeOn = false;
		}
	}

	if (e.button == SDL_BUTTON_RIGHT && !m_IsJumping && !(m_Smovement == SecondaryMovement::death))
	{
		m_Velocity.x = 0.0f;
		m_IsMeleeOn = true;
	}
}

 PlayerManager & Player::GetPlayerManager() 
{
	return m_PlayerManager;
}

bool Player::SetMovement(bool isMoving)
{
	m_IsMoving = isMoving;
	return m_IsMoving;
}

void Player::SetPosition(const Point2f& playerPos)
{
	m_CollisonBox.left = playerPos.x;
	m_CollisonBox.bottom = playerPos.y;
}

Rectf Player::GetShape() const
{
	return m_CollisonBox;
}

void Player::AddPoints(const int& type)
{
	int typePoint = type;
	// coins
	if (typePoint == 1)
	{
		m_PlayerManager.AddPoints(100);
	}
	// easy enemy
	if (typePoint == 2)
	{
		m_PlayerManager.AddPoints(250);
	}
	
}

void Player::AddHealth(const int & type)
{
	int healtCount{};
	int typePoint = type;
	// easy enemy
	if (typePoint == 1)
	{
		m_PlayerManager.AddHealth(-1);
	}
	// complete death
	else if (typePoint == 2)
	{
		m_PlayerManager.AddHealth(-m_PlayerManager.GetHealth());
	}
	// complete reset
	else if (typePoint == 3)
	{
		m_PlayerManager.SetHealth(27);
	}
}

void Player::SetSecondaryMovement(SecondaryMovement sMovement)
{
	m_Smovement = sMovement;
}

void Player::SetLevelBeginPos(const Point2f& pos)
{
	m_BeginPosition = pos;
}

Point2f Player::GetPosition() const
{
	return Point2f(m_CollisonBox.left, m_CollisonBox.bottom);
}

Vector2f Player::GetVelocity() const
{
	return m_Velocity;
}

void Player::SetVelocity(const Vector2f & velocity)
{
	m_Velocity.x += velocity.x;
	m_Velocity.y += velocity.y;
}

Rectf Player::GetBulletPosition()
{
	Rectf CurrentBulletPos;
	for (int i = 0; i < m_Bullets.size(); i++)
	{
		CurrentBulletPos = m_Bullets[i].GetBulletLocation();
	}
	return CurrentBulletPos;
}
