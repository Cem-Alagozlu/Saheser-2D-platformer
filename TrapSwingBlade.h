#pragma once
#include "Trap.h"

class TrapSwingBlade : public Trap
{
public:
	TrapSwingBlade(const Point2f& position, float angle, float scale, float swingBound);
	virtual void Draw() const override;
	virtual void Update(float elapsedSec, const Vector2f& player) override;

	bool BladeCollision(const Rectf& player) const;

private:
	std::string m_PathSVG;
	bool m_IsPositive{true};
	float m_SwingBounderies;
};
