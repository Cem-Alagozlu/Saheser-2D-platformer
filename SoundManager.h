#pragma once
#include "SoundEffect.h"
#include "SoundStream.h"
#include <map>


class SoundManager
{
public:
	SoundManager();

	static void InitSoundStreams();
	static void InitSoundEffects();

	// SOUND STREAM
	static void PlaySoundStream(const std::string& name, bool repeat);
	static void VolumeUpSoundStream();
	static void VolumeDownSoundStream();
	static int GetVolumeSoundStream();

	// SOUND-EFFECTS
	static void PlaySoundEffect(const std::string& name, bool repeat, bool isPlaying);
	static void PlaySoundEffectTraps(const Vector2f& player, const Vector2f& trapPos, const std::string& name, bool repeat, bool isPlaying);
	static void VolumeUpSoundEffect();
	static void VolumeDownSoundEffect();
	static int GetVolumeSoundEffect();
	static void StopSoundEffect(const std::string& name);
	static void Update(const Vector2f& player, const Vector2f& trapPos, const std::string& name);

	// EXTRA
	static bool IsPlaying(std::string name);

private:
	static std::map<std::string, SoundStream> m_SoundStreamMap;
	static std::map<std::string, SoundEffect> m_SoundEffectMap;
};
