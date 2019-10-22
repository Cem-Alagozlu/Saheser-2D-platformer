#include "stdafx.h"
#include "MenuQuit.h"
#include "MenuManager.h"
#include "Game.h"

MenuQuit::MenuQuit(MenuManager& manager)
	: m_Manager{ manager }
{
	m_Rects = { {130,150,235,75}, { 515,150,235,75 },{0,0,1280,720} };

	for (int i = 0; i <= m_Img; i++)
	{
		std::stringstream str;
		str << "Resources/Menu/Quit/0" << i << ".png";
		m_BackgroundIMG.push_back(std::make_unique<Texture>(str.str()));
	}
}

void MenuQuit::Draw() const
{
	m_BackgroundIMG[0]->Draw(m_Rects[2]);
	DrawButton();
}

void MenuQuit::DrawButton() const
{
	if (utils::IsPointInRect(m_MousePos,m_Rects[0]))
	{
		m_BackgroundIMG[1]->Draw(m_Rects[2]);
	}
	else if (utils::IsPointInRect(m_MousePos, m_Rects[1]))
	{
		m_BackgroundIMG[2]->Draw(m_Rects[2]);
	}
}

void MenuQuit::MouseMoved(const Point2f & mousePos)
{
	m_MousePos = mousePos;
}

void MenuQuit::MouseClick(const SDL_MouseButtonEvent & e) const
{
	if (utils::IsPointInRect(m_MousePos, m_Rects[0]))
	{
		SDL_Event quit;
		quit.type = SDL_QUIT;
		SDL_PushEvent(&quit);
	}
	else if (utils::IsPointInRect(m_MousePos, m_Rects[1]))
	{
		MenuManager::SetState(MenuManager::MenuState::menuMain);
	}
}
