#pragma once
class Hatch
{
public:
	explicit Hatch(const Point2f& posHatch, const Point2f& posMeter, const Point2f& posButtonBlue);

	void DrawFront()const;
	void DrawBack()const;

	void Update(float elapsedSec);
	Rectf GetButtonRect() const;

	bool BulletCollision(const Rectf& bullet, const Rectf& hatched);
	bool IsHatchedOpen();

private:
	bool m_IsPressed;
	bool m_IsHatchOpen;
	Texture m_Hatch;
	Texture m_Meter;
	Texture m_Buttons;
	
	Point2f m_PosHatch;
	Point2f m_PosMeter;
	Point2f m_PosButton;

	Rectf m_MeterFiller;
	float m_MeterAdder;
	float m_HatchSlider;
	float m_ButtonOffset{};
	int m_MeterAdderCount;
};

