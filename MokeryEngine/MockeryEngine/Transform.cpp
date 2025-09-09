#include "pch.h"
#include "Transform.h"

#include "GameObject.h"

Transform::Transform()
	:m_parent(nullptr), m_children{},
	m_renderTransformW(nullptr), m_renderTransformL(nullptr)
{
	m_renderTransformW = new RenderTransform();
	m_renderTransformL = new RenderTransform();
}

Transform::~Transform()
{

}

void Transform::Start()
{

}

void Transform::FixedUpdate(float dTime)
{

}

void Transform::Update(float dTime)
{
}

void Transform::LateUpdate(float dTime)
{

}

void Transform::Render()
{

}

void Transform::Release()
{
	delete m_renderTransformW;
}

void Transform::SetDirection()
{
	// ���� �ۼ� ������ ���� �ʿ�
	{
		m_DirMatrix = SimpleMath::Matrix::CreateFromYawPitchRoll(m_localRotation.y, m_localRotation.x, 0);

		m_Forward = { m_DirMatrix._31,m_DirMatrix._32,m_DirMatrix._33 };
		m_Forward.Normalize();
		m_Right = m_DirMatrix.Right();
		m_Right.Normalize();
		m_UP = m_DirMatrix.Up();
		m_UP.Normalize();

		m_MoveDir.x = (m_Forward.x * m_MoveSpeed.z) + (m_Right.x * m_MoveSpeed.x) + (m_UP.x * m_MoveSpeed.y);
		//m_MoveDir.y = (m_Forward.y * m_MoveSpeed.z) + (m_Right.y * m_MoveSpeed.x) + (m_UP.y * m_MoveSpeed.y);
		m_MoveDir.y = 0.f /*(m_Forward.y * m_MoveSpeed.z) + (m_Right.y * m_MoveSpeed.x) + (m_UP.y * m_MoveSpeed.y)*/;
		m_MoveDir.z = (m_Forward.z * m_MoveSpeed.z) + (m_Right.z * m_MoveSpeed.x) + (m_UP.z * m_MoveSpeed.y);


		m_localPosition += m_MoveDir;
	}
	UpdateTransform();
}

SimpleMath::Matrix Transform::GetParentTransform()
{
	return GetOwner()->GetParent()->GetComponent<Transform>()->GetWorld();
}



void Transform::UpdateTransform()
{
	// ���� ������ �����Ѵ�
	AssembleLocal();

	// �θ� �ִٸ�
	if (HasParent())
	{
		// �ڽ��� ���ÿ� �θ��� ���带 ���ؼ�
		// ���� ������ �����Ʈ������ �����
		_matWorld = _matLocal * m_parent->GetWorld();
	}
	else
	{
		_matWorld = _matLocal;

	}

	// �ϼ��� ���忡 ���ؼ�
	SimpleMath::Quaternion quat;
	// ���� ��Ʈ������ �����ϰ�
	_matWorld.Decompose(_scale, quat, _position);
	m_Quaternion = quat;
	// ���ʹϾ����� ������ ȸ���� ���� ����
	// ���Ϸ������� ��ȯ�ؼ� �����Ѵ�.
	//_rotation = ToEulerAngles(quat);
	_rotation = quat.ToEuler();

	m_renderTransformW->Position.x = _position.x;
	m_renderTransformW->Position.y = _position.y;
	m_renderTransformW->Position.z = _position.z;
	m_renderTransformW->Rotation.x = _rotation.x;
	m_renderTransformW->Rotation.y = _rotation.y;
	m_renderTransformW->Rotation.z = _rotation.z;
	m_renderTransformW->Scale.x = _scale.x;
	m_renderTransformW->Scale.y = _scale.y;
	m_renderTransformW->Scale.z = _scale.z;

	m_renderTransformL->Position.x = m_localPosition.x;
	m_renderTransformL->Position.y = m_localPosition.y;
	m_renderTransformL->Position.z = m_localPosition.z;
	m_renderTransformL->Rotation.x = m_localRotation.x;
	m_renderTransformL->Rotation.y = m_localRotation.y;
	m_renderTransformL->Rotation.z = m_localRotation.z;
	m_renderTransformL->Scale.x = m_localScale.x;
	m_renderTransformL->Scale.y = m_localScale.y;
	m_renderTransformL->Scale.z = m_localScale.z;

	// �ڽ��� ��Ʈ���� ������Ʈ�� �������� �̸� ����
	// �ڽİ�ü�鿡�� update�� ������� �ش�.
	for (Transform* child : m_children)
	{
		child->UpdateTransform();
	}
}

