#include "SoundManagement.h"



SoundManagement SoundManagement::_instance = SoundManagement();

void SoundManagement::AddAll()
{
	this->Add(_pDS, EOSound::BACKMUSIC_SOUND, "Resources/Sounds/BackMusic.wav");
	this->Add(_pDS, EOSound::BONUSAPPEAR_SOUND, "Resources/Sounds/BonusAppear.wav");
	this->Add(_pDS, EOSound::BRICKBROKEN_SOUND, "Resources/Sounds/BrickBroken.wav");
	this->Add(_pDS, EOSound::BULLETBREAK_SOUND, "Resources/Sounds/BulletBreak.wav");
	this->Add(_pDS, EOSound::DYING_SOUND, "Resources/Sounds/Dying.wav");
	this->Add(_pDS, EOSound::ENEMYDIE_SOUND, "Resources/Sounds/EnemyDie.wav");
	this->Add(_pDS, EOSound::EXTRALIFE_SOUND, "Resources/Sounds/ExtraLife.wav");
	this->Add(_pDS, EOSound::FINISHMAP_SOUND, "Resources/Sounds/FinishMap.wav");
	this->Add(_pDS, EOSound::GAMEOVER_SOUND, "Resources/Sounds/GameOver.wav");
	this->Add(_pDS, EOSound::GETCOIN_SOUND, "Resources/Sounds/GetCoin.wav");
	this->Add(_pDS, EOSound::HEADSHOOT_SOUND, "Resources/Sounds/HeadShoot.wav");
	this->Add(_pDS, EOSound::JUMP_SOUND, "Resources/Sounds/Jump.wav");
	this->Add(_pDS, EOSound::LEVELUP_SOUND, "Resources/Sounds/LevelUp.wav");
	this->Add(_pDS, EOSound::MENUCHANGE_SOUND, "Resources/Sounds/MenuChange.wav");
	this->Add(_pDS, EOSound::MENUMUSIC_SOUND, "Resources/Sounds/MenuMusic.wav");
	this->Add(_pDS, EOSound::PAUSE_SOUND, "Resources/Sounds/Pause.wav");
	this->Add(_pDS, EOSound::PIPE_SOUND, "Resources/Sounds/Pipe.wav");
	this->Add(_pDS, EOSound::SHOOT_SOUND, "Resources/Sounds/Shoot.wav");
	this->Add(_pDS, EOSound::SMALLER_SOUND, "Resources/Sounds/Smaller.wav");
	this->Add(_pDS, EOSound::STANDUP_SOUND, "Resources/Sounds/StandUp.wav");
	this->Add(_pDS, EOSound::WIN_SOUND, "Resources/Sounds/Win.wav");
}

bool SoundManagement::Init(HWND hWnd)
{
	HRESULT hr;

	hr = DirectSoundCreate8(NULL, &_pDS, NULL);
	if FAILED(hr)
		return false;

	// Set DirectSound cooperative level 
	hr = _pDS->SetCooperativeLevel(hWnd, DSSCL_PRIORITY);
	if FAILED(hr)
		return false;

	return true;
}

void SoundManagement::Add(LPDIRECTSOUND8 pDS, EOSound type, std::string wavFilename)
{
	DXSoundBuffer* sound = new DXSoundBuffer(pDS);
	sound->LoadWaveToSoundBuffer(wavFilename);
	sound->getSoundBuffer()->SetVolume(_volume);
	_ListSound[type] = sound;
}

DXSoundBuffer* SoundManagement::Get(EOSound type)
{
	map<EOSound, DXSoundBuffer*>::iterator i;
	i = _ListSound.find(type);
	if (i == _ListSound.end())
	{
		return NULL;
	}

	return i->second;
}

void SoundManagement::SetVolume(long value)
{
	// gh am thanh
	if (value < -10000)
	{
		value = -10000;
	}
	else if (value > 0)
	{
		value = 0;
	}

	_volume = value;

	map<EOSound, DXSoundBuffer *>::iterator i;
	for (i = _ListSound.begin(); i != _ListSound.end(); i++)
	{
		i->second->getSoundBuffer()->SetVolume(_volume);
	}
}

long SoundManagement::GetVolume()
{
	return this->_volume;
}

void SoundManagement::SetMute(bool value)
{
	this->_mute = value;
	if (_mute == true)
	{
		map<EOSound, DXSoundBuffer *>::iterator i;
		for (i = _ListSound.begin(); i != _ListSound.end(); i++)
		{
			i->second->getSoundBuffer()->SetVolume(-10000);
		}
	}
	else
	{
		this->SetVolume(_volume);
	}
}

bool SoundManagement::GetMute()
{
	return this->_mute;
}

void SoundManagement::VolumeUp()
{
	if (_volume < -900)
	{
		_volume = -900;
	}
	else
	{
		_volume += 100;
		if (_volume > 0)
			_volume = 0;
	}

	this->SetVolume(_volume);
}

void SoundManagement::VolumeDown()
{
	_volume -= 100;
	if (_volume < -900)
		_volume = -10000;

	this->SetVolume(_volume);
}
