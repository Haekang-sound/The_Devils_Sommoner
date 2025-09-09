// 240131 : �����
// �츮�� ���� ��� ���̴��� ���� ������ ���� ���� �մϴ�.

// �� ������ �����ų �������

cbuffer CameraBuffer : register(b0)
{
    matrix View;
    float3 CameraPosition;
    float1 PlayerHP;
    
    float4 CameraColor;
}

// �� ������ ������Ʈ���� �����ų �������
cbuffer ObjectBuffer : register(b1)
{
    matrix WorldTransform;
    
    float3 ObjectColor;
    float ObjectColorPower;
    
    float4 ObjectBaseColor;
    
    float Metallic;
    float Loughness;
    
    float2 Flag;
}

cbuffer BoneBuffer : register(b2)
{
    matrix BoneTransform[120];
}



// �ѹ� ���� �����ϸ� ���� ������ ���� �������
cbuffer EngineBuffer : register(b3)
{
    matrix Projection;
    matrix SpriteProjection;
}

// DirectionLight �������
cbuffer DirectionLightBuffer : register(b4)
{
    float3 WorldDirectionLight;
    float1 WorldDirectionPower;
}

// �ؽ��ĵ� �Ƹ� ������� ������ �ʹ�.
Texture2D txUI : register(t0);
Texture2D txDiffuseMap : register(t1);
Texture2D txSpecularMap : register(t2);
Texture2D txAmbientMap : register(t3);
Texture2D txEmissiveMap : register(t4);
Texture2D txHeightMap : register(t5);
Texture2D txNormalMap : register(t6);
Texture2D txShininessMap : register(t7);
Texture2D txOpacityMap : register(t8);
Texture2D txDisplacement : register(t9);
Texture2D txLightMap : register(t10);
Texture2D txReflectionMap : register(t11);
// PBR
Texture2D txColorMap : register(t12);
Texture2D txRoughness : register(t13);
Texture2D tx1 : register(t14);
Texture2D txMetalness : register(t15);
Texture2D tx2 : register(t16);

// �� �Ʒ��δ� ������� ������.
// �׸��ڸ� ���� �ؽ���
Texture2D txShadowMap : register(t20);

Texture2D txCombine : register(t21);


// ibl�� ���� �ؽ���
TextureCube txIBL_EnvMap : register(t30);
TextureCube txIBL_DiffuseMap : register(t31);
TextureCube txIBL_SpecularMap : register(t32);
Texture2D txIBL_SpecularBRDF_LUT : register(t33);

// ���÷�
SamplerState LinearSampler : register(s0);
SamplerState clampSampler : register(s1);

struct Static_VS_Input
{
    float4 Pos : POSITION;
    float3 UVW : TEXCOORD;
    float3 Normal : NORMAL;
    float3 Tangent : TANGENT;
};

struct Skeletal_VS_Input
{
    float4 Pos : POSITION;
    float3 UVW : TEXCOORD;
    float3 Normal : NORMAL;
    float3 Tangent : TANGENT;
    float3 Weights : WEIGHTS;
    float4 BoneIndices : BONEINDICES;
};

struct Combine_VS_INPUT
{
    float4 Pos : POSITION;
    float3 UVW : TEXCOORD;
};

struct PS_Input
{
    float4 Pos : SV_POSITION;
    float4 WorldPos : POSITION;
    float3 Normal : NORMAL;
    float3 Tangent : TANGENT;
    float3 BiTangent : BITANGENT;
    float3 UVW : TEXCOORD;
    float4 PosShadow : POSITION1;
};

struct Sprite_PS_Input
{
    float4 Pos : SV_POSITION;
    float4 WorldPos : POSITION;
    float3 Normal : NORMAL;
    float3 Tangent : TANGENT;
    float3 BiTangent : BITANGENT;
    float3 UVW : TEXCOORD;
    float4 PosShadow : POSITION1;
};