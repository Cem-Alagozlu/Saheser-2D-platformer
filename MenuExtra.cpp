#include "stdafx.h"
#include "MenuExtra.h"




MenuExtra::MenuExtra(MenuManager & manager)
	:m_Manager{manager}
{
	m_pBackgroundIMG = (std::make_unique<Texture>("Resources/Menu/Extra/00.png"));

}

void MenuExtra::Draw() const
{
	m_pBackgroundIMG->Draw(Rectf(0, 0, 1280, 720));
}

void MenuExtra::MouseMoved(const Point2f & mousePos)
{
	m_MousePos = mousePos;
}

void MenuExtra::MouseClick(const SDL_MouseButtonEvent & e) const
{
	if (utils::IsPointInRect(m_MousePos, Rectf(960, 600, 270, 70)))
	{
		m_Manager.SetState(MenuManager::MenuState::menuMain);
	}
}


