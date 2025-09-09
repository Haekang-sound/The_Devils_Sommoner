#pragma once
#include "Component.h"
#include "../Graphics/ID3DRenderer.h"

/// <summary>
/// 우리 트랜스폼 한다!
/// </summary>
class Transform : public Component
{
public:
	Transform();
	virtual ~Transform();
	virtual void Start() override;
	virtual void FixedUpdate(float dTime) override;
	virtual void Update(float dTime) override;
	virtual void LateUpdate(float dTime) override;
	virtual void Render() override;
	virtual void Release() override;


public:
	/// <summary>
	/// 240208 용준 작성
	/// 용준 : 임시로 여기다 변수를 만들어 둔다.
	/// 빠르게 구현하기위해 대충 만들었다.
	/// 필요에 맞춰 바꿔준다.
	/// </summary>
	SimpleMath::Vector3 m_MoveSpeed{ 0,0,0 };
	SimpleMath::Vector3 m_MoveDir{};

	SimpleMath::Matrix m_DirMatrix{};

	SimpleMath::Vector3 m_Right{ _matLocal.Right()};
	SimpleMath::Vector3 m_UP{ _matLocal.Up() };
	SimpleMath::Vector3 m_Forward{ _matLocal.Forward()*-1 };


	void SetDirection();
	// 계층관계
public:
	// 부모의 행렬을 얻어오자
	SimpleMath::Matrix GetParentTransform();
	bool HasParent() { return m_parent != nullptr; } // 부모가 존재하는가? 

	Transform* GetParent() { return m_parent; }
	void SetParent(Transform* parent) { m_parent = parent; }

	const std::vector<Transform*>& GetChildren() { return m_children; }
	void AddChild(Transform* child) { m_children.push_back(child); }

	// 트랜스폼 설정
public:
	// 전방벡터를 만들어보자

	// 실시간으로 부모와 자신의 local을 이용해서 world를 갱신한다.
	void UpdateTransform();

	// 쿼터니언 값을 오일러 각을 바꿔준다.
	SimpleMath::Vector3 ToEulerAngles(SimpleMath::Quaternion q);

	// 행렬 요소를 조립한다
	void AssembleLocal();
	SimpleMath::Matrix AssembleWorld();

	// get,set
public:
	// local
	SimpleMath::Matrix GetLocal() const { return _matLocal; }
	void SetLocal(SimpleMath::Matrix val) { _matLocal = val; }

	// world
	SimpleMath::Matrix GetWorld() const { return _matWorld; }
	void SetWorld(SimpleMath::Matrix val) { _matWorld = val; }

	// Local
	SimpleMath::Vector3 GetLocalScale() { return m_localScale; }
	void SetLocalScale(const SimpleMath::Vector3& localScale) { m_localScale = localScale; UpdateTransform(); }
	SimpleMath::Vector3 GetLocalRotation() { return m_localRotation; }
	void SetLocalRotation(const SimpleMath::Vector3& localRotation) { m_localRotation = localRotation; UpdateTransform(); }
	SimpleMath::Vector3 GetLocalPosition() { return m_localPosition; }
	void SetLocalPosition(const SimpleMath::Vector3& localPosition) { m_localPosition = localPosition; UpdateTransform(); }

	// World
	SimpleMath::Vector3 GetScale() { return _scale; }
	void SetScale(const SimpleMath::Vector3& scale);
	SimpleMath::Vector3 GetRotation() { return _rotation; }
	void SetRotation(const SimpleMath::Vector3& rotation);
	void SetRotation(const SimpleMath::Quaternion& quat);
	SimpleMath::Vector3 GetPosition() { return _position; }
	void SetPosition(const SimpleMath::Vector3& position);

	// 전방벡터
	DirectX::SimpleMath::Vector3 GetForward() const { return _matWorld.Forward() * -1.f; }

	/// 쿼터니언
	SimpleMath::Quaternion GetQuaternion() const { return m_Quaternion; }
	void SetQuaternion(SimpleMath::Quaternion val) { m_Quaternion = val; }

	// 랜더트랜스폼을 넘겨준다
	RenderTransform* GetRenderTransformW()const { return m_renderTransformW; };
	RenderTransform* GetRenderTransformL()const { return m_renderTransformL; };


/// <summary>
/// Movement
/// </summary>
public:
	// 이동 
	void TransportX(float speed);	// 1. x축 이동 +
	void TransportY(float speed);	// 3. y축 이동 +
	void TransportZ(float speed);	// 2. z축 이동 +
	
	// 회전
	void Pitch(float radian);	// x축 회전
	void Roll(float radian);	// y축 회전
	void Yaw(float radian);	// y축 회전

	// scale
	void ScaleX(float val);
	void ScaleY(float val);
	void ScaleZ(float val);

	// 원위치

	void GoBack();
	void GoBackPos();

private:
	SimpleMath::Matrix _matLocal = SimpleMath::Matrix::Identity;
	SimpleMath::Matrix _matWorld = SimpleMath::Matrix::Identity;

	// 분해된 srt 이것들을 조립해서 뭔가 만든다.
	SimpleMath::Vector3 m_localScale	= { 1.f, 1.f, 1.f };
	SimpleMath::Vector3 m_localRotation = { 0.f, 0.f, 0.f };
	SimpleMath::Vector3 m_localPosition = { 0.f, 0.f, 0.f };

	SimpleMath::Vector3 m_forward;
	SimpleMath::Quaternion m_Quaternion;

// 조립을 위한 임시값에 가까움
private:
	SimpleMath::Vector3 _scale;// world
	SimpleMath::Vector3 _rotation;// world
	SimpleMath::Vector3 _position;// world





private:
	Transform* m_parent;
	std::vector<Transform*> m_children;
	RenderTransform* m_renderTransformW;
	RenderTransform* m_renderTransformL;

};