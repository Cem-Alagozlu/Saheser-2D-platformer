#include "stdafx.h"
#include "Trap.h"
#include "SVGParser.h"
#include "Matrix2x3.h"

Trap::Trap(const Point2f& position, const std::string& path, float angle, float scale, const std::string& pathVertices)
	: m_Scale{scale}
	  , m_Angle{angle}
	  , m_Pos{position}
	  , m_Texure{path}
	  , m_VerticesLocal{}
{
	//sets parser file ( gets the vertices from file) 
	SVGParser::GetVerticesFromSvgFile(pathVertices, m_VerticesLocal);
	m_VerticesWorld = m_VerticesLocal;
}

void Trap::UpdateVertices(const Vector2f& trans02)
{
	//sets & updates the vertices
	Matrix2x3 t = Matrix2x3::CreateTranslationMatrix(Vector2f{m_Pos});
	Matrix2x3 r = Matrix2x3::CreateRotationMatrix(m_Angle);
	Matrix2x3 s = Matrix2x3::CreateScalingMatrix(m_Scale);
	Matrix2x3 t2 = Matrix2x3::CreateTranslationMatrix(trans02);


	Matrix2x3 world = t * r * s * t2;
	for (size_t i{}; i < m_VerticesLocal.size(); ++i)
	{
		m_VerticesWorld[i] = world.Transform(m_VerticesLocal[i]);
	}
}

void Trap::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const
{
	//handles the collision for the traps
	utils::HitInfo hitInfo;
	Point2f actorBottomPos{actorShape.left + actorShape.width / 2, actorShape.bottom};
	Point2f actorTopPos{actorShape.left + actorShape.width / 2, actorShape.bottom + actorShape.height};
	bool hit = Raycast(m_VerticesWorld, actorBottomPos, actorTopPos, hitInfo);
	if (hit)
	{
		actorShape.bottom = hitInfo.intersectPoint.y;
		if (actorVelocity.y <= 0)
		{
			actorVelocity.y = 0;
		}
	}
}
