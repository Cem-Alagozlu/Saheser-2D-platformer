#pragma once
#include "PlayerManager.h"

class HudShop
{
public:
	HudShop(PlayerManager& playerManager);

	void Draw() const;
	void Update(float elapsedSec);

	void MouseMoved(const Point2f& mousePos);
	void MouseClick(const SDL_MouseButtonEvent& e);

	Rectf GetCollisionRect(const int& button);

private:
	const int m_ShopIMGs{ 7 };
	bool m_IsMenuVisible{ false };
	std::vector<std::unique_ptr<Texture>> m_pHudShopTextures;
	std::vector<Rectf> m_ButtonRects;
	Point2f m_MousePos;
	PlayerManager& m_PlayerManager;

	//Texts
	std::unique_ptr<Texture> m_pLifeCounterTexture;
	std::unique_ptr<Texture> m_pPointCounterTexture;
	std::unique_ptr<Texture> m_pLevelCounterTexture;
	std::vector<Texture> m_PriceTexture;
};

