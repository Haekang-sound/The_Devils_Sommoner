#include "pch.h"
#include "Object.h"
#include "IComponent.h"

void Object::Update()
{
	for (auto e : m_components)
	{
		e->Update();
	}
}

void Object::Render()
{
	for (auto e : m_components)
	{
		e->Render();
	}
}

void Object::ReleaseComponent()
{
	for (auto e : m_components)
	{
		delete e;
	}
}

