#pragma once
/// <summary>
/// ��� ������ �ٰ��� �Ǵ� IBaseState
/// </summary>
class IBaseState
{
public:
	virtual ~IBaseState() {};

	virtual void OnStateEnter() abstract;
	virtual void OnStateUpdate(float dTime) abstract;
	virtual void OnStateExit() abstract;

};