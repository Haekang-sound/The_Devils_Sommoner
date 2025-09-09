#pragma once
#include "../Libraries/DXTK/Inc/SimpleMath.h"
#include "../KestrelSoundLibrary/KestrelSoundLibrary.h"
#include "SingleTon.h"
#include "GameObject.h"
#include "EnemyComponent.h"


using namespace DirectX;

class IKSL;

/// <summary>
/// Sound와 관련된 작업을 수행하는 사운드매니저
/// 전역적으로 하나의 시스템을 사용할 것
/// 여기서 audio와 관련된 모든 작업을 해보자
/// 3D 사운드와 관련된 작업도 여기서 해야할 것 같다.
/// 
/// 2024. 02. 08
/// 
/// KSL의 이중 함수처럼 구현된 상태
/// BGM 등의 전역적인 사운드나 이벤트를 제외하곤
/// 오디오 컴포넌트에서 여기있는 Play함수를 가져가 쓴다.
/// 
/// 채널을 동적으로 만들어서 쓰는 Mk.II
/// 
/// 2024. 02. 16
/// </summary>
class SoundManager : public SingleTon<SoundManager>
{
public:
	SoundManager();
	~SoundManager();


public:
	void Init();
	void Update();
	void Finalize();

	/// 매니저가 모든 사운드 관련 함수를 가지고 있고
	/// 오디오는 매니저에 접근해서 함수를 가져다 쓰게 만들자
	/// 싱글턴밖에 답이 없나?
public:
	void ReadSounds();
	void LoadSounds();
	void Load3DSound(string filename);
	void LoadSound(string filename);
	void Play3D(eSOUNDKIND);
	void PlayBGM(eSOUNDKIND);
	void PlaySFX(eSOUNDKIND);
	void PlayBGMC(eSOUNDKIND);
	void PlaySFXR(eSOUNDKIND);
	void PlayDoor0(eSOUNDKIND sound);
	void PlayDoor1(eSOUNDKIND sound);
	void PlayDoor2(eSOUNDKIND sound);
	void PlayDoor3(eSOUNDKIND sound);
	void PlayDoor4(eSOUNDKIND sound);
	void PlayDoor5(eSOUNDKIND sound);
	void PlayDoor6(eSOUNDKIND sound);
	void PlayDoor7(eSOUNDKIND sound);
	void PlayDoor8(eSOUNDKIND sound);
	void PlayDoor9(eSOUNDKIND sound);
	void PlayDoor10(eSOUNDKIND sound);
	void PlayDoor11(eSOUNDKIND sound);
	void PlayDoor12(eSOUNDKIND sound);
	void PlayDoor13(eSOUNDKIND sound);
	void PlayDoor14(eSOUNDKIND sound);
	void PlayDoor15(eSOUNDKIND sound);
	void PlayDoor16(eSOUNDKIND sound);
	void PlayDoor17(eSOUNDKIND sound);
	void PlayDoor18(eSOUNDKIND sound);
	void PlayDoor19(eSOUNDKIND sound);
	void PlayDoor20(eSOUNDKIND sound);
	void PlayDoor21(eSOUNDKIND sound);
	void PlayDoor22(eSOUNDKIND sound);
	void PlayDoor23(eSOUNDKIND sound);
	void PlayDoor24(eSOUNDKIND sound);
	void PlayDoor25(eSOUNDKIND sound);
	void PlayDoor26(eSOUNDKIND sound);
	void PlayDoor27(eSOUNDKIND sound);
	void PlayDoor28(eSOUNDKIND sound);
	void PlayDoor29(eSOUNDKIND sound);
	void PlayDoor30(eSOUNDKIND sound);
	void PlayDoor31(eSOUNDKIND sound);
	void PlayDoor32(eSOUNDKIND sound);
	void PlayDoor33(eSOUNDKIND sound);
	void PlayDoor34(eSOUNDKIND sound);
	void PlayDoor35(eSOUNDKIND sound);
	void PlayDoor36(eSOUNDKIND sound);
	void PlayDoor37(eSOUNDKIND sound);
	void PlayDoor38(eSOUNDKIND sound);
	void PlayDoor39(eSOUNDKIND sound);
	void PlayDemon();
	void PlaybackBGM(Sound* sound);
	void PlaybackSFX(Sound* sound);
	void Playback3D(Sound* sound);
	void PlaybackBGMC(Sound* sound);
	void PlaybackSFXR(Sound* sound);
	void PlayBGM2(Sound* sound);
	void PlaySFX2(Sound* sound);
	void Play3D2(Sound* sound);
	void PlayBGMC2(Sound* sound);
	void PlaySFXR2(Sound* sound);
	void PlayBlind(eSOUNDKIND sound);
	void PlayBlind2(Sound* sound);
	void PlayJane(eSOUNDKIND sound);
	void PlayJane2(Sound* sound);
	void PlayChaser(eSOUNDKIND sound);
	void PlayChaser2(Sound* sound);
	void PlayGhost(eSOUNDKIND sound);
	void PlayGhost2(Sound* sound);
	void PlayName(string filename);
	void PlaySound(Sound* sound, Channel** channel);
	void PlayerWalk();
	void PlayerRun();
	void StopMove();
	void StopSound(Channel* channel);
	void AddReverb(Channel* channel);
	void AddReverbParam(Channel* channel, float val);
	void RemoveReverb(Channel* channel);
	void UpdateListener();
	void UpdatePos(FMOD_VECTOR fVec);
	//void UpdateChase();
	Sound* GetSound(string filename);
	Sound* GetSound(eSOUNDKIND sound);
	void CreateChannel();
	bool GetChase();
	void DoChase();
	void DoEscape();
	void SetPriority(Channel* channel, float val);

