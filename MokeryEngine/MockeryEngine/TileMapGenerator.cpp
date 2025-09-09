#include "pch.h"
#include "TileMapGenerator.h"
#include "TileMap.h"
#include "EngineObjectManager.h"
#include "CollisionDetectManager.h"
#include "../Graphics/ID3DRenderer.h"
#include "GameObject.h"
#include "BoxCollision.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "../Libraries/DXTK/Inc/SimpleMath.h"
#include "DoorComponent.h"
#include "AudioComponent.h"
#include "CommonStructs.h"
#include "DemonAltarComponent.h"
#include "GameManager.h"
#include "ItemChest.h"
#include "HeartChest.h"

TileMapGenerator::TileMapGenerator()
	: m_tileMap(nullptr),
	m_objManager(nullptr),
	m_collisionDetectManager(nullptr),
	m_blockSize(0.f),
	m_objectVector(nullptr),
	m_altarCount(0)
{

}

TileMapGenerator::~TileMapGenerator()
{

}

void TileMapGenerator::Awake()
{
	GenerateMap();
}

void TileMapGenerator::Start()
{
}

void TileMapGenerator::FixedUpdate(float dTime)
{

}

void TileMapGenerator::Update(float dTime)
{

}

void TileMapGenerator::LateUpdate(float dTime)
{

}

void TileMapGenerator::Render()
{

}

void TileMapGenerator::Release()
{

}

void TileMapGenerator::SetObjectVectorTarget(std::vector<GameObject*>* objectVector)
{
	m_objectVector = objectVector;
}

void TileMapGenerator::SetCollisionDetectManager(CollisionDetectManager* detectManger)
{
	m_collisionDetectManager = detectManger;
}

void TileMapGenerator::SetEngineObjectManager(EngineObjectManager* engineObjectManager)
{
	m_objManager = engineObjectManager;
}

void TileMapGenerator::SetRenderer(ID3DRenderer* renderer)
{
	m_renderer = renderer;
}

void TileMapGenerator::SetTileMap(TileMap* tileMap)
{
	m_tileMap = tileMap;
}

//void TileMapGenerator::SetGroundTileMap(TileMap* groundTileMap)
//{
//	m_groundTileMap = groundTileMap;
//}

