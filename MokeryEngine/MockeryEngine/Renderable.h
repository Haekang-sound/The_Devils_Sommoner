#pragma once
/// <summary>
/// �׸������� ������Ʈ
/// ��ǻ� MeshRenderer�� ���� �������
/// 
/// ����� �̿����� �ƴ����� Ȯ������ ������
/// ���α׷��� ������ ������ ������
/// ������ ������Ʈ�� �����ϴ� �߿� 
/// renderer�����ʹ� �����Ϸ��� ���ο� ��� Ŭ������ �ʿ����� ������ �ʹ�
/// </summary>

class ID3DRenderer;

class Renderable
{
public:
	virtual ~Renderable() {};

	virtual void Render() abstract;

	ID3DRenderer* m_renderer;

};