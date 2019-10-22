#include "stdafx.h"
#include "LevelTwo.h"


LevelTwo::LevelTwo(LevelManager & levelmanager, std::shared_ptr<Player> player)
	:LevelBase{levelmanager,"Resources/Sprites/LevelTwo/LevelTwo.svg"}
	, m_pPlayer{ player }
	, m_Shop{{3435,185},0.95f,player,player->GetPlayerManager()}
	, m_Flag({1300,210})
	, m_Lever{{100,140},0.0f,1.25f}
{
	Initialize(); // initializes everything

	m_NextLevelTrigger = Rectf{75,630,120,150 };
}

void LevelTwo::DrawFront() const
{
	m_pLevelTwoTextureFront->Draw({ 0,0 }); // draws front texture
	m_Flag.Draw(); // draws the check point flag
	

	//draws all the coins
	for (int i = 0; i < m_pCoins.size(); i++)
	{
		m_pCoins[i]->Draw();
	}
	//draws all the enemies
	for (int i = 0; i < m_Enemies.size(); i++)
	{
		m_Enemies[i].Draw();
	}
	//draws all the jumppads
	for (int i = 0; i < m_JumpPads.size(); i++)
	{
		m_JumpPads[i].Draw();
	}	
}

void LevelTwo::DrawBack() const
{
	m_pLevelTwoTextureBack->Draw({ 0,0 }); // draws the back texture
	m_Shop.Draw();//draws the shop 
	m_Lever.Draw();//draws the levers
	//draws the traps
	for (int i = 0; i < m_CircleSawTraps.size(); i++)
	{
		m_CircleSawTraps[i].Draw();
	}
	//draws the laser
	if (m_IsLaserOn)
	{
		m_pLaserTexture->Draw({ 322,560 }, { m_pLaserTexture->GetWidth() / 2,0,m_pLaserTexture->GetWidth() / 2 ,m_pLaserTexture->GetHeight() });
	}
	else
	{
		m_pLaserTexture->Draw({ 322,560 }, { 0,0,m_pLaserTexture->GetWidth() / 2,m_pLaserTexture->GetHeight() });
	}
}

void LevelTwo::DrawLocal() const
{
	m_Shop.DrawLocal(); // draws the shop menu screen

	utils::SetColor({ 0.0f,0.0f,0.0f,m_FadingOpacity });
	utils::FillRect({ 0,0,1280,720 });
}

void LevelTwo::Update(float elapsedSec)
{
	m_pPlayer->SetMovement(true); //unfreezes player
	m_pPlayer->GetPlayerManager().SetLevel(2); // sets level count to two

	//player pos
	m_Pos.x = m_pPlayer->GetShape().left;
	m_Pos.y = m_pPlayer->GetShape().bottom;

	
	m_Shop.Update(elapsedSec);//updates the shop anim
	m_Flag.Update(elapsedSec);//updates the flag anim

	//deals enemy damage & updates the bullets
	for (int i = 0; i < m_Enemies.size(); i++)
	{
		m_Enemies[i].Update(elapsedSec);
		m_Enemies[i].BulletCollision(m_pPlayer->GetBulletPosition(), m_Enemies[i].GetPosition());
		// enemy damage collision
		if (m_Enemies[i].IsEnemyDead() == false)
		{
			if (utils::IsOverlapping(m_pPlayer->GetShape(), m_Enemies[i].GetPosition())
				|| m_Enemies[i].PlayerCollisionBullet(m_pPlayer->GetShape()))
			{
				m_TimerOverlapEnemyEasy += elapsedSec;
				if (m_TimerOverlapEnemyEasy <= 0.02f)
				{
					m_pPlayer->AddHealth(1);
				}
				if (m_TimerOverlapEnemyEasy >= 0.5f)
				{
					m_TimerOverlapEnemyEasy = 0.0f;
				}
			}
		}

		// deleting enemies
		if (m_Enemies[i].IsEnemyDestroyed())
		{
			m_pPlayer->AddPoints(2);
			std::swap(m_Enemies[i], m_Enemies.back());
			m_Enemies.pop_back();
		}


	}
	//updates the coin anim
	for (int i = 0; i < m_pCoins.size(); i++)
	{
		m_pCoins[i]->Update(elapsedSec);
	}
	//updates the trap rotations
	for (int i = 0; i < m_CircleSawTraps.size(); i++)
	{
		m_CircleSawTraps[i].Update(elapsedSec, m_pPlayer->GetPosition());
	}

	//checks if laser is on or not
	if (m_Lever.GetLeverState() == true)
	{
		m_IsLaserOn = true;
	}

	if (utils::IsOverlapping(m_pPlayer->GetShape(),m_NextLevelTrigger))
	{
		m_pPlayer->SetMovement(false);
		m_FadingOpacity += elapsedSec;
	}

	if (m_FadingOpacity >= 2.0f)
	{
		m_pPlayer->SetMovement(true);
		m_LevelManager.SetCurrentLevel(LevelManager::Level::levelThree);
	}

}

