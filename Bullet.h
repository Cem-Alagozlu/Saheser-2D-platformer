#pragma once


class Bullet
{
public:
	explicit Bullet(Point2f& pos, Vector2f& dir);

	void Update(float elapsedSec);
	void Draw() const;

	Rectf GetBulletLocation();

private:
	Texture m_BulletTexture;
	float m_Speed;
	Vector2f m_Velocity;
	Point2f m_Pos;
	
};

