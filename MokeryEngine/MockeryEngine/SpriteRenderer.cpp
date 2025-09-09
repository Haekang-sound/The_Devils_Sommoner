#include "pch.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Transform.h"

SpriteRenderer::SpriteRenderer()
{
//	isDraw = GetOwner()->GetIsDraw();

}

void SpriteRenderer::Start()
{
	m_transform = GetOwner()->GetComponent<Transform>();
	m_renderer->CreateSprite(GetAssetNum(), GetOwner()->GetObjectID(), GetWorldTM(), GetSize(), GetSate(), GetOwner()->GetIsDraw());
}

void SpriteRenderer::FixedUpdate(float dTime)
{
}

void SpriteRenderer::Update(float dTime)
{
}

void SpriteRenderer::LateUpdate(float dTime)
{
}

void SpriteRenderer::Render()
{
}

void SpriteRenderer::Release()
{
}

// 다른 컴포넌트에서 사용할 스프라이트를 선택해서 가져온다.
void SpriteRenderer::Trigger(unsigned int _flag)
{
	// 벡터에서 알맞은 에셋넘버를 가져온다.
	m_state = _flag;
	DrawActive();
}

void SpriteRenderer::Trigger()
{

}

void SpriteRenderer::SpriteToggle()
{
	if (m_state)
	{
		m_state = 0;
	}
	else
	{
		m_state = 1;
	}
}

void SpriteRenderer::SetRect(RECT _rect)
{
	m_pos = _rect;

 	//m_size.y = (m_pos.right - m_pos.left) + 1080 / 2;
 	//m_size.x = (m_pos.bottom - m_pos.top) + 1920 / 2;
 
  	GetOwner()->GetComponent<Transform>()->SetPosition({ static_cast<float>(m_pos.left), static_cast<float>(m_pos.top), m_layer });
  	m_worldTM = GetOwner()->GetComponent<Transform>()->GetWorld();


}

void SpriteRenderer::DrawActive()
{
	isDraw = true;
	GetOwner()->SetIsDrawRecursively(true);
}

void SpriteRenderer::DrawInactive()
{
	isDraw = false;
	GetOwner()->SetIsDrawRecursively(false);
}
