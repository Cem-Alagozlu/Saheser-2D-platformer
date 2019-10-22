#pragma once
#include "stdafx.h"
#include "LevelManager.h"
#include "LevelBase.h"
#include "TrapCircleSaw.h"
#include "TrapSwingBlade.h"
#include "TrapSpikeFall.h"
#include "EnemyMedium.h"

class LevelEnd : public LevelBase
{
public:
	explicit LevelEnd(LevelManager& levelmanager, std::shared_ptr<Player> player);

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
	std::vector<std::unique_ptr<Texture>> m_pParallax;
	std::unique_ptr<Texture> m_pFrontTexture01;
	std::unique_ptr<Texture> m_pBackTexture01;
	void Initialize();
	void PlayerDied();
	void PlayerDeathCollision();
	void UpdateTraps(float elapsedSec);

	//shops
	Shop m_Shop;
	std::vector<TrapSpikeFall> m_SpikeFalls;
	std::vector<TrapCircleSaw> m_CircleSaws;
	std::vector<TrapSwingBlade> m_SwingBlades;
	Rectf m_DeathReact;
	
	float m_Timer{};
	EnemyMedium m_Daevas;

	float m_FadingOpacity{};
	bool m_IsReversed;
};

