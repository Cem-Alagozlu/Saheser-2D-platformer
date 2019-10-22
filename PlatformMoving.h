#pragma once
#include "Platform.h"


class PlatformMoving : public Platform
{
public:
	enum class TravelDirection
	{
		up,
		down
	};

	PlatformMoving(const Point2f& position, const std::string& path, const Point2f& endPos, float angle, float scale, int type, const std::string& verticesSVG);

	virtual void Draw() const override;
	virtual void Update(float elapsedSec) override;

	bool PlatformCollision(const Rectf& player);
	void PlatformPlayerChange(Rectf& player) const;

private:
	std::string m_PathSVG;
	Point2f m_Mover;
	Point2f m_BeginPos;
	Point2f m_EndPos;
	bool m_IsHittingBottom;
	int m_Type;

	TravelDirection m_CurrentDirection = TravelDirection::up;
};
