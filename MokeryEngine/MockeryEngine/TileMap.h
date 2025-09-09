#pragma once

class TileMapBuilder;

class TileMap
{
	// 해강이형의 Type에서 기본적으로 사용할 것을 위에다 두겠다.
public:
	std::string m_data;
	static TileMapBuilder* m_builder;

public:
	void LoadData(const std::string& path);
	int** GetTileMap();
	int GetTileMapSize();

private:
	int** m_map;

	// 한 줄의 크기
	int m_mapSize;
};

