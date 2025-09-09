#include "pch.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Transform.h"


#ifdef _DEBUG
#include "InputManager.h"
UINT SpriteRenderer::m_assetNumMax = 0;
UINT SpriteRenderer::m_assetNumMin = INT32_MAX;
UINT SpriteRenderer::m_CurrAssetNum;
#endif // _DEBUG

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
	m_pos.right = m_pos.left + m_size.x;
	m_pos.bottom = m_pos.top + m_size.y;

	Vector2 screen = m_renderer->GetClientSize();

	m_NormalPos.x = m_pos.left / screen.x;
	m_NormalPos.y = m_pos.top / screen.y;
	m_NormalPos.z = m_pos.right / screen.x;
	m_NormalPos.w = m_pos.bottom / screen.y;


	GetOwner()->GetComponent<Transform>()->SetPosition({ static_cast<float>(m_pos.left), static_cast<float>(m_pos.top), m_layer });
	m_worldTM = GetOwner()->GetComponent<Transform>()->GetWorld();
}

void SpriteRenderer::Update(float dTime)
{
#ifdef _DEBUG
	auto mouse = InputManager::GetInstance()->m_Mouse;
	auto keyboard = InputManager::GetInstance()->m_Keyboard;
	if (m_assetNum == m_CurrAssetNum)
	{
		if (mouse.IsButtonDown(mouse.middleButton))
		{
			std::cout << m_CurrAssetNum << std::endl;
		}
		if (mouse.IsButtonHold(mouse.middleButton))
		{
			SetRect({ static_cast<LONG>(mouse.m_PosX),static_cast<LONG>(mouse.m_PosY),0,0 });
		}
		if (mouse.IsButtonUp(mouse.middleButton))
		{
			DX(
				SetRect({ static_cast<LONG>(mouse.m_PosX),static_cast<LONG>(mouse.m_PosY),0,0 });
				std::cout << mouse.m_PosX << " " << mouse.m_PosY << std::endl;
			);
			
		}

		
	}

	static bool debugCheck = true;
	if (keyboard.IsKeydown('B') && debugCheck == true)
	{
		debugCheck = false;
		m_CurrAssetNum++;
		if (m_CurrAssetNum > m_assetNumMax)
		{
			m_CurrAssetNum = m_assetNumMin;
		}
		std::cout << m_CurrAssetNum << " " << m_assetNumMin << " " << m_assetNumMax << std::endl;
	}
	if (keyboard.IsKeyUp('B') && debugCheck == false)
	{
		debugCheck = true;
	}


	
#endif // _DEBUG
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

void SpriteRenderer::SetSize(Vector2 _size)
{
	m_size = _size;
	
}

void SpriteRenderer::SetRect(RECT _rect)
{
	m_pos = _rect;
}

void SpriteRenderer::SetPos(int _X, int _Y)
{
	m_pos.left = _X;
	m_pos.top = _Y;

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
