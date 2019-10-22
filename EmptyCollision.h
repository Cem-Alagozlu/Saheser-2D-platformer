#pragma once
#include "EmptyCollision.h"
class EmptyCollision
{
public:
	EmptyCollision(const Rectf& boxCollision);
	void Draw() const;
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const;
	bool IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const;

private:
	std::vector<Point2f> m_Vertices;
};

