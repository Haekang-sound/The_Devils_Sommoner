#include "pch.h"
#include "InteractiveObject.h"
#include "GameObject.h"
#include "SoundManager.h"

InteractiveObject::InteractiveObject()
	: m_interactState(InteractState::None),
	m_isInteract(false)
	,m_isInteractAddTime(false)
	,m_isInteractSound(false)
{

}

InteractiveObject::~InteractiveObject()
{

}

void InteractiveObject::Start()
{

}

void InteractiveObject::FixedUpdate(float dTime)
{

}

void InteractiveObject::Update(float dTime)
{
	
}

void InteractiveObject::LateUpdate(float dTime)
{
	if (!m_isInteract)
	{
		m_currentTime = 0.f;
		//SoundManager::GetInstance()->StopSound(SoundManager::GetInstance()->GetSFXRChannel());
		m_isInteractSound = false;
	}

	m_isInteract = false;
	m_beforeTime = m_currentTime;
}

void InteractiveObject::Render()
{

}

void InteractiveObject::Release()
{

}

void InteractiveObject::SetLoadTime(float time)
{
	m_loadTime = time;
}

void InteractiveObject::Interact()
{
	m_isInteract = false;
	SoundManager::GetInstance()->StopSound(SoundManager::GetInstance()->GetSFXRChannel());
}

void InteractiveObject::InteractAddTime(float dTime)
{
	if (!m_isInteractSound)
	{
		SoundManager::GetInstance()->PlaySFXR(eSOUNDKIND::fPact);
		//SoundManager::GetInstance()->AddReverb(SoundManager::GetInstance()->GetSFXRChannel());
		m_isInteractSound = true;
	}
	m_isInteract = true;
	m_currentTime += dTime;
	// std::cout << "상호작용중 : " << ItemLoadRatio() << std::endl;
	if (m_currentTime >= m_loadTime)
	{
		Interact();
		//std::cout << m_pOwner->GetName() << std::endl;
	}
}