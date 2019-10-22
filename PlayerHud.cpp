#include "stdafx.h"
#include "PlayerHud.h"


PlayerHud::PlayerHud(const PlayerManager& playerManager)
	:m_HudTexture{ "Resources/Sprites/Hud/hud.png" }
	,m_PlayerManager{playerManager}
	,m_HealthBars{"Resources/Sprites/Hud/healthBar.png"}
{
}



void PlayerHud::Update(float elapsedSec)
{	
	m_pPointCounterTexture = std::make_unique<Texture>(std::to_string(m_PlayerManager.GetPoints()), "Resources/Fonts/Font01.otf", 25, Color4f(1, 1, 1, 1));
	m_pLifeCounterTexture = std::make_unique<Texture>(std::to_string(m_PlayerManager.GetLives()), "Resources/Fonts/Font01.otf", 30, Color4f(1, 1, 1, 1));
	m_pLevelCounterTexture = std::make_unique<Texture>(std::to_string(m_PlayerManager.GetLevel()), "Resources/Fonts/Font01.otf", 45, Color4f(1, 1, 1, 1));
}

void PlayerHud::Draw() const
{
	m_HudTexture.Draw({ 0,0,1280,720 });
	m_pLifeCounterTexture->Draw({ 50,639 });
	m_pLevelCounterTexture->Draw({ 205,635 });
	m_pPointCounterTexture->Draw({ 1150,642 });

	
	//destrect is position in de wereld en sourcerect is position op texture
	int hp = m_PlayerManager.GetHealth();
	for (int i = 0; i < m_PlayerManager.GetHealth(); i++)
	{
		glPushMatrix();
		glTranslatef(static_cast<float>(381) + static_cast<float>(i*18), static_cast<float>(634), 0.0f);
		glScalef(0.15f, 0.84f, 1.0f);
		if (hp  >= 18)
		{
			m_HealthBars.Draw({ 0,0 }, { m_HealthBars.GetWidth() - (m_HealthBars.GetWidth() / 6),0,m_HealthBars.GetWidth() / 6 ,m_HealthBars.GetHeight() });
		}
		else if (hp <= 10)
		{
			m_HealthBars.Draw({ 0,0 }, { 168,0,56 ,m_HealthBars.GetHeight() });
		}
		else if (hp >= 10 && hp <=17)
		{
			m_HealthBars.Draw({ 0,0 }, { 224,0,56 ,m_HealthBars.GetHeight() });
		}
		glPopMatrix();
	}
}
