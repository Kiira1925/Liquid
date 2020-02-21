#pragma once

template<class T>
class Singleton 
{
protected:
	Singleton() = default;
	~Singleton() = default;

public:

	static T* getInstance()
	{
		static T instance;
		return &instance;
	}
};