void TileMapGenerator::GenerateMap()
{
	int size = m_tileMap->GetTileMapSize();

	// 내 위치 기준으로 생성
	SimpleMath::Vector3 myPos = m_pOwner->GetComponent<Transform>()->GetPosition();

	// 일단 바닥이랑 천장을 깔아준다
	MakeGroundObject(size * m_blockSize / 4, size * m_blockSize / 4);

	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			if (m_tileMap->GetTileMap()[y][x] == static_cast<int>(TileType::Floor))
			{
				//GameObject* ground = MakeGroundObject(y, x);
			}
			else if (m_tileMap->GetTileMap()[y][x] == static_cast<int>(TileType::Door_1))
			{
				GameObject* door = MakeDoor1Object(y, x);
			}
			else if (m_tileMap->GetTileMap()[y][x] == static_cast<int>(TileType::Door_2))
			{
				GameObject* door = MakeDoor2Object(y, x);
			}
			else if (m_tileMap->GetTileMap()[y][x] == static_cast<int>(TileType::DevilAltar))
			{
				MakeAltarObject(y, x);
			}
			else if (m_tileMap->GetTileMap()[y][x] == static_cast<int>(TileType::ItemBox_1))
			{
				GameObject* obj = MakeItemBox(y, x, 3);
			}
			else if (m_tileMap->GetTileMap()[y][x] == static_cast<int>(TileType::ItemBox_2))
			{
				GameObject* obj = MakeItemBox(y, x, 0);
			}
			else if (m_tileMap->GetTileMap()[y][x] == static_cast<int>(TileType::ItemBox_3))
			{
				GameObject* obj = MakeItemBox(y, x, 1);
			}
			else if (m_tileMap->GetTileMap()[y][x] == static_cast<int>(TileType::ItemBox_4))
			{
				GameObject* obj = MakeItemBox(y, x, 2);
			}
			else if (m_tileMap->GetTileMap()[y][x] == static_cast<int>(TileType::HeartBox_1))
			{
				GameObject* obj = MakeHeartBox(y, x, 2);
			}
			else if (m_tileMap->GetTileMap()[y][x] == static_cast<int>(TileType::HeartBox_2))
			{
				GameObject* obj = MakeHeartBox(y, x, 3);
			}
			else if (m_tileMap->GetTileMap()[y][x] == static_cast<int>(TileType::HeartBox_3))
			{
				GameObject* obj = MakeHeartBox(y, x, 0);
			}
			else if (m_tileMap->GetTileMap()[y][x] == static_cast<int>(TileType::HeartBox_4))
			{
				GameObject* obj = MakeHeartBox(y, x, 1);
			}
			else
			{
				GameObject* gameObject = m_objManager->CreateObject();
				gameObject->SetName(std::format("Tile_{}_{}", y, x));
				//gameObject->AddComponent<BoxCollision, MeshRenderer>();
				gameObject->AddComponent<BoxCollision>();
				gameObject->GetComponent<BoxCollision>()->SetSize(SimpleMath::Vector3(1.0f,3.f,1.f));
				// 이 부분 수정할 수 있음
				gameObject->GetComponent<BoxCollision>()->SetCollisionType(CollisionType::Static);

				m_collisionDetectManager->AddBoxCollision(gameObject->GetComponent<BoxCollision>());
				gameObject->GetComponent<Transform>()->SetPosition(SimpleMath::Vector3(myPos.x + (y * m_blockSize), myPos.y, myPos.z + (x * m_blockSize)));
				gameObject->GetComponent<Transform>()->UpdateTransform();
				gameObject->SetParentByGameObject(this->m_pOwner);


				// Mesh Renderer
				GameObject* modelGameObject = m_objManager->CreateObject();
				modelGameObject->SetName(std::format("Tile_{}_{}_model", y, x));
				modelGameObject->AddComponent<MeshRenderer>();
				modelGameObject->GetComponent<MeshRenderer>()->SetAssetNum(static_cast<int>(EnumModel::Wall));
				modelGameObject->GetComponent<MeshRenderer>()->CreateModel();
				m_renderer->Send(11, modelGameObject->GetObjectID(), 1, {});
				m_renderer->Send(12, modelGameObject->GetObjectID(), 0.5, {});
				modelGameObject->SetParentByGameObject(gameObject);

				modelGameObject->GetComponent<Transform>()->SetScale({ 0.0034f,0.0034f,0.0034f });

				//float rot = 45.f * 3.141592f / 180.f;
				//modelGameObject->GetComponent<Transform>()->SetLocalRotation({ 0.f, rot, 0.f });
				//modelGameObject->GetComponent<Transform>()->SetLocalPosition({ 0.f, -1.f, 0.f });
				modelGameObject->GetComponent<Transform>()->SetLocalPosition({ 0.f, -1.f, 0.f });

				m_objectVector->push_back(gameObject);
				m_objectVector->push_back(modelGameObject);

				//gameObject->Start();
				//modelGameObject->Start();
			}
		}
	}

}

//void TileMapGenerator::GenerateGround()
//{
//	// 잠만, 할 필요가 없네
//}

void TileMapGenerator::SetBlockSize(const float& size)
{
	m_blockSize = size;
}

