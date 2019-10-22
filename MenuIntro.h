#pragma once
#include "MenuManager.h"
#include "LevelManager.h"
class Game;
class MenuIntro
{
public:
	MenuIntro(MenuManager& manager, std::shared_ptr<LevelManager> plevelManager);

	void Draw() const;
	void MouseClick(const SDL_MouseButtonEvent& e);
	void MouseMoved(const Point2f & mousePos);
	void Update(float elapsedSec);

private:
	const int m_ImgIntro = 3;
	Rectf m_ButtonRect;
	int m_CounterIMG{0};
	bool m_IsClicked{};
	float m_FadingOpacity{};
	Point2f m_MousePos;
	MenuManager& m_Manager;
	std::vector<std::unique_ptr<Texture>> m_IntroIMG;

	std::shared_ptr<LevelManager> m_pLevelManager;
};

