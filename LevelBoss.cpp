#include "stdafx.h"
#include "LevelBoss.h"

LevelBoss::LevelBoss(LevelManager & levelmanager, std::shared_ptr<Player> player)
	:LevelBase{ levelmanager,"Resources/Sprites/LevelBoss/LevelBoss.svg" }
	, m_pPlayer{ player }
	, m_BossLamia{Point2f{400,10},20,35,player }
{
	m_pFrontTexture = (std::make_unique<Texture>("Resources/Sprites/LevelBoss/front.png"));
	m_pBackTexture = (std::make_unique<Texture>("Resources/Sprites/LevelBoss/back.png"));
	m_pFogTexture = (std::make_unique<Texture>("Resources/Sprites/LevelBoss/fog.png"));
	m_pEnd = (std::make_unique<Texture>("Resources/Sprites/LevelBoss/end.png"));

	m_Boundaries = { 0,0,m_pBackTexture->GetWidth(),m_pBackTexture->GetHeight() };
	m_BeginPos = { 1800,100 };
}

void LevelBoss::DrawFront() const
{
	m_pFrontTexture->Draw({ 0,0 }); // draws front texture
	m_pFogTexture->Draw({ 0,0 });

}

void LevelBoss::DrawBack() const
{
	m_pBackTexture->Draw({ 0,0 }); // draws the back texture
	m_BossLamia.Draw();
}

void LevelBoss::DrawLocal() const
{

		utils::SetColor(Color4f{ 1,1,1,m_OpacityAdder });
		utils::FillRect(Rectf{ 0,0,1280,720 });

		if (m_OpacityAdder >= 2.0f)
		{
			m_pEnd->Draw(Rectf(0, 0, 1280, 720));
		}
}

void LevelBoss::Update(float elapsedSec)
{
	//player pos
	m_Pos.x = m_pPlayer->GetShape().left;
	m_Pos.y = m_pPlayer->GetShape().bottom;
	m_pPlayer->GetPlayerManager().SetLevel(0);

	m_BossLamia.Update(elapsedSec);

	if (m_BossLamia.GetEnemyLifeState() == true)
	{
		m_OpacityAdder += elapsedSec;
	}

	if (m_pPlayer->GetPlayerManager().GetHealth() <= 0)
	{
		m_pPlayer->SetSecondaryMovement(Player::SecondaryMovement::death);
	}

}

void LevelBoss::MouseMoved(const Point2f & mousePos)
{
}

void LevelBoss::MouseClick(const SDL_MouseButtonEvent & e)
{
}

void LevelBoss::ProcessKeyDownEvent(const SDL_KeyboardEvent & e)
{
}

void LevelBoss::HandleCollision(Rectf & Shape, Vector2f & actorVelocity)
{
	LevelBase::HandleCollision(Shape, actorVelocity);
	m_BossLamia.PlayerCollision(m_pPlayer->GetShape());
	m_BossLamia.BulletCollision(m_pPlayer->GetBulletPosition());

}

Rectf LevelBoss::GetBoundaries() const
{
	return m_Boundaries; // returns the second level boundary
}

void LevelBoss::PlayMusic()
{
	SoundManager::PlaySoundStream("Boss", true); // plays level boss song
}
