#include "stdafx.h"
#include "Shop.h"

Shop::Shop(const Point2f & pos, const float& size, std::shared_ptr<Player> player, PlayerManager& playerManager)
	:m_VendorPosition{pos}
	,m_Scale{ size }
	,m_pPlayer{ player }
	,m_VendorSprite{ "Resources/Sprites/Environment/Shop/Vendor01.png", 0.0f, 0.0f, 1128, 410, 4, 2,8 }
	,m_HudShop{playerManager}
	
{
	//gets collision rect for shop
	m_CollisionRect = {m_VendorPosition.x,m_VendorPosition.y,m_VendorSprite.GetWidth(),m_VendorSprite.GetHeight()};
}


void Shop::Draw() const
{
	//draw the shop
	glPushMatrix();
	glTranslatef(m_VendorPosition.x, m_VendorPosition.y, 1);
	glScalef(m_Scale, m_Scale, 1);
	m_VendorSprite.Draw();
	glPopMatrix();
}

void Shop::DrawLocal() const
{
	//draws the menu
	if (m_IsMenuOn == true)
	{
		m_HudShop.Draw();
	}
}

void Shop::Update(float elapsedSec)
{	
	//updates the menu && the shop 
	m_VendorSprite.Update(elapsedSec);
	m_HudShop.Update(elapsedSec);
}

void Shop::MouseMoved(const Point2f & mousePos)
{
	// checks & sets the mouse to use for your buttons
	if (m_IsMenuOn == true)
	{
		m_MousePos = mousePos;
		m_HudShop.MouseMoved(mousePos);
	}

}

void Shop::MouseClick(const SDL_MouseButtonEvent & e)
{
	//checks if you click on any button
	if (utils::IsPointInRect(m_MousePos,m_HudShop.GetCollisionRect(1)))
	{
		m_IsMenuOn = false;
		
	}

	m_HudShop.MouseClick(e);
}

void Shop::ProcessKeyDownEvent(const SDL_KeyboardEvent & e)
{
	//opens shop
	if (e.keysym.sym == SDLK_e&& utils::IsPointInRect(m_pPlayer->GetPosition(), m_CollisionRect))
	{
		m_IsMenuOn = true;
	}
}

