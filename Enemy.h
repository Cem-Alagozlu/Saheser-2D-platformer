#pragma once
#include "Sprite.h"
class Enemy
{
public:
	explicit Enemy(const Point2f& offSet);
	virtual bool IsEnemyDead() const;

protected:
	Point2f m_OffSetHealthBar;
	float m_HealthPoints;
	float m_LimitHealthBar;
	float m_EnemyDamage{};
	bool m_IsEnemyDead;
	bool m_IsDespawning;
	bool m_CanBeRemoved;

	//functions
	virtual void Update(float elapsedSec);
	virtual void DrawHealthBar() const;
	virtual Rectf GetPosition() const = 0;
	virtual void BulletCollision(const Rectf & bullet, const Rectf& enemy) = 0;

private:
	Rectf m_HealthBar;
	Texture m_HealthBarTexture;

	float m_CountTime{};
	float m_DespawnTime;
	int m_DespawnCounter{};
	int m_DespawnCounterLimit;

	//functions
	virtual void Draw() const = 0;
	virtual bool IsEnemyDestroyed() const = 0;
};

