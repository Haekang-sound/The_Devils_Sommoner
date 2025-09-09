#include "pch.h"
#include "AStarPathFindComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "TileMap.h"
//const int dy[] = { -1, 0, 1, 0, -1, 1, 1, -1 };
//const int dx[] = { 0, 1, 0, -1, 1, 1, -1, -1 };
//const int cost[] = { 10, 10, 10, 10, 14, 14, 14, 14 };
//const int dirCount = 8;

#define PATH_FINDING_FINISH -100
const int dy[] = { -1, 0, 1, 0 };
const int dx[] = { 0, 1, 0, -1 };
const int cost[] = { 10, 10, 10, 10 };
const int dirCount = 4;


AStarPathFindComponent::AStarPathFindComponent()
	: m_path(),
	m_pos(),
	m_destination(),
	m_map(nullptr),
	m_tileSize(0.f),
	m_mapSize(0),
	m_tileMap(nullptr)
{

}

AStarPathFindComponent::~AStarPathFindComponent()
{

}

void AStarPathFindComponent::Start()
{

}

void AStarPathFindComponent::Update(float dTime)
{
	
}

void AStarPathFindComponent::LateUpdate(float dTime)
{

}

void AStarPathFindComponent::FixedUpdate(float dTime)
{

}

void AStarPathFindComponent::Render()
{

}

void AStarPathFindComponent::Release()
{
	m_path.clear();
}

void AStarPathFindComponent::SetStartPos(PathPos pos)
{
	m_pos = pos;
}

void AStarPathFindComponent::SetDestination(PathPos pos)
{
	m_destination = pos;
}

bool AStarPathFindComponent::CheckDestination()
{
	// TODO : 구현
	return true;
}

void AStarPathFindComponent::AstarPathFinding()
{
	PathPos start = m_pos;
	PathPos destPos = m_destination;

	// 방문했는지
	std::vector<std::vector<bool>> closed(m_mapSize, std::vector<bool>(m_mapSize));

	// 지금까지 y,x에 대한 가장 좋은 비용을 저장한다.
	std::vector<std::vector<int>> best(m_mapSize, std::vector<int>(m_mapSize, INT32_MAX));

	std::map<PathPos, PathPos> parent;

	std::priority_queue<PQNode, std::vector<PQNode>, std::greater<PQNode>> pq;

	// 초기값 세팅
	int g = 0;
	int h = 10 * (abs(destPos.y - start.y) + abs(destPos.x - start.x));
	pq.push(PQNode{ g + h, g, start });
	best[start.y][start.x] = g + h;
	parent[start] = start;

	while (!pq.empty())
	{
		PQNode node = pq.top();
		pq.pop();

		if (closed[node.pos.y][node.pos.x])
			continue;
		if (best[node.pos.y][node.pos.x] < node.f)
			continue;
		
		// 방문
		closed[node.pos.y][node.pos.x] = true;

		if (node.pos == destPos)
		{
			// std::cout << "find path :: start Pos :" << start.y << ", " << start.x << " dest Pos : " << destPos.y << ", " << destPos.x << " parent size : " << parent.size() << std::endl;
			break;
		}

		for (int dir = 0; dir < dirCount; dir++)
		{
			PathPos nextPos;
			nextPos.y = node.pos.y + dy[dir];
			nextPos.x = node.pos.x + dx[dir];

			// 맵 바깥
			if (nextPos.y < 0 || nextPos.y > m_mapSize - 1
				|| nextPos.x < 0 || nextPos.x > m_mapSize - 1)
				continue;

			// 벽	// -1이 아니면 벽이 있는 것이다.
			//if (m_map[nextPos.y][nextPos.x]) continue;
			//if (m_map[nextPos.y][nextPos.x] != -1) continue;

			if (m_map[nextPos.y][nextPos.x] == static_cast<int>(TileType::NoPillarWall)) continue;
			if (m_map[nextPos.y][nextPos.x] == static_cast<int>(TileType::Wall)) continue;

			// 방문했는지
			if (closed[nextPos.y][nextPos.x]) continue;

			// 비용 계산
			int g = node.g + cost[dir];
			int h = 10 * (abs(destPos.y - nextPos.y) + abs(destPos.x - nextPos.y));

			if (best[nextPos.y][nextPos.x] <= g + h)
				continue;

			best[nextPos.y][nextPos.x] = g + h;
			PQNode nextPqNode = { g + h, g, nextPos };
			pq.push(nextPqNode);
			parent[nextPos] = node.pos;
		}
	}

	PathPos pos = destPos;
	m_path.clear();
	
	while (true)
	{
		//std::cout << m_path.size() << std::endl;
		m_path.push_back(pos);
		if (pos == parent[pos])
			break;
		pos = parent[pos];
	}
	// std::cout << "path size : " << m_path.size() << std::endl;
}

PathPos AStarPathFindComponent::GetNextPathPos()
{
	if (m_path.empty())
	{
		return { PATH_FINDING_FINISH,PATH_FINDING_FINISH };
	}
	PathPos nextPos = m_path.back();
	m_path.pop_back();
	return nextPos;
}

TileInfo AStarPathFindComponent::GetNextPos(const SimpleMath::Vector3& curPos)
{
	TileInfo ret;
	SimpleMath::Vector3 pos;
	PathPos p = GetNextPathPos();

	if (p.y == PATH_FINDING_FINISH)
	{
		ret.tileType = TileType::Floor;
		ret.tilePos = curPos;
		return ret;
	}
	if (p.y < 0 || p.y > m_mapSize - 1
		|| p.x < 0 || p.x > m_mapSize - 1
		)
	{
		ret.tileType = TileType::Floor;
		ret.tilePos = curPos;
		return ret;
	}
	// TODO : 타일이 0,0일경우를 가정하여 만들었음. 나중에 수정할 듯
	pos.x = p.y * m_tileSize;
	pos.z = p.x * m_tileSize;
	pos.y = 0;
	
	ret.tilePos = pos;
	ret.tileType = static_cast<TileType>(m_map[p.y][p.x]);
	
	return ret;
}

void AStarPathFindComponent::SetTileMap(TileMap* tileMap)
{
	m_tileMap = tileMap;
	m_map = tileMap->GetTileMap();
	m_mapSize = tileMap->GetTileMapSize();
}

void AStarPathFindComponent::SetTileSize(const float& tileSize)
{
	m_tileSize = tileSize;
}

float AStarPathFindComponent::GetTileSize()
{
	return m_tileSize;
}

int AStarPathFindComponent::GetMapSize()
{
	return m_mapSize;
}

bool AStarPathFindComponent::IsWallExist(PathPos pos)
{
	if (pos.y < 0 || pos.y > m_mapSize - 1
		|| pos.x < 0 || pos.x > m_mapSize - 1
		)
	{
		return true;
	}
	else if (m_map[pos.y][pos.x] != -1)
	{
		return true;
	}
	return false;
}