GameObject* TileMapGenerator::MakeDoor1Object(int y, int x)
{


	// 문 만드는 중
	GameObject* door = nullptr;
	GameObject* door1 = nullptr;
	GameObject* door2 = nullptr;
	GameObject* doorFrameModel = nullptr;
	GameObject* doorModel = nullptr;
	{
		// 문의 최상위 오브젝트
		door = m_objManager->CreateObject();
		door->SetName(std::format("Door_{}_{}", y, x));
		door->AddComponent<BoxCollision>();
		//m_collisionDetectManager->AddBoxCollision(door->GetComponent<BoxCollision>());
		door->GetComponent<BoxCollision>()->SetSize({ 1.f,1.f,1.f });
		door->GetComponent<BoxCollision>()->SetDebugCollisionColor(0.f, 1.f, 0.f, 1.f);

		m_objectVector->push_back(door);

		{
			doorFrameModel = m_objManager->CreateObject();
			doorFrameModel->SetName(std::format("Door_{}_{}_FrameModel", y, x));
			doorFrameModel->AddComponent<MeshRenderer>();
			doorFrameModel->GetComponent<MeshRenderer>()->SetAssetNum(static_cast<int>(EnumModel::DoorFrame));
			doorFrameModel->GetComponent<MeshRenderer>()->CreateModel();
			doorFrameModel->SetParentByGameObject(door);
			doorFrameModel->GetComponent<Transform>()->SetScale({ 0.0034f,0.0034f,0.0034f });
			doorFrameModel->GetComponent<Transform>()->SetLocalPosition({ -2.f, -1.f, 0.f });

			m_objectVector->push_back(doorFrameModel);
		}
	}
	{
		door1 = m_objManager->CreateObject();
		door1->GetComponent<Transform>()->SetLocalPosition({ -1.5f, 0.f, 0.f });	// 오차 2맞춰주면댐
		door1->SetName(std::format("Door_{}_{}_1", y, x));
		door1->SetParentByGameObject(door);
		m_objectVector->push_back(door1);
	}
	{
		// 문 본체
		door2 = m_objManager->CreateObject();
		door2->SetName(std::format("Door_{}_{}_2", y, x));
		door2->AddComponent<BoxCollision, DoorComponent, AudioComponent>();
		m_collisionDetectManager->AddBoxCollision(door2->GetComponent<BoxCollision>());
		door2->GetComponent<DoorComponent>()->SetLoadTime(3.f);
		door2->GetComponent<BoxCollision>()->SetSize({ 0.5f,1.0f,0.05f });
		door2->GetComponent<BoxCollision>()->SetDebugCollisionColor(0.f, 0.f, 1.f, 1.f);
		door2->SetParentByGameObject(door1);

		Transform* transform = door2->GetComponent<Transform>();
		SimpleMath::Vector3 pos = transform->GetPosition();
		pos.x += ((y)*m_blockSize);
		pos.z += ((x)*m_blockSize);
		transform->SetPosition(pos);

		SimpleMath::Vector3 door2LocalPosition = door->GetComponent<Transform>()->GetLocalPosition();
		door2LocalPosition.x -= 0.5f;	// 오차
		door2->GetComponent<Transform>()->SetLocalPosition(door2LocalPosition);
		door2->GetComponent<DoorComponent>()->SetDoorObject(door1);


		m_objectVector->push_back(door2);

		{
			doorModel = m_objManager->CreateObject();
			doorModel->SetName(std::format("Door_{}_{}_Model", y, x));
			doorModel->AddComponent<MeshRenderer>();
			doorModel->GetComponent<MeshRenderer>()->SetAssetNum(static_cast<int>(EnumModel::Door));
			doorModel->GetComponent<MeshRenderer>()->CreateModel();
			doorModel->GetComponent<Transform>()->SetScale({ 0.0034f,0.0034f,0.0034f });
			float rot = 180.f * 3.141592f / 180.f;
			doorModel->GetComponent<Transform>()->SetLocalRotation({ 0.f,rot,0.f });
			doorModel->GetComponent<Transform>()->SetLocalPosition({ 0.f, -1.f, 0.f });
			doorModel->SetParentByGameObject(door2);

			m_objectVector->push_back(doorModel);
		}
		door2->GetComponent<DoorComponent>()->SetDoorModelObject(doorModel);
	}

	// ground
	/*{
		GameObject* ground = m_objManager->CreateObject();
		ground->SetName(std::format("Ground_{}_{}_model", y, x));
		ground->AddComponent<MeshRenderer>();
		ground->GetComponent<MeshRenderer>()->SetAssetNum(static_cast<int>(EnumModel::Ground));
		ground->GetComponent<MeshRenderer>()->CreateModel();
		ground->SetParentByGameObject(door);
		ground->GetComponent<Transform>()->SetScale({ 0.0034f,0.0034f,0.0034f });
		ground->GetComponent<Transform>()->SetLocalPosition({ -2.f, -1.f, 0.f });
		m_objectVector->push_back(ground);
	}
	{
		GameObject* ceiling = m_objManager->CreateObject();
		ceiling->SetName(std::format("Ceiling_{}_{}_model", y, x));
		ceiling->AddComponent<MeshRenderer>();
		ceiling->GetComponent<MeshRenderer>()->SetAssetNum(static_cast<int>(EnumModel::Ceiling));
		ceiling->GetComponent<MeshRenderer>()->CreateModel();
		ceiling->SetParentByGameObject(door);

		ceiling->GetComponent<Transform>()->SetScale({ 0.0034f,0.0034f,0.0034f });
		float rot = 180.f * 3.141592f / 180.f;
		ceiling->GetComponent<Transform>()->SetLocalRotation({ rot, 0.f, 0.f });
		ceiling->GetComponent<Transform>()->SetLocalPosition({ -2.f,2.4f, 0.0f });
		m_objectVector->push_back(ceiling);
	}*/

	Transform* transform = door->GetComponent<Transform>();
	SimpleMath::Vector3 pos = transform->GetPosition();
	pos.x += ((y + 1) * m_blockSize);
	pos.z += ((x)*m_blockSize);
	transform->SetPosition(pos);
	return door;
}

