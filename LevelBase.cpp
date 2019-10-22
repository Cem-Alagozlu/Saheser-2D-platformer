#include "stdafx.h"
#include "LevelBase.h"


LevelBase::LevelBase(LevelManager& levelManager, const std::string& path)
	: m_LevelManager{ levelManager }
{
	//loads in the vertices for your level collision
	SVGParser::GetVerticesFromSvgFile(path, m_Vertices);
}

bool LevelBase::IsOnGround(Rectf& actorShape, Vector2f& actorVelocity) const
{
	//checks if player is on ground
	utils::HitInfo hitInfo;
	Point2f actorTopPos{ actorShape.left + actorShape.width / 2, actorShape.height + actorShape.bottom };
	bool hit = Raycast(m_Vertices, actorTopPos, { actorTopPos.x, actorTopPos.y - actorShape.height - 1.0f }, hitInfo);
	return hit;
}


void LevelBase::ProcessKeyDownEvent(const SDL_KeyboardEvent & e)
{
	//checks if player presses the E button open the shop
	if (e.keysym.sym == SDLK_e)
	{
		m_IsInteracting = true;
	}
	else
	{
		m_IsInteracting = false;
	}
}

bool LevelBase::HasReachedEnd(const Rectf& actorShape) const
{
	return false; 
}

Point2f LevelBase::GetBeginPos() const
{
	return m_BeginPos; // gets begin pos
}

void LevelBase::SetPos(float x, float y)
{
	// sets begin pos
	m_BeginPos.x = x;
	m_BeginPos.y = y;
}

bool LevelBase::GetLeftBool() const
{
	return m_IsLeft; // checks if enemy goes left 
}

void LevelBase::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity)
{
	//manages the collision for each level 
	utils::HitInfo hitInfo;
	Point2f actorBottomPos{ actorShape.left + actorShape.width / 2, actorShape.bottom };
	Point2f actorTopPos{ actorShape.left + actorShape.width / 2, actorShape.bottom + actorShape.height / 2  };

	bool hit = Raycast(m_Vertices, actorBottomPos, actorTopPos, hitInfo);
	if (hit)
	{
		actorShape.bottom = hitInfo.intersectPoint.y;
		if (actorVelocity.y <= 0)
		{
			actorVelocity.y = 0;
		}
	}

	Point2f actorLeftPos{ actorShape.left , actorShape.bottom + actorShape.height / 2 };
	Point2f actorRightPos{ actorShape.left + actorShape.width , actorShape.bottom + actorShape.height / 2 };

	hit = Raycast(m_Vertices, actorLeftPos, actorRightPos, hitInfo);
	if (hit)
	{
		if (hitInfo.normal.x > 0)
		{
			actorShape.left = hitInfo.intersectPoint.x ;
		    m_IsLeft = false;
		}
		else
		{
			actorShape.left = hitInfo.intersectPoint.x - actorShape.width -1;
			m_IsLeft = true;
		}
		
		actorVelocity.x = 0.0f;
	}


}
