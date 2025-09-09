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
	// �� ��ġ�� �������
	// �������� �������

	void SetStartPos(PathPos pos);
	void SetDestination(PathPos pos);
	bool CheckDestination();

	// ��ã�� �˰����� �����Ͽ� ��ΐe �޾ƿ´�.
	void AstarPathFinding();



	// ���� ���� ��ġ�� �޾ƿ´�.
	TileInfo GetNextPos(const SimpleMath::Vector3& curPos);

	// Ÿ�ϸ� ���ҽ��� �����Ѵ�.
	void SetTileMap(TileMap* tileMap);

	// Ÿ���� ũ�⸦ �����Ѵ�. // ���� ���ΰ� ���ٴ� ����
	void SetTileSize(const float& tileSize);
	float GetTileSize();

	// ���� ũ�⸦ ��ȯ�Ѵ�.
	int GetMapSize();

public:
	// TEST : ����� �� �Լ�
	bool IsWallExist(PathPos pos);

private:
	// ���� �迭 ��ġ�� �޾ƿ´�.
	PathPos GetNextPathPos();

private:
	// ������������ ���
	std::deque<PathPos> m_path;

	// ���� ������
	PathPos m_pos;
	// ������
	PathPos m_destination;
	
	// �� �迭
	int** m_map;
	
	// �� Ÿ�ϴ� ����ũ��
	float m_tileSize;

	// �� ũ��
	int m_mapSize;

	// Ÿ�� �� ���ҽ�
	TileMap* m_tileMap;
};

