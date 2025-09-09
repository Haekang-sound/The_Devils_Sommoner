#include "pch.h"
#include "FBXParser.h"
#include <filesystem>
#include <functional>


Converter::Converter()
{
	

	m_pScene = nullptr;
}

Converter::~Converter()
{

}

void Converter::ReadAssetFile(std::wstring file, UINT _AssetNum)
{
	//std::unique_ptr<Assimp::Importer> m_importer;

	//m_importer = std::make_unique<Assimp::Importer>();
	//m_importer->SetPropertyBool(AI_CONFIG_IMPORT_FBX_PRESERVE_PIVOTS, 0);

	Assimp::Importer m_importer;

	if (m_pResourceManager->GetAsset<SkeletalObject>(_AssetNum).lock().get() != nullptr ||
		m_pResourceManager->GetAsset<StaticObject>(_AssetNum).lock().get() != nullptr
		)
	{
		return;
	}

	m_IsMakeAnimation = false;
	m_NumMesh = 0;

	std::wstring fileStr = file;

	auto p = std::filesystem::path(fileStr);
	assert(std::filesystem::exists(p));

	const aiScene* scene;
	scene = m_importer.ReadFile(
		ToString(fileStr),
		aiProcess_ConvertToLeftHanded |
		aiProcess_Triangulate |
		aiProcess_GenUVCoords |
		aiProcess_GenNormals |
		aiProcess_CalcTangentSpace |
		aiProcess_PopulateArmatureData |
		aiProcess_LimitBoneWeights |
		aiProcess_GenBoundingBoxes
	);


	assert(scene != nullptr);
	m_pScene = scene;
	bool hasBone = false;
	aiString path;
	for (size_t meshIter = 0; meshIter < m_pScene->mNumMeshes; meshIter++)
	{
		if (m_pScene->mMeshes[meshIter]->HasBones() == true)
		{
			hasBone = true;
			break;
		}
	}

	if (hasBone == true)
	{


		// create SkeletalObject
		{
			std::shared_ptr<SkeletalObject> asset = std::make_shared<SkeletalObject>();
			ProcessSkeletalNode(m_pScene->mRootNode, asset->m_pNode.get(),AiMatrixToMatrix(m_pScene->mRootNode->mTransformation));
			asset->m_MeshNum = m_pScene->mNumMeshes;


			for (size_t materials = 0; materials < m_pScene->mNumMaterials; materials++)
			{
				// �ϴ� ������ؽ��ķθ� �Ǵ��Ѵ�.
				if (AI_SUCCESS == m_pScene->mMaterials[materials]->GetTexture(aiTextureType_OPACITY, 0, &path))
				{
					asset->m_IsOpaque = true;
					break;
				}
			}
			
			m_pResourceManager->AddAsset(_AssetNum, asset);
		}

		
	}
	else
	{
		
		// create StaticObject
		{
			std::shared_ptr<StaticObject> asset = std::make_shared<StaticObject>();
			ProcessStaticNode(m_pScene->mRootNode, asset->m_pNode.get());
			asset->m_MeshNum = m_pScene->mNumMeshes;

			for (size_t materials = 0; materials < m_pScene->mNumMaterials; materials++)
			{
				if (AI_SUCCESS == m_pScene->mMaterials[materials]->GetTexture(aiTextureType_OPACITY, 0, &path))
				{
					asset->m_IsOpaque = true;
					break;
				}
			}

			m_pResourceManager->AddAsset(_AssetNum, asset);
		}
	}


	{
#pragma region createAnim
		// create Animation
		if (m_pScene->HasAnimations() || hasBone == true)
		{
			Anim::AnimationInfo Anime;
			Anime.m_AssetNum = _AssetNum;
			
			// �ִϸ��̼� ����ŭ �����.
			Anime.m_Animation.resize(m_pScene->mNumAnimations);
			for (size_t animSize = 0; animSize < m_pScene->mNumAnimations; animSize++)
			{
				Anime.m_Animation[animSize].m_Name = m_pScene->mAnimations[animSize]->mName.C_Str();
				Anime.m_Animation[animSize].m_Duration = m_pScene->mAnimations[animSize]->mDuration;
				Anime.m_Animation[animSize].m_TickPerSec = m_pScene->mAnimations[animSize]->mTicksPerSecond;
				Anime.m_Animation[animSize].m_AnimationFullTime = Anime.m_Animation[animSize].m_Duration / Anime.m_Animation[animSize].m_TickPerSec;
				Anime.m_Animation[animSize].m_TickPerFrame = Anime.m_Animation[animSize].m_AnimationFullTime / Anime.m_Animation[animSize].m_Duration;


				// ������ �ִ� �޽���ŭ �����.
				Anime.m_Animation[animSize].m_Mesh.resize(m_pScene->mNumMeshes);
				for (size_t meshSize = 0; meshSize < m_pScene->mNumMeshes; meshSize++)
				{
					// �޽��� ���� �� ��ŭ �����.
					Anime.m_Animation[animSize].m_Mesh[meshSize].m_Bone.resize(m_pScene->mMeshes[meshSize]->mNumBones);

					// ���� ���� ����
					for (size_t boneSize = 0; boneSize < m_pScene->mMeshes[meshSize]->mNumBones; boneSize++)
					{
						for (size_t channelSize = 0; channelSize < m_pScene->mAnimations[animSize]->mNumChannels; channelSize++)
						{
							// (�ϴ� �ڵ������ ���̰�)
							aiString name = m_pScene->mAnimations[animSize]->mChannels[channelSize]->mNodeName;
							// ä���� ��尡 ������ �������� �ҷ��´�.
							if (m_pScene->mRootNode->FindNode(name) == m_pScene->mMeshes[meshSize]->mBones[boneSize]->mNode)
							{
								SimpleMath::Vector3 pos, scale;
								SimpleMath::Quaternion quat;
								aiVector3D aiPos, aiScale;
								aiQuaternion aiQuat;
								double time;
								for (size_t keySize = 0; keySize < m_pScene->mAnimations[animSize]->mChannels[channelSize]->mNumPositionKeys; keySize++)
								{
									aiPos = m_pScene->mAnimations[animSize]->mChannels[channelSize]->mPositionKeys[keySize].mValue;
									aiQuat = m_pScene->mAnimations[animSize]->mChannels[channelSize]->mRotationKeys[keySize].mValue;
									aiScale = m_pScene->mAnimations[animSize]->mChannels[channelSize]->mScalingKeys[keySize].mValue;
									time = m_pScene->mAnimations[animSize]->mChannels[channelSize]->mPositionKeys[keySize].mTime;
					/*				memcpy(&pos, &aiPos, sizeof(SimpleMath::Vector3));
									memcpy(&scale, &aiScale, sizeof(SimpleMath::Vector3));*/
									// ���øŽ� ���ʹϾ��ϰ� ����� ���ʹϾ��� �ٸ���..? xyzw wxyz
									//memcpy(&quat, &aiQuat, sizeof(SimpleMath::Quaternion));
									quat = { aiQuat.x,aiQuat.y,aiQuat.z,aiQuat.w };
									pos = { aiPos.x,aiPos.y,aiPos.z };
									scale = { aiScale.x,aiScale.y,aiScale.z };
									Anime.m_Animation[animSize].m_Mesh[meshSize].m_Bone[boneSize].m_Frame.push_back(SimpleMath::Matrix::CreateScale(scale)* SimpleMath::Matrix::CreateFromQuaternion(quat)* SimpleMath::Matrix::CreateTranslation(pos));


									time *= Anime.m_Animation[animSize].m_TickPerFrame;
									// �𸣰ڴ�.,. 8����Ʈ ���̴� �׳� Ǫ�ù��Ѵ�.
									Anime.m_Animation[animSize].m_Mesh[meshSize].m_Bone[boneSize].m_Time.push_back(time);

								}
								
								// �ݺ����� ����
								// �ٺҷ������� ���� ���� ä��ã�⸦ �ݺ��Ѵ�.
								break;
							}
						}
						Anime.m_Animation[animSize].m_Mesh[meshSize].m_Bone[boneSize].m_OffsetMatrix = AiMatrixToMatrix(m_pScene->mMeshes[meshSize]->mBones[boneSize]->mOffsetMatrix);
					}
					
				}
			}

			if (Anime.m_Animation.empty() == true)
			{
				Anime.m_Animation.resize(1);
				Anime.m_Animation[0].m_Mesh.resize(m_pScene->mNumMeshes);
				Anime.m_Animation[0].m_Name = "is not Animation. for bone";
				Anime.m_Animation[0].m_AnimationFullTime = D3D11_FLOAT32_MAX;
				Anime.m_Animation[0].m_TickPerFrame = D3D11_FLOAT32_MAX;


				for (size_t meshSize = 0; meshSize < m_pScene->mNumMeshes; meshSize++)
				{
					// �޽��� ���� �� ��ŭ �����.
					Anime.m_Animation[0].m_Mesh[meshSize].m_Bone.resize(m_pScene->mMeshes[meshSize]->mNumBones);
					for (size_t boneSize = 0; boneSize < m_pScene->mMeshes[meshSize]->mNumBones; boneSize++)
					{
						Anime.m_Animation[0].m_Mesh[meshSize].m_Bone[boneSize].m_OffsetMatrix = AiMatrixToMatrix(m_pScene->mMeshes[meshSize]->mBones[boneSize]->mOffsetMatrix);
					}
				}

			}
			// �ִϸ��̼��� �ٸ���������� ���ҽ��Ŵ����� �ϴ� �־��ش�.
			m_pResourceManager->AddResource(typeid(Anim::AnimationInfo).name(), std::to_string(_AssetNum), Anime);
			// �׽�Ʈ ��� �ϴ� �ߵȴ�.
			// ���������� �ҷ��� ����.
		}
#pragma endregion

		for (size_t materials = 0; materials < m_pScene->mNumMaterials; materials++)
		{
			Material mat;
			for (size_t textures = 0; textures < AI_TEXTURE_TYPE_MAX; textures++)
			{
				// ������ �ؽ��Ĵ� �ʸ��� 1�常 ����ִٰ� �����Ѵ�. ���߿� �ٲ�����ҵ�.
				if (AI_SUCCESS == m_pScene->mMaterials[materials]->GetTexture((aiTextureType)textures, 0, &path))
				{
					mat.m_path.push_back(path.C_Str());
					mat.m_path.back() = mat.m_path.back().substr(mat.m_path.back().rfind("\\"));
				}
				else
				{
					mat.m_path.emplace_back("");
				}
				
			}
			mat.m_pTextures.resize(mat.m_path.size());
			mat.m_Index = m_MaterialID;
			m_MaterialID++;
			m_pResourceManager->AddResource(typeid(Material).name(), m_pScene->mMaterials[materials]->GetName().C_Str() + std::to_string(_AssetNum), mat);
		}
		
	}

	
}

