#pragma once
#include "Scene.h"
// 매니저
#include "ObjectManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"

class ExampleScene : public Scene
{
public:
	ExampleScene();
	~ExampleScene();

	// scene이 생성될때 일어나는 행동을 한다.
	void Start(ResourceManager* resourceManager, ObjectManager* objManager, TimeManager* timeManager);

	// scene에 존재하는 오브젝트들을 일괄 Update한다.
	void Update(float dTime);

	// scene에 존재하는 오브젝트들을 일괄 Render한다.
	void Render(ID3DRenderer* renderer);

	// scene의 오브젝트들을 해제한다.
	void End();

private:
	// scene에 존재하는 오브젝트들
	GameObject* m_object;
	std::vector<GameObject*> m_objects;

	ObjectManager* m_objManager;
	ResourceManager* m_resourceManager;
	TimeManager* m_timeManager;

};

