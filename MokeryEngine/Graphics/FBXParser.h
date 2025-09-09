#pragma once

#include "ObjectManager.h"
#include "ResourceManager.h"


#include <Assimp/Importer.hpp>
#include <Assimp/scene.h>
#include <Assimp/postprocess.h>

#ifdef _DEBUG
#pragma comment(lib, "assimp-vc143-mtd.lib")
#pragma comment(lib, "tinyxml2d.lib")
#else
#pragma comment(lib, "assimp-vc143-mt.lib")
#endif


/// <summary>
/// assimp�� ����� fbx parser�� ������Ÿ��
/// ���ְ� ����� ���ؿ��� ���� �ѱ�
/// 
/// �⺻������ Converter�� �����
/// ReadFile() �� GetStaticRootNode()�ϸ�
/// fbx�� ù��° ��Ʈ ��尡 ��ȯ�ȴ�.
/// �޽� ������ ����ƽ ����� ���� ������ ����ƽ ��忡 �����
/// 
/// 
/// 2024. 02. 06
/// </summary>
class Converter
{
public:
	Converter();
	~Converter();

public:
	void ReadAssetFile(std::wstring file,UINT _AssetNum);
	void SetResourceManager(std::shared_ptr<Render::ResourceManager> _Value) { m_pResourceManager = _Value; };

private:
	std::string ToString(const std::wstring& wstr);
	SimpleMath::Matrix AiMatrixToMatrix(const aiMatrix4x4 aiMatrix);


	void ProcessStaticNode(aiNode* node, StaticNode* _Node);
	void ProcessSkeletalNode(aiNode* node, SkeletalNode* _Node,const SimpleMath::Matrix& _Parent);
	StaticMesh ReadStaticMeshData(aiMesh* mesh);
	SkeletalMesh ReadSkeletalMeshData(aiMesh* mesh);


private:
	std::shared_ptr<Render::ResourceManager> m_pResourceManager;

private:

private:
	const aiScene* m_pScene;

	bool m_IsMakeAnimation = false;

private:
	UINT m_MaterialID = 0;
	UINT m_NumMesh = 0;
};
