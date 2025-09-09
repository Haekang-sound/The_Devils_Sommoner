#pragma once
#include "Component.h"
#include <vector>

class TileMap;
class EngineObjectManager;
class CollisionDetectManager;
class ID3DRenderer;
class GameObject;

/// <summary>
/// TileMap 을 만들기 위한 컴포넌트... 팀원들의 반대를 받았다. 나중에 Component를 상속 안 받을 수 도 있다.
/// </summary>
class TileMapGenerator : public Component
{
public:
	TileMapGenerator();
	virtual ~TileMapGenerator();



public:
	void Awake() override;
	void Start() override;
	void FixedUpdate(float dTime) override;
	void Update(float dTime) override;
	void LateUpdate(float dTime) override;
	void Render() override;
	void Release() override;

public:
	// scene m_objects를 타겟팅함. 사실 잘 모르겠다;
	void SetObjectVectorTarget(std::vector<GameObject*>* objectVector);
	void SetCollisionDetectManager(CollisionDetectManager* detectManger);
	void SetEngineObjectManager(EngineObjectManager* engineObjectManager);
	void SetRenderer(ID3DRenderer* renderer);
	void SetTileMap(TileMap* tileMap);
	//void SetGroundTileMap(TileMap* groundTileMap);
	void GenerateMap();
	//void GenerateGround();
	void SetBlockSize(const float& size);

private:
	GameObject* MakeDoor1Object(int y, int x);
	GameObject* MakeDoor2Object(int y, int x);
	GameObject* MakeAltarObject(int y, int x);
	GameObject* MakeGroundObject(int y, int x);

	GameObject* MakeItemBox(int y, int x, int dir);
	GameObject* MakeHeartBox(int y, int x, int dir);
private:
	TileMap* m_tileMap;
	//TileMap* m_groundTileMap;
	EngineObjectManager* m_objManager;
	CollisionDetectManager* m_collisionDetectManager;
	ID3DRenderer* m_renderer;
	float m_blockSize;
	

	std::vector<GameObject*>* m_objectVector;

private:
	int m_altarCount;
};

