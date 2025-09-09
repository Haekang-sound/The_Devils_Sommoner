#include "pch.h"
#include "SoundManager.h"


SoundManager::SoundManager() :
	m_KSL(nullptr), m_minDist(1.0f), m_maxDist(40.0f), m_chase(false), m_escape(true)
{
	
}

SoundManager::~SoundManager()
{

}

void SoundManager::Init()
{
	m_KSL = new KSL();
	// 사운드시스템 초기화
	m_KSL->Initialize();
	// 음악 목록 읽기
	m_KSL->ReadSounds();
	// 음악 파일 로드하기
	m_KSL->LoadSounds();
	m_KSL->Load3DSound("EC.wav");
	// 일부 음악 파일의 최소 거리, 최대 거리 설정
	SetAll3DMinMaxDistance();
}

void SoundManager::Update()
{
	/// 3D 사운드 테스트
	m_KSL->UpdateListener();
	//UpdateChase();
	m_KSL->Update();
}

void SoundManager::Finalize()
{
	m_channels.clear();

	m_KSL->Finalize();
	delete m_KSL;
}

// 파일 경로에서 사운드의 이름들을 추출하여 벡터에 추가하는 과정
void SoundManager::ReadSounds()
{
	m_KSL->ReadSounds();
}

void SoundManager::LoadSounds()
{
	m_KSL->LoadSounds();
}

void SoundManager::Load3DSound(string filename)
{
	m_KSL->Load3DSound(filename);
}

void SoundManager::LoadSound(string filename)
{
	m_KSL->LoadSound(filename);
}

void SoundManager::Play3D(eSOUNDKIND soundKind)
{
	m_KSL->Play3D(soundKind);
}

void SoundManager::PlayBGM(eSOUNDKIND soundKind)
{
	m_KSL->PlayBGM(soundKind);
}

void SoundManager::PlaySFX(eSOUNDKIND soundKind)
{
	m_KSL->PlaySFX(soundKind);
}

void SoundManager::PlayBGMC(eSOUNDKIND soundKind)
{
	m_KSL->PlayBGMC(soundKind);
}

void SoundManager::PlaySFXR(eSOUNDKIND soundKind)
{
	m_KSL->PlaySFXR(soundKind);
}

#define PlayDoor(n) \
void SoundManager::PlayDoor##n##(eSOUNDKIND sound) \
{ \
	m_KSL->PlayDoor##n##(sound);\
}

PlayDoor(0)
PlayDoor(1)
PlayDoor(2)
PlayDoor(3)
PlayDoor(4)
PlayDoor(5)
PlayDoor(6)
PlayDoor(7)
PlayDoor(8)
PlayDoor(9)
PlayDoor(10)
PlayDoor(11)
PlayDoor(12)
PlayDoor(13)
PlayDoor(14)
PlayDoor(15)
PlayDoor(16)
PlayDoor(17)
PlayDoor(18)
PlayDoor(19)
PlayDoor(20)
PlayDoor(21)
PlayDoor(22)
PlayDoor(23)
PlayDoor(24)
PlayDoor(25)
PlayDoor(26)
PlayDoor(27)
PlayDoor(28)
PlayDoor(29)
PlayDoor(30)
PlayDoor(31)
PlayDoor(32)
PlayDoor(33)
PlayDoor(34)
PlayDoor(35)
PlayDoor(36)
PlayDoor(37)
PlayDoor(38)
PlayDoor(39)

/// 구형 PlayDoor들
//void SoundManager::PlayDoor1(eSOUNDKIND sound)
//{
//	m_KSL->PlayDoor1(sound);
//}
//
//void SoundManager::PlayDoor2(eSOUNDKIND sound)
//{
//	m_KSL->PlayDoor2(sound);
//}
//
//void SoundManager::PlayDoor3(eSOUNDKIND sound)
//{
//	m_KSL->PlayDoor3(sound);
//
//}
//
//void SoundManager::PlayDoor4(eSOUNDKIND sound)
//{
//	m_KSL->PlayDoor4(sound);
//
//}
//
//void SoundManager::PlayDoor5(eSOUNDKIND sound)
//{
//	m_KSL->PlayDoor5(sound);
//
//}
//
//void SoundManager::PlayDoor6(eSOUNDKIND sound)
//{
//	m_KSL->PlayDoor6(sound);
//
//}
//
//void SoundManager::PlayDoor7(eSOUNDKIND sound)
//{
//	m_KSL->PlayDoor7(sound);
//
//}
//
//void SoundManager::PlayDoor8(eSOUNDKIND sound)
//{
//	m_KSL->PlayDoor8(sound);
//
//}
//
//void SoundManager::PlayDoor9(eSOUNDKIND sound)
//{
//	m_KSL->PlayDoor9(sound);
//
//}
//
//void SoundManager::PlayDoor10(eSOUNDKIND sound)
//{
//	m_KSL->PlayDoor10(sound);
//
//}

