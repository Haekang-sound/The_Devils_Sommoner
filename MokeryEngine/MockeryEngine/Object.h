#pragma once
/// <summary>
/// 컴포넌트를 담는 Entity 클래스
/// </summary>

class IComponent;

class Object
{
public:
	void Update();
	void Render();

	// 엔티티에 컴포넌트를 추가한다.
	template<typename T>
	void AddComponent();
	
	// 원하는 컴포넌트를 반환한다.
	template<typename T>
	T* GetComponent();

	// 컴포넌트들을 삭제한다.
	void ReleaseComponent();

private:
	// 컴포넌트를 담아두는 벡터.
	std::vector<IComponent*> m_components;

};

template<typename T>
void Object::AddComponent()
{
	// T를 생성한다.
	T* newComponent = new T;

	m_components.push_back(newComponent);
}

template<typename T>
T* Object::GetComponent()
{
	// 벡터를 순회해서  
	for (auto e : m_components)
	{
		T* component = dynamic_cast<T*>(e);
		// T*가 존재한다면 
		if (component)
		{
			// T에 해당하는 컴포넌트를 반환한다.
			return component;
		}
	}
	// 벡터를 끝까지 순회하면 nullptr을 반환한다.
	return nullptr;
	 
}

