#include "stdafx.h"
#include "TrapSpikeFall.h"


TrapSpikeFall::TrapSpikeFall(const Point2f& position, float angle, float scale, float dropTime, bool flipped)
	: Trap{position,"Resources/Sprites/Environment/Traps/trap01.png",angle,scale,"Resources/Sprites/Environment/Traps/trap01-1.svg"}
	  , m_Gravity{0.0f,-9.81f}
	  , m_GravityInverse{0.0f,9.81f}
	  , m_DropTime{dropTime}
	  , m_TextureSpike{"Resources/Sprites/Environment/Traps/trap01-1.png"}
	  , m_TextureSpikeInverse{"Resources/Sprites/Environment/Traps/trap01Inverse.png"}
	  , m_SpikePos{position}
	  , m_IsFlipped{flipped}
{
}

void TrapSpikeFall::Draw() const
{
	//draws the trap
	if (m_IsFlipped == false)
	{
		m_Texure.Draw(m_Pos);
		m_TextureSpike.Draw(m_SpikePos);
	}
	if (m_IsFlipped == true)
	{
		m_TextureSpikeInverse.Draw(m_SpikePos);
	}
}

void TrapSpikeFall::Update(float elapsedSec, const Vector2f& player)
{
	++m_AccumSec;

	// checks if the trap is flipped
	// if not
	// spikes will go from up to down
	if (m_IsFlipped == false)
	{
		if (m_AccumSec >= m_DropTime)
		{
			m_SpikePos.y += m_Gravity.y;
		}
		if (m_SpikePos.y <= -1000.0f)
		{
			m_SpikePos.y = m_Pos.y - m_TextureSpike.GetHeight() + 2.0f;
			m_AccumSec = 0;
		}
	}

	// checks if the trap is flipped
	// if not
	// spikes will go from down to up
	if (m_IsFlipped == true)
	{
		if (m_AccumSec >= m_DropTime)
		{
			m_SpikePos.y += m_GravityInverse.y;
		}
		if (m_SpikePos.y >= 2000)
		{
			m_SpikePos.y = m_Pos.y;
			m_AccumSec = 0;
		}
	}
}


bool TrapSpikeFall::SpikeCollision(const Rectf& player) const
{
	//checks if there is collision between spikes and player
	return utils::IsOverlapping(Rectf(m_SpikePos.x, m_SpikePos.y, m_TextureSpike.GetWidth(), m_TextureSpike.GetHeight()), player);
}