void SoundManager::PlayDemon()
{
	m_KSL->PlayDemon();
}

void SoundManager::PlaybackBGM(Sound* sound)
{
	m_KSL->PlaybackBGM(sound);
}

void SoundManager::PlaybackSFX(Sound* sound)
{
	m_KSL->PlaybackSFX(sound);
}

void SoundManager::Playback3D(Sound* sound)
{
	m_KSL->Playback3D(sound);
}

void SoundManager::PlaybackBGMC(Sound* sound)
{
	m_KSL->PlaybackBGMC(sound);
}

void SoundManager::PlaybackSFXR(Sound* sound)
{
	m_KSL->PlaybackSFXR(sound);
}

void SoundManager::PlayBGM2(Sound* sound)
{
	m_KSL->PlayBGM2(sound);
}

void SoundManager::PlaySFX2(Sound* sound)
{
	m_KSL->PlaySFX2(sound);
}

void SoundManager::Play3D2(Sound* sound)
{
	m_KSL->Play3D2(sound);
}

void SoundManager::PlayBGMC2(Sound* sound)
{
	m_KSL->PlayBGMC2(sound);
}

void SoundManager::PlaySFXR2(Sound* sound)
{
	m_KSL->PlaySFXR2(sound);
}

void SoundManager::PlayBlind(eSOUNDKIND sound)
{
	m_KSL->PlayBlind(sound);
}

void SoundManager::PlayBlind2(Sound* sound)
{
	m_KSL->PlayBlind2(sound);
}

void SoundManager::PlayJane(eSOUNDKIND sound)
{
	m_KSL->PlayJane(sound);
}

void SoundManager::PlayJane2(Sound* sound)
{
	m_KSL->PlayJane2(sound);
}

void SoundManager::PlayChaser(eSOUNDKIND sound)
{
	m_KSL->PlayChaser(sound);
}

void SoundManager::PlayChaser2(Sound* sound)
{
	m_KSL->PlayChaser2(sound);
}

void SoundManager::PlayGhost(eSOUNDKIND sound)
{
	m_KSL->PlayGhost(sound);
}

void SoundManager::PlayGhost2(Sound* sound)
{
	m_KSL->PlayGhost2(sound);
}

void SoundManager::PlayName(string filename)
{
	m_KSL->PlayName(filename);
}

void SoundManager::PlaySound(Sound* sound, Channel** channel)
{
	m_KSL->PlaySound(sound, channel);
}

void SoundManager::PlayerWalk()
{
	m_KSL->PlayerWalk();
}

void SoundManager::PlayerRun()
{
	m_KSL->PlayerRun();
}

void SoundManager::StopMove()
{
	m_KSL->StopMove();
}


void SoundManager::StopSound(Channel* channel)
{
	m_KSL->StopSound(channel);
}


/// 리버브는 채널에서 새로 재생이 될 때마다 갱신한다.
void SoundManager::AddReverb(Channel* channel)
{
	m_KSL->AddReverb(channel);
}

void SoundManager::AddReverbParam(Channel* channel, float val)
{
	m_KSL->AddReverbParam(channel, val);
}

void SoundManager::RemoveReverb(Channel* channel)
{
	m_KSL->RemoveReverb(channel);
}

void SoundManager::UpdateListener()
{
	m_KSL->UpdateListener();
}

void SoundManager::UpdatePos(FMOD_VECTOR fVec)
{
	m_KSL->UpdatePos(fVec.x, fVec.y, fVec.z);
}

/// 지옥의 AND문
//void SoundManager::UpdateChase()
//{
//	if (
//		(m_enemies[0]->GetComponent<EnemyComponent>()->GetEnemyState() == EnemyState::Walk ||
//			m_enemies[0]->GetComponent<EnemyComponent>()->GetEnemyState() == EnemyState::Dead) &&
//		(m_enemies[1]->GetComponent<EnemyComponent>()->GetEnemyState() == EnemyState::Walk ||
//			m_enemies[1]->GetComponent<EnemyComponent>()->GetEnemyState() == EnemyState::Dead))
//	{
//		if (!m_escape &&
//			(m_enemies[0]->GetComponent<EnemyComponent>()->GetEnemyState() != EnemyState::Interact) &&
//			(m_enemies[1]->GetComponent<EnemyComponent>()->GetEnemyState() != EnemyState::Interact))
//		{
//			/*	PlaySFX(eSOUNDKIND::fEscaped);
//				StopSound(GetBGMCChannel());
//				m_chase = false;
//				m_escape = true;*/
//		}
//	}
//	else
//	{
//		if (!m_chase &&
//			(m_enemies[0]->GetComponent<EnemyComponent>()->GetEnemyState() != EnemyState::Stun) &&
//			(m_enemies[1]->GetComponent<EnemyComponent>()->GetEnemyState() != EnemyState::Stun))
//		{
//			if (m_enemies[0]->GetComponent<EnemyComponent>()->GetEnemyState() != EnemyState::NONE)
//			{
//				/*PlayBGMC(eSOUNDKIND::bChased);
//				m_chase = true;
//				m_escape = false;*/
//			}
//		}
//	}
//}

