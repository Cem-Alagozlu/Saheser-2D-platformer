#pragma once
#include "Trap.h"

class TrapSpikeFall : public Trap
{
public:
	explicit TrapSpikeFall(const Point2f& position, float angle, float scale, float dropTime, bool flipped);

	virtual void Draw() const override;
	virtual void Update(float elapsedSec, const Vector2f& player) override;

	bool SpikeCollision(const Rectf& player) const;

private:
	Vector2f m_Gravity;
	Vector2f m_GravityInverse;

	float m_AccumSec{};
	float m_DropTime;

	Texture m_TextureSpike;
	Texture m_TextureSpikeInverse;
	Point2f m_SpikePos;
	std::string m_PathSVG;

	bool m_IsFlipped{false};
};
