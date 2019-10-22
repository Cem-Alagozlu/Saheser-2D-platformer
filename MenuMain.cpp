#include "stdafx.h"
#include "MenuMain.h"
#include "Game.h"


MenuMain::MenuMain(MenuManager& manager)
	: m_Manager{ manager }
{
	m_pMainMenuText.push_back(std::make_unique<Texture>("Project Saheser 1.0.0 - Cem Alagozlu ", "Resources/Fonts/Font00.ttf", 50, Color4f{ 1,1,1,1 }));
	m_ButtonRects = { { 50,590,350,80 },{ 50,480,350,80 },{ 50,360,350,80 }, {50,250,350,80},{0,0,1280,720 } };

	for (size_t i = 0; i <= m_Img; i++)
	{
		std::stringstream str;
		str << "Resources/Menu/Main/0" << i << ".png";
		m_BackgroundIMG.push_back(std::make_unique<Texture>(str.str()));
	}

}
 
void MenuMain::Draw() const
{
	m_BackgroundIMG[0]->Draw(m_ButtonRects[4]);
	DrawButton();

	m_pMainMenuText[0]->Draw(m_BuildText);
}

void MenuMain::MouseMoved(const Point2f & mousePos)
{
	m_MousePos = mousePos;
}

void MenuMain::MouseClick(const SDL_MouseButtonEvent & e) const
{
	if (utils::IsPointInRect(m_MousePos,m_ButtonRects[0]))
	{
		SoundManager::PlaySoundStream("Intro", true);
		m_Manager.SetState(MenuManager::MenuState::menuIntro);
	}
	else if (utils::IsPointInRect(m_MousePos, m_ButtonRects[1]))
	{
		m_Manager.SetState(MenuManager::MenuState::menuOption);
	}
	else if (utils::IsPointInRect(m_MousePos, m_ButtonRects[2]))
	{
		m_Manager.SetState(MenuManager::MenuState::menuExtra);
	}
	else if (utils::IsPointInRect(m_MousePos, m_ButtonRects[3]))
	{
		m_Manager.SetState(MenuManager::MenuState::menuQuit);
	}
}

void MenuMain::DrawButton() const
{
	if (utils::IsPointInRect(m_MousePos, m_ButtonRects[0]))
	{
		m_BackgroundIMG[1]->Draw(Rectf{ m_ButtonRects[4] });
	}

	else if (utils::IsPointInRect(m_MousePos, m_ButtonRects[1]))
	{
		m_BackgroundIMG[2]->Draw(Rectf{ m_ButtonRects[4] });
	}
	else if (utils::IsPointInRect(m_MousePos, m_ButtonRects[2]))
	{
		m_BackgroundIMG[3]->Draw(Rectf{ m_ButtonRects[4] });
	}
	else if (utils::IsPointInRect(m_MousePos, m_ButtonRects[3]))
	{
		m_BackgroundIMG[4]->Draw(Rectf{ m_ButtonRects[4] });
	}
}
