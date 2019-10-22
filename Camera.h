#pragma once
class Camera
{
public:
	explicit Camera();

	void Draw() const;
	void Update(const Rectf& toTrack);
	void SetBoundaries(const Rectf& boundaries);


	Point2f GetPosition() const;
	void SetSize(const Vector2f& size);

private:
	Rectf m_Boundaries;

	void Clamp(Point2f& bottomLeftPos) const;
	Point2f Track(const Rectf& toTrack) const;
	Rectf m_Camera;
};
