#pragma once

#include "InteractiveObject.h"

enum class AltarSequence
{
	FirstAltar,
	SecondAltar,
	ThirdAltar,
	NONE,
};

class GameObject;

class DemonAltarComponent : public InteractiveObject
{
	using Super = InteractiveObject;

public:
	DemonAltarComponent();
	virtual ~DemonAltarComponent();

public:
	void Start() override;
	void FixedUpdate(float dTime) override;
	void Update(float dTime) override;
	void LateUpdate(float dTime) override;
	void Render() override;
	void Release() override;

	void SetAltarNumber(AltarSequence _sequence) { 
		AltarSequence a = _sequence;
		m_sequence = _sequence; }

	bool GetisAltarActivated() { return m_isActivated; }
	int GetAltarCount() { return m_altarCount; }

public:
	void Interact() override;
	void InteractAddTime(float dTime) override;
	static int m_altarCount;
private:
	AltarSequence m_sequence;
	bool m_isActivated;
	bool m_isDisabled;
	bool m_isFadeIn;
	bool m_isFadeOut;

public:
	float GetAffectDistanceRadius();
	void SetAffectDistanceRadius(float distance);

	void DrawSphere();
	void DoNotDrawSphere();

	void SetHeartSignModel(GameObject* obj);
public:
	GameObject* GetAltarModel();
	void SetAltarModel(GameObject* model);


private:
	// 심장에게 영향을 끼지는 범위
	float m_affectDistanceRadius;
	float m_passingtime;

	GameObject* m_altarModel;
	GameObject* m_heartSign;
};

