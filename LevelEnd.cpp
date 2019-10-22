#include "stdafx.h"
#include "LevelEnd.h"
#include "Player.h"

LevelEnd::LevelEnd(LevelManager & levelmanager, std::shared_ptr<Player> player)
	:LevelBase{ levelmanager,"Resources/Sprites/LevelEnd/LevelEnd.svg" }
	, m_pPlayer{ player }
	, m_IsReversed{false}
	, m_FadingOpacity{ 0 }
	, m_Shop{{100,65},1.15f,player,player->GetPlayerManager() }

{
	Initialize();
}

void LevelEnd::DrawFront() const
{
	//draw font texture
	m_pFrontTexture01->Draw({ 0,0 });

	//draw traps
	for (int i = 0; i < m_SpikeFalls.size(); i++)
	{
		m_SpikeFalls[i].Draw();
	}
	for (int i = 0; i < m_SwingBlades.size(); i++)
	{
		m_SwingBlades[i].Draw();
	}

	//draw Daevas
	m_Daevas.Draw();
}

void LevelEnd::DrawBack() const
{
	// parallax images 
	for (int i = 0; i < m_pParallax.size(); i++)
	{
		m_pParallax[i]->Draw({ -1000 + m_pPlayer->GetShape().left / (20 - (i + 2)),0,m_pParallax[0]->GetWidth(),m_pParallax[0]->GetHeight() });
	}
	//draws shop & background texture
	m_pBackTexture01->Draw({ 0,0 });
	m_Shop.Draw();

	//draw cirlesaws
	for (int i = 0; i < m_CircleSaws.size(); i++)
	{
		m_CircleSaws[i].Draw();
	}
}

void LevelEnd::DrawLocal() const
{
	m_Shop.DrawLocal();// draws the menu on local view space

	//checks if enemy is dead
	// if yes.. black fade in will appear on local view space
	if (m_Daevas.GetAliveState() == true)
	{
		utils::SetColor({ 0.0f,0.0f,0.0f,m_FadingOpacity });
		utils::FillRect({ 0,0,1280,720 });
	}
}

void LevelEnd::Update(float elapsedSec)
{
	//player pos
	m_Pos.x = m_pPlayer->GetShape().left;
	m_Pos.y = m_pPlayer->GetShape().bottom;
	m_pPlayer->GetPlayerManager().SetLevel(4);

	//update shop & traps
	m_Shop.Update(elapsedSec);
	UpdateTraps(elapsedSec);

	//update enemy Daevas
	m_Daevas.Update(elapsedSec, m_LevelManager, m_pPlayer->GetShape());
	
	//updates & delays bullet fire speed
	if (m_Daevas.PlayerCollisionBullet(m_pPlayer->GetShape()))
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

	//checks if enemy is dead.. if so -> start fading
	if (m_Daevas.GetAliveState() == true)
	{
		m_FadingOpacity += elapsedSec;
	}

	if (m_Daevas.GetAliveState() == true && m_FadingOpacity >= 2.0f)
	{
		m_LevelManager.SetCurrentLevel(LevelManager::Level::levelBoss);
	}
}

void LevelEnd::MouseMoved(const Point2f & mousePos)
{
	//mouse pos
	m_Shop.MouseMoved(mousePos);
}

void LevelEnd::MouseClick(const SDL_MouseButtonEvent & e)
{
	//clicks for mouse buttons
	m_Shop.MouseClick(e);
}

void LevelEnd::ProcessKeyDownEvent(const SDL_KeyboardEvent & e)
{
	//function for shop
	LevelBase::ProcessKeyDownEvent(e);
	m_Shop.ProcessKeyDownEvent(e);
}

void LevelEnd::HandleCollision(Rectf & Shape, Vector2f & actorVelocity)
{
	LevelBase::HandleCollision(Shape, actorVelocity); // handles collision for current level
	PlayerDeathCollision(); // handles death collision for player
	m_Daevas.BulletCollision(m_pPlayer->GetBulletPosition());//gets bullet pos
}

Rectf LevelEnd::GetBoundaries() const
{
	//returns the level boundaries
	return m_Boundaries;
}

