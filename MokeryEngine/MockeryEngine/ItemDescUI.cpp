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

	// obj벡터를 순회면서 itemchset를 찾는다.
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
	// 	순회
	for (auto& e : m_itemChests)
	{
		// 	m_isOpen가 true일 때
		if (e->GetisOpen())
		{
			// ui를 띄우기로한다
			m_isPresent = true;
			m_sprite->DrawActive();
			// 	itemType에 맞는 설명을 띄워준다.
			m_sprite->Trigger( static_cast<int>(e->GetItemType()));
			if (!m_forSound)
			{
				SoundManager::GetInstance()->PlayDoor1(eSOUNDKIND::fUI);
				m_forSound = true;
			}

			// 박스를 닫는다
			e->SetisClose();
		}
	}
	// UI가 출력되고 있을때
	if (m_isPresent == true)
	{
		// 전사시간을 누적합니다.
		m_presentTime += dTime;
		// 3초동안 전사했다면
		if (m_presentTime > 3.f)
		{
			// 출력을 중단합니다
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
