#include "pch.h"
#include "AudioComponent.h"
#include "Transform.h"
#include "AudioListener.h"
#include "GameObject.h"
#include "EngineObjectManager.h"


AudioComponent::AudioComponent()
{

}

/// 오디오 컴포넌트를 붙였다면
/// 채널을 하나 만들고 오디오컴포넌트 벡터에 오브젝트를 추가
void AudioComponent::Start()
{
	SoundManager::GetInstance().CreateChannel();
	SoundManager::GetInstance().PushAudio(GetOwner());
}

void AudioComponent::FixedUpdate(float dTime)
{

}
void AudioComponent::Update(float dTime)
{

}

void AudioComponent::LateUpdate(float dTime)
{
}

void AudioComponent::Render()
{
}

void AudioComponent::Release()
{
}

void AudioComponent::SetSound(string filename)
{
	m_sounds.push_back(SoundManager::GetInstance().GetSound(filename));
}

void AudioComponent::PlaybackSFX(Sound* sound)
{
	SoundManager::GetInstance().PlaybackSFX(sound);
}


void AudioComponent::Play3DSFX(Sound* sound)
{
	SoundManager::GetInstance().Playback3D(sound);
}

void AudioComponent::PlayAudio(Sound* sound, eTYPE type)
{
	switch (static_cast<int>(type))
	{
	case SFX:
		SoundManager::GetInstance().PlaySFX2(sound);
		break;
	case SFXR:
		SoundManager::GetInstance().PlaySFXR2(sound);
		break;
	case THREED:
		SoundManager::GetInstance().Play3D2(sound);
		break;
	case BLIND:
		SoundManager::GetInstance().PlayBlind2(sound);
		break;
	case JANE:
		SoundManager::GetInstance().PlayJane2(sound);
		break;
	case CHASER:
		SoundManager::GetInstance().PlayChaser2(sound);
		break;
	case GHOST:
		SoundManager::GetInstance().PlayGhost2(sound);
		break;
	case DOOR:
		SoundManager::GetInstance().PlayDoor1(eSOUNDKIND::fDoor);
		break;
	case DEMON:
		SoundManager::GetInstance().PlayDemon();
		break;
	default:
		break;
	}
}

void AudioComponent::SetAudio(Sound* sound)
{
	
	m_sounds.push_back(sound);
	//m_sound = sound;
}

FMOD::Sound* AudioComponent::GetAudio(int i)
{
	if (this->m_sounds.size() >= 1)
		return m_sounds[i];
	else
		return nullptr;
}

/// 플레이어(오디오리스너)의 월드TM을 받아 역행렬을 하고
/// 이 컴포넌트를 가진 오브젝트의 위치에 곱한 값을 뱉는 함수
/// FMOD가 오른손좌표계로 초기화되어 x값을 -로 해줘야한다.
FMOD_VECTOR AudioComponent::GetAudioPos()
{
	SimpleMath::Vector3 temp = GetOwner()->GetComponent<Transform>()->GetPosition();
	SimpleMath::Matrix mat = GetOwner()->GetObjectManager()->GetOBjectsByComponent<AudioListener>()->GetComponent<Transform>()->GetWorld().Invert();
	SimpleMath::Vector3 temp2 = SimpleMath::Vector3::Transform(temp, mat);
	FMOD_VECTOR result = { -temp2.x, temp2.y, temp2.z };

	return result;
}

