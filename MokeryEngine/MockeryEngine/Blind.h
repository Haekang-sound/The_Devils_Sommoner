#pragma once

#include "EnemyComponent.h"


class Blind : public EnemyComponent
{
	using Super = EnemyComponent;
public:
	Blind();
	~Blind();

	virtual void Awake() override;
	virtual void Start() override;
	virtual void FixedUpdate(float dTime) override;
	virtual void Update(float dTime) override;
	virtual void LateUpdate(float dTime) override;
	virtual void Render() override;
	virtual void Release() override;
	virtual void OnCollisionEnter(Collision* collision) override;
	virtual void OnCollisionStay(Collision* collision) override;
	virtual void OnCollisionExit(Collision* collision) override;

};

