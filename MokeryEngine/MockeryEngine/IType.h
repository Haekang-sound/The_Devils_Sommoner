#pragma once

/// <summary>
/// 타입들을 다형적으로 관리하기 위한 IType 인터페이스
/// </summary>
class IType
{
public:
	virtual ~IType() {};

	// 타입내부에서 메모리해제를 위한 release
	virtual void Release() abstract;

};