// aiNode�� ������ StaticNode�� ������ �־��ִ� ����
void Converter::ProcessStaticNode(aiNode* node, StaticNode* _Node)
{


	/// staticNode�� ������ �ִ� ����
	//// ���ȿ� ����ִ� Ʈ������ ����.
	//SimpleMath::Matrix m_Transform;
	_Node->m_LocalMatrix = AiMatrixToMatrix(node->mTransformation);
	// aiNode�� Mesh�� ������ �����ϱ�
	// ������ �� ���� ������ ��ȯ�� �ؾ��Ѵ�.

	for (size_t meshs = 0; meshs < node->mNumMeshes; meshs++)
	{
		_Node->m_Meshs.push_back(ReadStaticMeshData(m_pScene->mMeshes[node->mMeshes[meshs]]));

		// �ϴ� �޽��� ���ҽ��� �ִ°��� ���߿� ����.
		//m_pResourceManager->AddResource(typeid(_Node.m_Meshs.back()).name(),, _Node.m_Meshs.back());
	}

	// sNode�� �������� ����ƽ ��忡 �־��ش�


	//// ���� ������ �̰��� ��´�.
	//std::vector<StaticNode> m_Childs;
	//staicNode�� ��ȯ�� ���� Children���� �������� ���ȣ���
	for (int i = 0; i < node->mNumChildren; i++)
	{
		if (node->mNumChildren > 0)
		{
			_Node->m_Childs.emplace_back();
			_Node->m_Childs.back().m_pParent = _Node;
			ProcessStaticNode(node->mChildren[i], &(_Node->m_Childs.back()));
		}
	}
}

