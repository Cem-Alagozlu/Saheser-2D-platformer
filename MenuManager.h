#pragma once
#include "stdafx.h"
#include "Texture.h"
#include "LevelManager.h"

class Game;
class MenuMain;
class MenuQuit;
class MenuOption;
class MenuExtra;
class MenuIntro;

class MenuManager
{
public:
	enum class MenuState
	{
		menuMain,
		menuQuit,
		menuOption,
		menuExtra,
		menuIntro
	};


	explicit MenuManager(Game& game, std::shared_ptr<LevelManager> plevelManager);

	void Draw() const;
	void Update(float elapsedSec);

	void MouseMoved(const Point2f& mousePos) const;
	void MouseClick(const SDL_MouseButtonEvent& e);
	

	void FullScreenOn() const;
	void FullScreenOff() const;
	void VsyncOn() const;
	void VsyncOff() const;
	void StartGame();
	static void SetState(MenuState state);

private:
	Game& m_Game;
	static MenuState m_MenuState;

	std::shared_ptr<MenuMain> m_pMenuMain;
	std::shared_ptr<MenuQuit> m_pMenuQuit;
	std::shared_ptr<MenuOption> m_pMenuOption;
	std::shared_ptr<MenuExtra> m_pMenuExtra;
	std::shared_ptr<MenuIntro> m_pMenuIntro;

};
