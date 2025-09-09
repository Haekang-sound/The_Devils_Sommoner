#pragma once

#include "EnemyComponent.h"


class Ghost : public EnemyComponent
{
	using Super = EnemyComponent;
public:
	Ghost();
	~Ghost();

	virtual void Start() override;
	virtual void FixedUpdate(float dTime) override;
	virtual void Update(float dTime) override;
	virtual void LateUpdate(float dTime) override;
	virtual void Render() override;
	virtual void Release() override;
	virtual void OnCollisionEnter(Collision* collision) override;
	virtual void OnCollisionStay(Collision* collision) override;
	virtual void OnCollisionExit(Collision* collision) override;

	bool GetDisturb() { return m_isDisturbing; }
private:
	bool m_isDisturbing;
};

