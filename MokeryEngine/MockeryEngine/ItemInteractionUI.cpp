#include "pch.h"
#include "ItemInteractionUI.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "EngineObjectManager.h"
#include "InteractiveObject.h"

ItemInteractionUI::ItemInteractionUI()
	:m_currentInteract(nullptr), m_interacts{},
	m_pos{}
{

}

ItemInteractionUI::~ItemInteractionUI()
{

}

void ItemInteractionUI::Start()
{
	//m_sprite = GetOwner()->GetComponent<SpriteRenderer>();
	
	// 스프라이트 크기를 세팅한다.
	//m_sprite->SetRect(m_pos);

	// obj벡터를 순회면서 interactive오브젝트를 찾는다.
	for (auto& e : GetOwner()->GetObjectManager()->GetObjects())
	{
		InteractiveObject* interactive = e->GetComponent<InteractiveObject>();
		if (interactive != nullptr)
		{
			m_interacts.push_back(interactive);
		}
	}
}

void ItemInteractionUI::FixedUpdate(float dTime)
{
}

void ItemInteractionUI::Update(float dTime)
{


}

/// <summary>
/// interactiveObj를 순회하면서 active인지 점검한다.
/// active라면 오브젝트를 가져온다.
/// itemLoadRatio를 전달한다. 
/// </summary>
/// <param name="dTime"></param>
void ItemInteractionUI::LateUpdate(float dTime)
{
	if (m_currentInteract == nullptr)
	{
		// 벡터 루프를 돈다.
		for (auto& e : m_interacts)
		{
			//e->InteractAddTime(dTime);
			// 상호작용중인 컴포넌트를 찾는다면
			if (e->GetIsInteract())
			{
				// 현재 컴포넌트에 입력하고 
				m_currentInteract = e;
				break;
			}
		}
	}
	else // 상호작용중인 컴포넌트가 있다면
	{
		float per;
		per = m_currentInteract->ItemLoadRatio();
		//std::cout << "현재 상호작용 : " << per * 100 << "%" << std::endl;

		if (per >= 100.f || !(m_currentInteract->GetIsInteract()))
		{
			m_currentInteract = nullptr;
		}
	}
}

void ItemInteractionUI::Render()
{
}

void ItemInteractionUI::Release()
{
}
