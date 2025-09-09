#include "pch.h"
#include "Component.h"
#include "Collision.h"

bool Component::SetOwner(GameObject* owner)
{
	// �� �б⹮�� �ʿ��ϴٸ� ���ֵ� �ȴ�. 
	// ���� ������Ʈ�� ���� ������ �����ϸ� 1�� ��ȯ�Ѵ�.
	// ���� �Ұ��� ���� ���ص� ������ Ȯ���� ���� �Ұ��� ��ȯ�� ����.
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