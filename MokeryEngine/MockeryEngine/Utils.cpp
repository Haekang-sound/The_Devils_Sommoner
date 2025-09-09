#include "pch.h"
#include "Utils.h"

DirectX::SimpleMath::Quaternion Utils::LookAt(SimpleMath::Vector3 forward, SimpleMath::Vector3 up)
{


	return SimpleMath::Quaternion();





	/*DirectX::SimpleMath::Vector3 newForward = forward;
	newForward.Normalize();

	if (newForward.z < -0.9999999f)
	{
		return DirectX::SimpleMath::Quaternion(0.0f, 1.0f, 0.0f, 0.0f);
	}

	if (newForward.z > 0.9999999f)
	{
		return DirectX::SimpleMath::Quaternion::Identity;
	}

	DirectX::SimpleMath::Vector3 right = up.Cross(newForward);
	DirectX::SimpleMath::Vector3 newUp = newForward.Cross(right);

	DirectX::SimpleMath::Matrix rotationMatrix(
		right.x, right.y, right.z, 0.0f,
		newUp.x, newUp.y, newUp.z, 0.0f,
		newForward.x, newForward.y, newForward.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	DirectX::SimpleMath::Quaternion quaternion;
	quaternion = DirectX::SimpleMath::Quaternion::CreateFromRotationMatrix(rotationMatrix);

	return quaternion;*/

	/*SimpleMath::Vector3 newForward = -forward;
	newForward.Normalize();

	SimpleMath::Vector3 right = up.Cross(newForward);
	SimpleMath::Vector3 newUp = newForward.Cross(right);

	SimpleMath::Matrix rotationMatrix(
		right.x, right.y, right.z, 0.0f,
		newUp.x, newUp.y, newUp.z, 0.0f,
		newForward.x, newForward.y, newForward.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
	rotationMatrix.Transpose();

	SimpleMath::Quaternion quaternion;
	quaternion = SimpleMath::Quaternion::CreateFromRotationMatrix(rotationMatrix);

	return quaternion;*/
}

SimpleMath::Vector3 Utils::LookRotation(SimpleMath::Vector3 forward, SimpleMath::Vector3 up)
{
	SimpleMath::Vector3 newForward = forward;
	newForward.Normalize();

	// forward 벡터를 기준으로 right 벡터를 계산합니다.
	SimpleMath::Vector3 right = newForward.Cross(up);
	right.Normalize();

	// right와 forward를 기준으로 up 벡터를 계산합니다.
	SimpleMath::Vector3 newUp = right.Cross(newForward);
	newUp.Normalize();

	// forward, up, right를 행렬에 적용합니다.
	SimpleMath::Matrix rotationMatrix(
		right.x, up.x, -newForward.x, 0.0f,
		right.y, up.y, -newForward.y, 0.0f,
		right.z, up.z, -newForward.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	// 행렬을 이용하여 오일러 각을 계산합니다.
	float pitch = asinf(rotationMatrix._32);
	float yaw, roll;
	if (fabsf(rotationMatrix._32) < 0.9999999f) {
		yaw = atan2f(-rotationMatrix._31, rotationMatrix._33);
		roll = atan2f(-rotationMatrix._12, rotationMatrix._22);
	}
	else {
		yaw = 0.0f;
		roll = atan2f(rotationMatrix._21, rotationMatrix._11);
	}

	// 오일러 각을 반환합니다.
	return SimpleMath::Vector3(yaw, pitch, roll);
}