GameObject* TileMapGenerator::MakeDoor2Object(int y, int x)
{
	// 문 만드는 중
	GameObject* door = nullptr;
	GameObject* door1 = nullptr;
	GameObject* door2 = nullptr;
	GameObject* doorFrameModel = nullptr;
	GameObject* doorModel = nullptr;
	{
		// 문의 최상위 오브젝트
		door = m_objManager->CreateObject();
		door->SetName(std::format("Door_{}_{}", y, x));
		door->AddComponent<BoxCollision>();
		//m_collisionDetectManager->AddBoxCollision(door->GetComponent<BoxCollision>());
		door->GetComponent<BoxCollision>()->SetSize({ 1.f,1.f,1.f });
		door->GetComponent<BoxCollision>()->SetDebugCollisionColor(0.f, 1.f, 0.f, 1.f);

		m_objectVector->push_back(door);

		{
			doorFrameModel = m_objManager->CreateObject();
			doorFrameModel->SetName(std::format("Door_{}_{}_FrameModel", y, x));
			doorFrameModel->AddComponent<MeshRenderer>();
			doorFrameModel->GetComponent<MeshRenderer>()->SetAssetNum(static_cast<int>(EnumModel::DoorFrame));
			doorFrameModel->GetComponent<MeshRenderer>()->CreateModel();
			doorFrameModel->SetParentByGameObject(door);
			doorFrameModel->GetComponent<Transform>()->SetScale({ 0.0034f,0.0034f,0.0034f });
			doorFrameModel->GetComponent<Transform>()->SetLocalPosition({ -2.f, -1.f, 0.f });

			m_objectVector->push_back(doorFrameModel);
		}
	}
	{
		door1 = m_objManager->CreateObject();
		//door1->AddComponent<BoxCollision>();	// 중심 디버깅 용
		//door1->GetComponent<BoxCollision>()->SetDebugCollisionColor(0.f, 1.f, 1.f, 1.f);
		door1->GetComponent<Transform>()->SetLocalPosition({ -1.5f, 0.f, 0.f });	// 오차 2맞춰주면댐
		door1->SetName(std::format("Door_{}_{}_1", y, x));
		door1->SetParentByGameObject(door);
		m_objectVector->push_back(door1);


	}
	{
		// 문 본체
		door2 = m_objManager->CreateObject();
		door2->SetName(std::format("Door_{}_{}_2", y, x));
		door2->AddComponent<BoxCollision, DoorComponent, AudioComponent>();
		m_collisionDetectManager->AddBoxCollision(door2->GetComponent<BoxCollision>());
		door2->GetComponent<DoorComponent>()->SetLoadTime(3.f);
		door2->GetComponent<BoxCollision>()->SetSize({ 0.5f,1.0f,0.05f });
		door2->GetComponent<BoxCollision>()->SetDebugCollisionColor(0.f, 0.f, 1.f, 1.f);
		door2->SetParentByGameObject(door1);

		Transform* transform = door2->GetComponent<Transform>();
		SimpleMath::Vector3 pos = transform->GetPosition();
		pos.x += ((y)*m_blockSize);
		pos.z += ((x)*m_blockSize);
		transform->SetPosition(pos);

		SimpleMath::Vector3 door2LocalPosition = door->GetComponent<Transform>()->GetLocalPosition();
		door2LocalPosition.x -= 0.5f;	// 오차
		door2->GetComponent<Transform>()->SetLocalPosition(door2LocalPosition);
		door2->GetComponent<DoorComponent>()->SetDoorObject(door1);

		m_objectVector->push_back(door2);

		{
			doorModel = m_objManager->CreateObject();
			doorModel->SetName(std::format("Door_{}_{}_Model", y, x));
			doorModel->AddComponent<MeshRenderer>();
			doorModel->GetComponent<MeshRenderer>()->SetAssetNum(static_cast<int>(EnumModel::Door));
			doorModel->GetComponent<MeshRenderer>()->CreateModel();
			doorModel->GetComponent<Transform>()->SetScale({ 0.0034f,0.0034f,0.0034f });
			float rot = 180.f * 3.141592f / 180.f;
			doorModel->GetComponent<Transform>()->SetLocalRotation({ 0.f,rot,0.f });
			doorModel->GetComponent<Transform>()->SetLocalPosition({ 0.f, -1.f, 0.f });
			doorModel->SetParentByGameObject(door2);

			m_objectVector->push_back(doorModel);
		}
		door2->GetComponent<DoorComponent>()->SetDoorModelObject(doorModel);
	}

	// ground
	//{
	//	GameObject* ground = m_objManager->CreateObject();
	//	ground->SetName(std::format("Ground_{}_{}_model", y, x));
	//	ground->AddComponent<MeshRenderer>();
	//	ground->GetComponent<MeshRenderer>()->SetAssetNum(static_cast<int>(EnumModel::Ground));
	//	ground->GetComponent<MeshRenderer>()->CreateModel();
	//	ground->SetParentByGameObject(door);
	//	ground->GetComponent<Transform>()->SetScale({ 0.0034f,0.0034f,0.0034f });
	//	ground->GetComponent<Transform>()->SetLocalPosition({ -2.f, -1.f, 0.f });	/////////
	//	m_objectVector->push_back(ground);
	//}
	//{
	//	GameObject* ceiling = m_objManager->CreateObject();
	//	ceiling->SetName(std::format("Ceiling_{}_{}_model", y, x));
	//	ceiling->AddComponent<MeshRenderer>();
	//	ceiling->GetComponent<MeshRenderer>()->SetAssetNum(static_cast<int>(EnumModel::Ceiling));
	//	ceiling->GetComponent<MeshRenderer>()->CreateModel();
	//	ceiling->SetParentByGameObject(door);

	//	ceiling->GetComponent<Transform>()->SetScale({ 0.0034f,0.0034f,0.0034f });
	//	
	//	float rot = 180.f * 3.141592f / 180.f;
	//	ceiling->GetComponent<Transform>()->SetLocalRotation({ rot, 0.f, 0.f });
	//	ceiling->GetComponent<Transform>()->SetLocalPosition({ -2.f,2.4f, 0.f });
	//	m_objectVector->push_back(ceiling);
	//}

	Transform* transform = door->GetComponent<Transform>();
	SimpleMath::Vector3 pos = transform->GetPosition();
	pos.x += ((y)*m_blockSize);
	pos.z += ((x - 1) * m_blockSize);
	transform->SetPosition(pos);
	float rot = 90.f * 3.141592f / 180.f;
	door->GetComponent<Transform>()->SetRotation({ 0.f,rot,0.f });
	return door;
}

