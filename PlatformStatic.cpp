#include "stdafx.h"
#include "PlatformStatic.h"

PlatformStatic::PlatformStatic(const Point2f& position, const std::string& path, float angle, float scale, const std::string& pathVertices)
	: Platform{position,path,angle,scale,pathVertices}
	  , m_Texture{path}
{
	UpdateVertices(Vector2f(0.0f, 0.0f));
}

void PlatformStatic::Draw() const
{
	//draw a platform
	glPushMatrix();
	glTranslatef(m_Pos.x, m_Pos.y, 0);
	glRotatef(m_Angle, 0.0f, 0.0f, 1.0f);
	glScalef(m_Scale, m_Scale, 1.0f);
	m_Texure.Draw({0.0f,0.0f});
	glPopMatrix();
}

void PlatformStatic::Update(float elapsedSec)
{
}
