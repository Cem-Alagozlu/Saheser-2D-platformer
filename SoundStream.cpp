#include "stdafx.h"
#include "SoundStream.h"

SoundStream::SoundStream(std::string path)
	: m_pMixMusic{std::shared_ptr<Mix_Music>(Mix_LoadMUS(path.c_str()), [](Mix_Music* track) { Mix_FreeMusic(track); })}
{
	if (m_pMixMusic == nullptr)
	{
		std::string errorMsg = "SoundStream: Failed to load " + path + ",\nSDL_mixer Error: " + Mix_GetError();
		//std::cerr << errorMsg;

		throw std::runtime_error(errorMsg);
	}
}

SoundStream::~SoundStream()
{
}

bool SoundStream::IsLoaded() const
{
	return m_pMixMusic != nullptr;
}

bool SoundStream::Play(bool repeat) const
{
	if (m_pMixMusic != nullptr)
	{
		int result{Mix_PlayMusic(m_pMixMusic.get(), repeat ? -1 : 1)};
		return result == 0 ? true : false;
	}
	return false;
}

void SoundStream::Stop()
{
	Mix_HaltMusic();
}

void SoundStream::Pause()
{
	Mix_PauseMusic();
}

void SoundStream::Resume()
{
	Mix_ResumeMusic();
}

int SoundStream::GetVolume()
{
	return Mix_VolumeMusic(-1);
}

bool SoundStream::IsPlaying()
{
	return Mix_PlayingMusic() == 0 ? false : true;
}

void SoundStream::SetVolume(int value)
{
	Mix_VolumeMusic(value);
}
