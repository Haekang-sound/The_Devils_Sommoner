#pragma once

#include "InteractiveObject.h"

class GameObject;


class HeartComponent : public InteractiveObject
{
	using Super = InteractiveObject;

public:
	HeartComponent();
	virtual ~HeartComponent();

public:
	void Start() override;
	void FixedUpdate(float dTime) override;
	void Update(float dTime) override;
	void LateUpdate(float dTime) override;
	void Render() override;
	void Release() override;

	// �̰� ������ ���� �� ����� ��Ʈ �߰��ؾߵ�
	void SetAltarObject(std::vector<GameObject*> _altar) { m_altar = _altar; }

public:
	void Interact() override;

	bool GetisActivated() { return m_isActivated; }

private:
	std::vector<GameObject*> m_altar;
	int m_altarCount;
	bool m_isActivated;


};

