#pragma once
#include <dsound.h>
#include "dsutil.h"

class GameSound
{
private:
	LPDIRECTSOUNDBUFFER _soundBuffer;
	LPDIRECTSOUND8 _pDS;
public:
	GameSound();
	bool InitDirectSound(HWND hwnd);
	bool LoadWaveToSoundBuffer(std::string wavFilename);
	LPDIRECTSOUNDBUFFER getSoundBuffer();
	void Play();
	void PlayLoop();
	void Stop();
	void ShutdownDirectSound(void);
	~GameSound();

};

