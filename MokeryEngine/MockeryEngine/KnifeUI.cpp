#include "pch.h"
#include "KnifeUI.h"
#include "GameObject.h"
#include "EngineObjectManager.h"
#include "PlayerComponent.h"
#include "SpriteRenderer.h"

KnifeUI::KnifeUI()
{

}

KnifeUI::~KnifeUI()
{

}

void KnifeUI::Start()
{
	m_player = GetOwner()->GetObjectManager()->GetOBjectsByComponent<PlayerComponent>()->GetComponent<PlayerComponent>();
	m_sprite = GetOwner()->GetComponent<SpriteRenderer>();
}

void KnifeUI::FixedUpdate(float dTime)
{
}

void KnifeUI::Update(float dTime)
{
	if (m_player->GetIsKnifeReady())
	{
		m_sprite->Trigger(0);
	}
	else
	{
		m_sprite->Trigger(1);
	}

}

void KnifeUI::LateUpdate(float dTime)
{
}

void KnifeUI::Render()
{
}

void KnifeUI::Release()
{
}
