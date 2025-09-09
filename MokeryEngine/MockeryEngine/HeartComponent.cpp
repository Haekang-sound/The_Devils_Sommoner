#include "pch.h"
#include "HeartComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "AudioComponent.h"
#include "DemonAltarComponent.h"

HeartComponent::HeartComponent()
	: m_isActivated(false), m_altarCount(0)
{

}

HeartComponent::~HeartComponent()
{

}

void HeartComponent::Start()
{

}

void HeartComponent::FixedUpdate(float dTime)
{

}

void HeartComponent::Update(float dTime)
{
	if (m_isActivated)
	{
		// ��...
// 		if (m_altar[m_altarCount]->GetComponent<DemonAltarComponent>()->GetisAltarActivated()
// 			&& m_altarCount < m_altar.size() - 1)
// 		{
// 			m_altarCount++;
// 		}

		for (auto e : m_altar)
		{
			m_altarCount = e->GetComponent<DemonAltarComponent>()->GetAltarCount();
		}

		// �̰� ���ܰ� �÷��̾� ������ �Ÿ��� �ɰž�
		int m_distance = sqrt(pow(m_pOwner->GetComponent<Transform>()->GetPosition().x
			- m_altar[m_altarCount]->GetComponent<Transform>()->GetPosition().x, 2.f)
			+ pow(m_pOwner->GetComponent<Transform>()->GetPosition().z
				- m_altar[m_altarCount]->GetComponent<Transform>()->GetPosition().z, 2.f));


		// TODO : �Ҹ��� �޾ƿ��µ�
		// ���� �Ҹ� �߻� �ֱ⿡ ���� �ִ� m_distance�� ������ �ǰ���
// 		m_pOwner->GetComponent<AudioComponent>()->Play();
// 		m_pOwner->GetComponent<AudioComponent>()->Stop();
	}
}

void HeartComponent::LateUpdate(float dTime)
{
	Super::LateUpdate(dTime);
}

void HeartComponent::Render()
{

}

void HeartComponent::Release()
{

}

void HeartComponent::Interact()
{
	Super::Interact();

	m_isActivated = true;
}
