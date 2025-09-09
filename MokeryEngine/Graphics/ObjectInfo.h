#pragma once
#include <string>

/// �̰� ������ ������ �������̽��� d3d���ϱ� �������� ���� ���� math��� �����
#include "../Libraries/DXTK/Inc/SimpleMath.h"

/// <summary>
/// 2024.01.24 - ���Լ�
/// LightType�� ���� �������.
/// </summary>
enum class LightType
{
	Directional,
	Spot,
	Point,
};

/// <summary>
/// �� ID, �� Ÿ��, 
/// </summary>
struct LightInfo
{
	size_t _lightID;
	// Ÿ���� enum���� �ٲܿ���
	LightType _lightType;
	size_t _intensity = 1;

	DirectX::SimpleMath::Vector4 Ambient = { 1.0f, 1.0f, 1.0f, 1.0f };
	DirectX::SimpleMath::Vector3 Attenuation = { 0.f, 0.f, 1.f };
	float _range = 10.f;
};

/// <summary>
/// ������Ʈ ID, ���ϰ��, ���̴���� ����ü
/// </summary>
struct MeshObjectInfo
{
	size_t _objectID;

	const char* _meshPath;

	std::wstring _texturePath;

	std::wstring _shaderPath;

};


