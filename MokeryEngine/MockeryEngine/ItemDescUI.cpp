#include "pch.h"
#include "ItemDescUI.h"
#include "GameObject.h"
#include "EngineObjectManager.h"
#include "ItemChest.h"
#include "SpriteRenderer.h"
#include "SoundManager.h"

#include "Button.h"

ItemDescUI::ItemDescUI()
	: m_itemChests{}, m_sprite(nullptr), m_presentTime(0.f)
	, m_button(nullptr)
{

}

ItemDescUI::~ItemDescUI()
{

}

void ItemDescUI::Start()
{
	m_sprite = GetOwner()->GetComponent<SpriteRenderer>();
// 	m_pos.left = 0;
// 	m_pos.top = 0;
// 	m_pos.right = 400;
// 	m_pos.bottom = 400;
// 	m_sprite->SetRect(m_pos);
	m_sprite->DrawInactive();

	// obj���͸� ��ȸ�鼭 itemchset�� ã�´�.
	for (auto& e : GetOwner()->GetObjectManager()->GetObjects())
	{
		ItemChest* itemchest = e->GetComponent<ItemChest>();
		if (itemchest != nullptr)
		{
			m_itemChests.push_back(itemchest);
		}
	}
}

void ItemDescUI::FixedUpdate(float dTime)
{

}

void ItemDescUI::Update(float dTime)
{

}

void ItemDescUI::LateUpdate(float dTime)
{
	// 	��ȸ
	for (auto& e : m_itemChests)
	{
		// 	m_isOpen�� true�� ��
		if (e->GetisOpen())
		{
			// ui�� ������Ѵ�
			m_isPresent = true;
			m_sprite->DrawActive();
			// 	itemType�� �´� ������ ����ش�.
			m_sprite->Trigger( static_cast<int>(e->GetItemType()));
			if (!m_forSound)
			{
				SoundManager::GetInstance()->PlayDoor1(eSOUNDKIND::fUI);
				m_forSound = true;
			}

			// �ڽ��� �ݴ´�
			e->SetisClose();
		}
	}
	// UI�� ��µǰ� ������
	if (m_isPresent == true)
	{
		// ����ð��� �����մϴ�.
		m_presentTime += dTime;
		// 3�ʵ��� �����ߴٸ�
		if (m_presentTime > 3.f)
		{
			// ����� �ߴ��մϴ�
			m_sprite->DrawInactive();
			m_presentTime = 0.f;
			m_isPresent = false;
			m_forSound = false;
		}
	}
}

void ItemDescUI::Render()
{
}

void ItemDescUI::Release()
{
}
