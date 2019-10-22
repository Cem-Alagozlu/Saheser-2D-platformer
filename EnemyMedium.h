#pragma once
#include "LevelManager.h"


class EnemyMedium
{
public:
	enum class ActionState
	{
		idle,
		walking,
		shooting,
		dying,
	};
	enum class Direction
	{
		left,
		right,
	};

	EnemyMedium();

	void Draw() const;
	void Update(float elapsedSec, LevelManager& level, Rectf& playerShape);



	bool SetMovement(bool isMoving);
	void SetPosition(const Point2f& enemyPos);
	void SetActionState(ActionState actionState);
	void SetLevelBeginPos(const Point2f& pos);
	void UpdateCollision(std::shared_ptr<LevelBase> level);
	void UpdatePosition(float elapsedSec);

	void BulletCollision(const Rectf & bullet);
	bool PlayerCollisionBullet(const Rectf & player);
	Point2f GetPosition() const;
	Rectf GetShape() const;
	bool GetAliveState()const;

private:
	bool m_IsMoving{ true };
	bool m_IsGoingLeft;
	bool m_IsShootingLeft;
	int m_Life{};
	Sprite m_Idle;
	Sprite m_Walking;
	Sprite m_Shooting;
	Sprite m_Dead;
	Rectf m_Shape;
	float m_Scale{};
	Sprite* m_pCurrentSprite;

	Rectf m_PlayerCollisionRect;

	ActionState m_ActionState = ActionState::idle;
	Direction m_Direction = Direction::right;
	Point2f m_BeginPosition;
	Vector2f m_Acceleration{ 0,-9.81f };
	Vector2f m_Velocity{ 0.0f,0.0f };
	void UpdateSprite(float elapsedSec);

	Texture m_BulletTexture;
	std::deque<Rectf> m_BulletRect;
	std::deque<Point2f> m_BulletPos;
	std::deque<Point2f> m_PlayerPosDeque;
	std::deque<Point2f> m_CollisionCalculation;


	float m_AccumSec{};
	float m_WaitTime{};
	int m_Amounts{};
	bool m_IsDead;
};