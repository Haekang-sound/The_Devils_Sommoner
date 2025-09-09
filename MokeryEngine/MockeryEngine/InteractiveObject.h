#pragma once
#include "Component.h"

/// <summary>
/// 현재 계속 상호작용 되고 있는지
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
	// 상호작용하는데 필요한 시간을 정한다.
	void SetLoadTime(float time);

	virtual void InteractAddTime(float dTime);


public:
	virtual void Interact();

protected:
	InteractState m_interactState;
	bool m_isInteract;

	// 상호작용하는데 걸리는 시간
	float m_loadTime;
	float m_currentTime;

	float m_beforeTime;

	bool m_isInteractAddTime;
	bool m_isInteractSound;
	
/// <summary>
/// Item상호작용 UI를 만드려는데
///	상호작용중인지,
/// load/current Time비율은 어떻게 되는지 알려면 
/// 뭔가 필요해;
/// 작성자 : 오해강
/// </summary>
public:
	bool GetIsInteract() const { return m_isInteract; }
	float ItemLoadRatio() const { return m_currentTime / m_loadTime; }
};

