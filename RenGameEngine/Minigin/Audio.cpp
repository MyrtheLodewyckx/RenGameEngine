#include "MiniginPCH.h"
#include "Audio.h"
#include <cassert>
#include <thread>
#include <mutex>
#include <sdl_mixer.h>

null_sound_system AudioServiceLocator::default_instance;
sound_system* AudioServiceLocator::ss_instance = &default_instance;

AudioClip clips[]
{
	{int(PLAYER_DIES),"../Data/SoundEffects/LoseLifeFunny.wav"},
	{int(SCORE_UP),"../Data/SoundEffects/GainPoints.wav"}
};


//PIMPL
class sdl_sound_system::SDLImpl
{
	std::jthread m_Thread;
	Mix_Chunk* m_ChunkPtrs[sizeof(clips) / sizeof(AudioClip)]{};
	void LoadThread(int ID) 
	{ m_ChunkPtrs[ID] = Mix_LoadWAV(clips[ID].GetPath().c_str()); };

public:
	SDLImpl() {};
	~SDLImpl() {};

	bool IsLoaded(int ID);
	void Load(int ID);
	void Play(int ID);
	void SetVolume(int ID, int volume);

};

bool sdl_sound_system::SDLImpl::IsLoaded(int ID)
{
	return m_ChunkPtrs[ID] == nullptr ? false : true;
}

void sdl_sound_system::SDLImpl::Load(int ID)
{
	m_Thread = std::jthread(&SDLImpl::LoadThread,this, ID);
}

void sdl_sound_system::SDLImpl::Play(int ID)
{
	Mix_PlayChannel(-1, m_ChunkPtrs[ID], 0);
}

void sdl_sound_system::SDLImpl::SetVolume(int ID, int volume)
{
	Mix_VolumeChunk(m_ChunkPtrs[ID], volume);
}



sdl_sound_system::sdl_sound_system()
{
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
	m_pImpl = new SDLImpl();
}

sdl_sound_system::~sdl_sound_system()
{
	Mix_CloseAudio();
	delete m_pImpl;
	m_pImpl = nullptr;
}

void sdl_sound_system::Play(const int soundId, const int volume)
{
	assert((g_Tail + 1) % MAX_CLIPS != g_Head);

	for (int i = g_Head; i != g_Tail; i = (i + 1) % MAX_CLIPS)
	{
		if (g_Clips[i]->GetId() == soundId)
			return;
	}

	std::mutex lock;

	lock.lock();
	g_Clips[g_Tail] = &clips[soundId];
	lock.unlock();

	if (!m_pImpl->IsLoaded(g_Clips[g_Tail]->GetId()))
		m_pImpl->Load(g_Clips[g_Tail]->GetId());

	//Check again for multi-threading reasons
	if (m_pImpl->IsLoaded(g_Clips[g_Tail]->GetId()))
	m_pImpl->SetVolume(g_Clips[g_Tail]->GetId(), volume);

	lock.lock();
	g_Tail = (g_Tail + 1) % MAX_CLIPS;
	lock.unlock();
}

void sdl_sound_system::Update()
{
	std::mutex lock;

	// If there are no pending requests, do nothing.
	if (g_Head == g_Tail) return;

	//Check again for multi-threading reasons
	if (m_pImpl->IsLoaded(g_Clips[g_Head]->GetId()))
	{
		m_pImpl->Play(g_Clips[g_Head]->GetId());

		lock.lock();
		g_Head = (g_Head + 1) % MAX_CLIPS;
		lock.unlock();
	}
}

