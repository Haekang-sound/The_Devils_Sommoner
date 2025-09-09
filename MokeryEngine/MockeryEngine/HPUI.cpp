#include "pch.h"
#include "HPUI.h"
#include "GameObject.h"
#include "EngineObjectManager.h"
#include "PlayerComponent.h"
#include "SpriteRenderer.h"
// �׽�Ʈ�� �׽�Ʈ�� ������ ������
#include "Button.h"
#include "InputManager.h"
#include "SoundManager.h"

HPUI::HPUI()
	: m_player(nullptr),// m_sprite(nullptr),
	m_pos{}


	,m_button(nullptr)
	,m_isDead(false)
{


}

void HPUI::Start()
{
	m_player = GetOwner()->GetObjectManager()->GetOBjectsByComponent<PlayerComponent>()->GetComponent<PlayerComponent>();
	//m_sprite = GetOwner()->GetComponent<SpriteRenderer>();
	
	// ũ��� ��ġ�� ���Ѵ�.
	m_pos.left = 0;
	m_pos.top = 0;
	m_pos.right = 360;
	m_pos.bottom = 640;
	//m_sprite->SetRect(m_pos);
	
}

void HPUI::FixedUpdate(float dTime)
{
}

void HPUI::Update(float dTime)
{
//	return;

	// �׽�Ʈ�� ���ؼ� ��������ϴ� ����̴ϴ�! 
// 	if (InputManager::GetInstance()->m_Keyboard.IsKeyHold('N'))
// 	{
// 		m_player->SetHp(m_player->GetHp() - 10);
// 		//std::cout << "hp : " << m_player->GetHp() << std::endl;
// 	}
// 	if(InputManager::GetInstance()->m_Keyboard.IsKeyHold('M'))
// 	{
// 		m_player->SetHp(m_player->GetHp() + 10);
// 		//std::cout << "hp : " << m_player->GetHp() << std::endl;
// 	}


	int hp = m_player->GetHp();

	if (m_player->GetHp() <= 0.f)
	{
		if (!m_isDead)
		{
			SoundManager::GetInstance()->PlaySFX(eSOUNDKIND::fDead);
			m_isDead = true;
		}

		//std::cout <<"���� HP : " << hp << ", " << "���" << std::endl;
		// �̶��� ����ؾ��ϳ�? 
		//m_sprite->Trigger(Fatal);
		m_renderer->Send(0, 0, hp, { 0.f,0.f,0.f,1.f });
	}
	else if (m_player->GetHp() <= 20.f)
	{
		//std::cout <<"���� HP : " << hp << ", " << "������ ���ƿ�" << std::endl;
		//m_sprite->Trigger(Fatal);
		m_renderer->Send(0, 0, hp, { 0.3f,0.f,0.f,1.f });

	}
	else if(m_player->GetHp() <= 40.f)
	{
		//std::cout << "���� HP : " << hp << ", " << "�ʹ� ����" << std::endl;
		//m_sprite->Trigger(Half);
		m_renderer->Send(0, 0, hp, { 0.7f,0.f,0.f,1.f });
	}
	else
	{
		//std::cout << "���� HP : " << hp << ", " << "�Ⱦ��µ���?" << std::endl;
		//m_sprite->DrawInactive(); //�׸��� �ʴ´�
		m_isDead = false;
		m_renderer->Send(0, 0, hp, { 1.f,1.f,1.f,1.f });
	}
}

void HPUI::LateUpdate(float dTime)
{
}

void HPUI::Render()
{
}

void HPUI::Release()
{
}
