#pragma once

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.

// cpp�ܿ� ��������� �ʿ��� stl���� �߰��Ѵ�.
// ����� ����� �� �����ӿ�ũ ����� �߰��� ����Ѵ�.

#include "RendererDef.h"

#include <windows.h>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <memory>
#include <d3d11.h>
#include <dxgi.h>

#include "..\Libraries\DXTK\Inc\SimpleMath.h"
using namespace DirectX;

#include <wrl\client.h>
using namespace Microsoft;
using namespace WRL;


#pragma comment (lib, "d3d11.lib")
#pragma comment (lib,"dxgi.lib")

/// <summary>
/// �̷��� �޴´�. ��Ƽ���������� ���ٰ� �����Ѵ�.
/// 240205
/// -> ��Ƽ���� ������ ���������� ��ȭ��Ű�� �ʴ´ٰ� �����Ѵ�.
/// 240206
/// ������ ������Ʈ�� �������ִ� �Լ��� �������Ѵ�.(��������� ���);
/// </summary>


/// <summary>
/// ������ ������Ʈ���� ����ü�� ���� �ؾ� ȿ���������� �ϴ� �ϳ��� �� �����.
/// </summary>

struct ObjectInfo
{
	// �ٿ뵵�� ���� ����
	double m_Data = 0;
	float m_Metallic = 0;
	float m_Loughness = 0;
	bool m_IsLateRender = false;



	UINT m_ID = 0;
	RenderTransform* m_pWorldTM = nullptr;
	SimpleMath::Matrix* m_pWorldTransform = nullptr;
	UINT* m_pSTATE = nullptr;
	bool* m_pIsRender = nullptr;
	UINT m_CurrentSTATE = UINT32_MAX;
	SimpleMath::Color m_ColorPower{ 0.f,0.f,0.f,0.f };
	SimpleMath::Color m_BaseColor{0.f,0.f,0.f,0.f};


	// for sprite
	Vector2* m_pSize = nullptr;
	bool m_IsOriginCenter = false;

	// for Animation
	double m_CurrentTime = 0;
	UINT m_CurrentFrame = 0;
	float m_AnimationSpeed = 1.f;
	bool m_IsAnimationRefeat = false;
	bool m_IsAnimationPlay = true;
	bool m_IsAnimationComplete = false;

	// �����ڵ�
	bool m_ForBox = false;




	};
