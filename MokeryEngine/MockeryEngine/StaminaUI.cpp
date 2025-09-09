#include "pch.h"
#include "StaminaUI.h"
#include "GameObject.h"
#include "EngineObjectManager.h"
#include "PlayerComponent.h"
#include "SpriteRenderer.h"
#include "Transform.h"

StaminaUI::StaminaUI()
	:m_player(nullptr), m_rect{}
{

}

StaminaUI::~StaminaUI()
{

}

void StaminaUI::Start()
{
	// �÷��̾������� ��������
	m_player = GetOwner()->GetObjectManager()->GetOBjectsByComponent<PlayerComponent>()->GetComponent<PlayerComponent>();
	m_sprite = GetOwner()->GetComponent<SpriteRenderer>();
	m_transform = GetOwner()->GetComponent<Transform>();
}

void StaminaUI::FixedUpdate(float dTime)
{
}

void StaminaUI::Update(float dTime)
{
	float stamina = GetOwner()->GetObjectManager()->GetOBjectsByComponent<PlayerComponent>()->GetComponent<PlayerComponent>()->GetStamina();
	float maxStamina = 5.f;


	//std::cout << "���׹̳� : " << stamina << ", obID : " << GetOwner()->GetObjectManager()->GetOBjectsByComponent<PlayerComponent>()->GetObjectID() << std::endl;
	m_sprite->SetSize({ 100 * (stamina/maxStamina), 100});
}

void StaminaUI::LateUpdate(float dTime)
{
}

void StaminaUI::Render()
{
}

void StaminaUI::Release()
{
}

void StaminaUI::SetRect(RECT _rect)
{

}