GameObject* TileMapGenerator::MakeAltarObject(int y, int x)
{
	float distance = 2000.f;


	GameObject* altar = m_objManager->CreateObject();
	altar->SetName(std::format("Altar_{}_{}", y, x));
	//gameObject->AddComponent<BoxCollision, MeshRenderer>();
	altar->AddComponent<BoxCollision, DemonAltarComponent>();
	altar->GetComponent<BoxCollision>()->SetSize(SimpleMath::Vector3(1.0f));
	// 이 부분 수정할 수 있음
	altar->GetComponent<BoxCollision>()->SetCollisionType(CollisionType::Static);
	altar->GetComponent<BoxCollision>()->SetDebugCollisionColor(0.7f, 0.f, 0.2f, 1.f);

	m_collisionDetectManager->AddBoxCollision(altar->GetComponent<BoxCollision>());
	altar->GetComponent<Transform>()->SetPosition(SimpleMath::Vector3((y * m_blockSize), 0.f, (x * m_blockSize)));
	altar->GetComponent<Transform>()->UpdateTransform();
	altar->SetParentByGameObject(this->m_pOwner);

	altar->GetComponent<DemonAltarComponent>()->SetLoadTime(3.f);
	altar->GetComponent<DemonAltarComponent>()->SetAffectDistanceRadius(distance);
	altar->GetComponent<DemonAltarComponent>()->SetAltarNumber(static_cast<AltarSequence>(m_altarCount));
	GameManager::GetInstance()->AddAltarObject(altar);
	m_altarCount++;


	// Mesh Renderer
	GameObject* altarModel = m_objManager->CreateObject();
	altarModel->SetName(std::format("Tile_{}_{}_model", y, x));
	altarModel->AddComponent<MeshRenderer>();
	altarModel->GetComponent<MeshRenderer>()->SetAssetNum(static_cast<int>(EnumModel::DevilAltar));
	altarModel->GetComponent<MeshRenderer>()->CreateModel();
	altarModel->SetParentByGameObject(altar);

	altarModel->GetComponent<Transform>()->SetScale({ 0.0034f,0.0034f,0.0034f });

	//float rot = 45.f * 3.141592f / 180.f;
	//modelGameObject->GetComponent<Transform>()->SetLocalRotation({ 0.f, rot, 0.f });
	altarModel->GetComponent<Transform>()->SetLocalPosition({ 0.f, -1.f, 0.f });

	altar->GetComponent<DemonAltarComponent>()->SetAltarModel(altarModel);

	{
		GameObject* heartSign = m_objManager->CreateObject();
		heartSign->SetName(std::format("heartSign_{}_{}_model", y, x));
		heartSign->AddComponent<MeshRenderer>();
		heartSign->GetComponent<MeshRenderer>()->SetAssetNum(static_cast<int>(EnumModel::HeartSign));
		heartSign->GetComponent<MeshRenderer>()->CreateModel();
		//m_renderer->Send(2, heartSign->GetObjectID(), true, {});
		heartSign->SetParentByGameObject(altar);

		heartSign->GetComponent<Transform>()->SetScale({ 0.0034f,0.0034f,0.0034f });
		altar->GetComponent<DemonAltarComponent>()->SetHeartSignModel(heartSign);
		m_objectVector->push_back(heartSign);
		altar->GetComponent<DemonAltarComponent>()->SetHeartSignModel(heartSign);
	}
	// ground
	/*{
		GameObject* ground = m_objManager->CreateObject();
		ground->SetName(std::format("Ground_{}_{}_model", y, x));
		ground->AddComponent<MeshRenderer>();
		ground->GetComponent<MeshRenderer>()->SetAssetNum(static_cast<int>(EnumModel::Ground));
		ground->GetComponent<MeshRenderer>()->CreateModel();
		ground->SetParentByGameObject(gameObject);

		ground->GetComponent<Transform>()->SetScale({ 0.0034f,0.0034f,0.0034f });

		ground->GetComponent<Transform>()->SetLocalPosition({ 0.f, -1.f, 0.f });
		m_objectVector->push_back(ground);
	}
	{
		GameObject* ceiling = m_objManager->CreateObject();
		ceiling->SetName(std::format("Ceiling_{}_{}_model", y, x));
		ceiling->AddComponent<MeshRenderer>();
		ceiling->GetComponent<MeshRenderer>()->SetAssetNum(static_cast<int>(EnumModel::Ceiling));
		ceiling->GetComponent<MeshRenderer>()->CreateModel();
		ceiling->SetParentByGameObject(gameObject);

		ceiling->GetComponent<Transform>()->SetScale({ 0.0034f,0.0034f,0.0034f });
		float rot = 180.f * 3.141592f / 180.f;
		ceiling->GetComponent<Transform>()->SetLocalRotation({ rot, 0.f, 0.f });
		ceiling->GetComponent<Transform>()->SetLocalPosition({ 0.f,2.4f, 0.f });
		m_objectVector->push_back(ceiling);
	}*/
	m_objectVector->push_back(altar);
	m_objectVector->push_back(altarModel);

	/*gameObject->Start();
	modelGameObject->Start();*/

	GameManager::GetInstance()->SetCurrentAltarObject(GameManager::GetInstance()->GetAltarObject()[0]);

	return altar;
}

