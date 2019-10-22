#include "stdafx.h"
#include "Game.h"
#include "Core.h"

Point2f Game::m_Cam{ 0,0 };

Game::Game(const Window& window, Core& core)
	:m_Window{ window }
	,m_Core{ core }
	,m_pPlayer{ std::make_shared<Player>(m_Camera) }
	,m_pLevelManager{std::make_shared<LevelManager>(*this,m_pPlayer)}
	,m_pMenuManager{ std::make_shared<MenuManager>(*this,m_pLevelManager)}
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	m_Camera.SetSize(Vector2f(m_Window.width, m_Window.height));	
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{
	UpdateStates(elapsedSec);
	m_Camera.Update({ m_pPlayer->GetShape().left + m_Cam.x,m_pPlayer->GetShape().bottom + m_Cam.y,m_pPlayer->GetShape().width,m_pPlayer->GetShape().height });
	m_Camera.SetBoundaries(Rectf{ m_pLevelManager->GetLevelBoundaries() });
}

void Game::Draw( ) const
{
	ClearBackground( );
	DrawStates();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	if (e.keysym.sym == SDLK_f)
	{
		m_Core.SetFullScreen();
	}
	if (e.keysym.sym == SDLK_ESCAPE)
	{
		m_GameState = Game::GameState::menu;
	}

	m_pLevelManager->ProcessKeyDownEvent(e);
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	m_MousePosition.x = float(e.x);
	m_MousePosition.y = m_Window.height - e.y;

	switch (m_GameState)
	{
	case Game::GameState::menu:
		m_pMenuManager->MouseMoved(m_MousePosition);
		break;
	case Game::GameState::game:
		m_pLevelManager->MouseMoved(m_MousePosition);
		m_pPlayer->MouseMoved(m_MousePosition);
		break;
	}
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	switch (m_GameState)
	{
	case Game::GameState::menu:
		m_pMenuManager->MouseClick(e);
		break;
	case Game::GameState::game:
		m_pLevelManager->MouseClick(e);
		m_pPlayer->MouseClick(e);
		break;
	}
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.4f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::FullScreenOn() const
{
	m_Core.SetFullScreenOn();
}

void Game::FullScreenOff() const
{
	m_Core.SetFullScreenOff();
}

void Game::VsyncOn() const
{
	m_Core.ToggleVsyncOn();
}

void Game::VsyncOff() const
{
	m_Core.ToggleVsyncOff();
}

void Game::DrawStates() const
{
	switch (m_GameState)
	{
	case Game::GameState::menu:
		m_pMenuManager->Draw();
		break;
	case Game::GameState::game:
		DrawLevels();
		m_pPlayer->DrawHud();
		m_pLevelManager->DrawLocal();
		break;
	default:
		break;
	}
}

void Game::DrawLevels() const
{
	glPushMatrix();
	glTranslatef(-m_Camera.GetPosition().x, -m_Camera.GetPosition().y, 0);
	m_pLevelManager->DrawBackground();
	m_pPlayer->Draw();
	m_pLevelManager->DrawForeground();
	glPopMatrix();
}

void Game::UpdateStates(float elapsedSec)
{
	switch (m_GameState)
	{
	case Game::GameState::menu:
		m_pMenuManager->Update(elapsedSec);
		break;
	case Game::GameState::game:
		m_pLevelManager->Update(elapsedSec);
		m_pPlayer->Update(elapsedSec, m_pLevelManager->GetCurrentLevel());


		break;
	}
}