void Converter::ProcessSkeletalNode(aiNode* node, SkeletalNode* _Node,const SimpleMath::Matrix& _Parent)
{

	_Node->m_LocalMatrix = AiMatrixToMatrix(node->mTransformation);// *_Parent;
	if (node->mNumMeshes > 0)
	{
		if (_Node->m_pParent != nullptr)
		{
			if (_Node->m_pParent->m_IsBone == true)
			{
				_Node->m_ParentMatrix = AiMatrixToMatrix(node->mParent->mTransformation);
				_Node->m_pWeapon = _Node->m_pParent;
				_Node->m_BoneIndex = _Node->m_pParent->m_BoneIndex;
			}
		}
		_Node->m_MeshIndex = m_NumMesh + 1;

	}

	for (size_t meshs = 0; meshs < node->mNumMeshes; meshs++)
	{
		_Node->m_Meshs.push_back(ReadSkeletalMeshData(m_pScene->mMeshes[node->mMeshes[meshs]]));
		m_NumMesh++;


		// �ϴ� �޽��� ���ҽ��� �ִ°��� ���߿� ����.
		//m_pResourceManager->AddResource(typeid(_Node.m_Meshs.back()).name(),, _Node.m_Meshs.back());
	}

	// ��ȿ�������� ��ĥ �� ������ ����. ������ �ð������� �̷��� �Ѵ�.
	if (m_pScene->HasAnimations())
	{
		//if (_Node->m_IsBone == false)
		{
			UINT bonenum = 0;
			_Node->m_BoneIndex.resize(m_pScene->mNumMeshes);
			for (size_t meshSize = 0; meshSize < m_pScene->mNumMeshes; meshSize++)
			{
				for (size_t bones = 0; bones < m_pScene->mMeshes[meshSize]->mNumBones; bones++)
				{
					if (m_pScene->mMeshes[meshSize]->mBones[bones]->mNode == node)
					{
						_Node->m_BoneIndex[meshSize] = (bones + 1);
						_Node->m_IsBone = true;
						break;
					}
				}
			}
		}
	}

	

	

	

	for (int i = 0; i < node->mNumChildren; i++)
	{
		if (node->mNumChildren > 0)
		{
			_Node->m_Childs.push_back(SkeletalNode());
			_Node->m_Childs.back().m_pParent = _Node;
			ProcessSkeletalNode(node->mChildren[i], &_Node->m_Childs.back(), _Node->m_LocalMatrix);
		}
	}
}