GameObject* TileMapGenerator::MakeGroundObject(int y, int x)
{
	GameObject* gameObject = m_objManager->CreateObject();
	gameObject->SetName(std::format("Ground_{}_{}", y, x));
	gameObject->GetComponent<Transform>()->SetPosition(SimpleMath::Vector3((y * m_blockSize), 0.f, (x * m_blockSize)));
	gameObject->GetComponent<Transform>()->UpdateTransform();
	gameObject->SetParentByGameObject(this->m_pOwner);
	m_objectVector->push_back(gameObject);

	// Mesh Renderer
	{
		GameObject* ground = m_objManager->CreateObject();
		ground->SetName(std::format("Ground_{}_{}_model", y, x));
		ground->AddComponent<MeshRenderer>();
		
		ground->GetComponent<MeshRenderer>()->SetAssetNum(static_cast<int>(EnumModel::Ground));
		ground->GetComponent<MeshRenderer>()->CreateModel();
		m_renderer->Send(11, ground->GetObjectID(), 1, {});
		m_renderer->Send(12, ground->GetObjectID(), 0.5, {});
		ground->SetParentByGameObject(gameObject);

		//ground->GetComponent<Transform>()->SetScale({ 0.2f,0.2f,0.2f });
		ground->GetComponent<Transform>()->SetScale({ 0.13f,0.13f,0.13f });

		ground->GetComponent<Transform>()->SetLocalPosition({ 0.f, -1.f, 0.f });
		m_objectVector->push_back(ground);
	}
	// Mesh Renderer
	{
		GameObject* ground = m_objManager->CreateObject();
		ground->SetName(std::format("Ceiling_{}_{}_model", y, x));
		ground->AddComponent<MeshRenderer>();
		ground->GetComponent<MeshRenderer>()->SetAssetNum(static_cast<int>(EnumModel::Ceiling));
		ground->GetComponent<MeshRenderer>()->CreateModel();
		m_renderer->Send(11, ground->GetObjectID(), 1, {});
		m_renderer->Send(12, ground->GetObjectID(), 0.5, {});
		ground->SetParentByGameObject(gameObject);

		//ground->GetComponent<Transform>()->SetScale({ 0.0034f,0.0034f,0.0034f });
		ground->GetComponent<Transform>()->SetScale({ 0.2f,0.2f,0.2f });
		float rot = 180.f * 3.141592f / 180.f;
		ground->GetComponent<Transform>()->SetLocalRotation({ rot, 0.f, 0.f });
		//ground->GetComponent<Transform>()->SetLocalPosition({ 0.f,5.8f, 0.f });
		ground->GetComponent<Transform>()->SetLocalPosition({ 0.f,2.4f, 0.f });
		m_objectVector->push_back(ground);
	}

	return gameObject;
}

