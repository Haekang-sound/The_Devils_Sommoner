#include "pch.h"
#include "KnifeItem.h"
#include "GameObject.h"
#include "KnifeComponent.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "SoundManager.h"

KnifeItem::KnifeItem()
{

}

KnifeItem::~KnifeItem()
{

}

void KnifeItem::Start()
{
	m_pOwner->GetComponent<Transform>()->SetLocalPosition({ -100.f, -100.f,-100.f });
}

void KnifeItem::Select()
{
	//m_pOwner->GetComponent<Transform>()->SetLocalPosition({ 0.3f,-0.3f,1.f });
}

void KnifeItem::UnSelect()
{
	m_pOwner->GetComponent<Transform>()->SetLocalPosition({ -100.f, -100.f,-100.f });
}

void KnifeItem::Act(GameObject* player)
{
	SoundManager::GetInstance()->PlaySFX(eSOUNDKIND::fPskill);

	KnifeComponent* knifeComponent = m_knifeObject->GetComponent<KnifeComponent>();

	Transform* playerTransform = player->GetComponent<Transform>();
	SimpleMath::Vector3 pos = playerTransform->GetPosition();
	SimpleMath::Vector3 dir = playerTransform->GetForward();
	SimpleMath::Vector3 rot = playerTransform->GetRotation();
	pos += 1.f * dir;
	knifeComponent->Shoot(pos, dir, rot);

	// 모델 애니메이션
	if (m_handModel)
	{
		//m_handModel->GetComponent<MeshRenderer>()->SetAnimationState(1);
		m_pOwner->GetComponent<Transform>()->SetLocalPosition({ 0.3f,-0.3f,1.f });
		//m_handModel->GetComponent<MeshRenderer>()->SetAnimationRepeat(false);
		m_handModel->GetComponent<MeshRenderer>()->PlayAnimationOnce(0);
		m_handModel->GetComponent<MeshRenderer>()->SetAnimationSpeed(5.f);
		//m_handModel->GetComponent<MeshRenderer>()->SetAnimationSpeed(2.f);
		//m_handModel->GetComponent<MeshRenderer>()->PlayAnimation();
	}
	//m_handModel->GetComponent<MeshRenderer>()->SetAnimationRepeat(false);
}

void KnifeItem::SetKnifeObject(GameObject* knife)
{
	m_knifeObject = knife;
}

void KnifeItem::SetHandModel(GameObject* obj)
{
	m_handModel = obj;
}
