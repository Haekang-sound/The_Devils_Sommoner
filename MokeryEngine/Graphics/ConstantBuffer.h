#pragma once
#include "framework.h"

#pragma region ConstantBuffer
namespace CB
{
	struct CameraBuffer
	{
		SimpleMath::Matrix View;
		SimpleMath::Vector3 CameraPosition;
		float PlayerHP;

		SimpleMath::Color Color{1.f,1.f,1.f,1.f};
		// �׸��� ǥ�� ���ϰų� ����Ʈ�� ī�޶� ����ٴѴ�.
		//SimpleMath::Matrix ShadowView;
	};


	struct ObjectBuffer
	{
		SimpleMath::Matrix WorldTransform;

		// �츮�� ��Ʈ�� �����Ƿ� �� �ΰ��� ���� ���� �ʰڴ�.
		//float Metallic;
		//float Roughness;

		SimpleMath::Vector4 ObjectColor;

		SimpleMath::Vector4 ObjectBaseColor;

		float Metallic;
		float Loughness;

		SimpleMath::Vector2 Flag;
	};

	struct BoneBuffer
	{
		std::array<SimpleMath::Matrix,120> BoneTransform;
	};

	struct EngineBuffer
	{
		// �׸��� ǥ�� ���ϰų� ����Ʈ�� ī�޶� ����ٴѴ�.
		// SimpleMath::Matrix ShadowProjection;
		SimpleMath::Matrix Projection;
		SimpleMath::Matrix SpriteProjection;
	};

	struct DirectionLightBuffer
	{
		SimpleMath::Vector3 WorldDirectionLight;
		float WorldDirectionPower{};
	};
}
#pragma endregion