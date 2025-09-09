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
	// 스페이스바를 누를때 마다 리소스를 변경해주어야 한다.
	if (InputManager::GetInstance()->)
	{
 		//GetOwner()->GetComponent<Sprite>()->m_currentBitmap = m_resourceManager->GetResource<Image>("umappyoi_1")->m_type->m_data;	// 리소스를 얻어온다.
		GetOwner()->GetComponent<AudioComponent>()->Play();
		// 트랜스폼 이동실험
    	// GetOwner()->GetComponent<Controller>()->TransportPositiveX(dTime);
		SimpleMath::Matrix v = GetOwner()->GetComponent<Transform>()->GetWorld();
	}
 	else if (m_inputmanager->GetButtonUp(KeyType::SpaceBar))
	{
		//GetOwner()->GetComponent<Sprite>()->m_currentBitmap = m_resourceManager->GetResource<Image>("Mockery")->m_type->m_data;	// 리소스를 얻어온다.
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

