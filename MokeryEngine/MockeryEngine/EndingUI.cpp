#include "pch.h"
#include "EndingUI.h"
#include "GameObject.h"
#include "EngineObjectManager.h"
#include "PlayerComponent.h"
#include "Timer.h"
#include "GameManager.h"
#include "Button.h"
#include "SpriteRenderer.h"
#include "KnifeUI.h"
#include "DemonAltarComponent.h"
#include "InputManager.h"
#include "SoundManager.h"

EndingUI::EndingUI()
	:m_isWin(false)
{

}

EndingUI::~EndingUI()
{

}

void EndingUI::Start()
{
	m_player = GetOwner()->GetObjectManager()->GetOBjectsByComponent<PlayerComponent>()->GetComponent<PlayerComponent>();
	m_timer = GetOwner()->GetObjectManager()->GetOBjectsByComponent<Timer>()->GetComponent<Timer>();
	m_sprite = GetOwner()->GetComponent<SpriteRenderer>();
	m_button  = GetOwner()->GetComponent<Button>();
	m_spriteKnife = GetOwner()->GetObjectManager()->GetOBjectsByComponent<KnifeUI>()->GetComponent<SpriteRenderer>();// ->DrawInactive();

	
}

void EndingUI::FixedUpdate(float dTime)
{
}

void EndingUI::Update(float dTime)
{
	if(!m_isWin)
	{
		// Á×¾úÀ»¶§
		if (m_timer->GetIsOver() || m_player->GetHp() < 0.f)
		{
			m_button->SetEnable();
			m_sprite->DrawActive();
			m_sprite->Trigger(1);
			m_spriteKnife->DrawInactive();

			SoundManager::GetInstance().StopSound(SoundManager::GetInstance().GetBGMChannel());
			SoundManager::GetInstance().StopSound(SoundManager::GetInstance().GetBGMCChannel());
			SoundManager::GetInstance().StopSound(SoundManager::GetInstance().GetMoveChannel());
			SoundManager::GetInstance().StopSound(SoundManager::GetInstance().GetJaneChannel());
			SoundManager::GetInstance().StopSound(SoundManager::GetInstance().GetChaserChannel());
			SoundManager::GetInstance().StopSound(SoundManager::GetInstance().GetBlindChannel());
			SoundManager::GetInstance().StopSound(SoundManager::GetInstance().GetGhostChannel());
			SoundManager::GetInstance().StopSound(SoundManager::GetInstance().GetDoor0Channel());
		}
	}
// 	if (InputManager::GetInstance()->m_Keyboard.IsKeydown('H'))
// 	{
// 		DemonAltarComponent::m_altarCount += 1;
// 	}
	if (DemonAltarComponent::m_altarCount >= 3)
	{
		m_spriteKnife->DrawInactive();
	   m_isWin = true;
	   m_button->SetEnable();
	   m_sprite->DrawActive();
	   m_sprite->Trigger(0);
	   m_timer->StopTimer();
	   m_timer->m_sprite->DrawInactive();
		
	   SoundManager::GetInstance().StopSound(SoundManager::GetInstance().GetBGMChannel());
	   SoundManager::GetInstance().StopSound(SoundManager::GetInstance().GetBGMCChannel());
	   SoundManager::GetInstance().StopSound(SoundManager::GetInstance().GetMoveChannel());
	   SoundManager::GetInstance().StopSound(SoundManager::GetInstance().GetJaneChannel());
	   SoundManager::GetInstance().StopSound(SoundManager::GetInstance().GetChaserChannel());
	   SoundManager::GetInstance().StopSound(SoundManager::GetInstance().GetBlindChannel());
	   SoundManager::GetInstance().StopSound(SoundManager::GetInstance().GetGhostChannel());
	}

}

void EndingUI::LateUpdate(float dTime)
{
}

void EndingUI::Render()
{
}

void EndingUI::Release()
{
}
