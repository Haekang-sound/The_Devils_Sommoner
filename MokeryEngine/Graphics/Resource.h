#pragma once

class ResourceManager;


/// <summary>
/// FBX�������� �����ͼ� ����, �ؽ���, ���̴��� ����� �Ѱ��� ����
/// ���ҽ����� �������̽��� ���� ������ �� IResource�� �ٲ�ߵǳ�
/// </summary>
class Resource
{
public:
	Resource(ResourceManager* resourceManager)
		: _resourceManager(resourceManager) {};
	virtual ~Resource();

protected:
	ResourceManager* _resourceManager;
};

