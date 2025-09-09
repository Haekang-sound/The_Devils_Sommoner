#pragma once
#include "IKSL.h"
#include "fmod.hpp"
#include "fmod_common.h"

#include <vector>
#include <string>
#include <unordered_map>
#include <filesystem>
#include <iostream>


#define WIN32_LEAN_AND_MEAN // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#define GetDoorChannel(n) Channel* KSL::GetDoor##n##Channel();


using namespace FMOD;
using namespace std;

/// Ȳ������ ���� ���̺귯��
/// FMOD�� ����� ���� ���̺귯���� ������
/// 2023. 12. 12
/// 
/// ���� �����ͷ� ����� ������
/// ���� ���̺귯�� MK.II
/// ���� �̰� ���� ���� ����� �߰���
/// 2024. 02. 06
/// 
/// 3D ���带 ������
/// 2024. 02. 07
/// 
/// �������� ����� �����ϰ�
/// 3D ���� �Լ��� �����Ѵ�
/// 2024. 02. 08
/// 
/// ������ ���� ����� �������Ƿ�
/// �׿� �°� ä�ΰ� ���带 �����Ѵ�
/// + ������ �ϼ�
/// 2024. 02. 14
/// 
/// ��� ���� �ε带 Ȯ���ߴ�
/// 
/// 2024. 02. 15
/// 
/// ä�ΰ� �Լ��� �����ϴ� ��
/// 
/// 2024. 02. 16
/// 
/// ä���� ��¿ �� ���� �ϵ��ڵ��� �ؾ��� ����
/// �����ͷ� ������ ������ ���� ���´�..
/// 
/// 2024. 02. 19
/// 
/// ��ũ�� �Լ��� ����� ������ Ÿ�����
/// �� ä�� '30��'
/// 
/// 2024. 02. 21


/// ����ϴ� ���带 ������ enum class�Դϴ�.
enum class eSOUNDKIND
{
	/// bgm
	bLobby = 0,		// �κ� bgm
	bMain,			// ���� bgm (������)
	bChased,		// �߰ݴ��� bgm (������)

	//bEND,

	/// sfx
	fClick,			// ui Ŭ��
	fUI,			// ui ����
	fBox,			// ���� ����
	fSpotted,		// �߰���
	fEscaped,		// �߰� ����
	fDemon,			// �Ǹ� ��ȯ
	fPskill,		// �÷��̾� ��ų
	fPact,			// �÷��̾� ��ȣ�ۿ�
	fDoor,			// �� ����
	fClose,			// �� �ݱ�
	fBlindAttack,	// ����ε� �ٰŸ� ���� 
	fJaneAttack,	// ���� ���Ÿ� ����
	fChaserAttack,	// ü�̼� �ٰŸ� ����
	fPhit,			// �÷��̾� �ǰ�
	fEnemyHit,		// �� �ǰ�
	fMaleScream,	// ��� ����
	fFemaleScream,	// ��� ����
	fDead,			// ���
	fBuff,			// ����
	fDebuff,		// �����
	fHeart,			// ���� �ڵ�
	fTimer,			// Ÿ�̸�

	//fEND,

	/// sfx loop
	lPlayerWalk,	// �÷��̾� �ȱ�
	lPlayerRun,		// �÷��̾� �޸���
	lBlindWalk,		// ����ε� �ȱ�
	lBlindRun,		// ����ε� �޸���
	lJaneWalk,		// ���� �ȱ�
	lJaneRun,		// ���� �޸���
	lChaserWalk,	// ü�̼� �ȱ�
	lGhostWalk,		// ��Ʈ �ȱ�
	lHeartBeats,	// ��������ڵ�
	lHeartBeatf,	// ��������ڵ�
	lExhausted,		// Ż��

	//lEND,

	etc1,			// ��Ÿ

	END
};

/// ä���� ������ ������ enum class�Դϴ�.
enum class eChannelType
{
	BGM,
	SFX
};

