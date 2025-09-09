#pragma once
#include "../Libraries/DXTK/Inc/SimpleMath.h"

using namespace DirectX;

struct PathPos
{
	bool operator==(PathPos& other)
	{
		return y == other.y && x == other.x;
	}

	bool operator!=(PathPos& other)
	{
		return !(*this == other);
	}

	bool operator<(const PathPos& other) const
	{
		if (y != other.y)
			return y < other.y;
		return x < other.x;
	}

	PathPos operator+(PathPos& other)
	{
		PathPos ret;
		ret.y = y + other.y;
		ret.x = x + other.x;
		return ret;
	}

	PathPos& operator+=(PathPos& other)
	{
		y += other.y;
		x += other.x;
		return *this;
	}

	int y,x;
};

//enum class TileType : int
//{
//	Floor = -1,
//	Wall = 0,
//	Door = 1,
//	Altar = 2,
//	Door2 = 3,
//};

enum class TileType : int
{
	Floor = -1,
	NoPillarWall = 0,
	Wall = 1,
	Door_1 = 2,
	Door_2 = 3,
	DevilAltar = 4,
	ItemBox_1 = 5,
	ItemBox_2 = 6,
	ItemBox_3 = 7,
	ItemBox_4 = 8,
	HeartBox_1 = 9,
	HeartBox_2 = 10,
	HeartBox_3 = 11,
	HeartBox_4 = 12,
};


/// <summary>
/// 타일의 종류, 그리고 타일의 실제 위치 
/// </summary>
struct TileInfo
{
	TileType tileType;
	SimpleMath::Vector3 tilePos;
};