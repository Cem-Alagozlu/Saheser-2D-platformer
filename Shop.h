#pragma once
#include "stdafx.h"


class Shop
{
public:
	explicit Shop(const Point2f& pos, const float& size, std::shared_ptr<Player> player,PlayerManager& playerManager);

	void Draw() const;
	void DrawLocal() const;
	void Update(float elapsedSec);

	void MouseMoved(const Point2f& mousePos);
	void MouseClick(const SDL_MouseButtonEvent& e);
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);


private:
	HudShop m_HudShop;

	Point2f m_VendorPosition;
	Point2f m_MousePos;
	Rectf m_CollisionRect{};
	const float m_Scale;
	Sprite m_VendorSprite;
	std::shared_ptr<Player> m_pPlayer;
	bool m_IsMenuOn = false;
};

