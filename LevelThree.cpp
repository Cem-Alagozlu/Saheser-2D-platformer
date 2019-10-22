#include "stdafx.h"
#include "LevelThree.h"
#include "Game.h"
LevelThree::LevelThree(LevelManager & levelmanager, std::shared_ptr<Player> player)
	:LevelBase{ levelmanager,"Resources/Sprites/LevelThree/LevelThree.svg" }
	, m_pPlayer{ player }
	, m_IsScreenClear{false}
	, m_IsEventStarted{false}
	, m_IsArifKilled{false}
{
	//initialize textures 
	m_pFrontTexture01 = (std::make_unique<Texture>("Resources/Sprites/LevelThree/LevelThreeFront01.png"));
	m_pBackTexture01 = (std::make_unique<Texture>("Resources/Sprites/LevelThree/LevelThreeBack01.png"));
	m_pStoryTexture00 = (std::make_unique<Texture>("Resources/Sprites/LevelThree/StoryTelling00.png"));
	m_pStoryTexture01 = (std::make_unique<Texture>("Resources/Sprites/LevelThree/StoryTelling01.png"));
	m_pStoryTexture02 = (std::make_unique<Texture>("Resources/Sprites/LevelThree/StoryTelling02.png"));
	m_pMoon = (std::make_unique<Texture>("Resources/Sprites/LevelThree/Moon.png"));

	//create level boundaries + begin pos for player
	m_Boundaries = { 0,0,m_pFrontTexture01->GetWidth(),m_pFrontTexture01->GetHeight() };
	m_BeginPos = { 2400,200 }; // 2400 200

	

	// collision boxes for level
	m_CollisionBoxes.push_back(Rectf{ 1950,0,50,1400 });
	m_CollisionBoxes.push_back(Rectf{ 3920,0,50,1400 });
	m_CollisionBoxes.push_back(Rectf{ 7000,0,2000,25 });
	m_EventTriggerBox = { 3850,0,10,1400 };

	m_CamChange = (Point2f(-3500, -500));

	//set begin fase for enemy
	m_enemy.SetMovement(false);
	m_enemy.SetPosition({ 200,100 });
}

void LevelThree::DrawFront() const
{
	//draws front texture & the enemy ( daevas ) 
	m_pFrontTexture01->Draw({0,0});
	m_enemy.Draw();
}

void LevelThree::DrawBack() const
{
	// draws the rotating moon & back textures
	DrawMoon();
	m_pBackTexture01->Draw({ 0,0 });
}

void LevelThree::DrawLocal() const
{
	// intro/begin fader of level three
	if (m_IsScreenClear == false)
	{
		utils::SetColor({ 0,0,0,m_IntroFadeCounter });
		utils::FillRect({ 0,0,1280,720 });

		if (m_IntroFadeCounter >= 5.5f)
		{
			m_pStoryTexture00->Draw({ 0,0 });
		}
		else if (m_IntroFadeCounter <= 5.4f && m_IntroFadeCounter >= 1.5f)
		{
			m_pStoryTexture01->Draw({ 0,0 });
		}
	}

	// fader for fase 2
	if (m_IsArifKilled)
	{
		utils::SetColor({ 0,0,0,m_ArifKillCounter });
		utils::FillRect({ 0,0,1280,720 });
	}

	// checks counter is below 1 to contiue story
	if (m_ArifKillCounter <= -1.0f)
	{
		m_pStoryTexture02->Draw({ 0,0 });
		m_pPlayer->SetMovement(false);
	}

	//checks if next level is set to activate the fader
	if (m_IsNextLevel)
	{
		utils::SetColor({ 0.0f,0.0f,0.0f,m_FadingOpacity });
		utils::FillRect({ 0,0,1280,720 });
	}
}

void LevelThree::Update(float elapsedSec)
{
	// updates pos for player
	m_Pos.x = m_pPlayer->GetShape().left;
	m_Pos.y = m_pPlayer->GetShape().bottom;
	m_pPlayer->GetPlayerManager().SetLevel(3);
	
	// event updater (for arif & daevas)
	if (m_IsEventStarted)
	{
		if (m_IsArifKilled)
		{
			m_enemy.SetMovement(false);
			m_ArifKillCounter -= (elapsedSec);
		}
	}
	else
	{
		m_enemy.SetMovement(false);
	}

	m_enemy.Update(elapsedSec, m_LevelManager,m_pPlayer->GetShape());
	// rotates moon ( matrix )
	m_MoonRotator += elapsedSec;

	//fader screen
	if (m_IntroFadeCounter >= 0.0f)
	{
		m_IntroFadeCounter -= (elapsedSec);
	}
	
	if (m_IntroFadeCounter <= 0.0f)
	{
		m_IsScreenClear = true;
	}
	
	// camera change & follow up for arif
	if (m_IsEventStarted == true && m_CamChange.x <= 0 )
	{
		m_pPlayer->SetMovement(false);
		m_CamChange.x += 5;
		m_CamChange.y += 1;
		Game::m_Cam.x =m_CamChange.x;
		Game::m_Cam.y =m_CamChange.y;
	}
	
	// if arif gets killed  -> progress to next event 
	if (m_enemy.PlayerCollisionBullet(m_pPlayer->GetShape()))
	{
		m_pPlayer->SetLevelBeginPos({8200,30});
		m_IsArifKilled = true;
		m_pPlayer->SetSecondaryMovement(Player::SecondaryMovement::death);
	}

	//makes sure that your fader opacity kicks in
	if (m_IsNextLevel == true)
	{
		m_FadingOpacity += elapsedSec;
	}

	if (m_FadingOpacity >= 2.0f)
	{
		m_LevelManager.SetCurrentLevel(LevelManager::Level::LevelEnd);
	}
}



void LevelThree::MouseMoved(const Point2f & mousePos)
{
}

void LevelThree::MouseClick(const SDL_MouseButtonEvent & e)
{
	if (m_ArifKillCounter <= -5.0f && m_IsArifKilled)
	{
		m_IsNextLevel = true;
	}
}

void LevelThree::ProcessKeyDownEvent(const SDL_KeyboardEvent & e)
{
}


void LevelThree::HandleCollision(Rectf & Shape, Vector2f & actorVelocity)
{
	LevelBase::HandleCollision(Shape, actorVelocity);
	//collision for arif & daevas
	if (!m_IsEventStarted)
	{
		for (int i = 0; i < m_CollisionBoxes.size(); i++)
		{
			m_CollisionBoxes[i].HandleCollision(Shape, actorVelocity);
		}
	}

	//triggerbox for event (daevas killing arif) 
	if (utils::IsOverlapping(Shape, m_EventTriggerBox))
	{
		m_IsEventStarted = true;
	}
	
	//collision for final part
	m_CollisionBoxes[2].HandleCollision(Shape, actorVelocity);
}

Rectf LevelThree::GetBoundaries() const
{
	return m_Boundaries; // returns boundaries
}

void LevelThree::PlayMusic()
{
	SoundManager::PlaySoundStream("LevelThree00", true); // plays music
}

void LevelThree::DrawMoon() const
{
	//draws the spinning moon ( sfeer jwz ) 
	glPushMatrix();
	glTranslatef(0, -(m_pMoon->GetHeight() / 2), 0);
	glTranslatef(m_pMoon->GetWidth() / 2, m_pMoon->GetHeight() / 2, 0);
	glRotatef(m_MoonRotator, 0, 0, 1);
	glTranslatef(-m_pMoon->GetWidth() / 2, -m_pMoon->GetHeight() / 2, 0);
	m_pMoon->Draw({ 0, 0 });
	glPopMatrix();
}

