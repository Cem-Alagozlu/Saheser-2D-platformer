#include "stdafx.h"
#include "PlatformMoving.h"

PlatformMoving::PlatformMoving(const Point2f& position, const std::string& path, const Point2f& endPos, float angle, float scale, int type, const std::string& verticesSVG)
	: Platform{position,path,angle,scale,verticesSVG}
	  , m_EndPos{endPos}
	  , m_Type{type}
	  , m_IsHittingBottom{false}
{
	//sets begin positionfor your platform
	m_BeginPos = m_Pos;
}

void PlatformMoving::Draw() const
{
	//draws the platform
	glPushMatrix();
	glTranslatef(m_Pos.x, m_Pos.y, 0);
	glRotatef(m_Angle, 0.0f, 0.0f, 1.0f);
	glScalef(m_Scale, m_Scale, 1.0f);
	m_Texure.Draw({0.0f,0.0f});
	glPopMatrix();
}

void PlatformMoving::Update(float elapsedSec)
{
	//updates your platform to go up && down
	UpdateVertices(Vector2f(0, 0));
	m_Mover.x = 0;
	m_Mover.y = 0;
	
	//which type are you using
	if (m_Type == 1)
	{
		switch (m_CurrentDirection)
		{
		case PlatformMoving::TravelDirection::up:
			m_Mover.y += 300.0f * elapsedSec;
			break;
		case PlatformMoving::TravelDirection::down:
			m_Mover.y -= 300.0f * elapsedSec;
			break;
		}

 		if (m_Pos.y >= m_EndPos.y)
		{
			m_CurrentDirection = TravelDirection::down;
		}
		else if (m_Pos.y <= m_BeginPos.y)
		{
			m_CurrentDirection = TravelDirection::up;
		}

	}

	if (m_Type == 2)
	{
		if (m_Pos.x >= m_EndPos.x)
		{
			m_Mover.x -= 5.0f;
		}
		else if (m_Pos.x <= m_BeginPos.x)
		{
			m_Mover.x += 5.0f;
		}
	}

		m_Pos.y += m_Mover.y;
		m_Pos.x += m_Mover.x;
}

bool PlatformMoving::PlatformCollision(const Rectf& player)
{
	//checks collision for platforms
	Rectf platform;
	platform.left = m_VerticesWorld[0].x;
	platform.bottom = m_VerticesWorld[2].y;
	platform.width = m_VerticesWorld[1].x - m_VerticesWorld[0].x;
	platform.height = m_VerticesWorld[0].y - m_VerticesWorld[2].y + 10;

	if (utils::IsOverlapping(Rectf{platform.left,platform.bottom - 10,platform.width,0}, player))
	{
		m_CurrentDirection = TravelDirection::up;
		
	}

	return utils::IsOverlapping(platform, player);
}

void PlatformMoving::PlatformPlayerChange(Rectf& player) const
{
	player.left += m_Mover.x;
	player.bottom += m_Mover.y;
}
