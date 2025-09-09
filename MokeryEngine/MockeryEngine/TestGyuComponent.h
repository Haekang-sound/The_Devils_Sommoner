#pragma once
#include "Component.h"

class TestGyuComponent : public Component
{
public:
	TestGyuComponent();
	virtual ~TestGyuComponent();

public:
	void Start() override;
	void FixedUpdate(float dTime) override;
	void Update(float dTime) override;
	void LateUpdate(float dTime) override;
	void Render() override;
	void Release() override;
	void OnCollisionEnter(Collision* collision) override;
	void OnCollisionStay(Collision* collision) override;
	void OnCollisionExit(Collision* collision) override;

public:

};