std::string Converter::ToString(const std::wstring& wstr)
{
	return std::string().assign(wstr.begin(), wstr.end());
}

SimpleMath::Matrix Converter::AiMatrixToMatrix(const aiMatrix4x4 aiMatrix)
{
	SimpleMath::Matrix result2;

	memcpy(&result2, &aiMatrix,sizeof(SimpleMath::Matrix));

	return result2.Transpose();
}



StaticMesh Converter::ReadStaticMeshData(aiMesh* mesh)
{
	//if (node->mNumMeshes < 1)
	//	return;

	StaticMesh smesh;
	smesh.m_MaterialIndex = mesh->mMaterialIndex + m_MaterialID;
		// ���� �����ϴ� ����
		for (int v = 0; v < mesh->mNumVertices; v++)
		{
			// ���ؽ�
			StaticVertex vertex;
			memcpy(&vertex.m_Pos, &mesh->mVertices[v], sizeof(SimpleMath::Vector3));

			// UV
			if (mesh->HasTextureCoords(0))
				memcpy(&vertex.m_UVW, &mesh->mTextureCoords[0][v], sizeof(SimpleMath::Vector3));

			// �븻
			if (mesh->HasNormals())
				memcpy(&vertex.m_Normal, &mesh->mNormals[v], sizeof(SimpleMath::Vector3));

			// ź��Ʈ
			if (mesh->HasTangentsAndBitangents())
				memcpy(&vertex.m_Tangent, &mesh->mTangents[v], sizeof(SimpleMath::Vector3));

			smesh.m_Vertex.push_back(vertex);
		}

		// �ε���
		for (int j = 0; j < mesh->mNumFaces; j++)
		{
			aiFace& face = mesh->mFaces[j];

			for (int k = 0; k < face.mNumIndices; k++)
			{
				smesh.m_Indices.push_back(face.mIndices[k]);
			}
		}

		return smesh;
	
}

