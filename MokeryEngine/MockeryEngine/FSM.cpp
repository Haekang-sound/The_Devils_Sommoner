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
	// ĳ������ currentState�� ��� �����ϰ� �־���Ѵ�
	// ������ ���濩�δ� '�������' �� �����Ѵ�.
	// ���� ���´� �ڽ��� ����� �� �ִ� ���¸� ��� �˰� �־���Ѵ�.
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
	// ���� ������Ʈ�� ���ٸ� 
	if (m_currentState == nextState)
	{
		//�׳� �Ѿ��
		return;
	}
	// ���� �ʴٸ�
	m_currentState = nextState;
	// ���ο� ������Ʈ�� �����Ѵ�.
	m_currentState->OnStateEnter();
	return;
}
