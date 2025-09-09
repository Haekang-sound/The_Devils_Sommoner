#pragma once
#include "IKSL.h"
#include "fmod.hpp"
#include "fmod_common.h"

#include <vector>
#include <string>
#include <unordered_map>
#include <filesystem>
#include <iostream>


#define WIN32_LEAN_AND_MEAN // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
#define GetDoorChannel(n) Channel* KSL::GetDoor##n##Channel();


using namespace FMOD;
using namespace std;

/// 황조롱이 사운드 라이브러리
/// FMOD를 사용한 사운드 라이브러리를 만들어보자
/// 2023. 12. 12
/// 
/// 사운드 포인터로 재생이 가능한
/// 사운드 라이브러리 MK.II
/// 물론 이것 말고도 많은 기능이 추가됨
/// 2024. 02. 06
/// 
/// 3D 사운드를 만들어보자
/// 2024. 02. 07
/// 
/// 엔진에서 사용이 가능하게
/// 3D 사운드 함수를 수정한다
/// 2024. 02. 08
/// 
/// 사운드의 최종 목록이 나왔으므로
/// 그에 맞게 채널과 사운드를 변경한다
/// + 리버브 완성
/// 2024. 02. 14
/// 
/// 모든 사운드 로드를 확인했다
/// 
/// 2024. 02. 15
/// 
/// 채널과 함수를 수정하는 중
/// 
/// 2024. 02. 16
/// 
/// 채널은 어쩔 수 없이 하드코딩을 해야할 수도
/// 포인터로 받으면 에러가 많이 나온다..
/// 
/// 2024. 02. 19
/// 
/// 매크로 함수를 사용한 최후의 타즈딩고
/// 문 채널 '30배'
/// 
/// 2024. 02. 21


/// 사용하는 사운드를 정리한 enum class입니다.
enum class eSOUNDKIND
{
	/// bgm
	bLobby = 0,		// 로비 bgm
	bMain,			// 메인 bgm (리버브)
	bChased,		// 추격당함 bgm (리버브)

	//bEND,

	/// sfx
	fClick,			// ui 클릭
	fUI,			// ui 등장
	fBox,			// 상자 열기
	fSpotted,		// 발각됨
	fEscaped,		// 추격 해제
	fDemon,			// 악마 소환
	fPskill,		// 플레이어 스킬
	fPact,			// 플레이어 상호작용
	fDoor,			// 문 열기
	fClose,			// 문 닫기
	fBlindAttack,	// 블라인드 근거리 공격 
	fJaneAttack,	// 제인 원거리 공격
	fChaserAttack,	// 체이서 근거리 공격
	fPhit,			// 플레이어 피격
	fEnemyHit,		// 적 피격
	fMaleScream,	// 비명 남성
	fFemaleScream,	// 비명 여성
	fDead,			// 사망
	fBuff,			// 버프
	fDebuff,		// 디버프
	fHeart,			// 심장 박동
	fTimer,			// 타이머

	//fEND,

	/// sfx loop
	lPlayerWalk,	// 플레이어 걷기
	lPlayerRun,		// 플레이어 달리기
	lBlindWalk,		// 블라인드 걷기
	lBlindRun,		// 블라인드 달리기
	lJaneWalk,		// 제인 걷기
	lJaneRun,		// 제인 달리기
	lChaserWalk,	// 체이서 걷기
	lGhostWalk,		// 고스트 걷기
	lHeartBeats,	// 느린심장박동
	lHeartBeatf,	// 빠른심장박동
	lExhausted,		// 탈진

	//lEND,

	etc1,			// 기타

	END
};

/// 채널의 종류를 설정한 enum class입니다.
enum class eChannelType
{
	BGM,
	SFX
};

/// 사운드가 가지게 될 데이터 구조입니다.
struct SoundData
{
	string filename;
	Sound* pSound;
};

