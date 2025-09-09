#pragma once

template<typename T>
class SingleTon
{
public:
	static T* GetInstance()
	{
		if (m_instance == nullptr)
		{
			m_instance = new T();
		}
		return m_instance;
	}
protected:
	static T* m_instance;

private:
}; 

template<typename T>
T* SingleTon<T>::m_instance = nullptr;