void LevelTwo::MouseMoved(const Point2f & mousePos)
{
	m_Shop.MouseMoved(mousePos); // deals mouse movements
}

void LevelTwo::MouseClick(const SDL_MouseButtonEvent & e)
{
	m_Shop.MouseClick(e); // deals mouse clicks on menu
}

void LevelTwo::ProcessKeyDownEvent(const SDL_KeyboardEvent & e)
{
	LevelBase::ProcessKeyDownEvent(e); // deals if player hits the "E" button to open shop
	m_Shop.ProcessKeyDownEvent(e);
}

void LevelTwo::HandleCollision(Rectf & Shape, Vector2f & actorVelocity)
{
	//handles the collision for your level
	LevelBase::HandleCollision(Shape, actorVelocity);
	
	//handles collision if you pick up a coin ( + plays sound ) 
	for (size_t i = 0; i < m_pCoins.size(); i++)
	{
		if (m_pCoins[i]->IsOverlapping(Shape))
		{
			m_pCoins[i]->PlayCoinSound();
			m_pPlayer->AddPoints(1);
			m_pCoins.erase(m_pCoins.begin() + i);
		}
	}

	//handles the jump collision for the player
	for (int i = 0; i < m_JumpPads.size(); i++)
	{
		if (m_JumpPads[i].CollisionJumpPad(Shape))
		{
			m_JumpPads[i].SetIsJumping(true);
			actorVelocity.y = 700;
		}
		if (actorVelocity.y <= 0 && m_JumpPads[i].GetIsJumping())
		{
			m_JumpPads[i].SetIsJumping(false);
		}
	}

	//handles death collision for player
	for (int i = 0; i < m_CircleSawTraps.size(); i++)
	{
		if (m_CircleSawTraps[i].CircleCollision(m_pPlayer->GetShape()))
		{
			m_pPlayer->SetMovement(false);
			m_pPlayer->SetSecondaryMovement(Player::SecondaryMovement::death);
		}
	}
	for (int i = 0; i < m_DeathRects.size(); i++)
	{
		if (utils::IsOverlapping(Shape,m_DeathRects[i]))
		{
			m_pPlayer->SetMovement(false);
			m_pPlayer->SetSecondaryMovement(Player::SecondaryMovement::death);
		}
	}

	//sets flag // checkpoint on true
	if (m_Flag.CollisionFlag(Shape))
	{
		m_pPlayer->SetLevelBeginPos({1300,210});
		while (!m_HasReachedCheckPoint)
		{
			m_pPlayer->GetPlayerManager().AddPoints(1000);
			m_HasReachedCheckPoint = true;
		}
	}


	//checks if player health reaches  0, if so .. player dies
	if (m_pPlayer->GetPlayerManager().GetHealth() <= 0)
	{
		m_pPlayer->SetMovement(false);
		m_pPlayer->SetSecondaryMovement(Player::SecondaryMovement::death);
	}

	//checks to see if laser is off to disable the dead zone
	if (m_IsInteracting && !m_IsLaserOn)
	{
			if (m_Lever.Collision(Shape))
			{
				m_Lever.SetLeverPull(true);
				m_IsInteracting = false;
				for (int i = 0; i < 2; i++)
				{
					m_DeathRects.pop_back();
				}
				
			}
		}
}


