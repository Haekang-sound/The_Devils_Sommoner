#include "pch.h"
#include "EngineResourceManager.h"
#include "ResourceCreator.h"

EngineResourceManager::EngineResourceManager()
	: m_resourceFactory(nullptr), m_creator(nullptr) 
{
	m_resourceFactory = new ResourceFactory(); 
}

EngineResourceManager::~EngineResourceManager()
{
	delete m_resourceFactory;
	delete m_creator;
}

void EngineResourceManager::Init(KSL* soundmanager)
{
	m_creator = new ResourceCreator();
	m_creator->m_soundCreator = soundmanager;


}

void EngineResourceManager::Release()
{
	// ���ҽ����� ��ȸ�ϸ� �����Ѵ�.
	for (auto& e : m_resourceMap)
	{
 		e.second->ReleaseResource();
 		delete e.second;
	}
	m_resourceMap.clear();

}
