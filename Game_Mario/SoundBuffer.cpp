#include "SoundBuffer.h"


DXSoundBuffer::DXSoundBuffer(LPDIRECTSOUND8 pDS)
{
	this->_pDS = pDS;
	this->_soundBuffer = NULL;
}

bool DXSoundBuffer::LoadWaveToSoundBuffer(std::string wavFilename)
{
	CWaveFile *wavFile;
	HRESULT hr;

	wavFile = new CWaveFile();
	wavFile->Open((char*)wavFilename.c_str(), NULL, WAVEFILE_READ);
	if (wavFile->GetSize() == 0)
	{
		OutputDebugString("[SoundBuffer.cpp] Cannot init. DXSoundBuffer::LoadWaveToSoundBuffer(std::string wavFilename)");
		return false;
	}

	DSBUFFERDESC dsbd;
	ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
	dsbd.dwSize = sizeof(DSBUFFERDESC);
	//dsbd.dwFlags         = 0;
	dsbd.dwFlags = DSBCAPS_CTRLVOLUME;
	dsbd.dwBufferBytes = wavFile->GetSize();
	dsbd.guid3DAlgorithm = GUID_NULL;
	dsbd.lpwfxFormat = wavFile->m_pwfx;

	hr = _pDS->CreateSoundBuffer(&dsbd, &_soundBuffer, NULL);
	if FAILED(hr)
	{
		OutputDebugString("[SoundBuffer.cpp] Cannot init. DXSoundBuffer::LoadWaveToSoundBuffer(std::string wavFilename)");
		return false;
	}

	VOID*   pDSLockedBuffer = NULL; // Pointer to locked buffer memory
	DWORD   dwDSLockedBufferSize = 0;    // Size of the locked DirectSound buffer
	DWORD   dwWavDataRead = 0;    // Amount of data read from the wav file 

	hr = _soundBuffer->Lock(0, wavFile->GetSize(),
		&pDSLockedBuffer, &dwDSLockedBufferSize,
		NULL, NULL, 0L);
	if FAILED(hr)
		return false;

	// Reset the wave file to the beginning 
	wavFile->ResetFile();

	// Read the wave file
	hr = wavFile->Read((BYTE*)pDSLockedBuffer,
		dwDSLockedBufferSize,
		&dwWavDataRead);
	// Check to make sure that this was successful
	if FAILED(hr)
		return false;

	// Check to make sure the wav file is not empty
	if (dwWavDataRead == 0)
	{
		// Wav is blank, so just fill with silence
		FillMemory((BYTE*)pDSLockedBuffer,
			dwDSLockedBufferSize,
			(BYTE)(wavFile->m_pwfx->wBitsPerSample == 8 ? 128 : 0));
	}
	else if (dwWavDataRead < dwDSLockedBufferSize)
	{
		// Don't repeat the wav file, just fill in silence 
		FillMemory((BYTE*)pDSLockedBuffer + dwWavDataRead,
			dwDSLockedBufferSize - dwWavDataRead,
			(BYTE)(wavFile->m_pwfx->wBitsPerSample == 8 ? 128 : 0));
	}

	// Unlock the buffer, we don't need it anymore.
	_soundBuffer->Unlock(pDSLockedBuffer, dwDSLockedBufferSize, NULL, 0);

	// Clean up
	delete wavFile;

	return true;
}

void DXSoundBuffer::Play()
{
	this->_soundBuffer->Play(0, 0, 0);
}

void DXSoundBuffer::PlayLoop()
{
	this->_soundBuffer->Play(0, 0, DSBPLAY_LOOPING);
}

void DXSoundBuffer::Stop()
{
	this->_soundBuffer->Stop();
}

DXSoundBuffer::~DXSoundBuffer()
{
	if (_soundBuffer != NULL)
	{
		_soundBuffer->Release();
		_soundBuffer = NULL;
	}
}

LPDIRECTSOUNDBUFFER DXSoundBuffer::getSoundBuffer()
{
	return _soundBuffer;
}