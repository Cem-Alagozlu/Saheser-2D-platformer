#pragma once
#include "Texture.h"

class Sprite
{
public:
	explicit Sprite(const std::string& texture, float sheetLeft, float sheetTop, float sheetWidth, float sheetHeight, int cols, int rows, int framesPerSec);

	void Update(float elapsedSec);
	void Draw(bool flipped = false) const;
	float GetWidth() const;
	float GetHeight() const;
	bool HasEnded() const;
	void Lock();
	void Unlock();

private:
	const Texture m_Texture;
	const float m_SpriteSheetLeft;
	const float m_SpriteSheetTop;
	const float m_SpriteSheetWidth;
	const float m_SpriteSheetHeight;
	const int m_Cols;
	const int m_Rows;
	int m_FramesPerSec;
	float m_FrameTime;
	float m_Scale;

	float m_AccuSec{};
	int m_CurFrame{};
	Rectf m_SrcRect{};
	Rectf m_DestRect{};
	bool m_IsLocked{ false };

	void UpdateSourceRect();
};
