#pragma once
class PlayerManager
{	
public:
	int GetLives() const;
	void AddLives(int value);

	int GetLevel() const;
	void SetLevel(int value);

	int GetPoints() const;
	void AddPoints(int value);

	int GetArmor() const;
	void SetArmor(int value);

	float GetDamage() const;
	void AddDamage(float value);

	float GetSpeed() const;
	void AddSpeed(float value);

	float GetBulletSpeed() const;
	void AddBulletSpeed(float value);

	float GetJumpHeight() const;
	void AddJumpHeight(float value);

	int GetHealth() const;
	void AddHealth(int value);
	void SetHealth(int value);
	
private:


	int m_Lives{ 8 };
	int m_Level{ 1 };
	int m_Points{ 500 };
	int m_Health{27};
	int m_Armor{ 0 };
	float m_Damage{ 10.0f };
	float m_Speed{ 10.0f };
	float m_BulletSpeed{ 10.0f };
	float m_JumpHeight{ 10.0f };
};