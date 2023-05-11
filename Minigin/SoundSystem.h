#pragma once
#pragma once
#include <string>
#include <vector>

enum SoundId
{
	PLAYER_DIES,
	SCORE_UP
};

class AudioClip
{
	int m_Id;
	int m_Volume;
	std::string m_Path;
public:

	AudioClip(int id, const std::string& path) :m_Path{ path }, m_Id{ id } {}
	~AudioClip() {}

	void SetVolume(int volume) { m_Volume = volume; }
	int GetVolume() { return m_Volume; }
	int GetId() { return (int)m_Id; }
	std::string GetPath() { return m_Path; }
};


class sound_system
{
protected:
	static const int MAX_CLIPS;
	static int m_Head;
	static int m_Tail;
	static std::vector<AudioClip*> m_Clips;

public:
	virtual void Play(const int, const int) = 0;
	virtual void Update() = 0;
};

class null_sound_system : public sound_system
{

public:
	virtual void Play(const int, const int) override {}
	virtual void Update() override {}
};

class sdl_sound_system : public sound_system
{
	class SDLImpl;
	SDLImpl* m_pImpl{};

public:
	sdl_sound_system();
	~sdl_sound_system();
	virtual void Play(const int soundId, const int volume) override;
	virtual void Update() override;
};

class AudioServiceLocator
{
	static sound_system* ss_instance;
	static null_sound_system default_instance;

public:
	AudioServiceLocator() = delete;
	~AudioServiceLocator() = delete;
	AudioServiceLocator(const AudioServiceLocator& other) = delete;
	AudioServiceLocator(AudioServiceLocator&& other) = delete;
	AudioServiceLocator& operator=(const AudioServiceLocator& other) = delete;
	AudioServiceLocator& operator=(AudioServiceLocator&& other) = delete;
	static sound_system& get_sound_system()
	{
		if (ss_instance)
			return *ss_instance;

		else return default_instance;
	}
	static void register_sound_system(sound_system* ss)
	{
		ss_instance = ss;
	}
	static void Update() { ss_instance->Update(); }
};

