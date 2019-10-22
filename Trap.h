#pragma once

class Trap
{
public:
	explicit Trap(const Point2f& position, const std::string& path, float angle, float scale, const std::string& pathVertices);

	virtual void Draw() const = 0;
	virtual void Update(float elapsedSec, const Vector2f& player) = 0;
	void UpdateVertices(const Vector2f& trans02);
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const;

protected:
	float m_Scale;
	float m_Angle;
	Point2f m_Pos;
	Texture m_Texure;

	std::vector<Point2f> m_VerticesLocal;
	std::vector<Point2f> m_VerticesWorld;
};