GameObject* TileMapGenerator::MakeItemBox(int y, int x, int dir)
{
	// GameObject
	GameObject* itemChest = nullptr;
	itemChest = m_objManager->CreateObject();
	itemChest->SetName(std::format("ItemChest_{}_{}", y, x));
	itemChest->AddComponent<BoxCollision,ItemChest>();
	m_collisionDetectManager->AddBoxCollision(itemChest->GetComponent<BoxCollision>());
	itemChest->GetComponent<BoxCollision>()->SetSize({ 0.5f,0.5f,1.f });
	itemChest->GetComponent<Transform>()->SetPosition(SimpleMath::Vector3((y * m_blockSize), -0.5f, (x * m_blockSize)));
	itemChest->GetComponent<ItemChest>()->SetLoadTime(3.f);
	itemChest->GetComponent<ItemChest>()->SetRandomItemType();
	m_objectVector->push_back(itemChest);

	GameObject* itemChestModel = nullptr;
	itemChestModel = m_objManager->CreateObject();
	itemChestModel->SetName(std::format("ItemChestModel_{}_{}", y, x));
	itemChestModel->AddComponent<MeshRenderer>();
	itemChestModel->GetComponent<MeshRenderer>()->SetAssetNum(static_cast<int>(EnumModel::ItemBox));
	itemChestModel->GetComponent<MeshRenderer>()->CreateModel();
	itemChestModel->GetComponent<MeshRenderer>()->SetThisIsANIMATION();
	itemChestModel->GetComponent<Transform>()->SetLocalScale({ 0.03f, 0.03f, 0.03f });
	itemChestModel->GetComponent<Transform>()->SetLocalPosition({ 0.f,-0.5f,0.f });

	itemChestModel->SetParentByGameObject(itemChest);
	m_objectVector->push_back(itemChestModel);

	itemChest->GetComponent<ItemChest>()->SetItemChestModelObject(itemChestModel);

	// dir은 0부터
	float rot = 90.f * dir * 3.141592f / 180.f;
	itemChest->GetComponent<Transform>()->SetLocalRotation({ 0.f, rot, 0.f });

	return itemChest;
}

