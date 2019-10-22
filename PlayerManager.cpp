#include "stdafx.h"
#include "PlayerManager.h"


int PlayerManager::GetLives() const
{
	return m_Lives;
}

void PlayerManager::AddLives(int value)
{
	m_Lives += value;
}

int PlayerManager::GetLevel() const
{
	return m_Level;
}

void PlayerManager::SetLevel(int value)
{
	m_Level = value;
}

int PlayerManager::GetPoints() const
{
	return m_Points;
}

void PlayerManager::AddPoints(int value)
{
	m_Points += value;
}

int PlayerManager::GetArmor() const
{
	return m_Armor;
}

void PlayerManager::SetArmor(int value)
{
	m_Armor += value;
}


float PlayerManager::GetDamage() const
{
	return m_Damage;
}

void PlayerManager::AddDamage(float value)
{
	m_Damage += value;
}

float PlayerManager::GetSpeed() const
{
	return m_Speed;
}

void PlayerManager::AddSpeed(float value)
{
	m_Speed += value;
}

float PlayerManager::GetBulletSpeed() const
{
	return m_BulletSpeed;
}

void PlayerManager::AddBulletSpeed(float value)
{
	m_BulletSpeed += value;
}

float PlayerManager::GetJumpHeight() const
{
	return m_JumpHeight;
}

void PlayerManager::AddJumpHeight(float value)
{
	m_JumpHeight += value;
}

int PlayerManager::GetHealth() const
{
	return m_Health;
}

void PlayerManager::AddHealth(int value)
{
	m_Health += value;
}

void PlayerManager::SetHealth(int value)
{
	m_Health = value;
}