/// <summary>
/// ���ʹϾ��� ���Ϸ������� �ٲ��ִ� �Լ�
/// </summary>
/// <param name="q">���ʹϾ�</param>
/// <returns>Vector3</returns>
DirectX::SimpleMath::Vector3 Transform::ToEulerAngles(SimpleMath::Quaternion q)
{
	SimpleMath::Vector3 angles;

	// roll (x-axis rotation)
	double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
	double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
	angles.x = std::atan2(sinr_cosp, cosr_cosp);

	// pitch (y-axis rotation)
	double sinp = std::sqrt(1 + 2 * (q.w * q.y - q.x * q.z));
	double cosp = std::sqrt(1 - 2 * (q.w * q.y - q.x * q.z));
	angles.y = 2 * std::atan2(sinp, cosp) - 3.14159f / 2;

	// yaw (z-axis rotation)
	double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
	double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
	angles.z = std::atan2(siny_cosp, cosy_cosp);

	return angles;

}

/// <summary>
/// ���������� �����Ѵ�.
/// </summary>
void Transform::AssembleLocal()
{
	// vector�� ��ȯ, ��Ʈ���� ����
	/*SimpleMath::Matrix matScale = SimpleMath::Matrix::CreateScale(m_localScale);
	SimpleMath::Matrix matRotation = SimpleMath::Matrix::CreateRotationX(m_localRotation.x);
	matRotation *= SimpleMath::Matrix::CreateRotationY(m_localRotation.y);
	matRotation *= SimpleMath::Matrix::CreateRotationZ(m_localRotation.z);
	SimpleMath::Matrix matTranslation = SimpleMath::Matrix::CreateTranslation(m_localPosition);*/

	// ����
	_matLocal = SimpleMath::Matrix::CreateScale(m_localScale) * SimpleMath::Matrix::CreateFromYawPitchRoll(m_localRotation) * SimpleMath::Matrix::CreateTranslation(m_localPosition);
}

/// <summary>
/// ���� �����ִ� ���������� �����ؼ� �����Ѵ�.
/// </summary>
SimpleMath::Matrix Transform::AssembleWorld()
{
	// vector�� ��ȯ, ��Ʈ���� ����
	SimpleMath::Matrix matScale = SimpleMath::Matrix::CreateScale(_scale);
	SimpleMath::Matrix matRotation = SimpleMath::Matrix::CreateRotationX(_rotation.x);
	matRotation *= SimpleMath::Matrix::CreateRotationY(_rotation.y);
	matRotation *= SimpleMath::Matrix::CreateRotationZ(_rotation.z);
	SimpleMath::Matrix matTranslation = SimpleMath::Matrix::CreateTranslation(_position);

	// ����
	_matWorld *= matScale;
	_matWorld *= matRotation;
	_matWorld *= matTranslation;

	return _matWorld;
}


void Transform::SetScale(const SimpleMath::Vector3& worldScale)
{
	// �θ� �ִٸ�
	if (HasParent())
	{
		// �θ��� ������ ���� �޾ƿ´�.
		SimpleMath::Vector3 parentScale = m_parent->GetScale();

		// ������ ������ ���� �����´�.
		SimpleMath::Vector3 scale = worldScale;

		// �������� ������ ���ð����� ��ȯ�����ش�.
		scale.x /= parentScale.x;
		scale.y /= parentScale.y;
		scale.z /= parentScale.z;

		// ��ȯ�� ���ý������� �����Ѵ�.
		SetLocalScale(scale);
	}
	else // �θ� ���ٸ�
	{
		// ����� ���� �������� ����
		SetLocalScale(worldScale);
	}
}

