#include "pch.h"
#include "Image.h"
#include "BackGround.h"
#include "Move.h"
#include "Transform.h"

BackGround::BackGround()
	: m_resourceManager(nullptr),
	m_inputmanager(nullptr)
{

}
 
BackGround::~BackGround()
{

}

void BackGround::Start()
{
}

void BackGround::Update(float dTime)
{
	// �����̽��ٸ� ������ ���� ���ҽ��� �������־�� �Ѵ�.
	if (InputManager::GetInstance()->)
	{
 		//GetOwner()->GetComponent<Sprite>()->m_currentBitmap = m_resourceManager->GetResource<Image>("umappyoi_1")->m_type->m_data;	// ���ҽ��� ���´�.
		GetOwner()->GetComponent<AudioComponent>()->Play();
		// Ʈ������ �̵�����
    	// GetOwner()->GetComponent<Controller>()->TransportPositiveX(dTime);
		SimpleMath::Matrix v = GetOwner()->GetComponent<Transform>()->GetWorld();
	}
 	else if (m_inputmanager->GetButtonUp(KeyType::SpaceBar))
	{
		//GetOwner()->GetComponent<Sprite>()->m_currentBitmap = m_resourceManager->GetResource<Image>("Mockery")->m_type->m_data;	// ���ҽ��� ���´�.
		GetOwner()->GetComponent<AudioComponent>()->Stop();
	}
	

}

void BackGround::LateUpdate(float dTime)
{

}

void BackGround::Render()
{

}

void BackGround::Release()
{

}

void BackGround::FixedUpdate(float dTime)
{
}

