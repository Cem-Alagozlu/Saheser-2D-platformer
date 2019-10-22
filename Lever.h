#pragma once
class Lever
{
public:
	 explicit Lever( const Point2f& pos, float angle, float scale);

	void Draw() const;
	bool Collision(Rectf& actorShape) const;
	bool SetLeverPull(bool isPulled);
	bool GetLeverState();
	void PlayLeverSound() const;

private:
	Point2f m_Pos;
	Point2f m_PosFrame;
	float m_Angle;
	float m_Scale;
	bool m_IsLeverPulled{ false };

	Texture m_Lever;
};
