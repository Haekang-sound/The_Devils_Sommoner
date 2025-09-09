#include "pch.h"
#include "TitleScene.h"

// 매니저
#include "EngineObjectManager.h"
#include "EngineResourceManager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "SceneManager.h"

// 오브젝트
#include "GameObject.h"

// 컴포넌트
#include "Transform.h"
#include "Move.h"
#include "RenderComponent.h"
#include "Time.h"
#include "AudioComponent.h"
#include "AudioListener.h"
#include "PlayerController.h"
#include "CameraComponent.h"
#include "KnifeController.h"
#include "MeshRenderer.h"	// 랜더러 정보를 와따리 갔다리 해보자
#include "Button.h"
#include "Timer.h"
#include "SpriteRenderer.h"
#include "HPUI.h"
#include "XRayUI.h"
#include "StaminaUI.h"
#include "KnifeUI.h"
#include "EndingUI.h"

// 리소스
#include "Image.h"
#include "TestType.h"
#include "FBX.h"

// Test
#include "TileMap.h"
#include "AStarPathFindComponent.h"
#include "BoxCollision.h"
#include "SphereCollision.h"
#include "../Libraries/DXTK/Inc/SimpleMath.h"
#include "CollisionDetectManager.h"
#include "PhysicsManager.h"
#include "RigidBody.h"
#include "TestGyuComponent.h"
#include "RayComponent.h"
#include "Enemy.h"
#include "Blind.h"
#include "JaneD.h"
#include "Chaser.h"
#include "Ghost.h"
//#include "CollisionDetectManager.h"
#include "TileMapGenerator.h"
#include "PlayerComponent.h"
#include "ItemChest.h"
#include "DoorComponent.h"
#include "Inventory.h"
#include "Item.h"
#include "KnifeComponent.h"
#include "KnifeItem.h"
#include "HeartItem.h"
#include "HeartChest.h"
#include "ItemInteractionUI.h"
#include "ItemDescUI.h"
#include "DemonAltarComponent.h"
#include "HandItem.h"

TitleScene::TitleScene()
{

}

TitleScene::~TitleScene()
{

}

