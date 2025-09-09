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
	
	// ��������Ʈ ũ�⸦ �����Ѵ�.
	//m_sprite->SetRect(m_pos);

	// obj���͸� ��ȸ�鼭 interactive������Ʈ�� ã�´�.
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
/// interactiveObj�� ��ȸ�ϸ鼭 active���� �����Ѵ�.
/// active��� ������Ʈ�� �����´�.
/// itemLoadRatio�� �����Ѵ�. 
/// </summary>
/// <param name="dTime"></param>
void ItemInteractionUI::LateUpdate(float dTime)
{
	if (m_currentInteract == nullptr)
	{
		// ���� ������ ����.
		for (auto& e : m_interacts)
		{
			//e->InteractAddTime(dTime);
			// ��ȣ�ۿ����� ������Ʈ�� ã�´ٸ�
			if (e->GetIsInteract())
			{
				// ���� ������Ʈ�� �Է��ϰ� 
				m_currentInteract = e;
				break;
			}
		}
	}
	else // ��ȣ�ۿ����� ������Ʈ�� �ִٸ�
	{
		float per;
		per = m_currentInteract->ItemLoadRatio();
		//std::cout << "���� ��ȣ�ۿ� : " << per * 100 << "%" << std::endl;

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
