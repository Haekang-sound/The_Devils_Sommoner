#pragma once
#include "../Libraries/DXTK/Inc/SimpleMath.h"
#include "../KestrelSoundLibrary/KestrelSoundLibrary.h"
#include "SingleTon.h"
#include "GameObject.h"
#include "EnemyComponent.h"


using namespace DirectX;

class IKSL;

/// <summary>
/// Sound�� ���õ� �۾��� �����ϴ� ����Ŵ���
/// ���������� �ϳ��� �ý����� ����� ��
/// ���⼭ audio�� ���õ� ��� �۾��� �غ���
/// 3D ����� ���õ� �۾��� ���⼭ �ؾ��� �� ����.
/// 
/// 2024. 02. 08
/// 
/// KSL�� ���� �Լ�ó�� ������ ����
/// BGM ���� �������� ���峪 �̺�Ʈ�� �����ϰ�
/// ����� ������Ʈ���� �����ִ� Play�Լ��� ������ ����.
/// 
/// ä���� �������� ���� ���� Mk.II
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

	/// �Ŵ����� ��� ���� ���� �Լ��� ������ �ְ�
	/// ������� �Ŵ����� �����ؼ� �Լ��� ������ ���� ������
	/// �̱��Ϲۿ� ���� ����?
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
	/// ä���� ��� Door0�� ����Ҹ���
	/// Door1�� UI �Ҹ��� ������̴�
	/// Door2�� ������ �Ҹ��� �������
	/// Door3�� UIŸ�̸ӷ� ����ҵ�
	/// Door39�� ���¹̳� ä�η� ����Ѵ�
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
	// ����Ŵ����� ������ ������Ʈ�� ��ġ���� �޾� �Ѱ�����Ѵ�.
	FMOD_VECTOR ConvertVector(SimpleMath::Vector3 sVec, SimpleMath::Vector3 lVec);
	void Set3DMinMaxDistance(string filename, float min, float max);
	void Set3DMinMaxDistance(eSOUNDKIND sound, float min, float max);
	void SetAll3DMinMaxDistance();
	
	
	/// ���͸� �ݺ��ϱ� ���ؼ�
public:
	void PushEnemy(GameObject* object);
	void PushAudio(GameObject* object);
	void DoorOpen(int index);
	void DoorClose(int index);

	/// ��� ������ ������Ʈpos�� ������ ����
	/// �ƴϸ� �Ű������� �޾Ƽ� switch case�� ����
	//void UpdateJanePos(FMOD_VECTOR fVec);
	void UpdateSoundPos(FMOD_VECTOR fVec, string name);
	void UpdateSoundPos(FMOD_VECTOR fVec, Channel*& channel);
	void UpdateSoundPos(FMOD_VECTOR fVec, int index);
	// �׽�Ʈ��
	FMOD_VECTOR PosIsMove();
	FMOD_VECTOR PosIsMove2();
	FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f };

/// <summary>
/// TODO: audio ������Ʈ ���鶧����
/// 	���⿡ ���͵� ���� �����̳ʿ� �߰��ϰ�
/// 	���߿� �װ͸� �ݺ������� ���鼭 ������Ʈ üũ
/// 
/// </summary>

private:
	// KSL�� ���⼭ ����ִ´�.
	KSL* m_KSL;
	const int m_minDist;
	const int m_maxDist;
	vector<Channel*> m_channels;
	vector<GameObject*> m_enemies;
	vector<GameObject*> m_audioComps;		// �����������Ʈ�� ���� ���ӿ�����Ʈ��
	bool m_chase;
	bool m_escape;
};

