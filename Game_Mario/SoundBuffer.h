#pragma once
#include <dsound.h>
#include "dsutil.h"

class DXSoundBuffer
{
private:
	LPDIRECTSOUNDBUFFER _soundBuffer;
	LPDIRECTSOUND8 _pDS;
public:
	DXSoundBuffer(LPDIRECTSOUND8 pDS);
	bool LoadWaveToSoundBuffer(std::string wavFilename);
	LPDIRECTSOUNDBUFFER getSoundBuffer();
	void Play();
	void PlayLoop();
	void Stop();
	~DXSoundBuffer();
};

