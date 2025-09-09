#include "pch.h"
#include "PhysicsManager.h"
#include "RigidBody.h"


PhysicsManager::PhysicsManager()
{

}

PhysicsManager::~PhysicsManager()
{

}

void PhysicsManager::Init()
{

}

void PhysicsManager::Update()
{
	for (auto rigid : m_rigidBodies)
	{
		rigid->SetBeforePosition();
	}
}

void PhysicsManager::Finalize()
{
	m_rigidBodies.clear();
}

void PhysicsManager::AddRigidbody(RigidBody* rigid)
{
	m_rigidBodies.push_back(rigid);
}
