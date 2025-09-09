#include "pch.h"
#include "TileMap.h"
#include <fstream>
TileMapBuilder* TileMap::m_builder = nullptr;

void TileMap::LoadData(const std::string& path)
{
	// 맵 초기화 
	for (int i = 0; i < m_mapSize; i++)
	{
		delete m_map[i];
	}
	delete m_map;

	// 맵 로드
	std::string mapName;
	std::string temp;
	int size;

	std::ifstream ifs;
	ifs.open(path);
	ifs >> mapName;

	// 앞의 정보는 쓸데없는 정보이다.
	ifs >> temp >> temp >> temp >> size;

	// 맵 생성
	m_mapSize = size;

	m_map = new int* [size];
	for (int i = 0; i < size; i++)
	{
		m_map[i] = new int[size];

		for (int j = 0; j < size; j++)
		{
			m_map[i][j] = 0;
		}
	}

	// 맵 복사
	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			ifs >> m_map[y][x];
		}
	}

	ifs.close();
}

int** TileMap::GetTileMap()
{
	return m_map;
}

int TileMap::GetTileMapSize()
{
	return m_mapSize;
}
