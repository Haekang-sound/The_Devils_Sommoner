#pragma once
#include "../KestrelSoundLibrary/KestrelSoundLibrary.h"
#include "Component.h"
#include "SoundManager.h"


/// <summary>
/// 오디오 컴포넌트
/// 
/// 게임 오브젝트에 붙어있다
/// 재생은 사운드매니저에서 전역적으로 하고
/// 얘는 3D 사운드의 위치를 뽑기 위한 컴포넌트로 써야겠다
/// 
/// 어떻게 억지로 오디오에서 재생을 해보려고 하는데
/// 왜 자꾸 오류가 나는지 모르겠다
/// </summary>


/// 오디오 컴포넌트가 재생하는 사운드 종류들
enum eTYPE
{
	SFX,
	SFXR,
	THREED,
	BLIND,
	JANE,
	CHASER,
	GHOST,
	DOOR,
	DEMON
};

class AudioComponent : public Component
{
public:
	AudioComponent();
	// IComponent을(를) 통해 상속됨
	void Start() override;
	void FixedUpdate(float dTime) override;
	void Update(float dTime) override;
	void LateUpdate(float dTime) override;
	void Render() override;
	void Release() override;

public:
	// 사운드 목록에 파일 이름으로 추가
	void SetSound(string filename);

	// 벡터에 저장된 사운드포인터를 재생하기위해선 Playback함수 사용
	void PlaybackSFX(Sound* sound);
	void Play3DSFX(Sound* sound);
	void PlayAudio(Sound* sound, eTYPE type);
	void SetAudio(Sound* sound);
	Sound* GetAudio(int i);
	FMOD_VECTOR GetAudioPos();
	//void Play();
	//void Stop();

	
	// 오브젝트가 갖고 있을 사운드의 목록
private:
	vector<Sound*> m_sounds;
	Sound* m_sound;
};

