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
	// 용준 작성 적절히 변경 필요
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
	// 로컬 정보를 조립한다
	AssembleLocal();

	// 부모가 있다면
	if (HasParent())
	{
		// 자신의 로컬에 부모의 월드를 곱해서
		// 현재 계층의 월드매트릭스를 만든다
		_matWorld = _matLocal * m_parent->GetWorld();
	}
	else
	{
		_matWorld = _matLocal;

	}

	// 완성된 월드에 대해서
	SimpleMath::Quaternion quat;
	// 월드 매트릭스를 분해하고
	_matWorld.Decompose(_scale, quat, _position);
	m_Quaternion = quat;
	// 쿼터니언으로 생성된 회전의 대한 값은
	// 오일러각으로 변환해서 저장한다.
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

	// 자신의 메트릭스 업데이트가 끝났으니 이를 토대로
	// 자식객체들에게 update를 실행시켜 준다.
	for (Transform* child : m_children)
	{
		child->UpdateTransform();
	}
}

/// <summary>
/// 쿼터니언을 오일러각으로 바꿔주는 함수
/// </summary>
/// <param name="q">쿼터니언</param>
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
/// 로컬정보를 조립한다.
/// </summary>
void Transform::AssembleLocal()
{
	// vector를 변환, 매트릭스 생성
	/*SimpleMath::Matrix matScale = SimpleMath::Matrix::CreateScale(m_localScale);
	SimpleMath::Matrix matRotation = SimpleMath::Matrix::CreateRotationX(m_localRotation.x);
	matRotation *= SimpleMath::Matrix::CreateRotationY(m_localRotation.y);
	matRotation *= SimpleMath::Matrix::CreateRotationZ(m_localRotation.z);
	SimpleMath::Matrix matTranslation = SimpleMath::Matrix::CreateTranslation(m_localPosition);*/

	// 조립
	_matLocal = SimpleMath::Matrix::CreateScale(m_localScale) * SimpleMath::Matrix::CreateFromYawPitchRoll(m_localRotation) * SimpleMath::Matrix::CreateTranslation(m_localPosition);
}

/// <summary>
/// 현재 갖고있는 월드정보만 조합해서 리턴한다.
/// </summary>
SimpleMath::Matrix Transform::AssembleWorld()
{
	// vector를 변환, 매트릭스 생성
	SimpleMath::Matrix matScale = SimpleMath::Matrix::CreateScale(_scale);
	SimpleMath::Matrix matRotation = SimpleMath::Matrix::CreateRotationX(_rotation.x);
	matRotation *= SimpleMath::Matrix::CreateRotationY(_rotation.y);
	matRotation *= SimpleMath::Matrix::CreateRotationZ(_rotation.z);
	SimpleMath::Matrix matTranslation = SimpleMath::Matrix::CreateTranslation(_position);

	// 조립
	_matWorld *= matScale;
	_matWorld *= matRotation;
	_matWorld *= matTranslation;

	return _matWorld;
}


void Transform::SetScale(const SimpleMath::Vector3& worldScale)
{
	// 부모가 있다면
	if (HasParent())
	{
		// 부모의 스케일 값을 받아온다.
		SimpleMath::Vector3 parentScale = m_parent->GetScale();

		// 월드의 스케일 값을 가져온다.
		SimpleMath::Vector3 scale = worldScale;

		// 스케일을 나눠서 로컬값으로 변환시켜준다.
		scale.x /= parentScale.x;
		scale.y /= parentScale.y;
		scale.z /= parentScale.z;

		// 변환된 로컬스케일을 저장한다.
		SetLocalScale(scale);
	}
	else // 부모가 없다면
	{
		// 월드와 로컬 스케일은 같다
		SetLocalScale(worldScale);
	}
}

void Transform::SetRotation(const SimpleMath::Vector3& worldRotation)
{
	// 부모가 있다면
	if (HasParent())
	{
		// 부모의 역행렬을 가져온다.
		SimpleMath::Matrix inverseMatrix = m_parent->GetWorld().Invert();

		SimpleMath::Vector3 rotation;
		// 부모의 역행렬을 곱한 로컬 회전행렬을 만든다.
		rotation.TransformNormal(worldRotation, inverseMatrix);

		// 저장한다.
		SetLocalRotation(rotation);
	}
	else // 부모가 없다면
	{
		// 월드와 로컬 회전은 같다
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
	// 부모가 있다면
	if (HasParent())
	{
		// 부모의 역행렬을 가져온다.
		SimpleMath::Matrix worldToParentLocalMatrix = m_parent->GetWorld().Invert();

		SimpleMath::Vector3 position;
		// 부모의 역행렬을 곱한 로컬 이동행렬을 만든다.
		position.Transform(worldPosition, worldToParentLocalMatrix);
		// 저장한다.
		SetLocalPosition(position);
	}
	else // 부모가 없다면
	{
		// 월드와 로컬 위치는 같다
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

// 회전함수
void Transform::Pitch(float radian)
{
	SimpleMath::Vector3 _rot = GetLocalRotation();
	_rot.x += radian;

	// 카메라 각도 제한용
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
