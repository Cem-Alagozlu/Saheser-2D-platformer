#pragma once
#include "Vector2f.h"
#include "Player.h"

//class forward declaration 
//I need member variables from these classes in this class
class Game;
class LevelBase;
class LevelOne;
class LevelTwo;
class LevelThree;
class LevelEnd;

class LevelManager
{
public:
	enum class Level
	{
		levelOne,
		levelTwo,
		levelThree,
		levelBoss,
		LevelEnd
	};

	LevelManager(Game& game, std::shared_ptr<Player> player);

	void DrawForeground() const;
	void DrawBackground() const;
	void DrawLocal() const;
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const;
	void Update(float elapsedSec) const;

	void MouseMoved(const Point2f& mousePos) const;
	void MouseClick(const SDL_MouseButtonEvent& e) const;
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);


	static std::shared_ptr<LevelBase> GetCurrentLevel();
	void SetCurrentLevel(Level level);
	Point2f GetLevelBeginPos() const;
	Rectf GetLevelBoundaries() const;

private:
	Game& m_Game;
	Rectf m_Boundaries;

	static std::shared_ptr<LevelBase> m_pCurrentLevel;
	std::shared_ptr<Player> m_pPlayer;

	template <typename T>
	void UpdateCurrentLevel();
};

template<typename T>
void LevelManager::UpdateCurrentLevel()
{
	m_pCurrentLevel.reset();
	m_pCurrentLevel = { std::make_shared<T>(*this,m_pPlayer) };
	m_Boundaries = m_pCurrentLevel->GetBoundaries();
	m_pCurrentLevel->PlayMusic();
}
