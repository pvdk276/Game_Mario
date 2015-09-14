#pragma once

template <class T>
class Singleton
{
public:
	static T* getInstance()
	{
		if (!instance)
		{
			instance = new T();
		}
		return instance;
	}

	static T* instance;
};

template <class T> T* Singleton<T>::instance = nullptr;