#include "pch.h"
#include "HandItem.h"
#include "Transform.h"
#include "GameObject.h"

HandItem::HandItem()
	: m_handModel(nullptr)
{

}

HandItem::~HandItem()
{

}

void HandItem::Start()
{
	m_pOwner->GetComponent<Transform>()->SetLocalPosition({ -100.f, -100.f,-100.f });
	m_renderer->Send(2, m_handModel->GetObjectID(), true, {});
}

void HandItem::Select()
{
	m_pOwner->GetComponent<Transform>()->SetLocalPosition({ 0.3f,-0.3f,1.f });
}

void HandItem::UnSelect()
{
	m_pOwner->GetComponent<Transform>()->SetLocalPosition({ -100.f, -100.f,-100.f });
}

void HandItem::Act(GameObject* player)
{
	
}

void HandItem::SetHandModel(GameObject* obj)
{
	m_handModel = obj;
}
