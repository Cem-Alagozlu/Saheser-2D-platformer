#include "stdafx.h"
#include "Coin.h"


std::shared_ptr<Sprite> Coin::m_pCoinSprite{};

Coin::Coin(const Point2f& pos)
	:m_Scale{ 0.35f }
{
	m_pCoinSprite = std::make_shared<Sprite>("Resources/Sprites/Environment/Extra/Coins.png", 0.0f, 0.0f, 1500.0f, 142.0f, 10, 1, 1);

	//sets up shape pos & radius for circle
	m_Shape.center.x = pos.x + m_pCoinSprite->GetWidth() / 2;
	m_Shape.center.y = pos.y + m_pCoinSprite->GetHeight() / 2;
	m_Shape.radius = 15;
}


void Coin::Draw() const
{
	//draws the coin
	glPushMatrix();
	glTranslatef(m_Shape.center.x, m_Shape.center.y, 0);
	glScalef(m_Scale, m_Scale, 1.0f);
	glTranslatef(-m_pCoinSprite->GetWidth() / 2, -m_pCoinSprite->GetHeight() / 2, 0);
	m_pCoinSprite->Draw();
	glPopMatrix();
}

void Coin::Update(float elapsedSec) const
{
	//updates the coin ( rotation ) 
	m_pCoinSprite->Update(elapsedSec);
}

bool Coin::IsOverlapping(const Rectf& rect) const
{
	//checks if you picked up the coin
	if (utils::IsOverlapping(rect, m_Shape))
	{
		return true;
	}
	return false;
}

void Coin::PlayCoinSound() const
{
	//if you pick up a coin, a sound effect will be player
	SoundManager::PlaySoundEffect("Coin", false, false);
}
