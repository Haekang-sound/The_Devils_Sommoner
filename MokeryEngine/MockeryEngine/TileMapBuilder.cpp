#include "pch.h"
#include "TileMapBuilder.h"
#include "TileMap.h"

TileMapBuilder::TileMapBuilder()
{

}

TileMapBuilder::~TileMapBuilder()
{

}

void TileMapBuilder::Initialize(ResourceCreator* creator)
{

}

void TileMapBuilder::CreateType(std::string fileName)
{
	m_type = new TileMap();
	m_type->LoadData(fileName);
}

void TileMapBuilder::SetType(IResource* resource)
{
	resource->SetResource(m_type);
}