void Transform::SetRotation(const SimpleMath::Vector3& worldRotation)
{
	// �θ� �ִٸ�
	if (HasParent())
	{
		// �θ��� ������� �����´�.
		SimpleMath::Matrix inverseMatrix = m_parent->GetWorld().Invert();

		SimpleMath::Vector3 rotation;
		// �θ��� ������� ���� ���� ȸ������� �����.
		rotation.TransformNormal(worldRotation, inverseMatrix);

		// �����Ѵ�.
		SetLocalRotation(rotation);
	}
	else // �θ� ���ٸ�
	{
		// ����� ���� ȸ���� ����
		SetLocalRotation(worldRotation);
	}
}

void Transform::SetRotation(const SimpleMath::Quaternion& quat)
{
	SimpleMath::Vector3 rot = ToEulerAngles(quat);
	SetRotation(rot);
}

void Transform::SetPosition(const SimpleMath::Vector3& worldPosition)
{
	// �θ� �ִٸ�
	if (HasParent())
	{
		// �θ��� ������� �����´�.
		SimpleMath::Matrix worldToParentLocalMatrix = m_parent->GetWorld().Invert();

		SimpleMath::Vector3 position;
		// �θ��� ������� ���� ���� �̵������ �����.
		position.Transform(worldPosition, worldToParentLocalMatrix);
		// �����Ѵ�.
		SetLocalPosition(position);
	}
	else // �θ� ���ٸ�
	{
		// ����� ���� ��ġ�� ����
		SetLocalPosition(worldPosition);
	}
}

void Transform::TransportX(float speed)
{
	m_localPosition.x += speed;
	UpdateTransform();
}

void Transform::TransportY(float speed)
{
	m_localPosition.y += speed;
	UpdateTransform();
}

void Transform::TransportZ(float speed)
{
	m_localPosition.z += speed;
	UpdateTransform();
}

// ȸ���Լ�
void Transform::Pitch(float radian)
{
	SimpleMath::Vector3 _rot = GetLocalRotation();
	_rot.x += radian;

	// ī�޶� ���� ���ѿ�
	if (_rot.x > 80.f * 3.141592f / 180.f)
	{
		_rot.x = 80.f * 3.141592f / 180.f;
	}
	else if (_rot.x < -80.f * 3.141592f / 180.f)
	{
		_rot.x = -80.f * 3.141592f / 180.f;
	}

	SetLocalRotation(_rot);
}

void Transform::Roll(float radian)
{
	SimpleMath::Vector3 _rot = GetLocalRotation();

	_rot.y += radian;

	SetLocalRotation(_rot);
}

void Transform::Yaw(float radian)
{
	SimpleMath::Vector3 _rot = GetLocalRotation();
	_rot.z += radian;


	SetLocalRotation(_rot);
}

void Transform::ScaleX(float val)
{
	SimpleMath::Vector3 _scale = GetLocalScale();
	_scale.x += val;
	SetLocalScale(_scale);
}

void Transform::ScaleY(float val)
{
	SimpleMath::Vector3 _scale = GetLocalScale();
	_scale.y += val;
	SetLocalScale(_scale);
}

void Transform::ScaleZ(float val)
{
	SimpleMath::Vector3 _scale = GetLocalScale();
	_scale.z += val;
	SetLocalScale(_scale);
}

void Transform::GoBack()
{
	SetLocalScale({ 1.f, 1.f, 1.f });
	SetLocalRotation({ 0.f, 0.f, 0.f });
	SetLocalPosition({ 0.f, 0.f, 0.f });
}

void Transform::GoBackPos()
{
	SetLocalPosition({ 0.f, 0.f, 0.f });
}
