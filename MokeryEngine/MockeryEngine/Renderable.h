#pragma once
/// <summary>
/// 그리기위한 컴포넌트
/// 사실상 MeshRenderer를 위해 만들어짐
/// 
/// 상속을 이용할지 아닐지는 확실하지 않지만
/// 프로그램이 완전히 끝나기 전까지
/// 내부의 컴포넌트를 삭제하는 중에 
/// renderer포인터는 유지하려면 새로운 상속 클래스가 필요하지 않을까 싶다
/// </summary>

class ID3DRenderer;

class Renderable
{
public:
	virtual ~Renderable() {};

	virtual void Render() abstract;

	ID3DRenderer* m_renderer;

};