Sound* SoundManager::GetSound(string filename)
{
	return m_KSL->GetSound(filename);
}

FMOD::Sound* SoundManager::GetSound(eSOUNDKIND sound)
{
	Sound* result = m_KSL->GetSound(sound);
	return result;
}

void SoundManager::CreateChannel()
{
	Channel* channel = m_KSL->CreateChannel();
	m_channels.push_back(channel);
	int a = 3;
}

bool SoundManager::GetChase()
{
	return m_chase;
}

void SoundManager::DoChase()
{
	m_chase = true;
}

void SoundManager::DoEscape()
{
	m_chase = false;
	m_escape = true;
}

void SoundManager::SetPriority(Channel* channel, float val)
{
	m_KSL->SetPriority(channel, val);
}

KSL* SoundManager::getKSL()
{
	return m_KSL;
}

FMOD::Channel* SoundManager::GetBGMChannel()
{
	return m_KSL->GetBGMChannel();
}

FMOD::Channel* SoundManager::GetBGMCChannel()
{
	return m_KSL->GetBGMCChannel();
}

FMOD::Channel* SoundManager::GetSFXChannel()
{
	return m_KSL->GetSFXChannel();

}

FMOD::Channel* SoundManager::GetSFXRChannel()
{
	return m_KSL->GetSFXRChannel();

}

FMOD::Channel* SoundManager::Get3DChannel()
{
	return m_KSL->Get3DChannel();

}

FMOD::Channel* SoundManager::GetMoveChannel()
{
	return m_KSL->GetMoveChannel();
}

FMOD::Channel* SoundManager::GetBlindChannel()
{
	return m_KSL->GetBlindChannel();

}

FMOD::Channel* SoundManager::GetJaneChannel()
{
	return m_KSL->GetJaneChannel();

}

FMOD::Channel* SoundManager::GetChaserChannel()
{
	return m_KSL->GetChaserChannel();

}

FMOD::Channel* SoundManager::GetGhostChannel()
{
	return m_KSL->GetGhostChannel();

}

#define GetDoorChannel(n) \
FMOD::Channel* SoundManager::GetDoor##n##Channel() \
{ \
    return m_KSL->GetDoor##n##Channel(); \
}

GetDoorChannel(0)
GetDoorChannel(1)
GetDoorChannel(2)
GetDoorChannel(3)
GetDoorChannel(4)
GetDoorChannel(5)
GetDoorChannel(6)
GetDoorChannel(7)
GetDoorChannel(8)
GetDoorChannel(9)
GetDoorChannel(10)
GetDoorChannel(11)
GetDoorChannel(12)
GetDoorChannel(13)
GetDoorChannel(14)
GetDoorChannel(15)
GetDoorChannel(16)
GetDoorChannel(17)
GetDoorChannel(18)
GetDoorChannel(19)
GetDoorChannel(20)
GetDoorChannel(21)
GetDoorChannel(22)
GetDoorChannel(23)
GetDoorChannel(24)
GetDoorChannel(25)
GetDoorChannel(26)
GetDoorChannel(27)
GetDoorChannel(28)
GetDoorChannel(29)
GetDoorChannel(30)
GetDoorChannel(31)
GetDoorChannel(32)
GetDoorChannel(33)
GetDoorChannel(34)
GetDoorChannel(35)
GetDoorChannel(36)
GetDoorChannel(37)
GetDoorChannel(38)
GetDoorChannel(39)

