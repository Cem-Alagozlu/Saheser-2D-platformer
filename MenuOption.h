#pragma once
#include "MenuManager.h"

class Game;

class MenuOption
{
public:
	MenuOption(MenuManager& manager);

	void Draw() const;
	
	void DrawButtons()const;
	void Update(float elapsedSec);
	void MouseMoved(const Point2f& mousePos);
	void MouseClick(const SDL_MouseButtonEvent& e)const;

private:
	Point2f m_MousePos;
	MenuManager& m_Manager;
	std::vector<Rectf> m_Rects;

	std::vector<std::unique_ptr<Texture>> m_BackgroundIMG;
	std::unique_ptr<Texture> m_VolumeCounterStreamCounter;
	std::unique_ptr<Texture> m_VolumeCounterSFXcounter;
	std::unique_ptr<Texture> m_VolumeZero;


	int m_VolumeCounter{};
	int m_VolumeCounterPrevious{};

	int m_VolumeCounterSFX{};
	int m_VolumeCounterPreviousSFX{};

	void Initialize();

};