void TitleScene::EditScene(EngineResourceManager* resourceManager, EngineObjectManager* objManager, TimeManager* timeManager, CollisionDetectManager* collisionDetectManager, PhysicsManager* physicsManager)
{
	ShowCursor(false);
	// Scene 생성에 필요한 매니저 이식
	m_resourceManager = resourceManager;
	m_objManager = objManager;
	m_timeManager = timeManager;
	m_gameManager = GameManager::GetInstance();
	//m_inputManager = inputManager;


#pragma region UI

		/// 단검을 위한
	{
		SpriteRenderer* startSprite = nullptr;
		m_object = m_objManager->CreateObject();
		m_object->AddComponent< SpriteRenderer, KnifeUI>();

		startSprite = m_object->GetComponent<SpriteRenderer>();

		//m_object->GetComponent<Transform>()->SetLocalPosition({ 0.f,0.f,-1000.f });

		RECT spriteRect;
		spriteRect.left = 700;
		spriteRect.top = -500;
		spriteRect.bottom = 0;
		spriteRect.right = 0;

		startSprite->SetRect(spriteRect);
		startSprite->SetSize({ 200,200 });

		startSprite->SetLayer(10);
		startSprite->SetAssetNum(static_cast<int>(EnumModel::Knife_Icon));

		m_objects.push_back(m_object);

	}

	/// 타이머 
	{
		m_object = m_objManager->CreateObject();
		m_object->AddComponent<Timer, SpriteRenderer>();

		RECT rect;
		rect.left = -300;
		rect.top = 150;
		rect.bottom = 0;
		rect.right = 0;

		SpriteRenderer* sprite = m_object->GetComponent<SpriteRenderer>();
		sprite->DrawInactive();
		sprite->SetLayer(0);
		sprite->SetAssetNum(static_cast<int>(EnumModel::Timer));
		sprite->SetRect(rect);
		sprite->SetSize({ 600, 130 });


		Timer* timer = m_object->GetComponent<Timer>();

		m_objects.push_back(m_object);
	}

	/// 상호작용 팝업
	// hp팝업
	{
		m_object = m_objManager->CreateObject();
		m_object->AddComponent< HPUI/*, SpriteRenderer*/>();

		m_objects.push_back(m_object);
	}

	/// 크로스헤어
	// 1. 중앙에 있을것
	// 2. 또 있나? 
	{
		m_object = m_objManager->CreateObject();
		m_object->AddComponent<Button, SpriteRenderer>();

		RECT rect;
		rect.left = -10;
		rect.top = 10;
		rect.bottom = 0;
		rect.right = 0;

		SpriteRenderer* sprite = m_object->GetComponent<SpriteRenderer>();
		sprite->SetLayer(10);
		sprite->SetAssetNum(static_cast<int>(EnumModel::CrossHair_Icon));
		sprite->SetRect(rect);
		sprite->SetSize({ 20, 20 });

		m_objects.push_back(m_object);
	}

	/// 스테미나


	{
		m_object = m_objManager->CreateObject();
		m_object->AddComponent<SpriteRenderer, StaminaUI>();

		RECT rect;
		rect.left = -1920 / 2 + 100;
		rect.top = -600;
		rect.bottom = 0;
		rect.right = 0;

		m_object->GetComponent<Transform>()->SetLocalScale({ 8.f, 3.f,1.f });

		SpriteRenderer* sprite = m_object->GetComponent<SpriteRenderer>();
		sprite->SetLayer(10);
		sprite->SetAssetNum(static_cast<int>(EnumModel::Stamina));
		sprite->SetRect(rect);
		sprite->SetSize({ 1, 100 });

		m_objects.push_back(m_object);
	}


	/// 아이템 상호작용
	// ItemBox를 열때 상호작용정도를 표시하는 UIs
	{
		m_object = m_objManager->CreateObject();
		m_object->AddComponent<Button, /*SpriteRenderer,*/ ItemInteractionUI>();

		//SpriteRenderer* sprite = m_object->GetComponent<SpriteRenderer>();

		m_objects.push_back(m_object);
	}

	/// 아이템 설명작용
	// ItemBox를 열었을 때 아이템 설명을 띄워주는 UI
	{
		m_object = m_objManager->CreateObject();
		m_object->AddComponent<SpriteRenderer, ItemDescUI>();

		RECT rect;
		rect.left = -400;
		rect.top = 300;
		rect.bottom = 0;
		rect.right = 0;

		SpriteRenderer* sprite = m_object->GetComponent<SpriteRenderer>();
		sprite->SetLayer(0);
		sprite->SetAssetNum(static_cast<int>(EnumModel::ItemDesc_Icon));
		sprite->SetRect(rect);
		sprite->SetSize({ 800, 130 });

		m_objects.push_back(m_object);
	}

	/// XRay Item
	{
		// XRay를 위한 스프라이트 생성

		m_object = m_objManager->CreateObject();
		m_object->AddComponent< XRayUI> ();
		m_object->GetComponent<Transform>()->SetPosition({ 0.f,0.f, 1.f });

		XRayUI* xray = m_object->GetComponent<XRayUI>();

		m_objects.push_back(m_object);
	}

	/// EndingUI
	{
		// 오브젝트를 만든다.
		GameObject* ending = m_objManager->CreateObject();
		// 컴포넌트를 추가한다.
		ending->AddComponent< EndingUI, Button, SpriteRenderer >();
		// 스프라이트 사이즈를 정하기 위한 rect
		RECT rect;
		rect.left = -1920 / 2;
		rect.top = -1080 / 2;
		rect.bottom = 0;
		rect.right = 0;
		// 스프라이트를 임시 변수에 담는다.
		SpriteRenderer* sprite = ending->GetComponent<SpriteRenderer>();
		// 스프라이트 설정
		sprite->SetLayer(10);
		sprite->SetAssetNum(static_cast<int>(EnumModel::Ending_BackGround));
		sprite->SetRect(rect);
		sprite->SetSize({ 1890, 1080 });
		sprite->DrawInactive();

		// 버튼을 임시변수에 담는다.
		Button* endingbutton = ending->GetComponent<Button>();
		endingbutton->SetDisabled();
		// 버튼 크기 설정
		RECT rect_box;
		rect_box.left = 0;
		rect_box.top = 0;
		rect_box.bottom = 1080;
		rect_box.right = 1920;
		// 버튼 크기 적용
		endingbutton->SetButtonPos(rect_box);
		SceneManager* t = GetSceneManger();
		// 버튼 함수 설정
		endingbutton->SetOnPressed([=]() {
			endingbutton->SetDisabled();
			sprite->DrawInactive();
			DemonAltarComponent::m_altarCount = 0;
			t->ChangeScene(SceneNumber::Intro);
			//std::cout << " 엔딩씬" << std::endl;
			});


		m_objects.push_back(ending);
	}


#pragma endregion UI

#pragma region GameObject
	{
		{
			// player
			GameObject* player = nullptr;
			{
				m_object = m_objManager->CreateObject();
				player = m_object;
				m_object->SetName("Player");
				m_object->AddComponent<CameraComponent, PlayerController, Inventory, SphereCollision, PlayerComponent, RigidBody, RayComponent, AudioListener>();
				//m_object->GetComponent<SphereCollision>()->SetSize(SimpleMath::Vector3(3.f));
				m_object->GetComponent<SphereCollision>()->SetRadius(0.4f);
				m_object->GetComponent<SphereCollision>()->SetCollisionType(CollisionType::Dynamic);
				m_object->GetComponent<RayComponent>()->SetCollisionDetectManager(collisionDetectManager);
				m_object->GetComponent<Transform>()->SetPosition(SimpleMath::Vector3(72.f, 0.5f, 68.f));
				//collisionDetectManager->AddBoxCollision(m_object->GetComponent<BoxCollision>());
				collisionDetectManager->AddSphereCollision(m_object->GetComponent<SphereCollision>());
				physicsManager->AddRigidbody(m_object->GetComponent<RigidBody>());
				m_objects.push_back(m_object);

				m_gameManager->SetPlayerObject(m_object);
			}

			// Knife 아이템
			GameObject* knifeItem = nullptr;
			{
				m_object = m_objManager->CreateObject();
				knifeItem = m_object;
				m_object->SetName("KnifeItem");
				m_object->SetParentByGameObject(player);
				m_object->AddComponent<KnifeItem>();
				m_objects.push_back(m_object);

				{
					m_object = m_objManager->CreateObject();
					m_object->SetName("KnifeModel");
					m_object->AddComponent<MeshRenderer>();
					m_object->GetComponent<MeshRenderer>()->SetAssetNum(static_cast<int>(EnumModel::Knife));
					m_object->GetComponent<MeshRenderer>()->CreateModel();
					m_object->SetParentByGameObject(knifeItem);

					m_object->GetComponent<Transform>()->SetLocalScale({ 0.04f,0.04f,0.04f });
					float rot = -90.f * 3.141592f / 180.f;
					m_object->GetComponent<Transform>()->SetLocalRotation({ 0.f,rot,0.f });
					//m_object->GetComponent<Transform>()->SetLocalPosition({ 1.5f, -1.f, 1.5f });
					//m_object->GetComponent<Transform>()->SetLocalPosition({ 1.5f, -0.7f, 2.7f });
					m_objects.push_back(m_object);
				}
				{
					m_object = m_objManager->CreateObject();

					knifeItem->GetComponent<KnifeItem>()->SetHandModel(m_object);

					m_object->SetName("RightHandKnife");
					m_object->AddComponent<MeshRenderer>();
					m_object->GetComponent<MeshRenderer>()->SetAssetNum(static_cast<int>(EnumModel::RightHandKnife));
					m_object->GetComponent<MeshRenderer>()->CreateModel();
					//m_object->GetComponent<MeshRenderer>()->SetAnimationRepeat(true);
					//m_object->GetComponent<MeshRenderer>()->SetThisIsANIMATION();
					m_object->SetParentByGameObject(knifeItem);
					m_renderer->Send(2, m_object->GetObjectID(), true, {});
					m_object->GetComponent<Transform>()->SetLocalScale({ 0.04f,0.04f,0.04f });
					m_object->GetComponent<Transform>()->SetLocalPosition({ 0.3f,-0.3f,1.f });
					//float rot = -90.f * 3.141592f / 180.f;
					//m_object->GetComponent<Transform>()->SetLocalRotation({ 0.f,rot,0.f });
					//m_object->GetComponent<Transform>()->SetLocalPosition({ 1.5f, -0.7f, 2.7f });
					m_objects.push_back(m_object);
				}
			}

			GameObject* knifeObject = nullptr;
			{
				m_object = m_objManager->CreateObject();
				knifeObject = m_object;
				m_object->SetName("KnifeObject");
				m_object->AddComponent<SphereCollision, KnifeComponent>();
				collisionDetectManager->AddSphereCollision(m_object->GetComponent<SphereCollision>());
				m_object->GetComponent<SphereCollision>()->SetRadius(0.3f);
				m_object->GetComponent<SphereCollision>()->SetDebugCollisionColor(0.f, 1.f, 1.f, 1.f);
				m_object->GetComponent<SphereCollision>()->SetCollisionType(CollisionType::Dynamic);

				m_object->GetComponent<KnifeComponent>()->SetState(KnifeObjectState::Idle);
				m_object->GetComponent<KnifeComponent>()->SetSpeed(85.f);

				/*m_object->GetComponent<MeshRenderer>()->SetAssetNum(1);
				m_object->GetComponent<MeshRenderer>()->CreateModel();*/

				m_objects.push_back(m_object);
			}
			GameObject* knifeModel = nullptr;
			{
				m_object = m_objManager->CreateObject();
				knifeModel = m_object;
				m_object->SetName("KnifeModel");
				m_object->AddComponent<MeshRenderer>();
				m_object->GetComponent<MeshRenderer>()->SetAssetNum(static_cast<int>(EnumModel::Knife));
				m_object->GetComponent<MeshRenderer>()->CreateModel();
				m_object->SetParentByGameObject(knifeObject);
				m_objects.push_back(m_object);
			}
			knifeModel->GetComponent<Transform>()->SetLocalScale({ 0.04f,0.04f,0.04f });
			float rot = -90.f * 3.141592f / 180.f;
			knifeModel->GetComponent<Transform>()->SetLocalRotation({ 0.f,rot,0.f });
			// KnifeItem에 날라갈 오브젝트를 알려준다.
			knifeItem->GetComponent<KnifeItem>()->SetKnifeObject(knifeObject);

			/// 심장 아이템 
			GameObject* heartItem = nullptr;
			GameObject* heartModel = nullptr;
			{
				m_object = m_objManager->CreateObject();
				heartItem = m_object;
				m_object->SetName("HeartItem");
				m_object->SetParentByGameObject(player);
				m_object->AddComponent<HeartItem>();
				m_object->GetComponent<HeartItem>()->SetHeartBeatCycle(2.f);
				m_objects.push_back(m_object);
				{
					m_object = m_objManager->CreateObject();
					m_object->SetName("HeartModel");
					heartModel = m_object;
					m_object->AddComponent<MeshRenderer>();
					m_object->GetComponent<MeshRenderer>()->SetAssetNum(static_cast<int>(EnumModel::Heart));
					m_object->GetComponent<MeshRenderer>()->CreateModel();
					m_renderer->Send(2, m_object->GetObjectID(), true, {});
					m_object->SetParentByGameObject(heartItem);
					m_object->GetComponent<Transform>()->SetLocalScale({ 0.04f,0.04f,0.04f });
					float rot = 0.f * 3.141592f / 180.f;
					float rot2 = -90.f * 3.141592f / 180.f;
					m_object->GetComponent<Transform>()->SetLocalRotation({ rot2,rot,0.f });
					//m_object->GetComponent<Transform>()->SetLocalPosition({ 1.5f, -1.f, 1.5f });
					//m_object->GetComponent<Transform>()->SetLocalPosition({ 1.5f, -0.7f, 2.7f });
					m_objects.push_back(m_object);
				}
				{
					m_object = m_objManager->CreateObject();
					m_object->SetName("LeftHand");
					m_object->AddComponent<MeshRenderer>();
					m_object->GetComponent<MeshRenderer>()->SetAssetNum(static_cast<int>(EnumModel::LeftHand));
					m_object->GetComponent<MeshRenderer>()->CreateModel();
					m_object->GetComponent<MeshRenderer>()->SetThisIsANIMATION();

					m_renderer->Send(2, m_object->GetObjectID(), true, {});
					m_object->SetParentByGameObject(heartItem);
					float rotx = -40.f * 3.141592f / 180.f;
					float roty = -0.f * 3.141592f / 180.f;
					float rotz = 0.f * 3.141592f / 180.f;
					m_object->GetComponent<Transform>()->SetLocalRotation({ rotx,roty,rotz });
					m_object->GetComponent<Transform>()->SetLocalScale({ 0.04f,0.04f,0.04f });
					m_object->GetComponent<Transform>()->SetLocalPosition({ 0.f,-0.4f,-0.2f });

					m_objects.push_back(m_object);
				}
				// heartItem->GetComponent<HeartItem>()->SetHeartModel(heartModel);

				heartItem->GetComponent<HeartItem>()->SetHeartModelObject(heartModel);
			}

			GameObject* handItem = nullptr;
			GameObject* handModel = nullptr;
			{
				m_object = m_objManager->CreateObject();
				m_object->SetName("HandItem");
				handItem = m_object;
				m_object->AddComponent<HandItem>();
				m_object->GetComponent<HandItem>()->SetHandModel(handModel);
				m_object->SetParentByGameObject(player);
				m_objects.push_back(m_object);
				{
					m_object = m_objManager->CreateObject();
					handModel = m_object;
					handItem->GetComponent<HandItem>()->SetHandModel(m_object);

					m_object->SetName("HandModel");
					m_object->AddComponent<MeshRenderer>();
					m_object->GetComponent<MeshRenderer>()->SetAssetNum(static_cast<int>(EnumModel::RightHand));
					m_object->GetComponent<MeshRenderer>()->CreateModel();
					m_object->GetComponent<MeshRenderer>()->SetThisIsANIMATION();
					//m_object->GetComponent<MeshRenderer>()->SetAnimationRepeat(false);
					m_object->GetComponent<MeshRenderer>()->SetAnimationRepeat(true);
					m_renderer->Send(2, m_object->GetObjectID(), true, {});
					m_object->SetParentByGameObject(handItem);

					m_object->GetComponent<Transform>()->SetLocalScale({ 0.04f,0.04f,0.04f });

					//float rot = -90.f * 3.141592f / 180.f;
					//m_object->GetComponent<Transform>()->SetLocalRotation({ 0.f,rot,0.f });
					//m_object->GetComponent<Transform>()->SetLocalPosition({ 1.5f, -1.f, 1.5f });
					//m_object->GetComponent<Transform>()->SetLocalPosition({ 1.5f, -0.7f, 2.7f });
					m_objects.push_back(m_object);
				}
			}

			// 인벤토리에 아이템 추가 과정
			{
				player->GetComponent<Inventory>()->AddItem(knifeItem->GetComponent<KnifeItem>());
				player->GetComponent<Inventory>()->AddItem(heartItem->GetComponent<HeartItem>());
				player->GetComponent<Inventory>()->AddItem(handItem->GetComponent<HandItem>());
			}
			// GameManager 세팅
			{
				GameManager::GetInstance()->SetHeartObject(heartItem);
			}

			/// 아이템 상자
			{
				GameObject* itemChest = nullptr;
				GameObject* itemModel = nullptr;

				m_object = m_objManager->CreateObject();
				itemChest = m_object;
				m_object->SetName("ItemChest");
				m_object->AddComponent<BoxCollision, ItemChest>();
				collisionDetectManager->AddBoxCollision(m_object->GetComponent<BoxCollision>());
				m_object->GetComponent<BoxCollision>()->SetSize({ 0.2f, 0.2f, 0.2f });
				m_object->GetComponent<BoxCollision>()->SetDebugCollisionColor(0.5f, 0.5f, 1.f, 1.f);

				m_object->GetComponent<ItemChest>()->SetLoadTime(3.f);

				m_object->GetComponent<Transform>()->SetPosition({ -1.f, 0.f, 5.f });
				m_objects.push_back(m_object);

				{
					m_object = m_objManager->CreateObject();
					itemModel = m_object;
					m_object->SetName("ItemModel");
					m_object->AddComponent<MeshRenderer>();
					m_object->GetComponent<MeshRenderer>()->SetAssetNum(static_cast<int>(EnumModel::ItemBox));
					m_object->GetComponent<MeshRenderer>()->CreateModel();
					m_object->SetParentByGameObject(itemChest);
					m_object->GetComponent<Transform>()->SetLocalScale({ 0.01f,0.01f,0.01f });
					m_objects.push_back(m_object);
				}
				itemChest->GetComponent<ItemChest>()->SetItemChestModelObject(itemModel);
			}

		}

		{
			// Astar 예시
			//m_resourceManager->LoadResource<TileMap>("..\\Resources\\MapData\\m8.txt");
			//Resource<TileMap>* tilemap = m_resourceManager->GetResource<TileMap>("..\\Resources\\MapData\\m8.txt");
			m_resourceManager->LoadResource<TileMap>("..\\Resources\\MapData\\TDS_4.txt");
			Resource<TileMap>* tilemap = m_resourceManager->GetResource<TileMap>("..\\Resources\\MapData\\TDS_4.txt");

			m_object = m_objManager->CreateObject();
			m_object->SetName("Blind");
			m_object->AddComponent<Blind, AStarPathFindComponent, BoxCollision, MeshRenderer, RayComponent, AudioComponent>();
			//m_object->GetComponent<Enemy>()->SetSpeed(5.f);
			//m_object->GetComponent<Chaser>()->
			m_object->GetComponent<RayComponent>()->SetCollisionDetectManager(collisionDetectManager);
			m_object->GetComponent<BoxCollision>()->SetDebugCollisionColor(0.f, 1.f, 0.f, 1.f);
			m_object->GetComponent<BoxCollision>()->SetSize({ 0.3f,1.0f,0.3f });
			m_object->GetComponent<Blind>()->SetPlayerObject(m_gameManager->GetPlayerObject());
			m_object->GetComponent<Blind>()->SetEngineObjectManager(objManager);
			m_object->GetComponent<Blind>()->SetObjectVectorTarget(&m_objects);
			m_object->GetComponent<Blind>()->SetEnemyModel(EnumModel::EnemyBlind);



			m_object->GetComponent<Blind>()->SetStartPos(21, 36);
			m_object->GetComponent<AStarPathFindComponent>()->SetTileMap(tilemap->m_type);
			//m_object->GetComponent<AStarPathFindComponent>()->SetStartPos({ 0,0 });
			m_object->GetComponent<AStarPathFindComponent>()->SetDestination({ 1, 1 });
			m_object->GetComponent<AStarPathFindComponent>()->SetTileSize(2.f);

			collisionDetectManager->AddBoxCollision(m_object->GetComponent<BoxCollision>());
			m_objects.push_back(m_object);
			GameManager::GetInstance()->SetBlindObject(m_object);


			m_object = m_objManager->CreateObject();
			m_object->SetName("JaneD");

			m_object->AddComponent<JaneD, AStarPathFindComponent, Transform, BoxCollision, MeshRenderer, RayComponent, AudioComponent>();
			//m_object->GetComponent<Enemy>()->SetSpeed(5.f);
			//m_object->GetComponent<Chaser>()->
			m_object->GetComponent<RayComponent>()->SetCollisionDetectManager(collisionDetectManager);
			m_object->GetComponent<BoxCollision>()->SetDebugCollisionColor(0.f, 0.f, 1.f, 1.f);
			m_object->GetComponent<BoxCollision>()->SetSize({ 0.3f,1.0f,0.3f });
			m_object->GetComponent<JaneD>()->SetPlayerObject(m_gameManager->GetPlayerObject());
			m_object->GetComponent<JaneD>()->SetEngineObjectManager(objManager);
			m_object->GetComponent<JaneD>()->SetObjectVectorTarget(&m_objects);
			m_object->GetComponent<JaneD>()->SetEnemyModel(EnumModel::EnemyJaneD);
			m_object->GetComponent<JaneD>()->SetStartPos(27, 9);
			m_object->GetComponent<AStarPathFindComponent>()->SetTileMap(tilemap->m_type);
			//m_object->GetComponent<AStarPathFindComponent>()->SetStartPos({ 0,0 });
			m_object->GetComponent<AStarPathFindComponent>()->SetDestination({ 1, 1 });
			m_object->GetComponent<AStarPathFindComponent>()->SetTileSize(2.f);

			collisionDetectManager->AddBoxCollision(m_object->GetComponent<BoxCollision>());
			m_objects.push_back(m_object);
			GameManager::GetInstance()->SetJaneDObject(m_object);


			m_object = m_objManager->CreateObject();
			m_object->SetName("Chaser");

			m_object->AddComponent<Chaser, AStarPathFindComponent, BoxCollision, MeshRenderer, RayComponent, AudioComponent>();
			//m_object->GetComponent<Enemy>()->SetSpeed(5.f);
			//m_object->GetComponent<Chaser>()->
			m_object->GetComponent<RayComponent>()->SetCollisionDetectManager(collisionDetectManager);
			m_object->GetComponent<BoxCollision>()->SetDebugCollisionColor(1.f, 0.f, 0.f, 1.f);
			m_object->GetComponent<BoxCollision>()->SetSize({ 0.3f,1.f,0.3f });
			m_object->GetComponent<Chaser>()->SetPlayerObject(m_gameManager->GetPlayerObject());
			m_object->GetComponent<Chaser>()->SetEngineObjectManager(objManager);
			m_object->GetComponent<Chaser>()->SetObjectVectorTarget(&m_objects);
			m_object->GetComponent<Chaser>()->SetEnemyModel(EnumModel::EnemyChaser);
			//m_object->GetComponent<Chaser>()->SetStartPos(3, 1);
			m_object->GetComponent<Chaser>()->SetStartPos(1, 1);
			m_object->GetComponent<AStarPathFindComponent>()->SetTileMap(tilemap->m_type);
			//m_object->GetComponent<AStarPathFindComponent>()->SetStartPos({ 0,0 });
			m_object->GetComponent<AStarPathFindComponent>()->SetDestination({ 1, 1 });
			m_object->GetComponent<AStarPathFindComponent>()->SetTileSize(2.f);
			collisionDetectManager->AddBoxCollision(m_object->GetComponent<BoxCollision>());
			m_objects.push_back(m_object);
			GameManager::GetInstance()->SetChaserObject(m_object);


			m_object = m_objManager->CreateObject();
			m_object->SetName("Ghost");

			m_object->AddComponent<Ghost, AStarPathFindComponent, MeshRenderer, AudioComponent>();
			m_object->GetComponent<Ghost>()->SetPlayerObject(m_gameManager->GetPlayerObject());
			m_object->GetComponent<Ghost>()->SetEngineObjectManager(objManager);
			m_object->GetComponent<Ghost>()->SetObjectVectorTarget(&m_objects);
			m_object->GetComponent<Ghost>()->SetEnemyModel(EnumModel::EnemyGhost);
			m_object->GetComponent<Ghost>()->SetStartPos(20, 20);
			m_object->GetComponent<AStarPathFindComponent>()->SetTileMap(tilemap->m_type);
			m_object->GetComponent<AStarPathFindComponent>()->SetStartPos({ 0,0 });
			m_object->GetComponent<AStarPathFindComponent>()->SetDestination({ 1, 1 });
			m_object->GetComponent<AStarPathFindComponent>()->SetTileSize(2.f);
			m_objects.push_back(m_object);
			GameManager::GetInstance()->SetGhostObject(m_object);


			//// Test3
			m_object = m_objManager->CreateObject();
			m_object->SetName("TileMapGenerator");

			m_object->GetComponent<Transform>()->SetPosition(SimpleMath::Vector3(0.f, 0.f, 0.f));
			m_object->AddComponent<TileMapGenerator>();
			m_object->GetComponent<TileMapGenerator>()->SetEngineObjectManager(objManager);
			m_object->GetComponent<TileMapGenerator>()->SetRenderer(m_renderer);
			m_object->GetComponent<TileMapGenerator>()->SetCollisionDetectManager(collisionDetectManager);
			m_object->GetComponent<TileMapGenerator>()->SetObjectVectorTarget(&m_objects);
			m_object->GetComponent<TileMapGenerator>()->SetTileMap(tilemap->m_type);
			m_object->GetComponent<TileMapGenerator>()->SetBlockSize(2.f);
			m_objects.push_back(m_object);
		}
	}
#pragma endregion GameObject




	/// 오디오 리스너 컴포넌트를 가진 오브젝트(플레이어)를 등록한다.
	for (auto e : m_objects)
	{
		if (e->GetComponent<AudioListener>() != nullptr)
		{
			m_audioListener = e;
		}
	}
}