/// 구형 GetDoorChannel들
//FMOD::Channel* SoundManager::GetDoor1Channel()
//{
//	return m_KSL->GetDoor1Channel();
//}
//
//FMOD::Channel* SoundManager::GetDoor2Channel()
//{
//	return m_KSL->GetDoor2Channel();
//
//}
//
//FMOD::Channel* SoundManager::GetDoor3Channel()
//{
//	return m_KSL->GetDoor3Channel();
//
//}
//
//FMOD::Channel* SoundManager::GetDoor4Channel()
//{
//	return m_KSL->GetDoor4Channel();
//
//}
//
//FMOD::Channel* SoundManager::GetDoor5Channel()
//{
//	return m_KSL->GetDoor5Channel();
//
//}
//
//FMOD::Channel* SoundManager::GetDoor6Channel()
//{
//	return m_KSL->GetDoor6Channel();
//
//}
//
//FMOD::Channel* SoundManager::GetDoor7Channel()
//{
//	return m_KSL->GetDoor7Channel();
//
//}
//
//FMOD::Channel* SoundManager::GetDoor8Channel()
//{
//	return m_KSL->GetDoor8Channel();
//
//}
//
//FMOD::Channel* SoundManager::GetDoor9Channel()
//{
//	return m_KSL->GetDoor9Channel();
//
//}
//
//FMOD::Channel* SoundManager::GetDoor10Channel()
//{
//	return m_KSL->GetDoor10Channel();
//
//}

FMOD::Channel* SoundManager::GetDemonChannel()
{
	return m_KSL->GetDemonChannel();
}

std::vector<GameObject*> SoundManager::GetAudioComps()
{
	return m_audioComps;
}


std::vector<GameObject*> SoundManager::GetEnemyComps()
{
	return m_enemies;
}

GameObject* SoundManager::GetGameObject(int i)
{
	return m_audioComps[i];
}

/// 채널 벡터와 오디오 컴포넌트 벡터에 같은 순서로 들어가 있을테니
/// 게임오브젝트의 이름과 같은 순번의 채널을 리턴한다.
FMOD::Channel* SoundManager::GetAudioChannel(GameObject* object)
{
	int count = 0;
	for (auto e : m_audioComps)
	{
		if (e->GetName() == object->GetName())
		{
			return m_channels[count];
		}
		count++;
	}

	return nullptr;
}

std::vector<Channel*> SoundManager::GetChannels()
{
	return m_channels;
}

void SoundManager::ClearAudioComps()
{
	m_audioComps.clear();
}

FMOD_VECTOR SoundManager::ConvertVector(SimpleMath::Vector3 sVec, SimpleMath::Vector3 lVec)
{
	FMOD_VECTOR temp;
	temp.x = sVec.x - lVec.x;
	temp.y = sVec.y - lVec.y;
	temp.z = sVec.z - lVec.z;

	return temp;
}

void SoundManager::Set3DMinMaxDistance(string filename, float min, float max)
{
	m_KSL->Set3DMinMaxDistance(filename, min, max);
}

void SoundManager::Set3DMinMaxDistance(eSOUNDKIND sound, float min, float max)
{
	m_KSL->Set3DMinMaxDistance(sound, min, max);
}

void SoundManager::PushAudio(GameObject* object)
{
	m_audioComps.push_back(object);
}

