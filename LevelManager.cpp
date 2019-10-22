#include "stdafx.h"
#include "LevelManager.h"
#include "LevelBase.h"
#include "LevelOne.h"
#include "LevelTwo.h"
#include "LevelThree.h"
#include "LevelEnd.h"
#include "LevelBoss.h"
#include "SoundManager.h"

std::shared_ptr<LevelBase> LevelManager::m_pCurrentLevel{};

LevelManager::LevelManager(Game& game, std::shared_ptr<Player> player)
	: m_Game{game}
	, m_pPlayer{player}
{
	SetCurrentLevel(Level::levelOne); //sets your current level (dont do this.. only for testing)
}


void LevelManager::DrawForeground() const
{
	m_pCurrentLevel->DrawFront(); // draws the current level front textures
}

void LevelManager::DrawBackground() const
{
	m_pCurrentLevel->DrawBack(); // draws the current level background textures
}

void LevelManager::DrawLocal() const
{
	m_pCurrentLevel->DrawLocal(); // draws the current level local screen textures
}

void LevelManager::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const
{
	m_pCurrentLevel->HandleCollision(actorShape, actorVelocity); // handles the current level collision 
}

void LevelManager::Update(float elapsedSec) const
{
	m_pCurrentLevel->Update(elapsedSec); // updates the current level
}

void LevelManager::MouseMoved(const Point2f& mousePos) const
{
	m_pCurrentLevel->MouseMoved(mousePos); // updates the current level mouse pos
}

void LevelManager::MouseClick(const SDL_MouseButtonEvent& e) const
{
	m_pCurrentLevel->MouseClick(e); // updates the current level mouse clicks
}

void LevelManager::ProcessKeyDownEvent(const SDL_KeyboardEvent & e)
{ 
	m_pCurrentLevel->ProcessKeyDownEvent(e); // updates the current level input keys
}

std::shared_ptr<LevelBase> LevelManager::GetCurrentLevel()
{
	return m_pCurrentLevel; // gets the current level ptr
}

void LevelManager::SetCurrentLevel(Level level)
{
	switch (level)
	{
	case Level::levelOne:
		UpdateCurrentLevel<LevelOne>();
		break;
	case Level::levelTwo:
		UpdateCurrentLevel<LevelTwo>();
		break;
	case Level::levelThree:
		UpdateCurrentLevel<LevelThree>();
		break;
	case Level::LevelEnd:
		UpdateCurrentLevel<LevelEnd>();
		break;
	case Level::levelBoss:
		UpdateCurrentLevel<LevelBoss>();
		break;
	}

	if (m_pCurrentLevel != nullptr)
	{
		m_pPlayer->SetLevelBeginPos(m_pCurrentLevel->GetBeginPos());
		m_pPlayer->SetPosition(m_pCurrentLevel->GetBeginPos());
	}
}

Point2f LevelManager::GetLevelBeginPos() const
{
	return m_pCurrentLevel->GetBeginPos(); //gets the begin pos from the player
}

Rectf LevelManager::GetLevelBoundaries() const
{
	return m_Boundaries; //gets the level boundaries  
}