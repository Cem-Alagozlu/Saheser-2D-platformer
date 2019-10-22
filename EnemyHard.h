#pragma once
#include "Player.h"
class EnemyHard
{
public:
	enum class Phase
	{
	one,
	two,
	three,
	final
	};

	explicit EnemyHard(const Point2f& pos, float angle, float swingBoundaries,std::shared_ptr<Player> player);


	void Draw()const;
	void Update(float elapsedSec);
	void PlayerCollision(const Rectf& playerShape);
	void BulletCollision(const Rectf & bullet);
	bool GetEnemyLifeState();

private:
	std::shared_ptr<Player> m_pPlayer;
	Texture m_LowerBodyEnemy;
	Texture m_UpperBodyEnemy;
	Texture m_UpperBodyEnemyDamaged;
	Texture m_UpperBodyEnemyDamagedFinal;

	
	Texture m_Laser02;
	Texture m_Laser03;
	float m_Timer{};

	//Phase 01
	Texture m_Laser01;
	std::vector<Rectf> m_LaserBeamRect01;
	std::vector<Point2f> m_LaserBeamPos01;
	int m_LaserCounterPhase01{};
	bool m_IsLeftEyeHit;
	bool m_IsRightEyeHit;
	bool m_IsLeftEyeDestroyed;
	bool m_IsRightEyeDestroyed;
	float m_LeftEyeHP;
	float m_RightEyeHP;

	//Phase 02
	bool m_IsMouthDestroyed;
	bool m_IsMouthHit;
	float m_MouthHP;
	std::vector<Rectf> m_LaserBeamRect02;
	std::vector<Point2f> m_LaserBeamPos02;
	Rectf m_MouthRect;

	//Phase 03
	Rectf m_HeadRect;
	bool m_IsHeadHit;
	float m_HeadHP;

	//between phase lasers
	bool m_IsLaserEyesOn;

	Rectf m_EnemyCollision;
	Rectf m_AttackRange;

	int m_Amounts{};

	Point2f m_EnemyPos;
	Point2f m_EnemyHeadOffset;
	Ellipsef m_EyePositionRight;
	Ellipsef m_EyePositionLeft;

	float m_EyeSize;

	float m_Angle;
	float m_SwingBoundaries;
	bool m_IsPositive;
	bool m_IsAttacking;
	bool m_IsPlayerReachable;
	bool m_IsEnemeyCompletlyDead;

	Phase m_CurrentPhase = Phase::one;

	void DrawEnemy()const;
	void DrawEnemyAttacks()const;
	void UpdateEnemySwings();
	void UpdateEnemyAttacks(float elapsedSec);
	void AddDamage(float elapsedSec);
};

