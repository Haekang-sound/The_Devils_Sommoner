#include "pch.h"
#include "IntroScene.h"

// 매니저
#include "EngineObjectManager.h"
#include "EngineResourceManager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "InputManager.h"
#include "SceneManager.h"

// 오브젝트
#include "GameObject.h"

// 컴포넌트
#include "CameraComponent.h"	
#include "AudioComponent.h"	
#include "Transform.h"	
#include "MeshRenderer.h"	
#include "Button.h"			// UI
#include "Timer.h"
#include "SpriteRenderer.h"
#include "HPUI.h"
#include "XRayUI.h"
#include "KnifeUI.h"


IntroScene::IntroScene()
{

}

IntroScene::~IntroScene()
{

}

void IntroScene::EditScene(EngineResourceManager* resourceManager, EngineObjectManager* objManager, TimeManager* timeManager, CollisionDetectManager* collisionDetectManager, PhysicsManager* physicsManager)
{
	m_resourceManager = resourceManager;
	m_objManager = objManager;
	m_timeManager = timeManager;
	m_gameManager = GameManager::GetInstance();

#pragma region UI

	ShowCursor(true);

	/// 배경
// 1. 중앙에 있을것
// 2. 또 있나? 
	{
		m_object = m_objManager->CreateObject();
		m_object->AddComponent<SpriteRenderer>();

		RECT rect;
		rect.left = -1920/2;
		rect.top = -1080/2;
		rect.bottom = 0;
		rect.right = 0;

		SpriteRenderer* sprite = m_object->GetComponent<SpriteRenderer>();
		sprite->SetLayer(10);
		sprite->SetAssetNum(static_cast<int>(EnumModel::Intro_BackGround));
		sprite->SetRect(rect);
		sprite->SetSize({ 1890, 1080 });

		m_objects.push_back(m_object);
	}

	/// Button
	// gamestart
	Button* startButton = nullptr;
	SpriteRenderer* startSprite = nullptr;
	{
		m_object = m_objManager->CreateObject();
		m_object->AddComponent<Button, SpriteRenderer>();

		startSprite = m_object->GetComponent<SpriteRenderer>();

		//m_object->GetComponent<Transform>()->SetLocalPosition({ 0.f,0.f,-1000.f });
		
		RECT spriteRect;
		spriteRect.left = 400;
		spriteRect.top = - 200;
		spriteRect.bottom = 0;
		spriteRect.right = 0;

		startSprite->SetRect(spriteRect);
		startSprite->SetSize({500,100});

		startSprite->SetLayer(10);
		startSprite->SetAssetNum(static_cast<int>(EnumModel::GameStart_Button));

		RECT rect;
// 		rect.left = 1390;
// 		rect.top = 625;
// 		rect.right = 1390 + 500;
// 		rect.bottom = 625 + 100;
		rect.left = 2500;
		rect.top = 855;
		rect.bottom = 980;
		rect.right = 3275;

		m_object->GetComponent<Button>()->SetButtonPos(rect);
		startButton = m_object->GetComponent<Button>();

		startButton->SetOnNormal([=](){ startSprite->SetSpriteState(0); });
		startButton->SetOnHover([=](){	startSprite->SetSpriteState(1); });
		startButton->SetOnClick([=]() {m_sceneManager->ChangeScene(SceneNumber::Title);});
		m_objects.push_back(m_object);

	}

	// gameExit
	Button*			exitButton = nullptr;
	SpriteRenderer* exitSprite = nullptr;
	{
		m_object = m_objManager->CreateObject();
		m_object->AddComponent<Button, SpriteRenderer>();

		exitSprite = m_object->GetComponent<SpriteRenderer>();

		RECT spriteRect;
		spriteRect.left = 400;
		spriteRect.top = -200 - 110 - 110;
		spriteRect.bottom = 0;
		spriteRect.right = 0;

		exitSprite->SetRect(spriteRect);
		exitSprite->SetSize({ 500,100 });
		exitSprite->SetLayer(10);
		exitSprite->SetAssetNum(static_cast<int>(EnumModel::Exit_Button));

		RECT rect;
// 		rect.left = 1390;
// 		rect.top = 840;
// 		rect.bottom = 840 + 100;
// 		rect.right = 1390 + 500;

		rect.left = 2500;
		rect.top = 1150;
		rect.bottom = 1285;
		rect.right = 3275;
		m_object->GetComponent<Button>()->SetButtonPos(rect);
		exitButton = m_object->GetComponent<Button>();

		exitButton->SetOnNormal([=]() { exitSprite->SetSpriteState(0); });
		exitButton->SetOnHover([=]() { exitSprite->SetSpriteState(1); });
		exitButton->SetOnClick([=]() { PostQuitMessage(0); });

		m_objects.push_back(m_object);

	}

	SpriteRenderer* helpMainsprite = nullptr;

	///GameHelpDesc
	{
		m_object = m_objManager->CreateObject();
		m_object->AddComponent<SpriteRenderer>();

		RECT rect;
		rect.left = -1920 / 2 + 100;
		rect.top = -1080 / 2 + 100;
		rect.bottom = 0;
		rect.right = 0;

		helpMainsprite = m_object->GetComponent<SpriteRenderer>();
		helpMainsprite->DrawInactive();
		helpMainsprite->SetLayer(1);
		helpMainsprite->SetAssetNum(static_cast<int>(EnumModel::Help_BackGround));
		helpMainsprite->SetRect(rect);
		helpMainsprite->SetSize({ 1920/1.2f, 1080/1.2f });

		m_objects.push_back(m_object);
	}

	///GameHelpDescBottonAfter
	Button* afterButton = nullptr;
	SpriteRenderer* afterSprite = nullptr;
	
	Button* beforeButton = nullptr;
	SpriteRenderer* beforeSprite  = nullptr;

	Button* closeButton = nullptr;
	SpriteRenderer* closeSprite = nullptr;
	{
		m_object = m_objManager->CreateObject();
		m_object->AddComponent<Button, SpriteRenderer>();

		afterSprite = m_object->GetComponent<SpriteRenderer>();



		RECT spriteRect;
		spriteRect.left = (1920 / 2) - 400;
		spriteRect.top = (-1080 / 2) + 100;
		spriteRect.bottom = 0;
		spriteRect.right = 0;

		afterSprite->SetRect(spriteRect);
		afterSprite->SetSize({200,100});
		afterSprite->SetAssetNum(static_cast<int>(EnumModel::After_Button));
		afterSprite->DrawInactive();

		RECT rect;
		rect.left = 1520;
		rect.top = 850;
		rect.bottom = 850 + 100;
		rect.right = 1520 + 120;

		rect.left = 2785;
		rect.top = 1120;
		rect.bottom = 1270;
		rect.right = 3020;

		afterSprite->SetLayer(0);
		m_object->GetComponent<Button>()->SetButtonPos(rect);
		afterButton = m_object->GetComponent<Button>();
		afterButton->SetDisabled();

		m_object->GetComponent<Button>()->SetOnNormal([=]() { afterSprite->SetSpriteState(0); });
		m_object->GetComponent<Button>()->SetOnHover([=]() { afterSprite->SetSpriteState(1); });
		m_object->GetComponent<Button>()->SetOnClick
		(
			[=]() 
			{
				if(*helpMainsprite->GetSate() < 4)
				{
					helpMainsprite->SetSpriteState(*helpMainsprite->GetSate()+1); 
				}
			}
		);

		m_objects.push_back(m_object);

	}


	///GameHelpDescBottonBefore
	{
		m_object = m_objManager->CreateObject();
		m_object->AddComponent<Button, SpriteRenderer>();

		beforeSprite = m_object->GetComponent<SpriteRenderer>();

		RECT spriteRect;
		spriteRect.left = (-1920 / 2) + 100;
		spriteRect.top = (-1080 / 2) + 100;
		spriteRect.bottom = 0;
		spriteRect.right = 0;

		beforeSprite->SetRect(spriteRect);
		beforeSprite->SetSize({200,100});

		beforeSprite->SetLayer(0);
		beforeSprite->SetAssetNum(static_cast<int>(EnumModel::Before_Button));
		beforeSprite->DrawInactive();

		RECT rect;
		rect.left = 120;
		rect.top = 850;
		rect.bottom = 850 + 100;
		rect.right = 120 + 120;

		rect.left = 250;
		rect.top = 1120;
		rect.bottom = 1270;
		rect.right = 470;
		m_object->GetComponent<Button>()->SetButtonPos(rect);
		beforeButton = m_object->GetComponent<Button>();
		beforeButton->SetDisabled();

		m_object->GetComponent<Button>()->SetOnNormal([=]() { beforeSprite->SetSpriteState(0); });
		m_object->GetComponent<Button>()->SetOnHover([=]() { beforeSprite->SetSpriteState(1); });
		m_object->GetComponent<Button>()->SetOnClick
		(
			[=]()
			{
				if (*helpMainsprite->GetSate() >= 1)
				{
					helpMainsprite->SetSpriteState(*helpMainsprite->GetSate() - 1);
				}

			}
		);

		m_objects.push_back(m_object);

	}
	Button* helpButton = nullptr;
	SpriteRenderer* helpsprite = nullptr;
	///GameHelpDescBottonClose
	{
		m_object = m_objManager->CreateObject();
		m_object->AddComponent<Button, SpriteRenderer>();

		closeSprite = m_object->GetComponent<SpriteRenderer>();

		RECT spriteRect;
		spriteRect.left = 653;
		spriteRect.top = 372;
		spriteRect.bottom = 0;
		spriteRect.right = 0;

		closeSprite->SetRect(spriteRect);

		closeSprite->SetLayer(0);
		closeSprite->SetAssetNum(static_cast<int>(EnumModel::Closs_Button));
		closeSprite->DrawInactive();

		RECT rect;
		rect.left = 1600;
		rect.top = 80;
		rect.bottom = 80 + 100;
		rect.right = 1600 + 100;
		
		rect.left = 2910;
		rect.top = 115;
		rect.bottom = 215;
		rect.right = 3050;
		m_object->GetComponent<Button>()->SetButtonPos(rect);
		closeButton = m_object->GetComponent<Button>();
		closeButton->SetDisabled();

		closeButton->SetOnNormal([=]() { closeSprite->SetSpriteState(0); });
		closeButton->SetOnHover([=]() { closeSprite->SetSpriteState(1); });
// 		closeButton->SetOnClick
// 		(
// 			[=]()
// 			{
// 				//helpButton->SetEnable();
// 				exitButton->SetEnable();
// 				startButton->SetEnable();
// 				//helpsprite->DrawActive();
// 				exitSprite->DrawActive();
// 				startSprite->DrawActive();
// 
// 				afterButton->SetDisabled();
// 				beforeButton->SetDisabled();
// 				closeButton->SetDisabled();
// 
// 				afterSprite->DrawInactive();
// 				beforeSprite->DrawInactive();
// 				closeSprite->DrawInactive();
// 
// 				helpMainsprite->DrawInactive();
// 			}
// 		);

		m_objects.push_back(m_object);

	}



	// gameHelp
// 	Button* helpButton = nullptr;
// 	SpriteRenderer* helpsprite = nullptr;
	{
		m_object = m_objManager->CreateObject();
		m_object->AddComponent<Button, SpriteRenderer>();

		helpsprite = m_object->GetComponent<SpriteRenderer>();
		m_helpSprite = m_object->GetComponent<SpriteRenderer>();

		RECT spriteRect;
		spriteRect.left = 400;
		spriteRect.top = -200 - 110; 
		spriteRect.bottom = 0;
		spriteRect.right = 0;

		helpsprite->SetRect(spriteRect);
		
		helpsprite->DrawActive();
		
		helpsprite->SetLayer(0);
		helpsprite->SetSize({ 500,100 });
		helpsprite->SetAssetNum(static_cast<int>(EnumModel::Help_Button));

		//957 1070
		RECT rect;
// 		rect.left = 1390;
// 		rect.top = 735;
// 		rect.bottom = 735 + 100;
// 		rect.right = 1390 + 500;

// 		rect.left = 2500;
// 		rect.top = 1000;
// 		rect.bottom = 1029;// +150;
// 		rect.right = 3275;

		rect.left = 2500;
		rect.top = 1005;
		rect.bottom = 1135;
		rect.right = 3275;
		m_object->GetComponent<Button>()->SetButtonPos(rect);
		helpButton = m_object->GetComponent<Button>();
		m_helpButton = m_object->GetComponent<Button>();

		helpButton->SetEnable();
		
		helpButton->SetOnNormal([=]() { helpsprite->SetSpriteState(0); });
		helpButton->SetOnHover([=]() { helpsprite->SetSpriteState(1); });
		helpButton->SetOnClick(
			[=]()
			{
				if ((helpMainsprite->GetIsDraw()))
				{
					m_helpButton->SetEnable();
					exitButton->SetEnable();
					startButton->SetEnable();
					m_helpSprite->DrawActive();
					exitSprite->DrawActive();
					startSprite->DrawActive();

					afterButton->SetDisabled();
					beforeButton->SetDisabled();
					closeButton->SetDisabled();

					afterSprite->DrawInactive();
					beforeSprite->DrawInactive();
					closeSprite->DrawInactive();
					
					helpMainsprite->DrawInactive();
				}
				else if(!(helpMainsprite->GetIsDraw()))
				{
					exitButton->SetDisabled();
					startButton->SetDisabled();
					m_helpButton->SetDisabled();

					exitSprite->DrawInactive();
					startSprite->DrawInactive();
					m_helpSprite->DrawInactive();

					afterButton->SetEnable();
					beforeButton->SetEnable();
					closeButton->SetEnable();

					afterSprite->DrawActive();
					beforeSprite->DrawActive();
					closeSprite->DrawActive();
					helpMainsprite->DrawActive();
				}

			}
		);
		m_objects.push_back(m_object);

		// 클로즈버튼
		closeButton->SetOnClick
		(
			[=]()
			{
				helpButton->SetEnable();
				exitButton->SetEnable();
				startButton->SetEnable();
				helpsprite->DrawActive();
				exitSprite->DrawActive();
				startSprite->DrawActive();

				afterButton->SetDisabled();
				beforeButton->SetDisabled();
				closeButton->SetDisabled();

				afterSprite->DrawInactive();
				beforeSprite->DrawInactive();
				closeSprite->DrawInactive();

				helpMainsprite->DrawInactive();
			}
		);

	}




#pragma endregion UI

	/// camera
	GameObject* player = nullptr;
	{
		m_object = m_objManager->CreateObject();
		player = m_object;
		m_object->SetName("Player");
		m_object->AddComponent<CameraComponent>();

		m_objects.push_back(m_object);

		m_gameManager->SetPlayerObject(m_object);
	}

}

