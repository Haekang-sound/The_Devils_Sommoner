#pragma once
#include "../KestrelSoundLibrary/KestrelSoundLibrary.h"
#include "Component.h"
#include "SoundManager.h"


/// <summary>
/// ����� ������Ʈ
/// 
/// ���� ������Ʈ�� �پ��ִ�
/// ����� ����Ŵ������� ���������� �ϰ�
/// ��� 3D ������ ��ġ�� �̱� ���� ������Ʈ�� ��߰ڴ�
/// 
/// ��� ������ ��������� ����� �غ����� �ϴµ�
/// �� �ڲ� ������ ������ �𸣰ڴ�
/// </summary>


/// ����� ������Ʈ�� ����ϴ� ���� ������
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
	// IComponent��(��) ���� ��ӵ�
	void Start() override;
	void FixedUpdate(float dTime) override;
	void Update(float dTime) override;
	void LateUpdate(float dTime) override;
	void Render() override;
	void Release() override;

public:
	// ���� ��Ͽ� ���� �̸����� �߰�
	void SetSound(string filename);

	// ���Ϳ� ����� ���������͸� ����ϱ����ؼ� Playback�Լ� ���
	void PlaybackSFX(Sound* sound);
	void Play3DSFX(Sound* sound);
	void PlayAudio(Sound* sound, eTYPE type);
	void SetAudio(Sound* sound);
	Sound* GetAudio(int i);
	FMOD_VECTOR GetAudioPos();
	//void Play();
	//void Stop();

	
	// ������Ʈ�� ���� ���� ������ ���
private:
	vector<Sound*> m_sounds;
	Sound* m_sound;
};

