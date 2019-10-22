#pragma once
#include "stdafx.h"
#include "LevelManager.h"
#include "LevelBase.h"
#include "EnemyEasy.h"
#include "Coin.h"
#include "JumpPad.h"
#include "Flag.h"
#include "Lever.h"
#include "TrapCircleSaw.h"

class LevelTwo : public LevelBase
{
public:
	explicit LevelTwo(LevelManager& levelmanager, std::shared_ptr<Player> player);

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
	std::shared_ptr<Texture> m_pLevelTwoTextureFront;
	std::shared_ptr<Texture> m_pLaserTexture;;
	std::shared_ptr<Texture> m_pLevelTwoTextureBack;
	std::vector<std::unique_ptr<Coin>> m_pCoins;
	std::vector<EnemyEasy> m_Enemies;
	std::vector<JumpPad> m_JumpPads;
	std::vector<TrapCircleSaw> m_CircleSawTraps;

	std::vector<Rectf> m_DeathRects;
	Flag m_Flag;
	Lever m_Lever;

	// TECHNICAL STUFF
	Rectf m_Boundaries; // level width & height for camera matrix
	Rectf m_NextLevelTrigger;
	std::shared_ptr<Player> m_pPlayer;
	Point2f m_Pos;
	float m_TimerOverlapEnemyEasy{};
	Shop m_Shop;
	float m_FadingOpacity{};
	int m_Amounts{};
	bool m_HasReachedCheckPoint{};
	bool m_IsLaserOn{};
	void Initialize();
};

