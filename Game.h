#pragma once
#include "MenuManager.h"
#include "SoundManager.h"
#include "LevelManager.h"
#include "Camera.h"
#include "Player.h"

class Core;
class Game
{
public:
	enum class GameState
	{
		menu,
		game,
	};

	explicit Game(const Window& window, Core& core);
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	~Game();

	void Update( float elapsedSec );

	void Draw( ) const;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e );
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e );
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e );
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e );
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e );


	//extra Functions
	void FullScreenOn() const;
	void FullScreenOff() const;
	void VsyncOn() const;
	void VsyncOff() const;
	GameState m_GameState;

	static Point2f m_Cam;
private:
	// DATA MEMBERS
	const Window m_Window;
	Core& m_Core;
	SoundManager m_SoundManager;
	Camera m_Camera;

	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<MenuManager> m_pMenuManager;
	std::shared_ptr<LevelManager> m_pLevelManager;
	Point2f m_MousePosition;


	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( ) const;
	void DrawStates() const;
	void DrawLevels() const;
	void UpdateStates(float elapsedSec);

};