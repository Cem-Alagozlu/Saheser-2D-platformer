#pragma once
#include "MenuManager.h"

class Game;

class MenuMain
{
public:
	MenuMain(MenuManager& manager);

	void Draw() const;
	void DrawButton() const;
	void MouseMoved(const Point2f& mousePos);
	void MouseClick(const SDL_MouseButtonEvent& e)const;

private:
	Point2f m_MousePos;
	MenuManager& m_Manager;

	const int m_Img = 4;
	const Point2f m_BuildText = { 350,4 };
	
	std::vector<Rectf> m_ButtonRects;
	std::vector<std::unique_ptr<Texture>> m_BackgroundIMG;
	std::vector<std::unique_ptr<Texture>> m_pMainMenuText;
};