class KSL : public IKSL
{
public:
	KSL();
	~KSL();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Finalize() override;

public:
	// 사운드 로딩 관련
	void ReadSounds();
	void LoadSounds();
	void LoadSound(string filename);
	void Load3DSound(string filename);
	void AsyncLoadSound(string filename);
	void DynamicLoadSound(string filename);
	void UnloadSound();
	Channel* CreateChannel();
	void CreateAllChannel();

	// 사운드 재생 관련
	void PlayBGM(eSOUNDKIND);
	void PlayBGMC(eSOUNDKIND);
	void Play3D(eSOUNDKIND);
	void Stop3D();
	void StopBGM();
	void StopChannel(Channel* channel);
	void PauseBGM();
	void PlaySFX(eSOUNDKIND);
	void StopSFX();
	void PlaySFXR(eSOUNDKIND sound);
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
	//void PlayDoor(int idx, eSOUNDKIND sound);
	void PlayDemon();
	void PlaybackBGM(Sound* sound);
	void PlayBGM2(Sound* sound);
	void PlaybackBGMC(Sound* sound);
	void PlayBGMC2(Sound* sound);
	void PlaybackSFX(Sound* sound);
	void PlaySFX2(Sound* sound);
	void PlaybackSFXR(Sound* sound);
	void PlaySFXR2(Sound* sound);
	void Playback3D(Sound* sound);
	void Play3D2(Sound* sound);
	void PlayBlind(eSOUNDKIND);
	void PlayBlind2(Sound* sound);
	void PlayJane(eSOUNDKIND);
	void PlayJane2(Sound* sound);
	void PlayChaser(eSOUNDKIND);
	void PlayChaser2(Sound* sound);
	void PlayGhost(eSOUNDKIND);
	void PlayGhost2(Sound* sound);
	void PlayName(string filename);
	void PlayerWalk();
	void PlayerRun();
	void StopMove();
	void PlaySound(Sound* sound, Channel** channel);
	void PlaySound(Sound* sound);
	void StopSound(Channel* channel);
	void Reverb();
	void AddReverb(Channel* channel);
	void AddReverbParam(Channel* channel, float val);
	void RemoveReverb(Channel* channel);
	void SetPriority(Channel* channel, float val);

	// 사운드 음량 관련
	void AdjustMasterVolume(float amount);
	void AdjustChannelVolume(eChannelType channelType, float amount);
	float GetMasterVolume() { return m_mVolume; }
	float GetBGMVolume() { return m_bVolume; }
	float GetSFXVolume() { return m_fVolume; }
	void SetVolumeDirectly(Channel* channel, float amount);
	void Set3DMinMaxDistance(string filename, float min, float max);
	void Set3DMinMaxDistance(eSOUNDKIND sound, float min, float max);
	void Set3DMinMaxDistance(Sound* sound, float min, float max);

	// Get Sound
public:
	FMOD::Sound* GetSound(string filename);
	FMOD::Sound* GetSound(eSOUNDKIND sound);
	void SetSoundData(eSOUNDKIND, string, Sound*);
	void PushDynamicSound(Sound*& sound);

	// 3D 테스트

	// 업데이트
	void UpdateListener();
	void UpdatePos();
	void UpdatePos(float x, float y, float z);
	

	// 디버깅
	void PrintLPos();
	void PrintPos();
	FMOD_VECTOR PosIsMove();
	FMOD_VECTOR PosIsMove2();