/// ���尡 ������ �� ������ �����Դϴ�.
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
	// ���� �ε� ����
	void ReadSounds();
	void LoadSounds();
	void LoadSound(string filename);
	void Load3DSound(string filename);
	void AsyncLoadSound(string filename);
	void DynamicLoadSound(string filename);
	void UnloadSound();
	Channel* CreateChannel();
	void CreateAllChannel();

	// ���� ��� ����
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

	// ���� ���� ����
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

	// 3D �׽�Ʈ

	// ������Ʈ
	void UpdateListener();
	void UpdatePos();
	void UpdatePos(float x, float y, float z);
	

	// �����
	void PrintLPos();
	void PrintPos();
	FMOD_VECTOR PosIsMove();
	FMOD_VECTOR PosIsMove2();

	// channel get
	/// ������ �������� ����...
	/// �̷��� �ϴ°� �ϴ��� ������ ���ϴ�
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
	/// ä�ε�
	Channel* m_bgmChannel;		// bgm ä��
	Channel* m_sfxChannel;		// sfx ä��
	Channel* m_sfxRChannel;		// sfx + ������ ä��
	Channel* m_3dChannel;		// sfx (3d, ������) ä��
	Channel* m_moveChannel;		// sfx (�Ȱ� �޸��� ä��)
	Channel* m_uiChannel;		// ui
	Channel* m_bgmCChannel;		// �߰� bgm ä��
	//Channel* m_door1Channel;	// ��1 ä��
	//Channel* m_door2Channel;	// ��2 ä��
	//Channel* m_door3Channel;	// ��3 ä��
	//Channel* m_door4Channel;	// ��4 ä��
	//Channel* m_door5Channel;	// ��5 ä��
	//Channel* m_door6Channel;	// ��6 ä��
	//Channel* m_door7Channel;	// ��7 ä��
	//Channel* m_door8Channel;	// ��8 ä��
	//Channel* m_door9Channel;	// ��9 ä��
	//Channel* m_door10Channel;	// ��10 ä��
	Channel* m_demonChannel;	// �Ǹ� ��ȯ ä��
	Channel* m_BlindChannel;	// ���⼭���� ���� ����ϴ� ä��
	Channel* m_JaneChannel;		// 
	Channel* m_ChaserChannel;	// 
	Channel* m_GhostChannel;	// 
	Channel* m_etcChannel;
	/// �� ä���� 40�� ������...
	Channel* m_doorChannel[40];
	vector<ChannelGroup*> m_channelGroups;
	ChannelGroup* m_bgmChannelGroup;
	ChannelGroup* m_sfxChannelGroup;
	ChannelGroup* m_3dChannelGroup;
	ChannelGroup* m_enemyChannelGroup;
	Reverb3D* m_reverb;
	// ���� ������ ���
	vector<string> m_soundFiles;
	// ���⿣ m_�Ⱥ��ϰž�
	FMOD_RESULT result;
	

private:
	// ������/BGM/SFX ����(�Ķ����), BGMä��/SFXä��(���� ���) ��
	// + �����̴� �Ҹ����� ȯ���� �������� ���� �����ؾ߰ڴ�.
	float m_mVolume;
	float m_bVolume;
	float m_fVolume;
	float m_aVolume;
	float m_bChannelVolume;
	float m_fChannelVolume;
	float m_aChannelVolume;

	bool m_isBGMPlaying;
	bool m_isBGMPaused;

	// 3D ���õȰ�
	const int INTERFACE_UPDATETIME = 50;	// �������̽��� 50ms�� ������Ʈ
	const float DISTANCEFACTOR = 1.0f;		// ���� �� ����. ��Ʈ�� 3.28, ��Ƽ���ʹ� 100
	bool listenerflag = true;
	FMOD_VECTOR listenerpos = { 0.0f, 0.0f, 0.0f * DISTANCEFACTOR };
	FMOD_VECTOR pos = { 0.0f * DISTANCEFACTOR, 0.0f, 0.0f };
	FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f };


	FMOD_VECTOR forward = { 0.0f, 0.0f, 1.0f };		// ���� ����
	FMOD_VECTOR up = { 0.0f, 1.0f, 0.0f };			// �� ����

	// ������
	FMOD_REVERB_PROPERTIES m_noProp = FMOD_PRESET_OFF;
	FMOD_REVERB_PROPERTIES m_prop = FMOD_PRESET_HALLWAY;
	DSP* m_reverbDSP;


	// ���带 �ִ� ���
	wstring m_soundPath = L"../Resources/Sounds/";

	/// ������ �����͸� �����ϴ� �ؽ� ���Դϴ�.
	unordered_map<eSOUNDKIND, SoundData> m_soundMap;
};