void TitleScene::Awake()
{
	{
		for (auto& e : m_objects)
		{
			e->Awake();
		}
	}
}

void TitleScene::Start()
{
	GameManager::GetInstance()->Init();
	for (auto& e : m_objects)
	{
		e->Start();
	}

	SoundManager::GetInstance().StopSound(SoundManager::GetInstance().GetBGMChannel());
	SoundManager::GetInstance().PlayBGM(eSOUNDKIND::bMain);
	SoundManager::GetInstance().AddReverbParam(SoundManager::GetInstance().GetBGMChannel(), 0.2f);
	SoundManager::GetInstance().SetPriority(SoundManager::GetInstance().GetBGMChannel(), 0.0f);
}

void TitleScene::Update(float dTime)
{
	int count = 0;
	for (auto e : SoundManager::GetInstance().GetAudioComps())
	{
		// Audio컴포넌트를 가진 애들을 돌면서
		// 3d사운드 내는 애들의 위치를 업데이트해준다
		FMOD_VECTOR audioPos = e->GetComponent<AudioComponent>()->GetAudioPos();
		//SoundManager::GetInstance().UpdateSoundPos(audioPos, e->GetName());
		/// 마지막에 사용할 건 이거
		SoundManager::GetInstance().UpdateSoundPos(audioPos, count);
		/*SoundManager::GetInstance().UpdateSoundPos(audioPos, m_channels[count]);
		FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f };
		break;*/
		count++;
	}


	for (auto& e : m_objects)
	{
		e->Update(dTime);
	}

}

void TitleScene::LateUpdate(float dTime)
{
	for (auto& e : m_objects)
	{
		e->LateUpdate(dTime);
	}
}

void TitleScene::Render()
{
	for (auto& e : m_objects)
	{
		e->Render();
	}
}

void TitleScene::End()
{
	m_objManager->Release(); // 오브젝트 매니저가 정리한다.
	m_objects.clear();

}

void TitleScene::EndLayer(unsigned int _layer)
{
	m_objManager->OffScene();
	m_objManager->ReleaseLayer(_layer); // 오브젝트매니저가 레이어 단위로 정리한다
	m_objects.clear();	// scene의 내용은 클리어한다

}

SceneNumber TitleScene::GetSceneNum()
{
	return m_myNum;
}

FMOD::Channel* TitleScene::GetChannel(int index)
{
	return m_channels[index];
}

void TitleScene::FixedUpdate(float dTime)
{
	for (auto& e : m_objects)
	{
		e->FixedUpdate(dTime);
	}
}
