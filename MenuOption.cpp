#include "stdafx.h"
#include "MenuOption.h"
#include "MenuManager.h"
#include "SoundManager.h"
#include "Game.h"

MenuOption::MenuOption(MenuManager& manager)
	: m_Manager{ manager }
{
	Initialize();
}


void MenuOption::Draw() const
{

	m_BackgroundIMG[0]->Draw(m_Rects[9]);
	DrawButtons();

	// volume music counter
	if (m_VolumeCounter >= 10)
	{
		m_VolumeCounterStreamCounter->Draw({ 215,325,0,0 });
	}
	if (m_VolumeCounter == 0)
	{
		m_VolumeZero->Draw({ 218,325,0,0 });
	}


	//SFX
	// volume music counter
	if (m_VolumeCounterSFX >= 10)
	{
		m_VolumeCounterSFXcounter->Draw({ 215,90,0,0 });
	}

	if (m_VolumeCounterSFX == 0)
	{
		m_VolumeZero->Draw({ 218,90,0,0 });
	}
}


void MenuOption::Update(float elapsedSec)
{
	m_VolumeCounter = SoundManager::GetVolumeSoundStream();
	m_VolumeCounterSFX = SoundManager::GetVolumeSoundEffect();


	if (m_VolumeCounterPrevious != m_VolumeCounter)
	{
		m_VolumeCounterStreamCounter = std::make_unique<Texture>(std::to_string(m_VolumeCounter), "Resources/Fonts/Font00.ttf", 100, Color4f(1, 1, 1, 1));
	}

	if (m_VolumeCounterPreviousSFX != m_VolumeCounterSFX)
	{
		m_VolumeCounterSFXcounter = std::make_unique<Texture>(std::to_string(m_VolumeCounterSFX), "Resources/Fonts/Font00.ttf", 100, Color4f(1, 1, 1, 1));
	}
}

void MenuOption::MouseMoved(const Point2f & mousePos)
{
	m_MousePos = mousePos;
}

void MenuOption::MouseClick(const SDL_MouseButtonEvent & e) const
{
		
	if (utils::IsPointInRect(m_MousePos, m_Rects[0]))
	{
		m_Manager.SetState(MenuManager::MenuState::menuMain);
	}
	if (utils::IsPointInRect(m_MousePos, m_Rects[1]))
	{
		SoundManager::VolumeDownSoundStream(); // - music
	}
	if (utils::IsPointInRect(m_MousePos, m_Rects[2]))
	{
		SoundManager::VolumeUpSoundStream(); // + music
	}
	if (utils::IsPointInRect(m_MousePos, m_Rects[3]))
	{
		SoundManager::VolumeDownSoundEffect(); // - sfx
	}
	if (utils::IsPointInRect(m_MousePos, m_Rects[4]))
	{
		SoundManager::VolumeUpSoundEffect(); // + sfx
	}
	if (utils::IsPointInRect(m_MousePos, m_Rects[5]))
	{
		m_Manager.FullScreenOn();
	}
	if (utils::IsPointInRect(m_MousePos, m_Rects[6]))
	{
		m_Manager.FullScreenOff();
	}
}

void MenuOption::Initialize()
{
	for (size_t i = 0; i <= 9; i++)
	{
		std::stringstream str;
		str << "Resources/Menu/Options/0" << i << ".png";
		m_BackgroundIMG.push_back(std::make_unique<Texture>(str.str()));
	}


	m_Rects.push_back({ 960,600,270,70}); // Back     
	m_Rects.push_back({ 120,270,60,55 }); // Music -  
	m_Rects.push_back({ 120,345,60,55 }); // Music +  
	m_Rects.push_back({ 120,35,60,55  }); // SFX   -  
	m_Rects.push_back({ 120,105,60,55 }); // SFX   +  
	m_Rects.push_back({ 640,350,185,50 }); // full-on 
	m_Rects.push_back({ 640,270,185,50 }); // full-off 
	m_Rects.push_back({ 640,115,185,50 }); // vsync-on 
	m_Rects.push_back({ 640,35,185,50 }); // vsync-off 
	m_Rects.push_back({ 0,0,1280,720 }); // base-rect


	m_VolumeZero = std::make_unique<Texture>("0", "Resources/Fonts/Font00.ttf", 100, Color4f(1, 1, 1, 1));
}

void MenuOption::DrawButtons() const
{

	if (utils::IsPointInRect(m_MousePos,m_Rects[0]))
	{
		m_BackgroundIMG[1]->Draw(m_Rects[9]);
	}
	else if (utils::IsPointInRect(m_MousePos, m_Rects[1]))
	{
		m_BackgroundIMG[3]->Draw(m_Rects[9]);
	}
	else if (utils::IsPointInRect(m_MousePos, m_Rects[2]))
	{
		m_BackgroundIMG[2]->Draw(m_Rects[9]);
	}
	else if (utils::IsPointInRect(m_MousePos, m_Rects[3]))
	{
		m_BackgroundIMG[5]->Draw(m_Rects[9]);
	}
	else if (utils::IsPointInRect(m_MousePos, m_Rects[4]))
	{
		m_BackgroundIMG[4]->Draw(m_Rects[9]);
	}
	else if (utils::IsPointInRect(m_MousePos, m_Rects[5]))
	{
		m_BackgroundIMG[6]->Draw(m_Rects[9]);
	}
	else if (utils::IsPointInRect(m_MousePos, m_Rects[6]))
	{
		m_BackgroundIMG[7]->Draw(m_Rects[9]);
	}
	else if (utils::IsPointInRect(m_MousePos, m_Rects[7]))
	{
		m_BackgroundIMG[8]->Draw(m_Rects[9]);
	}
	else if (utils::IsPointInRect(m_MousePos, m_Rects[8]))
	{
		m_BackgroundIMG[9]->Draw(m_Rects[9]);
	}
}
