#include "pch.h"
#include "Component.h"
#include "Collision.h"

bool Component::SetOwner(GameObject* owner)
{
	// 이 분기문은 필요하다면 없애도 된다. 
	// 만약 컴포넌트에 오너 설정이 성공하면 1을 반환한다.
	// 굳이 불값을 리턴 안해도 되지만 확인을 위해 불값을 반환한 것임.
	if (m_pOwner == nullptr)
	{
		m_pOwner = owner;
		return true;
	}
	else
	{
		return false;
	}
}

ID3DRenderer* Component::m_renderer = nullptr;