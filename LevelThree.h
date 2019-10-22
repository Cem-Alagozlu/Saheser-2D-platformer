#pragma once
#include "stdafx.h"
#include "LevelManager.h"
#include "LevelBase.h"
#include "EnemyMedium.h"
#include "EmptyCollision.h"
class LevelThree : public LevelBase
{
public:
	explicit LevelThree(LevelManager& levelmanager, std::shared_ptr<Player> player);

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
	EnemyMedium m_enemy;

	std::unique_ptr<Texture> m_pFrontTexture01;
	std::unique_ptr<Texture> m_pBackTexture01;
	std::unique_ptr<Texture> m_pStoryTexture00;
	std::unique_ptr<Texture> m_pStoryTexture01;
	std::unique_ptr<Texture> m_pStoryTexture02;
	std::unique_ptr<Texture> m_pMoon;


	float m_MoonRotator{};
	bool m_IsScreenClear;

	float m_IntroFadeCounter{11.0f};
	float m_ArifKillCounter{ 5.0f };

	//cutescene
	std::vector<EmptyCollision> m_CollisionBoxes;
	Rectf m_EventTriggerBox;
	bool m_IsEventStarted;
	bool m_IsArifKilled;
	Point2f m_CamChange{};
	float m_FadingOpacity{};
	bool m_IsNextLevel{ false };
	void DrawMoon() const;
};


