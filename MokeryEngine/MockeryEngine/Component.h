#pragma once
#include "framework.h"
#include "../Libraries/DXTK/Inc/SimpleMath.h"
using namespace DirectX;

/// <summary>
/// 모든 컴포넌트들의 인터페이스가 되는 IComponent
/// </summary>

// 게임 오브젝트에 대한 전방 선언
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
	// 이 컴포넌트를 어느 오브젝트가 가지고 있는지 알려주는 포인터.
	GameObject* m_pOwner = nullptr;

	static ID3DRenderer* m_renderer;

private:
	friend class MockeryEngine;
	static void SetRenderer(ID3DRenderer* _Value) { if (m_renderer == nullptr) m_renderer = _Value; };
};

