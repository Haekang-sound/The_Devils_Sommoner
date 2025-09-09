#include "pch.h"
#include "FSM.h"
#include "IBaseState.h"

void FSM::Start()
{
}

void FSM::FixedUpdate(float dTime)
{
}

void FSM::Update(float dTime)
{
	// 캐릭터의 currentState를 계속 점검하고 있어야한다
	// 상태의 변경여부는 '현재상태' 가 결정한다.
	// 현재 상태는 자신이 변경될 수 있는 상태를 모두 알고 있어야한다.
	m_currentState->OnStateUpdate(dTime);

}

void FSM::LateUpdate(float dTime)
{
}

void FSM::Render()
{
}

void FSM::Release()
{
}

void FSM::OnEnterState()
{
	m_currentState->OnStateEnter();
}

void FSM::OnChangeState(IBaseState* nextState)
{
	// 현재 스테이트와 같다면 
	if (m_currentState == nextState)
	{
		//그냥 넘어간다
		return;
	}
	// 같지 않다면
	m_currentState = nextState;
	// 새로운 스테이트를 실행한다.
	m_currentState->OnStateEnter();
	return;
}
