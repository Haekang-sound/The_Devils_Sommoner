#pragma once
/// <summary>
/// 모든 상태의 근간이 되는 IBaseState
/// </summary>
class IBaseState
{
public:
	virtual ~IBaseState() {};

	virtual void OnStateEnter() abstract;
	virtual void OnStateUpdate(float dTime) abstract;
	virtual void OnStateExit() abstract;

};