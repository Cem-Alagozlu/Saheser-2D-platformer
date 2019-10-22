#include "stdafx.h"
#include "LevelOne.h"

LevelOne::LevelOne(LevelManager& levelmanager, std::shared_ptr<Player> player)
	:LevelBase{ levelmanager,"Resources/Sprites/LevelOne/LevelOne.svg" }
	, m_pPlayer{ player }
	, m_LevelOneTextureFront{"Resources/Sprites/LevelOne/LevelOneFront.png"}
	, m_LevelOneTextureBack{"Resources/Sprites/LevelOne/LevelOneBack.png"}
	, m_HiddenTextureFront{"Resources/Sprites/LevelOne/hidden.png"}
	, m_HiddenTextureBack{"Resources/Sprites/LevelOne/hidden-back.png"}
	, m_HiddenTextureHiding{"Resources/Sprites/LevelOne/HiddenFont02.png"}
	, m_Hatch{{3568,910},{3775,1100},{3700,1050}}
	, m_CircleSaw{{ 3200,480 },0.35f}
	, m_DoorSwitch{ {3625,135},{2100,135} }
{
	Initialize();
	
}

void LevelOne::DrawFront() const
{
	// Textures that will be drawn if player didn't reach second base
	if (m_IsHidden)
	{
		for (int i = 0; i < m_MovingPlatforms.size(); i++)
		{
			m_MovingPlatforms[i].Draw();
		}
		m_Hatch.DrawFront();
	    m_LevelOneTextureBack.Draw(Rectf(0, 0, m_LevelOneTextureBack.GetWidth(), m_LevelOneTextureBack.GetHeight()));
	}
	// Textures that will be drawn if player reached the second base
	else
	{
		m_CircleSaw.Draw();
		m_HiddenTextureFront.Draw(Rectf(0, 0, m_HiddenTextureFront.GetWidth(), m_HiddenTextureFront.GetHeight()));
	}

	// draws all coins
	for (int i = 0; i < m_pCoins.size(); i++)
	{
		m_pCoins[i]->Draw();
	}
	// draws all enemies
	for (int i = 0; i < m_Enemies.size(); i++)
	{
		m_Enemies[i].Draw();
	}

	// draws second layer 
	if (m_IsHidden)
	{
		m_HiddenTextureHiding.Draw(Rectf(0, 0, m_HiddenTextureHiding.GetWidth(), m_HiddenTextureHiding.GetHeight()));
	}
}

void LevelOne::DrawLocal() const
{
	//draws fade in if next level
	if (m_IsNextLevel)
	{
		utils::SetColor({ 0.0f,0.0f,0.0f,m_FadingOpacity });
		utils::FillRect({ 0,0,1280,720 });
	}
}

void LevelOne::DrawBack() const
{
	// parallax images 
	for (int i = 0; i < m_pParallax.size(); i++)
	{
		m_pParallax[i]->Draw({ -1000 + m_pPlayer->GetShape().left / (20- (i + 2)),0,m_pParallax[0]->GetWidth(),m_pParallax[0]->GetHeight() });
	}

	// draws hatches and the background texture of level one (main one, for the back) 
	m_Hatch.DrawBack();
	m_LevelOneTextureFront.Draw(Rectf(0, 0, m_LevelOneTextureFront.GetWidth(), m_LevelOneTextureFront.GetHeight()));

	// draws levers
	for (int i = 0; i < m_Levers.size(); i++)
	{
		m_Levers[i].Draw();
	}

	// draws textures if player reached second base
	if (m_IsHidden == false)
	{
		m_HiddenTextureBack.Draw(Rectf(0, 0, m_HiddenTextureBack.GetWidth(), m_HiddenTextureBack.GetHeight()));
		m_DoorSwitch.Draw();
	}
}

