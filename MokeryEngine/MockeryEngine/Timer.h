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
	// Component을(를) 통해 상속됨
	void Start() override;
	void FixedUpdate(float dTime) override;
	void Update(float dTime) override;
	void LateUpdate(float dTime) override;
	void Render() override;
	void Release() override;
	


public:
	float GetTime() const { return m_time; }

	void SetIsCountToggle() { isCount = !isCount; }; // 카운팅 상태를 반대로 바꾼다.
	void SetCountActive() { isCount = true; }
	void SetCountInactive() { isCount = false; }

	void SetTime(float time) { m_time = time; }		// 타이머 시간 세팅
	void SetTimeDefault(float time) { m_time = DEFALUT_TIME; }		// 타이머 시간 세팅
	void AddTime(float time) { m_time += time; }	// 타이머 시간 증가
	void SubTime(float time) { m_time -= time; }	// 타이머 시간 감소

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

