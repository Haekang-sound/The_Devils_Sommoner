#pragma once

class TileMapBuilder;

class TileMap
{
	// �ذ������� Type���� �⺻������ ����� ���� ������ �ΰڴ�.
public:
	std::string m_data;
	static TileMapBuilder* m_builder;

public:
	void LoadData(const std::string& path);
	int** GetTileMap();
	int GetTileMapSize();

private:
	int** m_map;

	// �� ���� ũ��
	int m_mapSize;
};

