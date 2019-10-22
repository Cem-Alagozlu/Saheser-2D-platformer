#include "stdafx.h"
#include "DoorSwitch.h"

DoorSwitch::DoorSwitch(const Point2f & doorPos, const Point2f & switchPos)
	:m_DoorTexture{"Resources/Sprites/Environment/DoorSwitch/door.png"}
	,m_SwitchTexture{"Resources/Sprites/Environment/DoorSwitch/switch.png"}
	,m_DoorPos{doorPos}
	,m_SwitchPos{switchPos}
	,m_IsSwitchActivated{false}
	,m_IsDoorOpen{false}
	,m_SwitchScale{ 0.45f,0.75f }
	,m_DoorScale{0.25f,0.75f}
{
}

void DoorSwitch::Draw() const
{
	//draws the switch ( but checks in whichs state )
	if (m_IsSwitchActivated)
	{
		glPushMatrix();
		glTranslatef(m_SwitchPos.x, m_SwitchPos.y, 0);
		glScalef(m_SwitchScale.x, m_SwitchScale.y, 1.0f);
		m_SwitchTexture.Draw({ 0,0 }, { m_SwitchTexture.GetWidth() / 2,0,m_SwitchTexture.GetWidth() / 2,m_SwitchTexture.GetHeight() });
		glPopMatrix();

		if (m_IsDoorOpen)
		{
			glPushMatrix();
			glTranslatef(m_DoorPos.x, m_DoorPos.y, 0);
			glScalef(m_DoorScale.x, m_DoorScale.y, 1.0f);
			m_DoorTexture.Draw({ 0,0 }, { m_DoorTexture.GetWidth() - m_DoorTexture.GetWidth()/3,0,m_DoorTexture.GetWidth() / 3.0f ,m_DoorTexture.GetHeight() });
			glPopMatrix();
		}
		else
		{
			glPushMatrix();
			glTranslatef(m_DoorPos.x, m_DoorPos.y, 0);
			glScalef(m_DoorScale.x, m_DoorScale.y, 1.0f);
			m_DoorTexture.Draw({ 0,0 }, { m_DoorTexture.GetWidth() / 3.0f,0,m_DoorTexture.GetWidth() / 3.0f ,m_DoorTexture.GetHeight() });
			glPopMatrix();
		}

	}
	else
	{
		glPushMatrix();
		glTranslatef(m_SwitchPos.x, m_SwitchPos.y, 0);
		glScalef(m_SwitchScale.x, m_SwitchScale.y, 1.0f);
		m_SwitchTexture.Draw({0,0}, { 0,0,m_SwitchTexture.GetWidth() / 2.0f ,m_SwitchTexture.GetHeight() });
		glPopMatrix();

		glPushMatrix();
		glTranslatef(m_DoorPos.x, m_DoorPos.y, 0);
		glScalef(m_DoorScale.x, m_DoorScale.y, 1.0f);
		m_DoorTexture.Draw({ 0,0 }, { 0,0,m_DoorTexture.GetWidth() / 3.0f ,m_DoorTexture.GetHeight() });
		glPopMatrix();
	}

}

bool DoorSwitch::CollisionSwitch(Rectf & actorShape) const
{
	//checks if player is in collision box of switch
	// and returns if so
	Rectf SwitchRect{ m_SwitchPos.x , m_SwitchPos.y,72,250 };

	if (utils::IsOverlapping(SwitchRect,actorShape))
	{
		return true;
	}
	return false;
}

bool DoorSwitch::SetSwitchActivated(bool isActivated)
{
	//sets the switch to on // off
	return m_IsSwitchActivated = isActivated;
}

bool DoorSwitch::CollisionDoor(Rectf & actorShape) const
{
	//checks if player is in reach of door 
	Rectf door{ m_DoorPos.x , m_DoorPos.y,m_DoorTexture.GetWidth()/3,m_DoorTexture.GetHeight() };
	if (utils::IsOverlapping(door, actorShape))
	{
		return true;
	}
	return false;
}

bool DoorSwitch::SetDoorOpen(bool isOpen)
{
	//sets if door is open or not
	return m_IsDoorOpen = isOpen;
}

bool DoorSwitch::GetDoorOpenState()
{
	// checks door state
	return m_IsDoorOpen;
}

bool DoorSwitch::GetSwitchState()
{
	//checks if switch is activated
	return m_IsSwitchActivated;
}