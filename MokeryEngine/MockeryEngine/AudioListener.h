#pragma once
#include "Component.h"


/// <summary>
/// 오디오 리스너
/// 플레이어(카메라)에 붙어 3D 사운드의 리스너를 정하는 컴포넌트
/// 구현은 하나도 없어도 되지 않을까
/// 
/// 2024. 02. 15
/// </summary>
class AudioListener : public Component
{
public:
	AudioListener();
	~AudioListener();
	virtual void Start() override;
	virtual void FixedUpdate(float dTime) override;
	virtual void Update(float dTime) override;
	virtual void LateUpdate(float dTime) override;
	virtual void Render() override;
	virtual void Release() override;

};