void SoundManager::DoorOpen(int index)
{
	switch (index)
	{
	case 4:
		PlayDoor4(eSOUNDKIND::fDoor);
		AddReverb(SoundManager::GetInstance().GetDoor4Channel());
		break;
	case 5:
		PlayDoor5(eSOUNDKIND::fDoor);
		AddReverb(SoundManager::GetInstance().GetDoor5Channel());
		break;
	case 6:
		PlayDoor6(eSOUNDKIND::fDoor);
		AddReverb(SoundManager::GetInstance().GetDoor6Channel());
		break;
	case 7:
		PlayDoor7(eSOUNDKIND::fDoor);
		AddReverb(SoundManager::GetInstance().GetDoor7Channel());
		break;
	case 8:
		PlayDoor8(eSOUNDKIND::fDoor);
		AddReverb(SoundManager::GetInstance().GetDoor8Channel());
		break;
	case 9:
		PlayDoor9(eSOUNDKIND::fDoor);
		AddReverb(SoundManager::GetInstance().GetDoor9Channel());
		break;
	case 10:
		PlayDoor10(eSOUNDKIND::fDoor);
		AddReverb(SoundManager::GetInstance().GetDoor10Channel());
		break;
	case 11:
		PlayDoor11(eSOUNDKIND::fDoor);
		AddReverb(SoundManager::GetInstance().GetDoor11Channel());
		break;
	case 12:
		PlayDoor12(eSOUNDKIND::fDoor);
		AddReverb(SoundManager::GetInstance().GetDoor12Channel());
		break;
	case 13:
		PlayDoor13(eSOUNDKIND::fDoor);
		AddReverb(SoundManager::GetInstance().GetDoor13Channel());
		break;
	case 14:
		PlayDoor14(eSOUNDKIND::fDoor);
		AddReverb(SoundManager::GetInstance().GetDoor14Channel());
		break;
	case 15:
		PlayDoor15(eSOUNDKIND::fDoor);
		AddReverb(SoundManager::GetInstance().GetDoor15Channel());
		break;
	case 16:
		PlayDoor16(eSOUNDKIND::fDoor);
		AddReverb(SoundManager::GetInstance().GetDoor16Channel());
		break;
	case 17:
		PlayDoor17(eSOUNDKIND::fDoor);
		AddReverb(SoundManager::GetInstance().GetDoor17Channel());
		break;
	case 18:
		PlayDoor18(eSOUNDKIND::fDoor);
		AddReverb(SoundManager::GetInstance().GetDoor18Channel());
		break;
	case 19:
		PlayDoor19(eSOUNDKIND::fDoor);
		AddReverb(SoundManager::GetInstance().GetDoor19Channel());
		break;
	case 20:
		PlayDoor20(eSOUNDKIND::fDoor);
		AddReverb(SoundManager::GetInstance().GetDoor20Channel());
		break;
	case 21:
		PlayDoor21(eSOUNDKIND::fDoor);
		AddReverb(SoundManager::GetInstance().GetDoor21Channel());
		break;
	case 22:
		PlayDoor22(eSOUNDKIND::fDoor);
		AddReverb(SoundManager::GetInstance().GetDoor22Channel());
		break;
	case 23:
		PlayDoor23(eSOUNDKIND::fDoor);
		AddReverb(SoundManager::GetInstance().GetDoor23Channel());
		break;
	case 24:
		PlayDoor24(eSOUNDKIND::fDoor);
		AddReverb(SoundManager::GetInstance().GetDoor24Channel());
		break;
	case 25:
		PlayDoor25(eSOUNDKIND::fDoor);
		AddReverb(SoundManager::GetInstance().GetDoor25Channel());
		break;
	case 26:
		PlayDoor26(eSOUNDKIND::fDoor);
		AddReverb(SoundManager::GetInstance().GetDoor26Channel());
		break;
	case 27:
		PlayDoor27(eSOUNDKIND::fDoor);
		AddReverb(SoundManager::GetInstance().GetDoor27Channel());
		break;
	case 28:
		PlayDoor28(eSOUNDKIND::fDoor);
		AddReverb(SoundManager::GetInstance().GetDoor28Channel());
		break;
	case 29:
		PlayDoor29(eSOUNDKIND::fDoor);
		AddReverb(SoundManager::GetInstance().GetDoor29Channel());
		break;
	case 30:
		PlayDoor30(eSOUNDKIND::fDoor);
		AddReverb(SoundManager::GetInstance().GetDoor30Channel());
		break;
	case 31:
		PlayDoor31(eSOUNDKIND::fDoor);
		AddReverb(SoundManager::GetInstance().GetDoor31Channel());
		break;
	case 32:
		PlayDoor32(eSOUNDKIND::fDoor);
		AddReverb(SoundManager::GetInstance().GetDoor32Channel());
		break;
	case 33:
		PlayDoor33(eSOUNDKIND::fDoor);
		AddReverb(SoundManager::GetInstance().GetDoor33Channel());
		break;
	case 34:
		PlayDoor34(eSOUNDKIND::fDoor);
		AddReverb(SoundManager::GetInstance().GetDoor34Channel());
		break;
	case 35:
		PlayDoor35(eSOUNDKIND::fDoor);
		AddReverb(SoundManager::GetInstance().GetDoor35Channel());
		break;
	case 36:
		PlayDoor36(eSOUNDKIND::fDoor);
		AddReverb(SoundManager::GetInstance().GetDoor36Channel());
		break;
	case 37:
		PlayDoor37(eSOUNDKIND::fDoor);
		AddReverb(SoundManager::GetInstance().GetDoor37Channel());
		break;
	case 38:
		PlayDoor38(eSOUNDKIND::fDoor);
		AddReverb(SoundManager::GetInstance().GetDoor38Channel());
		break;
	case 39:
		PlayDoor39(eSOUNDKIND::fDoor);
		AddReverb(SoundManager::GetInstance().GetDoor39Channel());
		break;
	default:
		break;
	}
}

