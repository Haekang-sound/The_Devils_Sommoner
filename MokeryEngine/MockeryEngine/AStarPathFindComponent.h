#pragma once
#include "Component.h"
#include "CommonStructs.h"
#include "../Libraries/DXTK/Inc/SimpleMath.h"
#include <vector>
#include <deque>

using namespace DirectX;

class TileMap;

struct PQNode
{
	PQNode() : f(0), g(0), pos() {}
	PQNode(const int& pf, const int& pg, const PathPos& ppos)
		: f(pf), g(pg), pos(ppos)
	{}

	bool operator<(const PQNode& other) const { return f < other.f; }
	bool operator>(const PQNode& other) const { return f > other.f; }
	
	int f, g;
	PathPos pos;
};

class AStarPathFindComponent : public Component
{
public:
	AStarPathFindComponent();
	virtual ~AStarPathFindComponent();

public:
	void Start() override;
	void Update(float dTime) override;
	void LateUpdate(float dTime) override;
	void FixedUpdate(float dTime) override;
	void Render() override;
	void Release() override;

public:
	// 내 위치가 어디인지
	// 목적지가 어디인지

	void SetStartPos(PathPos pos);
	void SetDestination(PathPos pos);
	bool CheckDestination();

	// 길찾기 알고리즘을 수행하여 경로릂 받아온다.
	void AstarPathFinding();



	// 다음 실제 위치를 받아온다.
	TileInfo GetNextPos(const SimpleMath::Vector3& curPos);

	// 타일맵 리소스를 적용한다.
	void SetTileMap(TileMap* tileMap);

	// 타일의 크기를 설정한다. // 가로 세로가 같다는 가정
	void SetTileSize(const float& tileSize);
	float GetTileSize();

	// 맵의 크기를 반환한다.
	int GetMapSize();

public:
	// TEST : 디버깅 용 함수
	bool IsWallExist(PathPos pos);

private:
	// 다음 배열 위치를 받아온다.
	PathPos GetNextPathPos();

private:
	// 목적지까지의 경로
	std::deque<PathPos> m_path;

	// 현재 포지션
	PathPos m_pos;
	// 목적지
	PathPos m_destination;
	
	// 맵 배열
	int** m_map;
	
	// 한 타일당 실제크기
	float m_tileSize;

	// 맵 크기
	int m_mapSize;

	// 타일 맵 리소스
	TileMap* m_tileMap;
};

