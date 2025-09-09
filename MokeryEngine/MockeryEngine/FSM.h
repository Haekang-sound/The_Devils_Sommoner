#pragma once
#include "Component.h"

class IBaseState;
/// <summary>
/// ������Ʈ�� ���¸� �����ϴ� 
/// ���ѻ��±��(FSM)
/// </summary>
class FSM : public Component
{
public:
    // IComponent��(��) ���� ��ӵ�
	virtual void Start() override; 
    virtual void FixedUpdate(float dTime) override;
    virtual void Update(float dTime) override;
    virtual void LateUpdate(float dTime) override;
    virtual void Render() override;
    virtual void Release() override;

public:
    void OnEnterState();
    void OnChangeState(IBaseState* nextState);

private:
    IBaseState* m_currentState;
    IBaseState* m_nextState;


   

};