void IntroScene::Awake()
{
	{
		for (auto& e : m_objects)
		{
			e->Awake();
		}
	}
}

void IntroScene::Start()
{
	for (auto& e : m_objects)
	{
		e->Start();
	}

	SoundManager::GetInstance().StopSound(SoundManager::GetInstance().GetBGMChannel());
	SoundManager::GetInstance().PlayBGM(eSOUNDKIND::bLobby);
}

void IntroScene::FixedUpdate(float dTime)
{
	for (auto& e : m_objects)
	{
		e->FixedUpdate(dTime);
	}
}

void IntroScene::Update(float dTime)
{
// 	for (auto e : m_objects)
// 	{
// 		if (e->GetComponent<AudioComponent>() != nullptr)
// 		{
// 			// 오디오 소스를 갖고있는 애들만 반복하며
// 			// 오디오 위치에서 플레이어 위치를 뺀 후
// 			// 그 값을 pos값에 넣어서 업데이트
// 			SimpleMath::Vector3 audioPos = e->GetComponent<Transform>()->GetPosition();
// 			SimpleMath::Vector3 listenerPos = m_audioListener->GetComponent<Transform>()->GetPosition();
// 			FMOD_VECTOR aVec = SoundManager::GetInstance().ConvertVector(audioPos, listenerPos);
// 			SoundManager::GetInstance().UpdatePos(aVec);
// 		}
// 	}

	for (auto& e : m_objects)
	{
		e->Update(dTime);
	}
}

void IntroScene::LateUpdate(float dTime)
{
	for (auto& e : m_objects)
	{
		e->LateUpdate(dTime);
	}
}

void IntroScene::Render()
{
	for (auto& e : m_objects)
	{
		e->Render();
	}
}

void IntroScene::End()
{
	m_objManager->Release(); // 오브젝트 매니저가 정리한다.
	m_objects.clear();
}

void IntroScene::EndLayer(unsigned int _layer)
{
	m_objManager->OffScene();
	m_objManager->ReleaseLayer(_layer); // 오브젝트매니저가 레이어 단위로 정리한다
	m_objects.clear();	// scene의 내용은 클리어한다
}

SceneNumber IntroScene::GetSceneNum()
{
	return SceneNumber();
}
