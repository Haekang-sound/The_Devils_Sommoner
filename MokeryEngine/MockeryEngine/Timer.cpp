#include "pch.h"
#include "Timer.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "SoundManager.h"

Timer::Timer()
{

}

Timer::~Timer()
{

}

void Timer::Start()
{
	m_sprite = GetOwner()->GetComponent<SpriteRenderer>();
	m_time = 0.01f;
}

void Timer::FixedUpdate(float dTime)
{

}

void Timer::Update(float dTime)
{

// 	if (!isCount)
// 	{
// 
// 		isCount = true;
// 	}
	//std::cout << m_time << std::endl;
	
	if (isCount)
	{

		m_time -= dTime;// *3.f;
		if (m_time < 0.f)
		{
			isOver = true;
			//m_renderer->Send(1, GetOwner()->GetObjectID(), 1.f, { 0.f,0.f,0.f,1.f });
			m_sprite->DrawInactive();
			if (m_forSound)
			{
				SoundManager::GetInstance().StopSound(SoundManager::GetInstance().GetDoor3Channel());
				SoundManager::GetInstance().PlaySFX(eSOUNDKIND::fDead);
				m_forSound = false;
			}
		}
		else if (m_time < 30.f)
		{
			m_sprite->Trigger(0);
			if (!m_forSound)
			{
				SoundManager::GetInstance().PlayDoor3(eSOUNDKIND::fTimer);
				m_forSound = true;
			}
		}
		else if (m_time < 60.f && m_time > 57.f)
		{
			m_sprite->Trigger(1);
		}
		else if (m_time < 120.f && m_time > 117.f)
		{
			m_sprite->Trigger(2);
		}
		else if (m_time < 180.f && m_time > 177.f)
		{
			m_sprite->Trigger(3);
		}
		else if (m_time < 240.f && m_time > 237.f)
		{
			m_sprite->Trigger(4);
		}
		else
		{
			m_sprite->DrawInactive();
		}
		

	}

	if (m_isPresent == true)
	{
		// 전사시간을 누적합니다.
		m_presentTime += dTime;
		// 3초동안 전사했다면
		if (m_presentTime > 3.f)
		{
			// 출력을 중단합니다
			m_sprite->DrawInactive();
			m_presentTime = 0.f;
			m_isPresent = false;
		}
	}

}

void Timer::LateUpdate(float dTime)
{
}

void Timer::Render()
{
}

void Timer::Release()
{
}