Rectf LevelTwo::GetBoundaries() const
{
	return m_Boundaries; // returns the second level boundary
}

void LevelTwo::PlayMusic()
{
	SoundManager::PlaySoundStream("LevelTwo", true);
}

void LevelTwo::Initialize()
{
	//inits the laser // level textures
	m_pLaserTexture = (std::make_shared<Texture>("Resources/Sprites/LevelTwo/Laser.png"));
	m_pLevelTwoTextureFront = (std::make_shared<Texture>("Resources/Sprites/LevelTwo/LevelTwoFront.png"));
	m_pLevelTwoTextureBack = (std::make_shared<Texture>("Resources/Sprites/LevelTwo/LevelTwoBack.png"));
	//inits the level boundaries && begin pos for your player
	m_Boundaries = { 0,0,m_pLevelTwoTextureFront->GetWidth(),m_pLevelTwoTextureFront->GetHeight() };
	m_BeginPos = Point2f{ 3600,200 };// 3600 200

	m_Enemies.push_back(EnemyEasy(Point2f{ 2650,500 }, Point2f{ 3380,500 }, std::string("FlyingEasy"), { 10 ,100 }, 3.0f, 1.0f));
	m_Enemies.push_back(EnemyEasy(Point2f{ 2140,35 }, Point2f{ 2430,35 }, std::string("SlimyEasy"), { 10 ,100 }, 3.0f, 1.0f));
	m_Enemies.push_back(EnemyEasy(Point2f{ 400,500 }, Point2f{ 1100,500 }, std::string("FlyingEasy"), { 10 ,100 }, 3.0f, 1.0f));

	//first
	m_pCoins.push_back(std::make_unique<Coin>(Point2f(3240, 70)));
	m_pCoins.push_back(std::make_unique<Coin>(Point2f(3140, 70)));
	m_pCoins.push_back(std::make_unique<Coin>(Point2f(3040, 70)));
	m_pCoins.push_back(std::make_unique<Coin>(Point2f(2940, 70)));


	//second
	m_pCoins.push_back(std::make_unique<Coin>(Point2f(1600, 420)));
	m_pCoins.push_back(std::make_unique<Coin>(Point2f(1700, 420)));
	m_pCoins.push_back(std::make_unique<Coin>(Point2f(1800, 420)));
	m_pCoins.push_back(std::make_unique<Coin>(Point2f(1900, 420)));

	m_JumpPads.push_back(Point2f{ 2040,70 });
	m_JumpPads.push_back(Point2f{ 450,140 });


	m_CircleSawTraps.push_back(TrapCircleSaw({ 2970,-120 }, 0.35f));
	m_CircleSawTraps.push_back(TrapCircleSaw({ 2735,-40 }, 0.20f));
	m_CircleSawTraps.push_back(TrapCircleSaw({ 2440,-40 }, 0.20f));

	m_CircleSawTraps.push_back(TrapCircleSaw({ 1750,240 }, 0.20f));
	m_CircleSawTraps.push_back(TrapCircleSaw({ 1550,240 }, 0.20f));
	m_CircleSawTraps.push_back(TrapCircleSaw({ 1350,60 }, 0.5f));

	m_DeathRects.push_back({ 630,0,350,135 });
	m_DeathRects.push_back({ 350,625,40,300 });
	m_DeathRects.push_back({ 0,500,400,120 });
}
