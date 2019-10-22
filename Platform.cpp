#include "stdafx.h"
#include "Platform.h"
#include "SVGParser.h"
#include "Matrix2x3.h"

Platform::Platform(const Point2f& position, const std::string& path, float angle, float scale, const std::string& pathVertices)
	: m_Scale{scale}
	  , m_Angle{angle}
	  , m_Texure{path}
	  , m_Pos{position}
	  , m_VerticesLocal{}
{
	//adds vertices to the parser
	SVGParser::GetVerticesFromSvgFile(pathVertices, m_VerticesLocal);
	m_VerticesWorld = m_VerticesLocal;
}

bool Platform::IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const
{
	//checks if actor is on ground
	utils::HitInfo hitInfo;
	Point2f actorBottomPos{actorShape.left + actorShape.width / 2, actorShape.height + actorShape.bottom};
	bool hit = Raycast(m_VerticesWorld, actorBottomPos, {actorBottomPos.x, actorBottomPos.y - actorShape.height - 1.0f}, hitInfo);
	return hit;
}

void Platform::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const
{
	//handles collision for the platforms
	utils::Raycast(m_VerticesWorld, actorShape, actorVelocity);
}

void Platform::UpdateVertices(const Vector2f& trans02)
{
	//updates your vertices for the platform
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
