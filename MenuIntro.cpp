#include "stdafx.h"
#include "MenuIntro.h"
#include "LevelBase.h"

MenuIntro::MenuIntro(MenuManager & manager, std::shared_ptr<LevelManager> plevelManager)
	: m_Manager{ manager }
	, m_pLevelManager{ plevelManager }
{

	for (size_t i = 0; i <= m_ImgIntro; i++)
	{
		std::stringstream str;
		str << "Resources/Menu/Intro/0" << i << ".png";
		m_IntroIMG.push_back(std::make_unique<Texture>(str.str()));
	}
	m_ButtonRect = { 410,285,480,155 };

	
}

void MenuIntro::Draw() const
{
	m_IntroIMG[m_CounterIMG]->Draw({ 0,0 }, { 0,0,1280,720 });
	if (m_CounterIMG == 2 && utils::IsPointInRect(m_MousePos,m_ButtonRect))
	{
		m_IntroIMG[3]->Draw({ 0,0 }, { 0,0,1280,720 });
	}

	if (m_IsClicked && m_CounterIMG == 2)
	{
		utils::SetColor({ 1.0f,1.0f,1.0f,m_FadingOpacity });
		utils::FillRect({ 0,0,1280,720 });
	}
}

void MenuIntro::MouseClick(const SDL_MouseButtonEvent & e) 
{
	if (m_CounterIMG < 2)
	{
		++m_CounterIMG;
	}
	if (utils::IsPointInRect(m_MousePos, m_ButtonRect) && m_CounterIMG == 2 && m_FadingOpacity <= 0)
	{
		SoundManager::PlaySoundEffect("OkieDokie",false,true);
		m_IsClicked = true;
	}
	if (m_FadingOpacity >= 1.0f)
	{
		m_pLevelManager->GetCurrentLevel()->PlayMusic();
		m_Manager.StartGame();
		m_IsClicked = false;
		m_FadingOpacity = 0.0f;
		m_Manager.SetState(MenuManager::MenuState::menuMain);
	}
}

void MenuIntro::MouseMoved(const Point2f & mousePos)
{
	m_MousePos = mousePos;

}

void MenuIntro::Update(float elapsedSec)
{
	if (m_IsClicked)
	{
		m_FadingOpacity += elapsedSec / 2;
	}
}

