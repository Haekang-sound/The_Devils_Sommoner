#pragma once

/// <summary>
/// Ÿ�Ե��� ���������� �����ϱ� ���� IType �������̽�
/// </summary>
class IType
{
public:
	virtual ~IType() {};

	// Ÿ�Գ��ο��� �޸������� ���� release
	virtual void Release() abstract;

};