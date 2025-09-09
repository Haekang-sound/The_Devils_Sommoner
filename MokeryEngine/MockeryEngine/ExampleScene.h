#pragma once
#include "Scene.h"
// �Ŵ���
#include "ObjectManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"

class ExampleScene : public Scene
{
public:
	ExampleScene();
	~ExampleScene();

	// scene�� �����ɶ� �Ͼ�� �ൿ�� �Ѵ�.
	void Start(ResourceManager* resourceManager, ObjectManager* objManager, TimeManager* timeManager);

	// scene�� �����ϴ� ������Ʈ���� �ϰ� Update�Ѵ�.
	void Update(float dTime);

	// scene�� �����ϴ� ������Ʈ���� �ϰ� Render�Ѵ�.
	void Render(ID3DRenderer* renderer);

	// scene�� ������Ʈ���� �����Ѵ�.
	void End();

private:
	// scene�� �����ϴ� ������Ʈ��
	GameObject* m_object;
	std::vector<GameObject*> m_objects;

	ObjectManager* m_objManager;
	ResourceManager* m_resourceManager;
	TimeManager* m_timeManager;

};

