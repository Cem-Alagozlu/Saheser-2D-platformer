#pragma once

class SoundStream
{
public:
	explicit SoundStream(std::string path);
	~SoundStream();
	SoundStream(const SoundStream& other) = default;
	SoundStream& operator=(const SoundStream& rhs) = default;

	bool IsLoaded() const;
	bool Play(bool repeat) const;
	static void Stop();
	static void Pause();
	static void Resume();
	static void SetVolume(int value);
	static int GetVolume();
	static bool IsPlaying();

private:
	std::shared_ptr<Mix_Music> m_pMixMusic;
};
