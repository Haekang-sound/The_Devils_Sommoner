#include "pch.h"
#include "GameManager.h"
#include "GameObject.h"
#include "HeartItem.h"
#include "DemonAltarComponent.h"

void GameManager::Init()
{
	std::vector<GameObject*> newAltar;
	newAltar.push_back(m_altar[1]);
	newAltar.push_back(m_altar[2]);
	newAltar.push_back(m_altar[0]);

	m_altar[1]->GetComponent<DemonAltarComponent>()->SetAltarNumber(AltarSequence::FirstAltar);
	m_altar[2]->GetComponent<DemonAltarComponent>()->SetAltarNumber(AltarSequence::SecondAltar);
	m_altar[0]->GetComponent<DemonAltarComponent>()->SetAltarNumber(AltarSequence::ThirdAltar);

	m_currentAltar = m_altar[1];
	SetCurrentAltarObject(m_currentAltar);
	m_altar.clear();
	m_altar = newAltar;

	// TEST : 임의 설정
	m_altarCount = 0;
}

void GameManager::Update()
{

}

void GameManager::Finalize()
{
	m_altar.clear();
	m_heartChest.clear();
}

void GameManager::SetNextAltar(int count)
{
	m_altarCount = count;
	if (m_altarCount < m_altar.size())
	{
		m_currentAltar = m_altar[m_altarCount];
	}
	m_heart->GetComponent<HeartItem>()->SetHeartAltar(m_currentAltar);
}

void GameManager::SetCurrentAltarObject(GameObject* altar)
{
	m_currentAltar = altar;
	m_heart->GetComponent<HeartItem>()->SetHeartAltar(altar);
}