GameObject* TileMapGenerator::MakeHeartBox(int y, int x, int dir)
{

	// GameObject
	GameObject* heartChest = nullptr;
	heartChest = m_objManager->CreateObject();
	heartChest->SetName(std::format("HeartChest_{}_{}", y, x));
	heartChest->AddComponent<BoxCollision, HeartChest>();
	m_collisionDetectManager->AddBoxCollision(heartChest->GetComponent<BoxCollision>());
	heartChest->GetComponent<BoxCollision>()->SetSize({ 0.8f,0.5f,0.4f });
	heartChest->GetComponent<Transform>()->SetPosition(SimpleMath::Vector3((y * m_blockSize), -0.5f, (x * m_blockSize)));
	heartChest->GetComponent<HeartChest>()->SetLoadTime(3.f);
	m_objectVector->push_back(heartChest);

	GameObject* heartChestModel = nullptr;
	heartChestModel = m_objManager->CreateObject();
	heartChestModel->SetName(std::format("HeartChestModel_{}_{}", y, x));
	heartChestModel->AddComponent<MeshRenderer>();
	heartChestModel->GetComponent<MeshRenderer>()->SetAssetNum(static_cast<int>(EnumModel::HeartBox));
	heartChestModel->GetComponent<MeshRenderer>()->CreateModel();
	heartChestModel->GetComponent<MeshRenderer>()->SetAnimationRepeat(false);
	heartChestModel->GetComponent<MeshRenderer>()->SetThisIsANIMATION();
	heartChestModel->GetComponent<Transform>()->SetLocalScale({ 0.015f, 0.015f, 0.015f });
	heartChestModel->GetComponent<Transform>()->SetLocalPosition({ 0.f, -0.5f, 0.f });
	heartChestModel->SetParentByGameObject(heartChest);
	m_objectVector->push_back(heartChestModel);

	heartChest->GetComponent<HeartChest>()->SetHeartChestModel(heartChestModel);

	// dir은 0부터
	float rot = 90.f * dir * 3.141592f / 180.f;

	heartChest->GetComponent<Transform>()->SetLocalRotation({ 0.f, rot, 0.f });

	return heartChest;
}