void LevelOne::Update(float elapsedSec)
{
	//player pos
	m_Pos.x = m_pPlayer->GetShape().left;
	m_Pos.y = m_pPlayer->GetShape().bottom;

	// checks lever state to activate platforms
	for (int i = 0; i < m_Levers.size(); i++)
	{
			if (m_Levers[i].GetLeverState() == true)
			{
				m_MovingPlatforms[i].Update(elapsedSec);
			}
	}

	// updates coin animation
	for (int i = 0; i < m_pCoins.size(); i++)
	{
		m_pCoins[i]->Update(elapsedSec);
	}

	// updates animation
	m_CircleSaw.Update(elapsedSec, m_pPlayer->GetPosition());
	m_Hatch.Update(elapsedSec);

	// updates enemy animation && movement
	for (int i = 0; i < m_Enemies.size(); i++)
	{
		m_Enemies[i].Update(elapsedSec);
	}
	
	// updates player spawn point after base has been reached
	if (m_IsHidden == false)
	{
		m_pPlayer->SetLevelBeginPos({ 3658, 670 });
	}

	for (int i = 0; i < m_Enemies.size(); i++)
	{
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

	// sets to level 2 if opacity > 2 && if door is open
	if (m_DoorSwitch.GetDoorOpenState() && m_DoorSwitch.CollisionDoor(m_pPlayer->GetShape()))
	{
		if (m_FadingOpacity >= 2.0f)
		{
			m_LevelManager.SetCurrentLevel(LevelManager::Level::levelTwo);
		}
		
	}

	//checks if next level is set.. (to freeze player)
	//fade in will start
	if (m_IsNextLevel == true)
	{
		m_pPlayer->SetMovement(false);
		m_FadingOpacity += elapsedSec;
	}
}

void LevelOne::PlayMusic()
{
	SoundManager::PlaySoundStream("LevelOne", true); // plays level one song
}

void LevelOne::MouseMoved(const Point2f& mousePos)
{
}

void LevelOne::MouseClick(const SDL_MouseButtonEvent& e)
{
}

void LevelOne::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity)
{
	LevelBase::HandleCollision(actorShape, actorVelocity);
	// death collisions
	for (int i = 0; i < m_DeathRects.size(); i++)
	{
		if (utils::IsOverlapping(m_DeathRects[i], m_pPlayer->GetShape())
			|| m_CircleSaw.CircleCollision(m_pPlayer->GetShape())
			|| m_pPlayer->GetPlayerManager().GetHealth() <= 0)
		{
			m_pPlayer->SetMovement(false);
			m_pPlayer->SetSecondaryMovement(Player::SecondaryMovement::death);
		}
	}

	// platform collisionsq
	for (int i = 0; i < m_MovingPlatforms.size(); i++)
	{
		m_MovingPlatforms[i].HandleCollision(actorShape, actorVelocity);

		if (m_MovingPlatforms[i].PlatformCollision(actorShape))
		{
			m_MovingPlatforms[i].PlatformPlayerChange(actorShape);
		}
	}

	// empty collisions 
	for (int i = 1; i < m_CollisionBoxes.size(); i++)
	{
		m_CollisionBoxes[i].HandleCollision(actorShape, actorVelocity);
	}

	// collision for hatch ( second base ) 
	if (!m_Hatch.IsHatchedOpen())
	{
		m_CollisionBoxes[0].HandleCollision(actorShape, actorVelocity);
	}

	// collision for interaction between objects
	if (m_IsInteracting)
	{
		for (int i = 0; i < m_Levers.size(); i++)
		{
			if (m_Levers[i].Collision(actorShape))
			{
				m_Levers[i].SetLeverPull(true);
				m_IsInteracting = false;
			}
		}
		if (m_DoorSwitch.CollisionSwitch(actorShape))
		{
			m_DoorSwitch.SetSwitchActivated(true);
			m_IsInteracting = false;
		}
		if (m_DoorSwitch.CollisionDoor(actorShape) && m_DoorSwitch.GetSwitchState() == true)
		{
			m_DoorSwitch.SetDoorOpen(true);
			m_IsNextLevel = true;
			m_IsInteracting = false;
		}
	}

	// collision for coins
	for (size_t i = 0; i < m_pCoins.size(); i++)
	{
		if (m_pCoins[i]->IsOverlapping(actorShape))
		{
			m_pCoins[i]->PlayCoinSound();
			m_pPlayer->AddPoints(1);
			m_pCoins.erase(m_pCoins.begin() + i);
		}
	}
	
	// collision for second base hatch
	if (utils::IsOverlapping(m_HiddenRect,actorShape))
	{
		m_IsHidden = false;
	}

	// collision between bullet & hatch meter
	m_Hatch.BulletCollision(m_pPlayer->GetBulletPosition(), m_Hatch.GetButtonRect());

	
}

