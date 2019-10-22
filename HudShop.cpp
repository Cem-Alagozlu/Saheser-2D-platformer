#include "stdafx.h"
#include "HudShop.h"
#include "Shop.h"

HudShop::HudShop( PlayerManager& playerManager)
	: m_PlayerManager{ playerManager }
{
	for (size_t i = 0; i <= m_ShopIMGs; i++)
	{
		std::stringstream str;
		str << "Resources/Sprites/Environment/Shop/Menu/0" << i << ".png";
		m_pHudShopTextures.push_back(std::make_unique<Texture>(str.str()));
	}

	m_ButtonRects.push_back(Rectf{ 0,0,1280,720 });
	m_ButtonRects.push_back(Rectf{ 970,605,260,60 });	// back button	
	m_ButtonRects.push_back(Rectf{ 115,260,150,55 });	// upgrade bullet
	m_ButtonRects.push_back(Rectf{ 505,260,150,55 });	// buy hacks
	m_ButtonRects.push_back(Rectf{ 896,260,150,55 });	// buy dmg melee
	m_ButtonRects.push_back(Rectf{ 115,60,150,55 });	// buy speed
	m_ButtonRects.push_back(Rectf{ 505,60,150,55 });	// buy armor
	m_ButtonRects.push_back(Rectf{ 896,60,150,55 });  // buy lives

	m_PriceTexture.push_back(Texture(std::to_string(1000), "Resources/Fonts/Font01.otf", 30, Color4f(1, 1, 1, 1)));
	m_PriceTexture.push_back(Texture(std::to_string(4000), "Resources/Fonts/Font01.otf", 30, Color4f(1, 1, 1, 1)));
	m_PriceTexture.push_back(Texture(std::to_string(999999), "Resources/Fonts/Font01.otf", 20, Color4f(1, 1, 1, 1)));
	m_PriceTexture.push_back(Texture(std::to_string(100), "Resources/Fonts/Font01.otf", 30, Color4f(1, 1, 1, 1)));
	m_PriceTexture.push_back(Texture("Buy", "Resources/Fonts/Font01.otf", 30, Color4f(1, 1, 1, 1)));
}


void HudShop::Draw() const
{
	//checks if menu is on
	if (m_IsMenuVisible == false)
	{
		m_pHudShopTextures[0]->Draw(Rectf{ m_ButtonRects[0] });
	}

	//draws the button textures
	for (int i = 0; i < m_ButtonRects.size() ; i++)
	{
		if (utils::IsPointInRect(m_MousePos, m_ButtonRects[i]))
		{
			m_pHudShopTextures[i]->Draw(Rectf{ m_ButtonRects[0] });
		}
	}
	//draws the texture texts
	m_pLifeCounterTexture->Draw({ 210,493 }); // lives
	m_pLevelCounterTexture->Draw({ 970,493 }); // level
	m_pPointCounterTexture->Draw({ 620,493 }); // points
	m_PriceTexture[0].Draw({ 1075, 70 });  // buy lives
	m_PriceTexture[1].Draw({ 1070, 270 }); // melee upgrade
	m_PriceTexture[2].Draw({ 680, 275 }); // hacks
	m_PriceTexture[3].Draw({ 695, 70 }); // lives
	m_PriceTexture[1].Draw({ 290, 270 }); // bullets
	m_PriceTexture[1].Draw({ 290, 70 }); // speed

	//draws the prices
	for (int i = 0; i < 3; i++)
	{
		m_PriceTexture[4].Draw({ static_cast<float>(155) + static_cast<float>(i * 390),70 });
	}
	for (int i = 0; i < 3; i++)
	{
		m_PriceTexture[4].Draw({ static_cast<float>(155) + static_cast<float>(i * 390),270 });
	}
}

void HudShop::Update(float elapsedSec)
{
	//checks button visiblity
	for (int i = 0; i < m_ButtonRects.size(); i++)
	{
		if (utils::IsPointInRect(m_MousePos, m_ButtonRects[i]))
		{
			m_IsMenuVisible = true;
		}
		else
		{
			m_IsMenuVisible = false;
		}
	}
	//updates the text
	m_pLifeCounterTexture = std::make_unique<Texture>(std::to_string(m_PlayerManager.GetLives()), "Resources/Fonts/Font01.otf", 30, Color4f(1, 1, 1, 1));
	m_pPointCounterTexture = std::make_unique<Texture>(std::to_string(m_PlayerManager.GetPoints()), "Resources/Fonts/Font01.otf", 30, Color4f(1, 1, 1, 1));
	m_pLevelCounterTexture = std::make_unique<Texture>(std::to_string(m_PlayerManager.GetLevel()), "Resources/Fonts/Font01.otf", 30, Color4f(1, 1, 1, 1));
}

void HudShop::MouseMoved(const Point2f & mousePos)
{
	m_MousePos = mousePos; // sets mousepos 
}

void HudShop::MouseClick(const SDL_MouseButtonEvent & e)
{
	//checks which button is clicked for you
	if (utils::IsPointInRect(m_MousePos, m_ButtonRects[2]))
	{
		if (m_PlayerManager.GetPoints() >= 4000)
		{
			m_PlayerManager.AddBulletSpeed(50); // upgrade bullet 4000
			m_PlayerManager.AddPoints(-4000);
		}
	}
	 if (utils::IsPointInRect(m_MousePos, m_ButtonRects[3]))
	{
		//buy hacks
	}
	 if (utils::IsPointInRect(m_MousePos, m_ButtonRects[4]))
	{
	// buy dmg melee
	}
	 if (utils::IsPointInRect(m_MousePos, m_ButtonRects[5]))
	{
		 if (m_PlayerManager.GetPoints() >= 4000)
		 {
			 m_PlayerManager.AddSpeed(50); //buy speed 4000
			 m_PlayerManager.AddPoints(-4000);
		 }
	}
	 if (utils::IsPointInRect(m_MousePos, m_ButtonRects[6]))
	{
		if (!(m_PlayerManager.GetHealth() >= 27) && m_PlayerManager.GetPoints() >= 100)
		{
			m_PlayerManager.AddHealth(1);
			m_PlayerManager.AddPoints(-100);
		}
	}
	 if (utils::IsPointInRect(m_MousePos, m_ButtonRects[7]))
	{
		if (m_PlayerManager.GetPoints() >= 1000)
		{
			 m_PlayerManager.AddLives(1);
			 m_PlayerManager.AddPoints(- 1000);
		}
	}
}

Rectf HudShop::GetCollisionRect(const int & button)
{
	//checks which button you pressed
	int rectButtonNumber = button;
	Rectf collisionRect{};

	switch (rectButtonNumber)
	{
	case 1 :
		collisionRect = m_ButtonRects[1];
		break;
	case 2:
		collisionRect = m_ButtonRects[2];
		break;
	case 3:
		collisionRect = m_ButtonRects[3];
		break;
	case 4:
		collisionRect = m_ButtonRects[4];
		break;
	case 5:
		collisionRect = m_ButtonRects[5];
		break;
	case 6:
		collisionRect = m_ButtonRects[6];
		break;
	case 7:
		collisionRect = m_ButtonRects[7];
		break;
	}

	return collisionRect;
}
