#pragma once
#include "stdafx.h"
#include "LevelManager.h"
#include "LevelBase.h"
#include "EnemyHard.h"
class LevelBoss : public LevelBase
{
public:
	explicit LevelBoss(LevelManager& levelmanager, std::shared_ptr<Player> player);

	virtual void DrawFront() const override;
	virtual void DrawBack() const override;
	virtual void DrawLocal() const override;
	virtual void Update(float elapsedSec) override;

	//Player input
	virtual void MouseMoved(const Point2f& mousePos) override;
	virtual void MouseClick(const SDL_MouseButtonEvent& e) override;
	virtual void ProcessKeyDownEvent(const SDL_KeyboardEvent& e) override;

	//Level functions
	virtual void HandleCollision(Rectf& Shape, Vector2f& actorVelocity) override;
	virtual Rectf GetBoundaries() const override;
	virtual void PlayMusic() override;

private:
	// TECHNICAL STUFF
	Rectf m_Boundaries; // level width & height for camera matrix
	std::shared_ptr<Player> m_pPlayer;
	Point2f m_Pos;

	std::unique_ptr<Texture> m_pFrontTexture;
	std::unique_ptr<Texture> m_pBackTexture;
	std::unique_ptr<Texture> m_pFogTexture;
	std::unique_ptr<Texture> m_pEnd;

	float m_OpacityAdder{};
	EnemyHard m_BossLamia;

};