	/// get
	/// 채널의 경우 Door0을 심장소리로
	/// Door1를 UI 소리로 사용중이다
	/// Door2는 아이템 소리로 사용하자
	/// Door3를 UI타이머로 사용할듯
	/// Door39는 스태미너 채널로 사용한다
public:
	KSL* getKSL();
	Channel* GetBGMChannel();
	Channel* GetBGMCChannel();
	Channel* GetSFXChannel();
	Channel* GetSFXRChannel();
	Channel* Get3DChannel();
	Channel* GetMoveChannel();
	Channel* GetBlindChannel();
	Channel* GetJaneChannel();
	Channel* GetChaserChannel();
	Channel* GetGhostChannel();
	Channel* GetDoor0Channel();
	Channel* GetDoor1Channel();
	Channel* GetDoor2Channel();
	Channel* GetDoor3Channel();
	Channel* GetDoor4Channel();
	Channel* GetDoor5Channel();
	Channel* GetDoor6Channel();
	Channel* GetDoor7Channel();
	Channel* GetDoor8Channel();
	Channel* GetDoor9Channel();
	Channel* GetDoor10Channel();
	Channel* GetDoor11Channel();
	Channel* GetDoor12Channel();
	Channel* GetDoor13Channel();
	Channel* GetDoor14Channel();
	Channel* GetDoor15Channel();
	Channel* GetDoor16Channel();
	Channel* GetDoor17Channel();
	Channel* GetDoor18Channel();
	Channel* GetDoor19Channel();
	Channel* GetDoor20Channel();
	Channel* GetDoor21Channel();
	Channel* GetDoor22Channel();
	Channel* GetDoor23Channel();
	Channel* GetDoor24Channel();
	Channel* GetDoor25Channel();
	Channel* GetDoor26Channel();
	Channel* GetDoor27Channel();
	Channel* GetDoor28Channel();
	Channel* GetDoor29Channel();
	Channel* GetDoor30Channel();
	Channel* GetDoor31Channel();
	Channel* GetDoor32Channel();
	Channel* GetDoor33Channel();
	Channel* GetDoor34Channel();
	Channel* GetDoor35Channel();
	Channel* GetDoor36Channel();
	Channel* GetDoor37Channel();
	Channel* GetDoor38Channel();
	Channel* GetDoor39Channel();
	Channel* GetDemonChannel();
	vector<GameObject*> GetAudioComps();
	vector<GameObject*> GetEnemyComps();
	GameObject* GetGameObject(int i);
	Channel* GetAudioChannel(GameObject* object);
	vector<Channel*> GetChannels();
	void ClearAudioComps();

	/// 3D
public:
	// 사운드매니저가 씬에서 오브젝트의 위치값을 받아 넘겨줘야한다.
	FMOD_VECTOR ConvertVector(SimpleMath::Vector3 sVec, SimpleMath::Vector3 lVec);
	void Set3DMinMaxDistance(string filename, float min, float max);
	void Set3DMinMaxDistance(eSOUNDKIND sound, float min, float max);
	void SetAll3DMinMaxDistance();
	
	
	/// 벡터를 반복하기 위해서
public:
	void PushEnemy(GameObject* object);
	void PushAudio(GameObject* object);
	void DoorOpen(int index);
	void DoorClose(int index);

	/// 모든 적마다 업데이트pos를 만들어야 할지
	/// 아니면 매개변수를 받아서 switch case를 돌지
	//void UpdateJanePos(FMOD_VECTOR fVec);
	void UpdateSoundPos(FMOD_VECTOR fVec, string name);
	void UpdateSoundPos(FMOD_VECTOR fVec, Channel*& channel);
	void UpdateSoundPos(FMOD_VECTOR fVec, int index);
	// 테스트용
	FMOD_VECTOR PosIsMove();
	FMOD_VECTOR PosIsMove2();
	FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f };

/// <summary>
/// TODO: audio 컴포넌트 만들때마다
/// 	여기에 벡터든 뭐든 컨테이너에 추가하고
/// 	나중에 그것만 반복문으로 돌면서 업데이트 체크
/// 
/// </summary>

private:
	// KSL을 여기서 들고있는다.
	KSL* m_KSL;
	const int m_minDist;
	const int m_maxDist;
	vector<Channel*> m_channels;
	vector<GameObject*> m_enemies;
	vector<GameObject*> m_audioComps;		// 오디오컴포넌트를 가진 게임오브젝트들
	bool m_chase;
	bool m_escape;
};

