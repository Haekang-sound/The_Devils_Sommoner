#pragma once
/// <summary>
/// ������Ʈ�� ��� Entity Ŭ����
/// </summary>

class IComponent;

class Object
{
public:
	void Update();
	void Render();

	// ��ƼƼ�� ������Ʈ�� �߰��Ѵ�.
	template<typename T>
	void AddComponent();
	
	// ���ϴ� ������Ʈ�� ��ȯ�Ѵ�.
	template<typename T>
	T* GetComponent();

	// ������Ʈ���� �����Ѵ�.
	void ReleaseComponent();

private:
	// ������Ʈ�� ��Ƶδ� ����.
	std::vector<IComponent*> m_components;

};

template<typename T>
void Object::AddComponent()
{
	// T�� �����Ѵ�.
	T* newComponent = new T;

	m_components.push_back(newComponent);
}

template<typename T>
T* Object::GetComponent()
{
	// ���͸� ��ȸ�ؼ�  
	for (auto e : m_components)
	{
		T* component = dynamic_cast<T*>(e);
		// T*�� �����Ѵٸ� 
		if (component)
		{
			// T�� �ش��ϴ� ������Ʈ�� ��ȯ�Ѵ�.
			return component;
		}
	}
	// ���͸� ������ ��ȸ�ϸ� nullptr�� ��ȯ�Ѵ�.
	return nullptr;
	 
}

