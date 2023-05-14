#include "SoundSystem.h"
#include <cassert>
#include <thread>
#include <mutex>
#include <sdl_mixer.h>
#include <future>

null_sound_system AudioServiceLocator::default_instance;
sound_system* AudioServiceLocator::ss_instance = &default_instance;

const int sound_system::MAX_CLIPS = 30;
int sound_system::m_Head = 0;
int sound_system::m_Tail = 0;
std::vector<AudioClip*> sound_system::m_Clips{};

AudioClip clips[]
{
	{int(PLAYER_DIES),"../Data/SoundEffects/LoseLifeFunny.wav"},
	{int(SCORE_UP),"../Data/SoundEffects/GainPoints.wav"}
};


//PIMPL
class sdl_sound_system::SDLImpl
{
	Mix_Chunk* m_ChunkPtrs[sizeof(clips) / sizeof(AudioClip)]{};
	std::mutex lock{};
	std::mutex sleepThreadMutex{};
	std::condition_variable readyCondVar{};
	bool ReadyFlag{ false };

	void Load(int ID);
	void HandleRequests();


public:
	SDLImpl() { Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096); };
	~SDLImpl() { Mix_CloseAudio(); };

	void Play(int ID, const int volume);
	void SetVolume(int ID, int volume);
	void Update();
};

void sdl_sound_system::SDLImpl::Load(int ID)
{
	m_ChunkPtrs[ID] = Mix_LoadWAV(clips[ID].GetPath().c_str());
}

void sdl_sound_system::SDLImpl::HandleRequests()
{
	while (m_Head != m_Tail)
	{
		//bool r = ReadyFlag;
		//std::unique_lock<std::mutex> ul(sleepThreadMutex);
		//readyCondVar.wait(ul, [r]() {return m_Head != m_Tail; });

		int ID = m_Clips[m_Head]->GetId();

		if (!m_ChunkPtrs[ID])
			Load(ID);

		SetVolume(ID, m_Clips[m_Head]->GetVolume());
		Mix_PlayChannel(-1, m_ChunkPtrs[ID], 0);


		std::lock_guard<std::mutex> lg(lock);
		m_Head = (m_Head + 1) % MAX_CLIPS;
	}
}

void sdl_sound_system::SDLImpl::Play(int ID, const int volume)
{
	assert((m_Tail + 1) % MAX_CLIPS != m_Head);

	for (int i = m_Head; i != m_Tail; i = (i + 1) % MAX_CLIPS)
	{
		if (m_Clips[i]->GetId() == ID)
			return;
	}

	sleepThreadMutex.lock();
	clips[ID].SetVolume(volume);
	m_Clips[m_Tail] = &clips[ID];
	m_Tail = (m_Tail + 1) % MAX_CLIPS;
	sleepThreadMutex.unlock();

	readyCondVar.notify_one();

}

void sdl_sound_system::SDLImpl::SetVolume(int ID, int volume)
{
	Mix_VolumeChunk(m_ChunkPtrs[ID], volume);
}

void sdl_sound_system::SDLImpl::Update()
{
	auto f = std::async(std::launch::async, &SDLImpl::HandleRequests, this);

}



sdl_sound_system::sdl_sound_system()
{
	m_Clips.resize(MAX_CLIPS);
	m_pImpl = new SDLImpl();
}

sdl_sound_system::~sdl_sound_system()
{
	delete m_pImpl;
	m_pImpl = nullptr;
}

void sdl_sound_system::Play(const int soundId, const int volume)
{
	m_pImpl->Play(soundId, volume);
}

void sdl_sound_system::Update()
{
	m_pImpl->Update();
}

