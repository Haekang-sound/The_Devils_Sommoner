#include "pch.h"
#include "RandomNumber.h"
#include <random>

RandomNumber::RandomNumber()
{

}

RandomNumber::~RandomNumber()
{

}

void RandomNumber::Start()
{

}

void RandomNumber::FixedUpdate(float dTime)
{

}

void RandomNumber::Update(float dTime)
{

}

void RandomNumber::LateUpdate(float dTime)
{

}

void RandomNumber::Render()
{

}

void RandomNumber::Release()
{

}

void RandomNumber::OnCollisionEnter(Collision* collision)
{

}

void RandomNumber::OnCollisionStay(Collision* collision)
{

}

void RandomNumber::OnCollisionExit(Collision* collision)
{

}

int RandomNumber::GetRandomInt(int _min, int _max)
{
	// �õ尪 ����
	std::random_device rd;
	// �õ尪���� ���� ���� ���� �ʱ�ȭ
	std::mt19937 gen(rd());
	// �յ� ���� ����
	std::uniform_int_distribution<int> dis(_min, _max);
	// ���� ��ȯ
	return dis(gen);
}
