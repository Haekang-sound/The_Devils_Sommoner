#pragma once
#include "framework.h"
#include "../Libraries/DXTK/Inc/SimpleMath.h"
using namespace DirectX;

/// <summary>
/// ��� ������Ʈ���� �������̽��� �Ǵ� IComponent
/// </summary>

// ���� ������Ʈ�� ���� ���� ����
class GameObject;
class Collision;

class Component
{
public:
	virtual ~Component() {};

	virtual void Awake() {};
	virtual void Start() abstract;
	virtual void FixedUpdate(float dTime) abstract;
	virtual void Update(float dTime) abstract;
	virtual void LateUpdate(float dTime) abstract;
	virtual void Render() abstract;
	virtual void Release() abstract;

public:
	bool SetOwner(GameObject* owner);
	GameObject* GetOwner() { return m_pOwner; }

	virtual void OnCollisionEnter(Collision* collision) {};
	virtual void OnCollisionStay(Collision* collision) {};
	virtual void OnCollisionExit(Collision* collision) {};

protected:
	// �� ������Ʈ�� ��� ������Ʈ�� ������ �ִ��� �˷��ִ� ������.
	GameObject* m_pOwner = nullptr;

	static ID3DRenderer* m_renderer;

private:
	friend class MockeryEngine;
	static void SetRenderer(ID3DRenderer* _Value) { if (m_renderer == nullptr) m_renderer = _Value; };
};