void SoundManager::DoorClose(int index)
{
	switch (index)
	{
	case 4:
		PlayDoor4(eSOUNDKIND::fClose);
		//AddReverb(SoundManager::GetInstance().GetDoor4Channel());
		break;
	case 5:
		PlayDoor5(eSOUNDKIND::fClose);
		//AddReverb(SoundManager::GetInstance().GetDoor5Channel());
		break;
	case 6:
		PlayDoor6(eSOUNDKIND::fClose);
		//AddReverb(SoundManager::GetInstance().GetDoor6Channel());
		break;
	case 7:
		PlayDoor7(eSOUNDKIND::fClose);
		//AddReverb(SoundManager::GetInstance().GetDoor7Channel());
		break;
	case 8:
		PlayDoor8(eSOUNDKIND::fClose);
		//AddReverb(SoundManager::GetInstance().GetDoor8Channel());
		break;
	case 9:
		PlayDoor9(eSOUNDKIND::fClose);
		//AddReverb(SoundManager::GetInstance().GetDoor9Channel());
		break;
	case 10:
		PlayDoor10(eSOUNDKIND::fClose);
		//AddReverb(SoundManager::GetInstance().GetDoor10Channel());
		break;
	case 11:
		PlayDoor11(eSOUNDKIND::fClose);
		//AddReverb(SoundManager::GetInstance().GetDoor11Channel());
		break;
	case 12:
		PlayDoor12(eSOUNDKIND::fClose);
		//AddReverb(SoundManager::GetInstance().GetDoor12Channel());
		break;
	case 13:
		PlayDoor13(eSOUNDKIND::fClose);
		//AddReverb(SoundManager::GetInstance().GetDoor13Channel());
		break;
	case 14:
		PlayDoor14(eSOUNDKIND::fClose);
		//AddReverb(SoundManager::GetInstance().GetDoor14Channel());
		break;
	case 15:
		PlayDoor15(eSOUNDKIND::fClose);
		//AddReverb(SoundManager::GetInstance().GetDoor15Channel());
		break;
	case 16:
		PlayDoor16(eSOUNDKIND::fClose);
		//AddReverb(SoundManager::GetInstance().GetDoor16Channel());
		break;
	case 17:
		PlayDoor17(eSOUNDKIND::fClose);
		//AddReverb(SoundManager::GetInstance().GetDoor17Channel());
		break;
	case 18:
		PlayDoor18(eSOUNDKIND::fClose);
		//AddReverb(SoundManager::GetInstance().GetDoor18Channel());
		break;
	case 19:
		PlayDoor19(eSOUNDKIND::fClose);
		//AddReverb(SoundManager::GetInstance().GetDoor19Channel());
		break;
	case 20:
		PlayDoor20(eSOUNDKIND::fClose);
		//AddReverb(SoundManager::GetInstance().GetDoor20Channel());
		break;
	case 21:
		PlayDoor21(eSOUNDKIND::fClose);
		//AddReverb(SoundManager::GetInstance().GetDoor21Channel());
		break;
	case 22:
		PlayDoor22(eSOUNDKIND::fClose);
		//AddReverb(SoundManager::GetInstance().GetDoor22Channel());
		break;
	case 23:
		PlayDoor23(eSOUNDKIND::fClose);
		//AddReverb(SoundManager::GetInstance().GetDoor23Channel());
		break;
	case 24:
		PlayDoor24(eSOUNDKIND::fClose);
		//AddReverb(SoundManager::GetInstance().GetDoor24Channel());
		break;
	case 25:
		PlayDoor25(eSOUNDKIND::fClose);
		//AddReverb(SoundManager::GetInstance().GetDoor25Channel());
		break;
	case 26:
		PlayDoor26(eSOUNDKIND::fClose);
		//AddReverb(SoundManager::GetInstance().GetDoor26Channel());
		break;
	case 27:
		PlayDoor27(eSOUNDKIND::fClose);
		//AddReverb(SoundManager::GetInstance().GetDoor27Channel());
		break;
	case 28:
		PlayDoor28(eSOUNDKIND::fClose);
		//AddReverb(SoundManager::GetInstance().GetDoor28Channel());
		break;
	case 29:
		PlayDoor29(eSOUNDKIND::fClose);
		//AddReverb(SoundManager::GetInstance().GetDoor29Channel());
		break;
	case 30:
		PlayDoor30(eSOUNDKIND::fClose);
		//AddReverb(SoundManager::GetInstance().GetDoor30Channel());
		break;
	case 31:
		PlayDoor31(eSOUNDKIND::fClose);
		//AddReverb(SoundManager::GetInstance().GetDoor31Channel());
		break;
	case 32:
		PlayDoor32(eSOUNDKIND::fClose);
		//AddReverb(SoundManager::GetInstance().GetDoor32Channel());
		break;
	case 33:
		PlayDoor33(eSOUNDKIND::fClose);
		//AddReverb(SoundManager::GetInstance().GetDoor33Channel());
		break;
	case 34:
		PlayDoor34(eSOUNDKIND::fClose);
		//AddReverb(SoundManager::GetInstance().GetDoor34Channel());
		break;
	case 35:
		PlayDoor35(eSOUNDKIND::fClose);
		//AddReverb(SoundManager::GetInstance().GetDoor35Channel());
		break;
	case 36:
		PlayDoor36(eSOUNDKIND::fClose);
		//AddReverb(SoundManager::GetInstance().GetDoor36Channel());
		break;
	case 37:
		PlayDoor37(eSOUNDKIND::fClose);
		//AddReverb(SoundManager::GetInstance().GetDoor37Channel());
		break;
	case 38:
		PlayDoor38(eSOUNDKIND::fClose);
		//AddReverb(SoundManager::GetInstance().GetDoor38Channel());
		break;
	case 39:
		PlayDoor39(eSOUNDKIND::fClose);
		//AddReverb(SoundManager::GetInstance().GetDoor39Channel());
		break;
	default:
		break;
	}
}

