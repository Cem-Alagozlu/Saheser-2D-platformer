#pragma once
#include "MenuManager.h"

class Game;
class MenuExtra
{
public:
	MenuExtra(MenuManager& manager);

	void Draw() const;
	void MouseMoved(const Point2f& mousePos);
	void MouseClick(const SDL_MouseButtonEvent& e)const;

private:
	Point2f m_MousePos;
	MenuManager& m_Manager;

	std::unique_ptr<Texture> m_pBackgroundIMG;
};



