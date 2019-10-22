#include "stdafx.h"
#include "EmptyCollision.h"

EmptyCollision::EmptyCollision(const Rectf & boxCollision)
{
	//creates the vertices for your collision ( hidden ) 
	m_Vertices.push_back(Point2f(boxCollision.left, boxCollision.bottom));
	m_Vertices.push_back(Point2f(boxCollision.left + boxCollision.width, boxCollision.bottom));
	m_Vertices.push_back(Point2f(boxCollision.left + boxCollision.width, boxCollision.bottom + boxCollision.height));
	m_Vertices.push_back(Point2f(boxCollision.left, boxCollision.bottom + boxCollision.height));
}

void EmptyCollision::Draw() const
{
	//draws your "invisible lines" 
	utils::SetColor(Colors::Red);
	utils::DrawPolygon(m_Vertices);
	
}

void EmptyCollision::HandleCollision(Rectf & actorShape, Vector2f & actorVelocity) const
{
	//sets up collision (y) 
	utils::HitInfo hitInfo;
	Point2f actorBottomPos{ actorShape.left + actorShape.width / 2, actorShape.bottom };
	Point2f actorTopPos{ actorShape.left + actorShape.width / 2, actorShape.bottom + actorShape.height / 2 };

	bool hit = Raycast(m_Vertices, actorBottomPos, actorTopPos, hitInfo);
	if (hit)
	{
		actorShape.bottom = hitInfo.intersectPoint.y;
		if (actorVelocity.y < 0)
		{
			actorVelocity.y = 0;
		}
	}

	Point2f actorLeftPos{ actorShape.left , actorShape.bottom + actorShape.height / 2 };
	Point2f actorRightPos{ actorShape.left + actorShape.width , actorShape.bottom + actorShape.height / 2 };

	//sets up collision (x) 
	hit = Raycast(m_Vertices, actorLeftPos, actorRightPos, hitInfo);
	if (hit)
	{
		if (hitInfo.normal.x > 0)
		{
			actorShape.left = hitInfo.intersectPoint.x;
		}
		else
		{
			actorShape.left = hitInfo.intersectPoint.x - actorShape.width ;
		}
		actorVelocity.x = 0.0f;
	}
}

bool EmptyCollision::IsOnGround(const Rectf & actorShape, const Vector2f & actorVelocity) const
{
	utils::HitInfo hitInfo;
	Point2f actorBottomPos{ actorShape.left + actorShape.width / 2, actorShape.height + actorShape.bottom };
	bool hit = Raycast(m_Vertices, actorBottomPos, { actorBottomPos.x, actorBottomPos.y - actorShape.height - 1.0f }, hitInfo);
	return hit;
}
