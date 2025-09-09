#pragma once
#include "ConstantBuffer.h"
#include <array>

class SkeletalObject;
class StaticObject;
class SpriteObject;


#pragma region Data
struct Material
{
	std::vector<std::string> m_path;
	UINT m_Index = 0;
	std::vector<ComPtr<ID3D11ShaderResourceView>> m_pTextures;
	float m_Metalic;
	float m_Loughness;
};

struct Texture
{
	ComPtr<ID3D11ShaderResourceView> m_pTexture = nullptr;
	Vector2 m_Size;
};

struct StaticVertex
{
	SimpleMath::Vector3 m_Pos{};		// ���ؽ� ��ġ
	SimpleMath::Vector3 m_UVW{};		//
	SimpleMath::Vector3 m_Normal{};	//
	SimpleMath::Vector3 m_Tangent{};	//
};

struct SkeletalVertex : public StaticVertex
{
	float m_BoneWeights[3] = {0,0,0};		// ���� ����ġ��
	float m_BoneIndex[4] = {0,0,0,0};		// ���� �ε���
};

class MeshBase
{
public:
	virtual ~MeshBase() {};
	ComPtr<ID3D11Buffer> m_pVertexBuffer = nullptr;
	ComPtr<ID3D11Buffer> m_pIndexBuffer = nullptr;

	// ����׸��� �ε����� �� �������� Ȯ���Ѵ�.

	std::vector<UINT> m_Indices;			// ���ؽ��� �ε������� �����մϴ�.


	UINT m_IndexCount = 0;
	UINT m_Offset = 0;
	UINT m_MaterialIndex = 0;

};



// ���ø����� �ۼ����� �ʴ´�. 
class StaticMesh : public MeshBase
{
public:
	virtual ~StaticMesh() {};

	std::vector<StaticVertex> m_Vertex;

	const static size_t m_Stride = sizeof(StaticVertex);

};

class SpriteObject : public StaticMesh
{
public:
	SimpleMath::Matrix m_WorldMatrix;
	std::map<UINT,std::weak_ptr<Texture>> m_pTexture;
	bool m_IsOriginCenter = false;
	Vector2 m_Size;
};

class SkeletalMesh : public MeshBase
{
public:
	SkeletalMesh() {};
	std::vector<SkeletalVertex> m_Vertex;

	const static size_t m_Stride = sizeof(SkeletalVertex);
};

#pragma endregion
#pragma region Node
/// <summary>
/// �̰��� �Ľ��� �����͸� ���� �غ���.
/// ó�� �����Ǵ� ������Ʈ�� ��Ʈ ����̴�.
/// ������ ������Ʈ�� �����Ϸ� ������ �ѹ� ���� �ʿ伺�� ���� ���� ����ϰ� ������Ʈ�� ���Ѵ�.
/// </summary>

class Node
{
public:
	Node() {}
	virtual ~Node() {}
public:
	// ���ȿ� ����ִ� Ʈ������ ����.
	SimpleMath::Matrix m_LocalMatrix{};

};

class StaticNode : public Node
{
public:
	StaticNode() {}
	~StaticNode() {}

public:
	SimpleMath::Matrix m_WorldMatrix{};

	// ���� ������ �̰��� ��´�.
	std::vector<StaticNode> m_Childs;

	// �� ��忡 �޽��� ������ ��� ���� �� �ִ�.
	std::vector<StaticMesh> m_Meshs;

	StaticNode* m_pParent;

	bool m_IsHasMesh = false;


};

class SkeletalNode : public Node
{
public:
	SkeletalNode() {}
	~SkeletalNode() {}
public:
	// �Ž����� �ٸ� ���� Ʈ�������� �ʿ��ϴ�.
// �ð��� �����Ƿ� �˳��ϰ� 100���� ��´�.
	std::array<SimpleMath::Matrix, 10> m_WorldMatrix;
	// ���� ������ �̰��� ��´�.
	std::vector<SkeletalNode> m_Childs;

	// �� ��忡 �޽��� ������ ��� ���� �� �ִ�.
	std::vector<SkeletalMesh> m_Meshs;

	std::vector < UINT> m_BoneIndex;
	UINT m_MeshIndex = 0;
	bool m_IsBone = false;

	UINT m_CurrentFrame = 0;
	UINT m_NextFrame = 0;
	SkeletalNode* m_pParent= nullptr;

	// �ִϸ��̼ǿ��� ������ ���� ���
	SkeletalNode* m_pWeapon = nullptr;

	SimpleMath::Matrix m_ParentMatrix;
};

#pragma endregion
#pragma region Object

class Object
{
public:
	virtual ~Object() {}

public:
	UINT m_ID = 0;
	UINT m_MeshNum = 0;

	// �� ������Ʈ�� �������Ѱ�?
	bool m_IsOpaque = true;
};

class StaticObject : public Object
{
public:
	StaticObject()
	{
		m_pNode = std::make_shared<StaticNode>();
	}
	~StaticObject() {}

public:
	std::shared_ptr<StaticNode> m_pNode;


};





class SkeletalObject : public Object
{
public:
	SkeletalObject()
	{
		m_pNode = std::make_shared<SkeletalNode>();
	}
	~SkeletalObject() {}

public:
	std::shared_ptr<SkeletalNode> m_pNode;


	// �� ������Ʈ�� �������Ѱ�?
	bool m_IsOpaque = true;

};

#pragma endregion

namespace Anim
{
	struct Bone
	{
		std::vector<SimpleMath::Matrix> m_Frame;
		// ���� ����ִ� ������ ����.
		// ����ȣ�� �����µ� �Ž����� �ٸ���.
		SimpleMath::Matrix m_OffsetMatrix;
		std::vector<double> m_Time;

	};

	struct Clip
	{
		// �� ������� �ִ´�.
		std::vector<Bone> m_Bone;


	};

	struct Animation
	{
		// �ִϸ��̼� �̸���?
		std::string m_Name;
		// � �޽��� ����� �ִϸ��̼��ΰ�?
		std::vector<Clip> m_Mesh;

		// �ִϸ��̼� ��
		double m_Duration = 0;
		// �ʴ� ������
		double m_TickPerSec = 0;
		// �ִϸ��̼��� ����Ǵ� ��ü�ð�
		double m_AnimationFullTime = 0;
		// 1�����ӿ� �ɸ��� �ð�
		double m_TickPerFrame = 0;
	};

	struct AnimationInfo
	{
		// � ���� ������ �ִ� �ִϸ��̼��ΰ�>?
		UINT m_AssetNum = 0;
		// ���° ���¿� ������ �ִϸ��̼��ΰ�>'
		std::vector<Animation> m_Animation;
	};
}