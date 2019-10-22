#pragma once
#include "MenuManager.h"

class Game;

class MenuQuit
{
public:
	MenuQuit(MenuManager& manager);

	void Draw() const;
	void DrawButton() const;
	void MouseMoved(const Point2f& mousePos);
	void MouseClick(const SDL_MouseButtonEvent& e)const;

private:
	Point2f m_MousePos;
	MenuManager& m_Manager;
	const int m_Img = 2;

	std::vector<Rectf> m_Rects;
	std::vector<std::unique_ptr<Texture>> m_BackgroundIMG;
};

