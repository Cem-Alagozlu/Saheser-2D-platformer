#pragma once
#include "LevelManager.h"
#include "Player.h"

class LevelBase
{
public:
	explicit LevelBase(LevelManager& levelmanager, const std::string& path);

	virtual void DrawFront() const = 0;
	virtual void DrawBack() const = 0;
	virtual void DrawLocal() const = 0;
	virtual void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity);
	virtual void Update(float elapsedSec) = 0;

	virtual void MouseMoved(const Point2f& mousePos) = 0;
	virtual void MouseClick(const SDL_MouseButtonEvent& e) = 0;
	virtual void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);

	virtual Rectf GetBoundaries() const = 0;
	virtual bool HasReachedEnd(const Rectf& actorShape) const;

	bool IsOnGround(Rectf& actorShape, Vector2f& actorVelocity) const;
	virtual Point2f GetBeginPos() const;

	virtual void PlayMusic() = 0;
	bool GetLeftBool() const;

protected:

	Point2f m_BeginPos;
	LevelManager& m_LevelManager;
	bool m_IsInteracting{ false };
	std::vector<Point2f> m_Vertices;
	void SetPos(float x, float y);
	bool m_IsLeft{ false };

};
