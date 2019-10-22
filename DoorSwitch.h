#pragma once
class DoorSwitch
{
public:
	explicit DoorSwitch(const Point2f& doorPos, const Point2f& switchPos);

	void Draw() const;

	bool CollisionSwitch(Rectf& actorShape) const;
	bool SetSwitchActivated(bool isActivated);
	bool GetSwitchState();


	bool CollisionDoor(Rectf& actorShape) const;
	bool SetDoorOpen(bool isOpen);
	bool GetDoorOpenState();


private:
	Point2f m_DoorPos;
	Point2f m_SwitchPos;

	bool m_IsSwitchActivated;
	bool m_IsDoorOpen;

	Texture m_DoorTexture;
	Texture m_SwitchTexture;

	Vector2f m_DoorScale;
	Vector2f m_SwitchScale;
};