	// channel get
	/// 일일이 만들어놓은 이유...
	/// 이렇게 하는게 일단은 오히려 편하다
	Channel* GetChannel(int index);
	Channel* GetBGMChannel();
	Channel* GetBGMCChannel();
	Channel* GetSFXChannel();
	Channel* GetSFXRChannel();
	Channel* Get3DChannel();
	Channel* GetMoveChannel();
	Channel* GetUIChannel();
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
	Channel* GetBlindChannel();
	Channel* GetJaneChannel();
	Channel* GetChaserChannel();
	Channel* GetGhostChannel();
	FMOD_VECTOR GetVel() { return vel; }

private:
	System* m_system;
	vector<Sound*> m_dSounds;
	Sound* m_sounds[static_cast<int>(eSOUNDKIND::END)];
	vector<Channel*> m_channels;
	/// 채널들
	Channel* m_bgmChannel;		// bgm 채널
	Channel* m_sfxChannel;		// sfx 채널
	Channel* m_sfxRChannel;		// sfx + 리버브 채널
	Channel* m_3dChannel;		// sfx (3d, 리버브) 채널
	Channel* m_moveChannel;		// sfx (걷고 달리는 채널)
	Channel* m_uiChannel;		// ui
	Channel* m_bgmCChannel;		// 추격 bgm 채널
	//Channel* m_door1Channel;	// 문1 채널
	//Channel* m_door2Channel;	// 문2 채널
	//Channel* m_door3Channel;	// 문3 채널
	//Channel* m_door4Channel;	// 문4 채널
	//Channel* m_door5Channel;	// 문5 채널
	//Channel* m_door6Channel;	// 문6 채널
	//Channel* m_door7Channel;	// 문7 채널
	//Channel* m_door8Channel;	// 문8 채널
	//Channel* m_door9Channel;	// 문9 채널
	//Channel* m_door10Channel;	// 문10 채널
	Channel* m_demonChannel;	// 악마 소환 채널
	Channel* m_BlindChannel;	// 여기서부턴 적이 사용하는 채널
	Channel* m_JaneChannel;		// 
	Channel* m_ChaserChannel;	// 
	Channel* m_GhostChannel;	// 
	Channel* m_etcChannel;
	/// 문 채널을 40개 만들자...
	Channel* m_doorChannel[40];
	vector<ChannelGroup*> m_channelGroups;
	ChannelGroup* m_bgmChannelGroup;
	ChannelGroup* m_sfxChannelGroup;
	ChannelGroup* m_3dChannelGroup;
	ChannelGroup* m_enemyChannelGroup;
	Reverb3D* m_reverb;
	// 사운드 파일의 목록
	vector<string> m_soundFiles;
	// 여기엔 m_안붙일거야
	FMOD_RESULT result;
	

private:
	// 마스터/BGM/SFX 볼륨(파라미터), BGM채널/SFX채널(실제 사용) 순
	// + 움직이는 소리들을 환경음 볼륨으로 따로 설정해야겠다.
	float m_mVolume;
	float m_bVolume;
	float m_fVolume;
	float m_aVolume;
	float m_bChannelVolume;
	float m_fChannelVolume;
	float m_aChannelVolume;

	bool m_isBGMPlaying;
	bool m_isBGMPaused;

	// 3D 관련된거
	const int INTERFACE_UPDATETIME = 50;	// 인터페이스를 50ms로 업데이트
	const float DISTANCEFACTOR = 1.0f;		// 유닛 퍼 미터. 피트는 3.28, 센티미터는 100
	bool listenerflag = true;
	FMOD_VECTOR listenerpos = { 0.0f, 0.0f, 0.0f * DISTANCEFACTOR };
	FMOD_VECTOR pos = { 0.0f * DISTANCEFACTOR, 0.0f, 0.0f };
	FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f };


	FMOD_VECTOR forward = { 0.0f, 0.0f, 1.0f };		// 전방 벡터
	FMOD_VECTOR up = { 0.0f, 1.0f, 0.0f };			// 업 벡터

	// 리버브
	FMOD_REVERB_PROPERTIES m_noProp = FMOD_PRESET_OFF;
	FMOD_REVERB_PROPERTIES m_prop = FMOD_PRESET_HALLWAY;
	DSP* m_reverbDSP;


	// 사운드를 넣는 경로
	wstring m_soundPath = L"../Resources/Sounds/";

	/// 사운드의 데이터를 저장하는 해시 맵입니다.
	unordered_map<eSOUNDKIND, SoundData> m_soundMap;
};