SkeletalMesh Converter::ReadSkeletalMeshData(aiMesh* mesh)
{
	SkeletalMesh smesh;
	smesh.m_MaterialIndex = mesh->mMaterialIndex + m_MaterialID;
	// ���� �����ϴ� ����
	for (int v = 0; v < mesh->mNumVertices; v++)
	{
		// ���ؽ�
		SkeletalVertex vertex;
		memcpy(&vertex.m_Pos, &mesh->mVertices[v], sizeof(SimpleMath::Vector3));

		// UV
		if (mesh->HasTextureCoords(0))
			memcpy(&vertex.m_UVW, &mesh->mTextureCoords[0][v], sizeof(SimpleMath::Vector2));

		// �븻
		if (mesh->HasNormals())
			memcpy(&vertex.m_Normal, &mesh->mNormals[v], sizeof(SimpleMath::Vector3));

		// ź��Ʈ
		if (mesh->HasTangentsAndBitangents())
			memcpy(&vertex.m_Tangent, &mesh->mTangents[v], sizeof(SimpleMath::Vector3));

		smesh.m_Vertex.push_back(vertex);
	}

	// �ε���
	for (int j = 0; j < mesh->mNumFaces; j++)
	{
		aiFace& face = mesh->mFaces[j];

		for (int k = 0; k < face.mNumIndices; k++)
		{
			smesh.m_Indices.push_back(face.mIndices[k]);
		}
	}




	for (size_t bones = 0; bones < mesh->mNumBones; bones++)
	{
		UINT vID;
		for (size_t whight = 0; whight < mesh->mBones[bones]->mNumWeights; whight++)
		{
			vID = mesh->mBones[bones]->mWeights[whight].mVertexId;
			for (size_t i = 0; i < 3; i++)
			{
				if (smesh.m_Vertex[vID].m_BoneWeights[i] <= 0)
				{
					smesh.m_Vertex[vID].m_BoneIndex[i] = bones;
					smesh.m_Vertex[vID].m_BoneWeights[i] = mesh->mBones[bones]->mWeights[whight].mWeight;
					break;
				}
			}
		}
	}

	// ����ƽ �Ž��� ���Ϳ� �����͸� �־��ش�
	return smesh;
}

