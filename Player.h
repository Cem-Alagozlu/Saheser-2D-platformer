#pragma once
#include "Bullet.h"
#include "Camera.h"
#include "PlayerHud.h"
#include "PlayerManager.h"
#include <deque>

class LevelBase;
class Player
{
public:
	enum class PrimaryMovement
	{
		left,
		right,
	};
	enum class SecondaryMovement
	{
		idle,
		run,
		jump,
		idleShoot,
		runShoot,
		jumpShoot,
		death,
		melee,
	};

	Player(const Camera& cam);

	void Update(float elapsedSec,std::shared_ptr<LevelBase>base);
	void Draw() const;
	void DrawHud() const;

	bool SetMovement(bool isMoving);
	void SetPosition(const Point2f& playerPos);

	Point2f GetPosition() const;
	Vector2f GetVelocity()const;
	void SetVelocity(const Vector2f& velocity);
	Rectf GetBulletPosition();
	Rectf GetShape() const;
	void AddPoints(const int& type);
	void AddHealth(const int& type);
	void SetSecondaryMovement(SecondaryMovement sMovement);


	void SetLevelBeginPos(const Point2f& pos);
	void MouseMoved(const Point2f& mousePos);
	void MouseClick(const SDL_MouseButtonEvent& e);
	PlayerManager& GetPlayerManager();

	bool m_IsMoving;
private:
	PrimaryMovement m_Pmovement = PrimaryMovement::right;
	SecondaryMovement m_Smovement = SecondaryMovement::idle;

	void UpdateSprite(float elapsedSec);
	void UpdatePosition(float elapsedSec);
	void UpdateCollision(std::shared_ptr<LevelBase> level);
	void UpdateReset(float elapsedSec);
	void UpdateAnimations();
	void DrawDebugHelp() const;




	Rectf m_CollisonBox;
	float m_Scale{};
	

	Sprite m_Jump;
	Sprite m_Death;
	Sprite m_JumpShoot;
	Sprite m_Melee;
	Sprite m_Idle;
	Sprite m_Run;
	Sprite m_RunShoot;
	Sprite m_IdleShoot;
	Sprite* m_pCurrentSprite;

	

	bool m_HasPlayedDeathSound{ false };
	Vector2f m_Acceleration{0,-9.81f};
	Vector2f m_Velocity{0.0f,0.0f};
	const float m_HorSpeed{500.0f};//225.0f
	const float m_JumpSpeed{450.0f};//800.0f
	

	const float m_TotalTimerReset{1.0f};
	float m_TotalAccum{};

	float m_ShootTimer{ };
	const float m_TotalShootTime{0.5f};

	void HandleMoveKeysState(float elapsedSec);
	
	Point2f m_MousePos;
	Point2f m_BeginPosition;
	std::deque<Bullet> m_Bullets;
	
	const Camera& m_Camera;
	PlayerHud m_PlayerHud;
	PlayerManager m_PlayerManager;

	Point2f m_BulletPos;
	bool m_IsJumping{ false };
	bool m_IsInBound{ false };
	bool m_IsMeleeOn{ false };
	bool m_IsIdleShooting{ false };
	bool m_IsRunShooting{ false };
	bool m_IsJumpShooting{ false };
};

