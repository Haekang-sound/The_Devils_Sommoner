#pragma once
#include "Component.h"

#define DEFALUT_TIME 300.f

class SpriteRenderer;

class Timer : public Component
{
public:
	Timer();
	virtual ~Timer();

public:
	// Component��(��) ���� ��ӵ�
	void Start() override;
	void FixedUpdate(float dTime) override;
	void Update(float dTime) override;
	void LateUpdate(float dTime) override;
	void Render() override;
	void Release() override;
	


public:
	float GetTime() const { return m_time; }

	void SetIsCountToggle() { isCount = !isCount; }; // ī���� ���¸� �ݴ�� �ٲ۴�.
	void SetCountActive() { isCount = true; }
	void SetCountInactive() { isCount = false; }

	void SetTime(float time) { m_time = time; }		// Ÿ�̸� �ð� ����
	void SetTimeDefault(float time) { m_time = DEFALUT_TIME; }		// Ÿ�̸� �ð� ����
	void AddTime(float time) { m_time += time; }	// Ÿ�̸� �ð� ����
	void SubTime(float time) { m_time -= time; }	// Ÿ�̸� �ð� ����

	bool GetIsOver() const { return isOver; }
	void SetIsOverTrue() { isOver = true; }
	void SetIsOverfalse() { isOver = false; }
	bool GetisCount() const { return isCount; }

	void StopTimer() { m_time = DEFALUT_TIME; isCount == false; }
	SpriteRenderer* m_sprite;
private:
	float m_time = DEFALUT_TIME;
	bool isCount = false;
	bool isOver = false;
	bool m_isPresent = false;
	float m_presentTime = 0.f;
	bool m_forSound = false;
};

