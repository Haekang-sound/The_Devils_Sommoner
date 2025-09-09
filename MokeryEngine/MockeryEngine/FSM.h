#pragma once
#include "Component.h"

class IBaseState;
/// <summary>
/// 오브젝트의 상태를 관리하는 
/// 유한상태기계(FSM)
/// </summary>
class FSM : public Component
{
public:
    // IComponent을(를) 통해 상속됨
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

