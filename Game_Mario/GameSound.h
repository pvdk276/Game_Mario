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

	//Khoi tao direct sound
	bool InitDirectSound(HWND hwnd);

	//Load file vao buffer
	bool LoadWaveToSoundBuffer(std::string wavFilename);

	//lay buffer sau khi da load file sound de chuan bi play
	LPDIRECTSOUNDBUFFER getSoundBuffer();

	void Play();
	void PlayLoop();
	void Stop();

	//Huy bo doi tuong buffer
	void ShutdownDirectBuffer(void);

	//Huy bo doi tuong direct sound
	void ShutdownDirectSound(void);
	~GameSound();

};

