#include "stdafx.h"
#include "Camera.h"
#include "utils.h"

Camera::Camera()
{
}

void Camera::Draw() const
{
	glColor3f(0, 0, 1);
	utils::DrawRect(m_Camera);
}

void Camera::Update(const Rectf& toTrack)
{
	Point2f center{Track(toTrack)};
	Point2f bottomLeft{center.x - m_Camera.width / 2, center.y - m_Camera.height / 2};
	Clamp(bottomLeft);
	m_Camera = {bottomLeft.x, bottomLeft.y, m_Camera.width, m_Camera.height};
}

void Camera::SetBoundaries(const Rectf& boundaries)
{
	m_Boundaries = boundaries;
}

Point2f Camera::GetPosition() const
{
	return {m_Camera.left, m_Camera.bottom};
}

void Camera::SetSize(const Vector2f& size)
{
	m_Camera.width = size.x;
	m_Camera.height = size.y;
}

void Camera::Clamp(Point2f& bottomLeftPos) const
{
	if (bottomLeftPos.x < m_Boundaries.left)
	{
		bottomLeftPos.x = 0.0f;
	}
	if (bottomLeftPos.y < m_Boundaries.bottom)
	{
		bottomLeftPos.y = 0.0f;
	}
	if (bottomLeftPos.x + m_Camera.width > m_Boundaries.left + m_Boundaries.width)
	{
		bottomLeftPos.x = m_Boundaries.left + m_Boundaries.width - m_Camera.width;
	}
	if (bottomLeftPos.y + m_Camera.height > m_Boundaries.bottom + m_Boundaries.height)
	{
		bottomLeftPos.y = m_Boundaries.bottom + m_Boundaries.height - m_Camera.height;
	}
}

Point2f Camera::Track(const Rectf& toTrack) const
{
	return Point2f{toTrack.left + toTrack.width / 2 , toTrack.bottom + toTrack.height / 2};
}
