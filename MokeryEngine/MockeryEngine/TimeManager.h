#pragma once
#include <chrono>

/// <summary>
///  시간을 관리하는 매니저
/// </summary>
class TimeManager 
{
public:
	TimeManager();

	void	Init();
	void	Update();

	float	GetDTime() const	{ return m_deltaTime; };	// 단위 ms
	int		GetFPS() const		{ return m_fps;};

private:
	int m_fps;
	float m_deltaTime;

private:
	std::chrono::duration<float> m_dTime;
	std::chrono::system_clock::time_point m_start;
	std::chrono::system_clock::time_point m_end;
};