//void Converter::LoadAnimation(SkeletalObject* _Object)
//{
//	/*if (m_pScene->HasAnimations())
//	{
//		_Object->m_AnimInfo.resize(m_pScene->mNumAnimations);
//		for (size_t animIndex = 0; animIndex < m_pScene->mNumAnimations; animIndex++)
//		{
//			_Object->m_AnimInfo[animIndex].m_ID = animIndex;
//			_Object->m_AnimInfo[animIndex].m_Name = m_pScene->mAnimations[animIndex]->mName.C_Str();
//
//			for (size_t bones = 0; bones < m_pScene->mMeshes[0]->mNumBones; bones++)
//			{
//				for (size_t channelIndex = 0; channelIndex < m_pScene->mAnimations[animIndex]->mNumChannels; channelIndex++)
//				{
//					if ((m_pScene->mRootNode->FindNode(m_pScene->mAnimations[animIndex]->mChannels[channelIndex]->mNodeName)
//						== m_pScene->mMeshes[0]->mBones[bones]->mNode))
//					{
//
//						for (size_t key = 0; key < m_pScene->mAnimations[animIndex]->mChannels[channelIndex]->mNumPositionKeys; key++)
//						{
//							SimpleMath::Vector3 pos, scale;
//							SimpleMath::Quaternion quat;
//							memcpy(&pos, &m_pScene->mAnimations[animIndex]->mChannels[channelIndex]->mPositionKeys[key].mValue, sizeof(SimpleMath::Vector3));
//							memcpy(&quat, &m_pScene->mAnimations[animIndex]->mChannels[channelIndex]->mRotationKeys[key].mValue, sizeof(SimpleMath::Quaternion));
//							memcpy(&scale, &m_pScene->mAnimations[animIndex]->mChannels[channelIndex]->mScalingKeys[key].mValue, sizeof(SimpleMath::Vector3));
//							_Object->m_Bone[animIndex][bones].m_Animation.push_back(SimpleMath::Matrix::CreateScale(scale) * SimpleMath::Matrix::CreateFromQuaternion(quat) * SimpleMath::Matrix::CreateTranslation(pos));
//
//						}
//					}
//				}
//			}
//		}
//	}*/
//
//	// Load Anim
//
//	//if (m_pScene->HasAnimations())
//	//{
//	//	_Node->m_Bone.resize(m_pScene->mNumMeshes);
//	//	for (size_t meshSize = 0; meshSize < m_pScene->mNumMeshes; meshSize++)
//	//	{
//	//		_Node->m_Bone[meshSize].resize(m_pScene->mNumAnimations);
//	//		for (size_t animIndex = 0; animIndex < m_pScene->mNumAnimations; animIndex++)
//	//		{
//	//			for (size_t bones = 0; bones < m_pScene->mMeshes[meshSize]->mNumBones; bones++)
//	//			{
//	//				for (size_t channelIndex = 0; channelIndex < m_pScene->mAnimations[animIndex]->mNumChannels; channelIndex++)
//	//				{
//	//					// ���� ���, ���� ���� ä���� ��尡 ������
//	//					if ((m_pScene->mRootNode->FindNode(m_pScene->mAnimations[animIndex]->mChannels[channelIndex]->mNodeName)
//	//						== m_pScene->mMeshes[meshSize]->mBones[bones]->mNode) && (m_pScene->mMeshes[meshSize]->mBones[bones]->mNode == node))
//	//					{
//	//						for (size_t key = 0; key < m_pScene->mAnimations[animIndex]->mChannels[channelIndex]->mNumPositionKeys; key++)
//	//						{
//	//							SimpleMath::Vector3 pos, scale;
//	//							SimpleMath::Quaternion quat;
//	//							memcpy(&pos, &m_pScene->mAnimations[animIndex]->mChannels[channelIndex]->mPositionKeys[key].mValue, sizeof(SimpleMath::Vector3));
//	//							memcpy(&quat, &m_pScene->mAnimations[animIndex]->mChannels[channelIndex]->mRotationKeys[key].mValue, sizeof(SimpleMath::Quaternion));
//	//							memcpy(&scale, &m_pScene->mAnimations[animIndex]->mChannels[channelIndex]->mScalingKeys[key].mValue, sizeof(SimpleMath::Vector3));
//	//							_Node->m_Bone[meshSize][animIndex].m_AnimMatrix.push_back(SimpleMath::Matrix::CreateScale(scale) * SimpleMath::Matrix::CreateFromQuaternion(quat) * SimpleMath::Matrix::CreateTranslation(pos));
//
//	//						}
//	//						_Node->m_Offset = AiMatrixToMatrix(&m_pScene->mMeshes[meshSize]->mBones[bones]->mOffsetMatrix);
//	//						_Node->m_IsBone = true;
//	//						
//	//						break;
//	//					}
//	//					if (_Node->m_IsBone == true)
//	//						break;
//	//				}
//	//				_Node->m_BoneIndex = bones;
//	//				if (_Node->m_IsBone == true)
//	//					break;
//	//			}
//	//		}
//	//	}
//	//}
//}
