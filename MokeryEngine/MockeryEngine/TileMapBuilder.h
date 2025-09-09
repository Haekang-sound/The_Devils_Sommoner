#pragma once
#include "IBuilder.h"

class TileMap;

class TileMapBuilder : public IBuilder
{
public:
	TileMapBuilder();
	virtual ~TileMapBuilder();

public:
	void Initialize(ResourceCreator* creator) override;
	void CreateType(std::string fileName) override;
	void SetType(IResource* resource) override;

private:
	TileMap* m_type;
};

