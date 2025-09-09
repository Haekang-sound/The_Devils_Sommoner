#include "pch.h"
#include "TileMap.h"
#include <fstream>
TileMapBuilder* TileMap::m_builder = nullptr;

void TileMap::LoadData(const std::string& path)
{
	// �� �ʱ�ȭ 
	for (int i = 0; i < m_mapSize; i++)
	{
		delete m_map[i];
	}
	delete m_map;

	// �� �ε�
	std::string mapName;
	std::string temp;
	int size;

	std::ifstream ifs;
	ifs.open(path);
	ifs >> mapName;

	// ���� ������ �������� �����̴�.
	ifs >> temp >> temp >> temp >> size;

	// �� ����
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

	// �� ����
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
