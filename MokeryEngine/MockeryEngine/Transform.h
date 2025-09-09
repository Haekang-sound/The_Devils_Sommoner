#pragma once
#include "Component.h"
#include "../Graphics/ID3DRenderer.h"

/// <summary>
/// �츮 Ʈ������ �Ѵ�!
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
	/// 240208 ���� �ۼ�
	/// ���� : �ӽ÷� ����� ������ ����� �д�.
	/// ������ �����ϱ����� ���� �������.
	/// �ʿ信 ���� �ٲ��ش�.
	/// </summary>
	SimpleMath::Vector3 m_MoveSpeed{ 0,0,0 };
	SimpleMath::Vector3 m_MoveDir{};

	SimpleMath::Matrix m_DirMatrix{};

	SimpleMath::Vector3 m_Right{ _matLocal.Right()};
	SimpleMath::Vector3 m_UP{ _matLocal.Up() };
	SimpleMath::Vector3 m_Forward{ _matLocal.Forward()*-1 };


	void SetDirection();
	// ��������
public:
	// �θ��� ����� ������
	SimpleMath::Matrix GetParentTransform();
	bool HasParent() { return m_parent != nullptr; } // �θ� �����ϴ°�? 

	Transform* GetParent() { return m_parent; }
	void SetParent(Transform* parent) { m_parent = parent; }

	const std::vector<Transform*>& GetChildren() { return m_children; }
	void AddChild(Transform* child) { m_children.push_back(child); }

	// Ʈ������ ����
public:
	// ���溤�͸� ������

	// �ǽð����� �θ�� �ڽ��� local�� �̿��ؼ� world�� �����Ѵ�.
	void UpdateTransform();

	// ���ʹϾ� ���� ���Ϸ� ���� �ٲ��ش�.
	SimpleMath::Vector3 ToEulerAngles(SimpleMath::Quaternion q);

	// ��� ��Ҹ� �����Ѵ�
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

	// ���溤��
	DirectX::SimpleMath::Vector3 GetForward() const { return _matWorld.Forward() * -1.f; }

	/// ���ʹϾ�
	SimpleMath::Quaternion GetQuaternion() const { return m_Quaternion; }
	void SetQuaternion(SimpleMath::Quaternion val) { m_Quaternion = val; }

	// ����Ʈ�������� �Ѱ��ش�
	RenderTransform* GetRenderTransformW()const { return m_renderTransformW; };
	RenderTransform* GetRenderTransformL()const { return m_renderTransformL; };


/// <summary>
/// Movement
/// </summary>
public:
	// �̵� 
	void TransportX(float speed);	// 1. x�� �̵� +
	void TransportY(float speed);	// 3. y�� �̵� +
	void TransportZ(float speed);	// 2. z�� �̵� +
	
	// ȸ��
	void Pitch(float radian);	// x�� ȸ��
	void Roll(float radian);	// y�� ȸ��
	void Yaw(float radian);	// y�� ȸ��

	// scale
	void ScaleX(float val);
	void ScaleY(float val);
	void ScaleZ(float val);

	// ����ġ

	void GoBack();
	void GoBackPos();

private:
	SimpleMath::Matrix _matLocal = SimpleMath::Matrix::Identity;
	SimpleMath::Matrix _matWorld = SimpleMath::Matrix::Identity;

	// ���ص� srt �̰͵��� �����ؼ� ���� �����.
	SimpleMath::Vector3 m_localScale	= { 1.f, 1.f, 1.f };
	SimpleMath::Vector3 m_localRotation = { 0.f, 0.f, 0.f };
	SimpleMath::Vector3 m_localPosition = { 0.f, 0.f, 0.f };

	SimpleMath::Vector3 m_forward;
	SimpleMath::Quaternion m_Quaternion;

// ������ ���� �ӽð��� �����
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