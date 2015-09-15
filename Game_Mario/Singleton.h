#pragma once

template <class T>
class CSingleton
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

template <class T> T* CSingleton<T>::instance = nullptr;