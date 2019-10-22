#pragma once
#include "Sprite.h"

class Coin
{
public:
	explicit Coin(const Point2f& pos);

	void Draw() const;
	void Update(float elapsedSec) const;
	bool IsOverlapping(const Rectf& rect) const;
	void PlayCoinSound() const;

private:
	Circlef m_Shape;
	Point2f m_Pos;
	float m_Scale;
	//laad 1 keer in
	static std::shared_ptr<Sprite> m_pCoinSprite;
};
