#pragma once
#include "PlayerManager.h"
class PlayerHud
{
public:
	explicit PlayerHud(const PlayerManager& playerManager);

	void Update(float elapsedSec);
	void Draw() const;

private:
	const PlayerManager& m_PlayerManager;
	Texture m_HudTexture;

	std::unique_ptr<Texture> m_pLifeCounterTexture;
	std::unique_ptr<Texture> m_pPointCounterTexture;
	std::unique_ptr<Texture> m_pLevelCounterTexture;
	Texture m_HealthBars;
};