void SoundManager::SetAll3DMinMaxDistance()
{
	Set3DMinMaxDistance(eSOUNDKIND::fBlindAttack, m_minDist, m_maxDist);
	Set3DMinMaxDistance(eSOUNDKIND::fJaneAttack, m_minDist, m_maxDist);
	Set3DMinMaxDistance(eSOUNDKIND::fChaserAttack, m_minDist, m_maxDist);
	Set3DMinMaxDistance(eSOUNDKIND::lBlindWalk, m_minDist, m_maxDist);
	Set3DMinMaxDistance(eSOUNDKIND::lBlindRun, m_minDist, m_maxDist);
	Set3DMinMaxDistance(eSOUNDKIND::lJaneWalk, m_minDist, m_maxDist);
	Set3DMinMaxDistance(eSOUNDKIND::lJaneRun, m_minDist, m_maxDist);
	Set3DMinMaxDistance(eSOUNDKIND::lChaserWalk, m_minDist, m_maxDist);
	Set3DMinMaxDistance(eSOUNDKIND::lGhostWalk, m_minDist, m_maxDist);
	Set3DMinMaxDistance(eSOUNDKIND::fDoor, m_minDist, m_maxDist);
	Set3DMinMaxDistance(eSOUNDKIND::fClose, m_minDist, m_maxDist);
}

void SoundManager::PushEnemy(GameObject* object)
{
	m_enemies.push_back(object);
}

//void SoundManager::UpdateJanePos(FMOD_VECTOR fVec)
//{
//	m_KSL->GetJaneChannel()->set3DAttributes(&fVec, &vel);
//}

/// 오디오 컴포넌트를 가진 애들에 따라서
/// 채널의 3D 정보를 업데이트해준다
void SoundManager::UpdateSoundPos(FMOD_VECTOR fVec, string name)
{
	int num = 0;
	if (name == "Blind")
		num = 1;
	else if (name == "JaneD")
		num = 2;
	else if (name == "Chaser")
		num = 3;
	else if (name == "Ghost")
		num = 4;
	// 테스트용
	else if (name == "ItemChest")
		num = 5;
	else if (name == "Door_1_10_2")
		num = 6;
	else if (name == "Door_6_7_2")
		num = 7;
	else if (name == "Door_12_13_2")
		num = 8;
	else
		num = -1;

	switch (num)
	{
	case 1:
		m_KSL->GetBlindChannel()->set3DAttributes(&fVec, &vel);
		break;
	case 2:
		m_KSL->GetJaneChannel()->set3DAttributes(&fVec, &vel);
		break;
	case 3:
		m_KSL->GetChaserChannel()->set3DAttributes(&fVec, &vel);
		break;
	case 4:
		m_KSL->GetGhostChannel()->set3DAttributes(&fVec, &vel);
		break;
	case 5:
		m_KSL->GetDoor10Channel()->set3DAttributes(&fVec, &vel);
		break;
	case 6:
		m_KSL->GetDoor2Channel()->set3DAttributes(&fVec, &vel);
		break;
	case 7:
		m_KSL->GetDoor3Channel()->set3DAttributes(&fVec, &vel);
		break;
	case 8:
		m_KSL->GetDoor1Channel()->set3DAttributes(&fVec, &vel);
		break;
	default:
		break;
	}
}

/// 채널을 뺏기고 있다.... 왜?
void SoundManager::UpdateSoundPos(FMOD_VECTOR fVec, Channel*& channel)
{
	//PlaySound(SoundManager::GetSound(eSOUNDKIND::fClick), &channel);
	FMOD_RESULT result = channel->set3DAttributes(&fVec, &vel);
	int a = 3;
}