void LevelEnd::PlayMusic()
{
	//plays current level song
	SoundManager::PlaySoundStream("LevelEnd", true);
}

void LevelEnd::Initialize()
{
	m_Daevas.SetPosition({ 5400,60 }); // spawn point Daevas

	//initialize background && foreground texture
	m_pFrontTexture01 = (std::make_unique<Texture>("Resources/Sprites/LevelEnd/LevelEndFront.png"));
	m_pBackTexture01 = (std::make_unique<Texture>("Resources/Sprites/LevelEnd/LevelEndBack.png"));

	//sets the level boundaries
	m_Boundaries = { 0,0,m_pFrontTexture01->GetWidth(),m_pFrontTexture01->GetHeight() };
	
	//begin pos of Arif
	m_BeginPos = Point2f{ 50,70 };// 3600 200

	//parallax for the background
	for (int idx = 0; idx < 3; ++idx)
	{
		std::stringstream str;
		str << "Resources/Sprites/LevelEnd/Parallax/Parallax0" << idx << ".png";
		m_pParallax.push_back(std::make_unique<Texture>(str.str()));
	}

	//initialize traps (spikes && saws && blades) 
	m_SpikeFalls.push_back(TrapSpikeFall({ 927,400 }, 0.0f, 1.0f, 10.0f, false));
	m_SpikeFalls.push_back(TrapSpikeFall({ 1500,400 }, 0.0f, 1.0f, 5.5f, false));
	m_SpikeFalls.push_back(TrapSpikeFall({ 2420,-20 }, 0.0f, 1.0f, 10.0f, true));
	m_SpikeFalls.push_back(TrapSpikeFall({ 2920,-20 }, 0.0f, 1.0f, 20.0f, true));
	m_CircleSaws.push_back(TrapCircleSaw({ 1145,-130 }, 0.45f));
	m_CircleSaws.push_back(TrapCircleSaw({ 4600, 425 }, 0.45f));
	m_SwingBlades.push_back(TrapSwingBlade({ 2350,-15 }, 0, 0.50f, 360));
	m_SwingBlades.push_back(TrapSwingBlade({ 3450,-15 }, 0, 0.50f, 360));
	m_SwingBlades.push_back(TrapSwingBlade({ 3800,1000 }, 0, 0.8f, 140));
	m_DeathReact = Rectf(2000, 0, 1700, 50); // death-zone
}

void LevelEnd::PlayerDied()
{
	//sets player to dead
	m_pPlayer->SetSecondaryMovement(Player::SecondaryMovement::death);
}

void LevelEnd::PlayerDeathCollision()
{
	// checks if player has been hit by trap
	for (int i = 0; i < m_SpikeFalls.size(); i++)
	{
		if (m_SpikeFalls[i].SpikeCollision(m_pPlayer->GetShape()))
		{
			PlayerDied();
		}
	}
	for (int i = 0; i < m_CircleSaws.size(); i++)
	{
		if (m_CircleSaws[i].CircleCollision(m_pPlayer->GetShape()))
		{
			PlayerDied();
		}
	}
	for (int i = 0; i < m_SwingBlades.size(); i++)
	{
		if (m_SwingBlades[i].BladeCollision(m_pPlayer->GetShape()))
		{
			PlayerDied();
		}
	}

	//checks if player is inside the deathzone
	if (utils::IsOverlapping(m_pPlayer->GetShape(), m_DeathReact))
	{
		PlayerDied();
	}
}

void LevelEnd::UpdateTraps(float elapsedSec)
{
	for (int i = 0; i < m_SpikeFalls.size(); i++)
	{
		m_SpikeFalls[i].Update(elapsedSec, m_pPlayer->GetPosition());
	}
	for (int i = 0; i < m_CircleSaws.size(); i++)
	{
		m_CircleSaws[i].Update(elapsedSec, m_pPlayer->GetPosition());
	}
	for (int i = 0; i < m_SwingBlades.size(); i++)
	{
		m_SwingBlades[i].Update(elapsedSec, m_pPlayer->GetPosition());
	}
}
