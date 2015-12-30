#pragma once

#include "SoundBuffer.h"
#include <map>
#include "Global.h"


class SoundManagement
{
private:
	map<EOSound, DXSoundBuffer*> _ListSound;
	long _volume;
	bool _mute;
	LPDIRECTSOUND8 _pDS;

	static SoundManagement _instance;
	SoundManagement() { _volume = 0; _mute = false; };
public:
	EOSound enumSound;
	static SoundManagement* GetInstance()
	{
		return &_instance;
	};
	bool Init(HWND hWnd);
	void Add(LPDIRECTSOUND8, EOSound, std::string);
	void AddAll();
	DXSoundBuffer* Get(EOSound);
	void SetVolume(long);
	long GetVolume();
	void SetMute(bool);
	bool GetMute();
	void VolumeUp();
	void VolumeDown();
};