Rectf LevelOne::GetBoundaries() const
{
	return m_Boundaries; // return level boundaries
}

void LevelOne::Initialize()
{
	//sets boundaries for cam
	m_Boundaries = { 0,0,m_LevelOneTextureFront.GetWidth(),m_LevelOneTextureFront.GetHeight() };
	m_BeginPos = Point2f{ 100,100 }; // begin pos of player

	//initializes the parallax img's
	for (int idx = 0; idx < 3; ++idx)
	{
		std::stringstream str;
		str << "Resources/Sprites/LevelOne/Parallax0" << idx << ".png";
		m_pParallax.push_back(std::make_unique<Texture>(str.str()));
	}

		

	//places the levers // platforms// invisible collision boxes
	m_Levers.push_back(Lever{ { 1250,280 }, 0, 1.0f });
	m_Levers.push_back(Lever{ { 2200,489 }, 0, 1.0f });
	m_MovingPlatforms.push_back(PlatformMoving({ 1700,70 }, "Resources/Sprites/Platform/platform01.png", { 1700,570 }, 0.0f, 1.0f, 1, "Resources/Sprites/Platform/platform01.svg"));
	m_MovingPlatforms.push_back(PlatformMoving({ 2425,490 }, "Resources/Sprites/Platform/platform01.png", { 2425,880 }, 0.0f, 1.0f, 1, "Resources/Sprites/Platform/platform01.svg"));
	m_CollisionBoxes.push_back(EmptyCollision({ 3550,907,250,70}));
	m_CollisionBoxes.push_back(EmptyCollision({ 10,500,450,10  }));
	m_CollisionBoxes.push_back(EmptyCollision({ 950,610,400,10 }));
	m_CollisionBoxes.push_back(EmptyCollision({ 1935,1060,345,10 }));

	//places the coins
	m_pCoins.push_back(std::make_unique<Coin>(Point2f(0,490)));
	m_pCoins.push_back(std::make_unique<Coin>(Point2f(120, 490)));
	m_pCoins.push_back(std::make_unique<Coin>(Point2f(240, 490)));
	m_pCoins.push_back(std::make_unique<Coin>(Point2f(360, 490)));

	m_pCoins.push_back(std::make_unique<Coin>(Point2f(960, 620)));
	m_pCoins.push_back(std::make_unique<Coin>(Point2f(1080, 620)));
	m_pCoins.push_back(std::make_unique<Coin>(Point2f(1200, 620)));
	
	m_pCoins.push_back(std::make_unique<Coin>(Point2f(1910, 1070)));
	m_pCoins.push_back(std::make_unique<Coin>(Point2f(2030, 1070)));
	m_pCoins.push_back(std::make_unique<Coin>(Point2f(2150, 1070)));

	// DEEL TWO
	m_pCoins.push_back(std::make_unique<Coin>(Point2f(2710, 570)));
	m_pCoins.push_back(std::make_unique<Coin>(Point2f(2830, 570)));

	m_pCoins.push_back(std::make_unique<Coin>(Point2f(3160, 640)));

	m_pCoins.push_back(std::make_unique<Coin>(Point2f(3110, 100)));
	m_pCoins.push_back(std::make_unique<Coin>(Point2f(3230, 100)));
	m_pCoins.push_back(std::make_unique<Coin>(Point2f(3350, 100)));
	
	//deadzones for player
	m_DeathRects.push_back({840,0,140,80});
	m_DeathRects.push_back({ 2435,0,140,120 });
	m_DeathRects.push_back({ 3110,0,400,120 });

	m_HiddenRect = { 3570,920,200,30 };

	//creates the enemies
	m_Enemies.push_back(EnemyEasy(Point2f{ 2670,945 }, Point2f{ 3360,945 }, std::string("SlimyEasy"), { 10,100 }, 10.0f,0.5f));
	m_Enemies.push_back(EnemyEasy(Point2f{ 2170,100 }, Point2f{ 2370,100 }, std::string("SlimyEasy"), { 10,100 }, 5.0f, 0.5f));
	m_Enemies.push_back(EnemyEasy(Point2f{ 2580,100 }, Point2f{ 2900,100 }, std::string("SlimyEasy"), { 10,100 }, 5.0f, 0.5f));

}
