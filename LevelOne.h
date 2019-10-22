#pragma once
#include "stdafx.h"
#include "LevelManager.h"
#include "LevelBase.h"
#include "Shop.h"
#include "PlatformMoving.h"
#include "Lever.h"
#include "Hatch.h"
#include "TrapCircleSaw.h"
#include "DoorSwitch.h"
#include "EmptyCollision.h"
#include "Coin.h"
#include "EnemyEasy.h"

class LevelOne : public LevelBase
{
public:
	explicit LevelOne(LevelManager& levelmanager, std::shared_ptr<Player> player);


	//Draw level & update
	virtual void DrawFront() const override;
	virtual void DrawBack() const override;
	virtual void DrawLocal() const override;
	virtual void Update(float elapsedSec) override;
	
	virtual void PlayMusic() override;

	//Player input
	virtual void MouseMoved(const Point2f& mousePos) override;
	virtual void MouseClick(const SDL_MouseButtonEvent& e) override;
	//virtual void ProcessKeyDownEvent(const SDL_KeyboardEvent& e) override;

	//Level functions
	virtual void HandleCollision(Rectf& Shape, Vector2f& actorVelocity) override;
	virtual Rectf GetBoundaries() const override;



private:
	Texture m_LevelOneTextureFront;
	Texture m_LevelOneTextureBack;
	Texture m_HiddenTextureFront;
	Texture m_HiddenTextureBack;
	Texture m_HiddenTextureHiding;



	// TECHNICAL STUFF
	Rectf m_Boundaries; // level width & height for camera matrix
	Rectf m_HiddenRect{};
	bool m_IsHidden{ true };
	std::shared_ptr<Player> m_pPlayer;
	Point2f m_Pos;


	std::vector<PlatformMoving> m_MovingPlatforms;
	std::vector<Lever> m_Levers;
	std::vector<EnemyEasy> m_Enemies;
	std::vector<EmptyCollision> m_CollisionBoxes;
	Hatch m_Hatch;

	std::vector<std::unique_ptr<Texture>> m_pParallax;

	
	TrapCircleSaw m_CircleSaw;
	DoorSwitch m_DoorSwitch;
	float m_FadingOpacity{};
	bool m_IsNextLevel{ false };
	std::vector<std::unique_ptr<Coin>> m_pCoins;
	std::vector<Rectf> m_DeathRects;
	void Initialize();
	float m_TimerOverlapEnemyEasy{};

};

