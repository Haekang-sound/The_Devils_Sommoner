#pragma once

#include <vector>

class RigidBody;

class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();
	
public:
	void Init();
	void Update();
	void Finalize();

public:
	void AddRigidbody(RigidBody* rigid);

private:
	std::vector<RigidBody*> m_rigidBodies;
};

