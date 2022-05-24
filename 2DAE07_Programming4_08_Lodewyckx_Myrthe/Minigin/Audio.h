#pragma once
#include <sdl_mixer.h>
#include <string>

enum SoundId
{
	PLAYER_DIES,
	SCORE_UP
};

class AudioClip 
{
	int m_Id;
	std::string m_Path;
public:

	AudioClip(int id, const std::string& path) :m_Path{ path }, m_Id{ id } {}
	~AudioClip() {}

	int GetId() { return (int)m_Id; }
	std::string GetPath() { return m_Path; }
};


static const int MAX_CLIPS = 30;
static int g_Head{ 0 };
static int g_Tail{ 0 };
static AudioClip* g_Clips[MAX_CLIPS];


class sound_system
{
public:
	virtual ~sound_system() = default;
	virtual void Play(const int, const int) { std::cout << "sound error"; }
	virtual void Update() {}
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

class ServiceLocator
{
	static sound_system* ss_instance;
	static null_sound_system default_instance;

public:
	ServiceLocator() = default;
	~ServiceLocator() { delete ss_instance; ss_instance = nullptr; }
	ServiceLocator(const ServiceLocator& other) = delete;
	ServiceLocator(ServiceLocator&& other) = delete;
	ServiceLocator& operator=(const ServiceLocator& other) = delete;
	ServiceLocator& operator=(ServiceLocator&& other) = delete;
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

