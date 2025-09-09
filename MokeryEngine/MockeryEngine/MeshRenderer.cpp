#include "pch.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "GameObject.h"

MeshRenderer::MeshRenderer()
	: m_animationState(0)
	, m_animationRepeat(true)
	, m_isReturnToBeforeState(true)
{

}

void MeshRenderer::Start()
{

}

void MeshRenderer::FixedUpdate(float dTime)
{

}

void MeshRenderer::Update(float dTime)
{
	//if (m_isPlayAnimation)
	//{
	//	bool isAnimationFinish = m_renderer->GetAnimationComplete(m_pOwner->GetObjectID());
	//	if (isAnimationFinish)
	//	{
	//		m_renderer->StopAnimation(m_pOwner->GetObjectID());
	//		// 원래 애니메이션으로 돌려준다.
	//		m_animationState = m_beforeAnimation;

	//		if (m_isReturnToBeforeState)
	//		{
	//			m_renderer->PlayAnimation(m_pOwner->GetObjectID());
	//		}
	//	}
	//}

	if (m_isPlayAnimation)
	{

		bool isAnimationFinish = m_renderer->GetAnimationComplete(m_pOwner->GetObjectID());
		if (isAnimationFinish)
		{
			// 애니메이션이 반복 재생되어야 할 때
			if (m_animationRepeat)
			{	
				//m_renderer->PlayAnimation(m_pOwner->GetObjectID());
			}
			else
			{
				m_renderer->StopAnimation(m_pOwner->GetObjectID());
			}

		}
	}
}

void MeshRenderer::LateUpdate(float dTime)
{

}

void MeshRenderer::Render()
{

}

void MeshRenderer::Release()
{

}

void MeshRenderer::CreateModel()
{
	m_renderer->CreateModel(&m_AssetID, m_pOwner->GetObjectID(), GetOwner()->GetComponent<Transform>()->GetRenderTransformW(), &m_animationState, GetOwner()->GetIsDraw());
}

void MeshRenderer::SetAnimationState(UINT idx)
{
	m_animationState = idx;
}

void MeshRenderer::PlayAnimation()
{
	m_renderer->PlayAnimation(m_pOwner->GetObjectID());
}

void MeshRenderer::PlayAnimation(UINT state)
{
	m_animationState = state;
	m_renderer->PlayAnimation(m_pOwner->GetObjectID());
	m_isPlayAnimation = true;
}

void MeshRenderer::SetThisIsANIMATION()
{
	m_isPlayAnimation = true;
	m_renderer->SetAnimationRepeat(m_pOwner->GetObjectID(), true);
}

void MeshRenderer::StopAnimation()
{
	m_renderer->StopAnimation(m_pOwner->GetObjectID());
}

void MeshRenderer::SetAnimationSpeed(float speed)
{
	m_renderer->SetAnimationSpeed(m_pOwner->GetObjectID(), speed);
}

void MeshRenderer::SetAnimationRepeat(bool value)
{
	//m_renderer->SetAnimationRepeat(m_AssetID, value);
	m_animationRepeat = value;
}

bool MeshRenderer::IsFinishAnimation()
{
	return m_renderer->GetAnimationComplete(m_pOwner->GetObjectID());
}

void MeshRenderer::PlayAnimationOnce(UINT state)
{
	m_beforeAnimation = m_animationState;
	m_animationState = state;
	//m_animationRepeat = false;
	m_renderer->PlayAnimation(m_pOwner->GetObjectID());
	m_isPlayAnimation = true;
}

void MeshRenderer::PlayAnimationOnce(UINT state, bool returnToBeforeState)
{
	m_isReturnToBeforeState = returnToBeforeState;
	m_beforeAnimation = m_animationState;
	m_animationState = state;
	//m_animationRepeat = false;
	m_renderer->PlayAnimation(m_pOwner->GetObjectID());
	m_isPlayAnimation = true;
}