void SoundManager::UpdateSoundPos(FMOD_VECTOR fVec, int index)
{
	switch (index)
	{
		// 0 ~ 3 까지는 움직이는 적들이
		case 0:
			m_KSL->GetBlindChannel()->set3DAttributes(&fVec, &vel);
			break;
		case 1:
			m_KSL->GetJaneChannel()->set3DAttributes(&fVec, &vel);
			break;
		case 2:
			m_KSL->GetChaserChannel()->set3DAttributes(&fVec, &vel);
			break;
		case 3:
			m_KSL->GetGhostChannel()->set3DAttributes(&fVec, &vel);
			break;
		// 4번부터는 모두 문(door)이다
		case 4:
			m_KSL->GetDoor4Channel()->set3DAttributes(&fVec, &vel);
			break;
		case 5:
			m_KSL->GetDoor5Channel()->set3DAttributes(&fVec, &vel);
			break;
		case 6:
			m_KSL->GetDoor6Channel()->set3DAttributes(&fVec, &vel);
			break;
		case 7:
			m_KSL->GetDoor7Channel()->set3DAttributes(&fVec, &vel);
			break;
		case 8:
			m_KSL->GetDoor8Channel()->set3DAttributes(&fVec, &vel);
			break;
		case 9:
			m_KSL->GetDoor9Channel()->set3DAttributes(&fVec, &vel);
			break;
		case 10:
			m_KSL->GetDoor10Channel()->set3DAttributes(&fVec, &vel);
			break;
		case 11:
			m_KSL->GetDoor11Channel()->set3DAttributes(&fVec, &vel);
			break;
		case 12:
			m_KSL->GetDoor12Channel()->set3DAttributes(&fVec, &vel);
			break;
		case 13:
			m_KSL->GetDoor13Channel()->set3DAttributes(&fVec, &vel);
			break;
		case 14:
			m_KSL->GetDoor14Channel()->set3DAttributes(&fVec, &vel);
			break;
		case 15:
			m_KSL->GetDoor15Channel()->set3DAttributes(&fVec, &vel);
			break;
		case 16:
			m_KSL->GetDoor16Channel()->set3DAttributes(&fVec, &vel);
			break;
		case 17:
			m_KSL->GetDoor17Channel()->set3DAttributes(&fVec, &vel);
			break;
		case 18:
			m_KSL->GetDoor18Channel()->set3DAttributes(&fVec, &vel);
			break;
		case 19:
			m_KSL->GetDoor19Channel()->set3DAttributes(&fVec, &vel);
			break;
		case 20:
			m_KSL->GetDoor20Channel()->set3DAttributes(&fVec, &vel);
			break;
		case 21:
			m_KSL->GetDoor21Channel()->set3DAttributes(&fVec, &vel);
			break;
		case 22:
			m_KSL->GetDoor22Channel()->set3DAttributes(&fVec, &vel);
			break;
		case 23:
			m_KSL->GetDoor23Channel()->set3DAttributes(&fVec, &vel);
			break;
		case 24:
			m_KSL->GetDoor24Channel()->set3DAttributes(&fVec, &vel);
			break;
		case 25:
			m_KSL->GetDoor25Channel()->set3DAttributes(&fVec, &vel);
			break;
		case 26:
			m_KSL->GetDoor26Channel()->set3DAttributes(&fVec, &vel);
			break;
		case 27:
			m_KSL->GetDoor27Channel()->set3DAttributes(&fVec, &vel);
			break;
		case 28:
			m_KSL->GetDoor28Channel()->set3DAttributes(&fVec, &vel);
			break;
		case 29:
			m_KSL->GetDoor29Channel()->set3DAttributes(&fVec, &vel);
			break;
		case 30:
			m_KSL->GetDoor30Channel()->set3DAttributes(&fVec, &vel);
			break;
		case 31:
			m_KSL->GetDoor31Channel()->set3DAttributes(&fVec, &vel);
			break;
		case 32:
			m_KSL->GetDoor32Channel()->set3DAttributes(&fVec, &vel);
			break;
		case 33:
			m_KSL->GetDoor33Channel()->set3DAttributes(&fVec, &vel);
			break;
		case 34:
			m_KSL->GetDoor34Channel()->set3DAttributes(&fVec, &vel);
			break;
		case 35:
			m_KSL->GetDoor35Channel()->set3DAttributes(&fVec, &vel);
			break;
		case 36:
			m_KSL->GetDoor36Channel()->set3DAttributes(&fVec, &vel);
			break;
		case 37:
			m_KSL->GetDoor37Channel()->set3DAttributes(&fVec, &vel);
			break;
		case 38:
			m_KSL->GetDoor38Channel()->set3DAttributes(&fVec, &vel);
			break;
		case 39:
			m_KSL->GetDoor39Channel()->set3DAttributes(&fVec, &vel);
			break;
		default:
			break;
	}

}


FMOD_VECTOR SoundManager::PosIsMove()
{
	return m_KSL->PosIsMove();
}

FMOD_VECTOR SoundManager::PosIsMove2()
{
	return m_KSL->PosIsMove2();
}
