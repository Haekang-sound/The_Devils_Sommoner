#pragma once
#include "Component.h"

/// <summary>
/// ���� ��� ��ȣ�ۿ� �ǰ� �ִ���
/// </summary>
enum class InteractState
{
	None,
	Enter,
	Stay,
	Exit,
};

class InteractiveObject : public Component
{
public:
	InteractiveObject();
	virtual ~InteractiveObject();

public:
	void Start() override;
	void FixedUpdate(float dTime) override;
	void Update(float dTime) override;
	void LateUpdate(float dTime) override;
	void Render() override;
	void Release() override;

public:
	// ��ȣ�ۿ��ϴµ� �ʿ��� �ð��� ���Ѵ�.
	void SetLoadTime(float time);

	virtual void InteractAddTime(float dTime);


public:
	virtual void Interact();

protected:
	InteractState m_interactState;
	bool m_isInteract;

	// ��ȣ�ۿ��ϴµ� �ɸ��� �ð�
	float m_loadTime;
	float m_currentTime;

	float m_beforeTime;

	bool m_isInteractAddTime;
	bool m_isInteractSound;
	
/// <summary>
/// Item��ȣ�ۿ� UI�� ������µ�
///	��ȣ�ۿ�������,
/// load/current Time������ ��� �Ǵ��� �˷��� 
/// ���� �ʿ���;
/// �ۼ��� : ���ذ�
/// </summary>
public:
	bool GetIsInteract() const { return m_isInteract; }
	float ItemLoadRatio() const { return m_currentTime / m_loadTime; }
};

