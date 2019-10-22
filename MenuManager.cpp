#include "stdafx.h"
#include "MenuManager.h"
#include "Game.h"
#include "MenuMain.h"
#include "MenuQuit.h"
#include "MenuOption.h"
#include "MenuExtra.h"
#include "MenuIntro.h"

MenuManager::MenuState MenuManager::m_MenuState{ MenuState::menuMain };

MenuManager::MenuManager(Game& game, std::shared_ptr<LevelManager> plevelManager)
	: m_Game{game}
	, m_pMenuMain{std::make_shared<MenuMain>(*this)}
	, m_pMenuQuit{std::make_shared<MenuQuit>(*this)}
	, m_pMenuOption{ std::make_shared<MenuOption>(*this) }
	, m_pMenuExtra{std::make_shared<MenuExtra>(*this)}
	, m_pMenuIntro{ std::make_shared<MenuIntro>(*this,plevelManager) }
{
}

void MenuManager::Draw() const
{
	switch (m_MenuState)
	{
	case MenuManager::MenuState::menuMain:
		m_pMenuMain->Draw();
		break;
	case MenuManager::MenuState::menuQuit:
		m_pMenuQuit->Draw();
			break;
	case MenuManager::MenuState::menuOption:
		m_pMenuOption->Draw();
		break;
	case MenuManager::MenuState::menuExtra:
		m_pMenuExtra->Draw();
		break;
	case MenuManager::MenuState::menuIntro:
		m_pMenuIntro->Draw();
		break;
	}
}

void MenuManager::Update(float elapsedSec)
{
	switch (m_MenuState)
	{
	case MenuManager::MenuState::menuOption:
		m_pMenuOption->Update(elapsedSec);
		break;
	case MenuManager::MenuState::menuIntro:
		m_pMenuIntro->Update(elapsedSec);
		break;
	}
}

void MenuManager::MouseMoved(const Point2f& mousePos) const
{
	switch (m_MenuState)
	{
	case MenuManager::MenuState::menuMain:
		m_pMenuMain->MouseMoved(mousePos);
		break;
	case MenuManager::MenuState::menuQuit:
		m_pMenuQuit->MouseMoved(mousePos);
			break;
	case MenuManager::MenuState::menuOption:
		m_pMenuOption->MouseMoved(mousePos);
		break;
	case MenuManager::MenuState::menuExtra:
		m_pMenuExtra->MouseMoved(mousePos);
		break;
	case MenuManager::MenuState::menuIntro:
		m_pMenuIntro->MouseMoved(mousePos);
		break;
	}
}

void MenuManager::MouseClick(const SDL_MouseButtonEvent& e)
{
	switch (m_MenuState)
	{
	case MenuManager::MenuState::menuMain:
		m_pMenuMain->MouseClick(e);
		break;
	case MenuManager::MenuState::menuQuit:
		m_pMenuQuit->MouseClick(e);
		break;
	case MenuManager::MenuState::menuOption:
		m_pMenuOption->MouseClick(e);
		break;
	case MenuManager::MenuState::menuExtra:
		m_pMenuExtra->MouseClick(e);
		break;
	case MenuManager::MenuState::menuIntro:
		m_pMenuIntro->MouseClick(e);
		break;
	}
}



void MenuManager::FullScreenOn() const
{
	m_Game.FullScreenOn();
}

void MenuManager::FullScreenOff() const
{
	m_Game.FullScreenOff();
}

void MenuManager::VsyncOn() const
{
	m_Game.VsyncOn();
}

void MenuManager::VsyncOff() const
{
	m_Game.VsyncOff();
}

void MenuManager::StartGame()
{
	m_Game.m_GameState = Game::GameState::game;
}


void MenuManager::SetState(MenuState state)
{
	m_MenuState = state;
}
