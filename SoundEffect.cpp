#include "stdafx.h"
#include "SoundEffect.h"
#include <iostream>

SoundEffect::SoundEffect(std::string path)
	: m_pMixChunk{std::shared_ptr<Mix_Chunk>(Mix_LoadWAV(path.c_str()), [](Mix_Chunk* track) { Mix_FreeChunk(track); })}
	  , m_Channel(0)
{
	if (m_pMixChunk == nullptr)
	{
		std::string errorMsg = "SoundEffect: Failed to load " + path + ",\nSDL_mixer Error: " + Mix_GetError();
		//std::cerr << errorMsg;

		throw std::runtime_error(errorMsg);
	}
}

SoundEffect::~SoundEffect()
{
}

bool SoundEffect::IsLoaded() const
{
	return m_pMixChunk != nullptr;
}

bool SoundEffect::Play(int loops)
{
	// Don't save the channel as a data member, 
	// because when it stops playing the channel becomes free
	// and available for usage by other effects
	if (m_pMixChunk != nullptr)
	{
		m_Channel = {Mix_PlayChannel( -1, m_pMixChunk.get(), loops )};
		return m_Channel == -1 ? false : true;
	}
	return false;
}

void SoundEffect::PlaySoundEffectTraps(const Vector2f& player, const Vector2f& trapPos)
{
	Vector2f newPos = player - trapPos;
	float angle = newPos.AngleWith({0,1});

	float distance = newPos.Length() / 8.0f;

	if (distance >= 255)
	{
		distance = 255;
	}

	m_Channel = Mix_PlayChannel(-1, m_pMixChunk.get(), 0);
	Mix_SetPosition(m_Channel, int(angle), int(distance));
}

void SoundEffect::Update(const Vector2f& player, const Vector2f& trapPos) const
{
	Vector2f newPos = player - trapPos;
	float angle = newPos.AngleWith({0,1});

	float distance = newPos.Length() / 8.0f;

	if (distance >= 255)
	{
		distance = 255;
	}

	Mix_SetPosition(m_Channel, int(angle), int(distance));

	std::cout << distance << std::endl;
}

void SoundEffect::SetVolume(int value) const
{
	if (m_pMixChunk != nullptr)
	{
		Mix_VolumeChunk(m_pMixChunk.get(), value);
	}
}

int SoundEffect::GetVolume() const
{
	if (m_pMixChunk != nullptr)
	{
		return Mix_VolumeChunk(m_pMixChunk.get(), -1);
	}
	return -1;
}

void SoundEffect::StopAll()
{
	Mix_HaltChannel(-1);
}

void SoundEffect::Stop() const
{
	for (int i = 0; i < Mix_AllocateChannels(-1); i++)
	{
		if (Mix_GetChunk(i) == m_pMixChunk.get())
		{
			Mix_HaltChannel(i);
			return;
		}
	}
}

void SoundEffect::PauseAll()
{
	Mix_Pause(-1);
}

void SoundEffect::ResumeAll()
{
	Mix_Resume(-1);
}

bool SoundEffect::IsPlaying(int channel) const
{
	return Mix_GetChunk(channel) == m_pMixChunk.get() && Mix_Playing(channel);
}
