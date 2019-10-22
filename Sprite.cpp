#include "stdafx.h"
#include "Sprite.h"


Sprite::Sprite(const std::string& texture, float sheetLeft, float sheetTop, float sheetWidth, float sheetHeight, int cols, int rows, int framesPerSec)
	: m_Texture{ texture }
	, m_SpriteSheetLeft{ sheetLeft }
	, m_SpriteSheetTop{ sheetTop }
	, m_SpriteSheetWidth{ sheetWidth }
	, m_SpriteSheetHeight{ sheetHeight }
	, m_Cols{ cols }
	, m_Rows{ rows }
	, m_FramesPerSec{ framesPerSec }
{
	m_SrcRect.width = m_SpriteSheetWidth / m_Cols;
	m_SrcRect.height = m_SpriteSheetHeight / m_Rows;

	UpdateSourceRect();

	m_DestRect.width = m_SpriteSheetWidth / m_Cols;
	m_DestRect.height = m_SpriteSheetHeight / m_Rows;

	m_FrameTime = 1.0f / m_FramesPerSec;
}


void Sprite::Update(float elapsedSec)
{
	m_AccuSec += elapsedSec;
	if (m_AccuSec > m_FrameTime && m_IsLocked == false)
	{
		++m_CurFrame %= m_Cols * m_Rows;
		m_AccuSec -= m_FrameTime;
		UpdateSourceRect();
	}
}

void Sprite::Draw(bool flipped) const
{
	m_Texture.Draw(m_DestRect, m_SrcRect, flipped);
}

float Sprite::GetWidth() const
{
	return m_Texture.GetWidth() / m_Cols;
}

float Sprite::GetHeight() const
{
	return m_Texture.GetHeight() / m_Rows;
}

bool Sprite::HasEnded() const
{
	if ((m_CurFrame + 1) / m_Cols == 1)
	{
		return true;
	}
	return false;
}

void Sprite::Lock()
{
	m_IsLocked = true;
}

void Sprite::Unlock()
{
	m_IsLocked = false;
	m_CurFrame = 0;
	m_AccuSec = 0.0f;
}

void Sprite::UpdateSourceRect()
{
	m_SrcRect.left = m_SpriteSheetLeft + m_CurFrame % m_Cols * m_SrcRect.width;
	m_SrcRect.bottom = m_SpriteSheetTop + (m_CurFrame / m_Cols + 1) * m_SrcRect.height;
}
