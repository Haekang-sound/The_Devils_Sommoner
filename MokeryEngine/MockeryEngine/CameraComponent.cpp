#include "pch.h"
#include "CameraComponent.h"
#include "Transform.h"
#include "GameObject.h"
#include "../Graphics/ID3DRenderer.h"

#include "InputManager.h"

CameraComponent::CameraComponent()
	: m_cameraID(), m_View{}, m_pTransform(nullptr)
{

}

CameraComponent::~CameraComponent()
{
	

}

void CameraComponent::Start()
{
	m_pTransform = GetOwner()->GetComponent<Transform>();
	m_renderer->CreateCamera(m_cameraID, GetOwner()->GetComponent<Transform>()->GetRenderTransformL(),&m_RenderView);
	m_renderer->SetCameraProjection(45, 16.f / 9.f, 0.1f, 100.f, m_cameraID);
	temp.x = m_pTransform->GetForward().x;
	temp.y = m_pTransform->GetForward().y;
	temp.z = m_pTransform->GetForward().z;
	m_renderer->SetDirectionLight(&temp, &m_power);

}


void CameraComponent::FixedUpdate(float dTime)
{
}

void CameraComponent::Update(float dTime)
{
	

// 	if (InputManager::GetInstance()->m_Keyboard.IsKeyHold('I'))
// 	{
// 		m_renderer->SetCameraProjection(60.f, 0);
// 	}
// 	if (InputManager::GetInstance()->m_Keyboard.IsKeyUp('I'))
// 	{
// 		m_renderer->SetCameraProjection(90.f, 0);
// 	}

}

void CameraComponent::LateUpdate(float dTime)
{

}

void CameraComponent::Render()
{
	temp.x = m_pTransform->GetForward().x;
	temp.y = m_pTransform->GetForward().y;
	temp.z = m_pTransform->GetForward().z;
	m_pTransform->SetDirection();
	// 용준작성 수정 필요
	m_View = SimpleMath::Matrix::CreateLookAt(
		m_pTransform->GetPosition(), m_pTransform->GetPosition() + (-m_pTransform->m_Forward), m_pTransform->m_UP
	);

	memcpy(&m_RenderView, &m_View, sizeof(SimpleMath::Matrix));
}

void CameraComponent::Release()
{
}

void CameraComponent::SetFov(int fov)
{
	m_renderer->SetCameraProjection(fov, m_cameraID);
}
