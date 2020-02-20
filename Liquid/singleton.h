#pragma once

template<class T>
class Singleton 
{
protected:
	Singleton() = default;
	virtual ~Singleton() {}

public:
	static T* getInstance()
	{
		static T instance;
		return &instance;
	}
};