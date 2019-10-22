#pragma once
class Platform
{
public:
	explicit Platform(const Point2f& position, const std::string& path, float angle, float scale, const std::string& pathVertices);

	virtual void Draw() const = 0;
	virtual void Update(float elapsedSec) = 0;

	void UpdateVertices(const Vector2f& trans02);
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const;
	bool IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const;

protected:
	float m_Scale;
	float m_Angle;
	Texture m_Texure;
	Point2f m_Pos;

	std::vector<Point2f> m_VerticesLocal;
	std::vector<Point2f> m_VerticesWorld;
};
