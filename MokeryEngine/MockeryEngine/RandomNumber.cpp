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
	// 시드값 생성
	std::random_device rd;
	// 시드값으로 난수 생성 엔진 초기화
	std::mt19937 gen(rd());
	// 균등 분포 정의
	std::uniform_int_distribution<int> dis(_min, _max);
	// 난수 반환
	return dis(gen);
}
