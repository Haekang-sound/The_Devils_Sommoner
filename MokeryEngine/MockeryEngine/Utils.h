#pragma once
#include "../Libraries/DXTK/Inc/SimpleMath.h"

using namespace DirectX;

class Utils
{
public:
	static SimpleMath::Quaternion LookAt(SimpleMath::Vector3 forward, SimpleMath::Vector3 up);
	static SimpleMath::Vector3 LookRotation(SimpleMath::Vector3 forward, SimpleMath::Vector3 up);
};