#pragma once

template <typename T>
class Singleton
{
protected:
	Singleton() {}
	~Singleton() {}
	static T* instance; 

public:
	static T* GetInstance()
	{
		if (nullptr == instance)
		{
			instance = new T;
		}
		return instance;
	}
	void DestroyInstance()
	{
		if (nullptr != instance)
		{
			delete instance;
			instance = nullptr;
		}
	}
};

template<typename T>
T* Singleton<T>::instance = nullptr;