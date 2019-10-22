#pragma once
#include "Enemy.h"
class EnemyEasy : public Enemy
{
public:
	explicit EnemyEasy(const Point2f& actorPos, const Point2f& endPoint,const std::string& type, const Point2f& offset, float dmg, float waitTime);

	virtual void Draw() const override;
	virtual void Update(float elapsedSec) override;

	virtual void BulletCollision(const Rectf & bullet, const Rectf& enemy) override;
	virtual Rectf GetPosition() const override;
	virtual bool IsEnemyDestroyed() const; 
	bool PlayerCollisionBullet(const Rectf& player);

private:
	std::string m_EnemyTypeString;
	
	Texture m_EasyEnemySlimy;
	Texture m_EasyEnemyFlying;
	Texture m_BulletTexture;

	std::deque<Rectf> m_BulletRect;
	std::deque<Point2f> m_BulletPos;
	std::vector<float> m_BulletDownForce{};


	Point2f m_ActorPos;
	Point2f m_BeginPos;
	Point2f m_EndPos;
	Point2f m_PosAdder{};

	int m_Amounts{};
	bool m_IsMoving;
	bool m_IsMovingLeft;
	float m_AccumSec{};
	float m_WaitTime{ };
	float m_MovementSpeed;
};

