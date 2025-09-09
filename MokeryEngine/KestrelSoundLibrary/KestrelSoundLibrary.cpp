#include "KestrelSoundLibrary.h"


using namespace std;
using namespace FMOD;


KSL::KSL()
{
	m_system = nullptr;

	for (int i = 0; i < static_cast<int>(eSOUNDKIND::END); i++)
	{
		m_sounds[i] = nullptr;
	}

	for (int i = 0; i < 30; i++)
	{
		m_doorChannel[i] = nullptr;
	}

	m_bgmChannel = nullptr;
	m_sfxChannel = nullptr;
	m_sfxRChannel = nullptr;
	m_3dChannel = nullptr;
	m_moveChannel = nullptr;
	m_BlindChannel = nullptr;
	m_JaneChannel = nullptr;
	m_ChaserChannel = nullptr;
	m_GhostChannel = nullptr;
	m_etcChannel = nullptr;
	m_bgmChannelGroup = nullptr;
	m_sfxChannelGroup = nullptr;
	m_3dChannelGroup = nullptr;
	m_enemyChannelGroup = nullptr;

	m_channels.push_back(m_bgmChannel);
	m_channels.push_back(m_sfxChannel);
	m_channels.push_back(m_sfxRChannel);
	m_channels.push_back(m_3dChannel);
	m_channels.push_back(m_moveChannel);
	m_channels.push_back(m_BlindChannel);
	m_channels.push_back(m_JaneChannel);
	m_channels.push_back(m_ChaserChannel);
	m_channels.push_back(m_GhostChannel);
	m_channels.push_back(m_etcChannel);


	m_mVolume = 0.f;
	m_bVolume = 0.f;
	m_fVolume = 0.f;
	m_aVolume = 0.f;
	m_bChannelVolume = 0.f;
	m_fChannelVolume = 0.f;
	m_aChannelVolume = 0.f;

	m_isBGMPlaying = false;
	m_isBGMPaused = false;

	m_reverb = nullptr;
	m_reverbDSP = nullptr;

	result = FMOD_OK;
}

KSL::~KSL()
{

}

/// 사운드 라이브러리 초기화 함수
/// 시스템 생성, 사운드 로드, 멤버 초기화 등은 여기서
void KSL::Initialize()
{
	// 시스템 생성
	result = System_Create(&m_system);
	if (result != FMOD_OK) { return; }

	// 시스템 초기화 (채널 개수, 시스템 모드-3d 오른손좌표계, 엑스트라 드라이버? 몰루)
	result = m_system->init(4095, FMOD_INIT_3D_RIGHTHANDED, nullptr);
	if (result != FMOD_OK) { return; }

	// 디스턴스 유닛 설정 (미터/피트 등등)
	result = m_system->set3DSettings(1.0, DISTANCEFACTOR, 1.0f);
	if (result != FMOD_OK) { return; }


	// 자주 사용되는 효과음 등은 미리 로딩해서 사용한다.
	//LoadSounds();


	// 나머지 멤버 초기화
	m_mVolume = 0.5f;
	m_bVolume = 0.3f;
	m_fVolume = 1.0f;
	m_aVolume = 0.5f;


	m_isBGMPlaying = false;
	m_isBGMPaused = false;
}

/// 시스템 업데이트 함수
/// 채널을 재사용합니다.
void KSL::Update()
{
	m_system->update();
}

/// 시스템 종료시 호출할 함수
/// 할당한 사운드 해제하고 시스템 종료
void KSL::Finalize()
{
	// 시스템 해제
	for (int i = 0; i < static_cast<int>(eSOUNDKIND::END); i++)
	{
		m_sounds[i]->release();
	}
	m_reverb->release();
	m_system->close();
	m_system->release();

	// FMOD는 시스템 해제 시 메모리 해제
}

void KSL::ReadSounds()
{
	m_soundFiles.clear();
	int count = 0;
	try
	{
		for (const auto& entry : filesystem::directory_iterator(m_soundPath)) {
			// 파일인 경우만 처리
			if (filesystem::is_regular_file(entry))
			{
				// 파일의 경로에서 파일 이름만 추출하여 벡터에 추가
				m_soundFiles.push_back(entry.path().filename().string());
				
			}
			count++;
		}
	}
	catch (const std::exception& e)
	{
		cerr << "Error while accessing directory: " << e.what() << endl;
	}

	int a = 3;
}

/// 시작과 동시에 사운드를 로드하는 함수
/// 효과음 등 자주 사용되거나 가벼운 사운드는 미리 로드합니다
/// 효과음은 전부 3D 선형-제곱 감쇠로 로드하는게 더 좋은 것 같아서 그렇게 했습니다
void KSL::LoadSounds()
{
	try
	{
		auto iter = filesystem::directory_iterator(m_soundPath);
		if (iter != filesystem::directory_iterator())
		{
			const auto& entry = *iter;
			// 파일인 경우만 처리
			if (filesystem::is_regular_file(entry))
			{
				// BGM을 로드한다면?
				for (int i = static_cast<int>(eSOUNDKIND::bLobby); i < static_cast<int>(eSOUNDKIND::fClick); i++)
				{
					const string& filepath = "../Resources/Sounds/" + m_soundFiles[i];
					result = m_system->createSound(filepath.c_str(), FMOD_DEFAULT, nullptr, &m_sounds[i]);
					SetSoundData(static_cast<eSOUNDKIND>(i), m_soundFiles[i], m_sounds[i]);
					if (result != FMOD_OK)
					{
						return;
					}
					result = m_sounds[i]->setMode(FMOD_LOOP_NORMAL);
					if (result != FMOD_OK)
					{
						return;
					}
				}

				// SFX를 로드한다면?
				for (int i = static_cast<int>(eSOUNDKIND::fClick); i < static_cast<int>(eSOUNDKIND::lPlayerWalk); i++)
				{
					const string& filepath = "../Resources/Sounds/" + m_soundFiles[i];
					result = m_system->createSound(filepath.c_str(), FMOD_3D_LINEARSQUAREROLLOFF, nullptr, &m_sounds[i]);
					SetSoundData(static_cast<eSOUNDKIND>(i), m_soundFiles[i], m_sounds[i]);
					if (result != FMOD_OK)
					{
						return;
					}
				}

				// SFX를 루프하게 로드하기
				for (int i = static_cast<int>(eSOUNDKIND::lPlayerWalk); i < static_cast<int>(eSOUNDKIND::etc1); i++)
				{
					const string& filepath = "../Resources/Sounds/" + m_soundFiles[i];
					result = m_system->createSound(filepath.c_str(), FMOD_3D_LINEARSQUAREROLLOFF, nullptr, &m_sounds[i]);
					SetSoundData(static_cast<eSOUNDKIND>(i), m_soundFiles[i], m_sounds[i]);
					if (result != FMOD_OK)
					{
						return;
					}
					result = m_sounds[i]->setMode(FMOD_LOOP_NORMAL);
					if (result != FMOD_OK)
					{
						return;
					}
				}
			}
		}

	}

	catch (const std::exception& e)
	{
		cerr << "Error while accessing directory: " << e.what() << endl;
	}
	
}

/// 현재 사운드를 뭉탱이로 읽고 있지 않으므로
/// 하나만 읽어와서 테스트하는 용도로 만들었다.
/// 아마 나중에도 쓸 일이 있을 듯? 일단 etc1 enum class에 저장해놓음
void KSL::LoadSound(string filename)
{
	const string& filepath = "../Resources/Sounds/" + filename;
	result = m_system->createSound(filepath.c_str(), FMOD_LOOP_NORMAL, nullptr, &m_sounds[static_cast<int>(eSOUNDKIND::etc1)]);
	SetSoundData(eSOUNDKIND::etc1, filename, m_sounds[static_cast<int>(eSOUNDKIND::etc1)]);
	if (result != FMOD_OK)
	{
		return;
	}
}

/// 3D 모드로 사운드를 로드하는 함수
/// 3D 사운드에 필요한 설정도 같이 해준다.
/// 역시 테스트용...
void KSL::Load3DSound(string filename)
{
	const string& filepath = "../Resources/Sounds/" + filename;
	result = m_system->createSound(filepath.c_str(), FMOD_3D_LINEARSQUAREROLLOFF, 0, &m_sounds[static_cast<int>(eSOUNDKIND::etc1)]);
	result = m_sounds[static_cast<int>(eSOUNDKIND::etc1)]->
		set3DMinMaxDistance(0.5f * DISTANCEFACTOR, 5000.0f * DISTANCEFACTOR);
	SetSoundData(eSOUNDKIND::etc1, filename, m_sounds[static_cast<int>(eSOUNDKIND::etc1)]);
	if (result != FMOD_OK)
	{
		return;
	}
}

/// 비동기 로드 함수
/// BGM 등 용량이 크거나 메모리를 아끼기 위해 백그라운드에서 로딩할 때 사용합니다
void KSL::AsyncLoadSound(string filename)
{
	const string& filepath = "../Resources/Sounds/" + filename;
	result = m_system->createSound(filepath.c_str(), FMOD_LOOP_NORMAL, nullptr, &m_sounds[static_cast<int>(eSOUNDKIND::etc1)]);
	SetSoundData(eSOUNDKIND::etc1, filename, m_sounds[static_cast<int>(eSOUNDKIND::etc1)]);
	if (result != FMOD_OK)
	{
		return;
	}

	while (result == FMOD_ERR_NOTREADY)
		m_system->update();
}

/// 동적 로드 함수
/// 바로 사운드 포인터를 만들어 로드하고 재생합니다.
/// 사용이 끝났다면 바로 UnloadSound해야함
/// 이왕이면 BGM이 아닌 걸 로드하면 좋겠다.
void KSL::DynamicLoadSound(string filename)
{
	const string& filepath = "../Resources/Sounds/" + filename;

	Sound* dSound = nullptr;
	result = m_system->createSound(filepath.c_str(), FMOD_3D_HEADRELATIVE, nullptr, &dSound);
	if (result != FMOD_OK)
	{
		return;
	}
	result = m_system->playSound(dSound, nullptr, false, &m_etcChannel);
	PushDynamicSound(dSound);
	
}

/// 사운드 해제 함수
/// 동적 로드된 사운드, 비동기 로드 사운드 등 사용이 끝난 사운드를 해제합니다
/// 귀찮으니까 벡터에 다 때려박고 해제할때 한꺼번에 해제하자
void KSL::UnloadSound()
{
	for (auto e : m_dSounds)
	{
		e->release();
	}
	m_dSounds.clear();
}


/// 채널에 재생 후 바로 정지하여 빈 채널을 만들고
/// 그 포인터를 반환하는 채널 생성 함수
FMOD::Channel* KSL::CreateChannel()
{
	Channel* newChannel = nullptr;
	result = m_system->playSound(m_sounds[0], m_3dChannelGroup, false, &newChannel);
	if (result != FMOD_OK)
		return nullptr;
	result = newChannel->stop();
	if (result != FMOD_OK)
		return nullptr;
	return newChannel;
}

/// 사운드 파일의 수 만큼
/// 채널을 만들어 벡터에 저장한다.
void KSL::CreateAllChannel()
{
	for (int i = 0; i < static_cast<int>(eSOUNDKIND::END); i++)
	{
		Channel* channel = nullptr;
		m_channels.push_back(channel);
	}
}

/// BGM 플레이 함수
void KSL::PlayBGM(eSOUNDKIND sound)
{
	// bgm 재생 중 PlayBGM이 실행되면 리턴하게 만들지 말고...
	// 한번 Stop하고 Play하자.
	if (m_isBGMPlaying != false)
		StopBGM();
	if (m_isBGMPaused)
		m_isBGMPaused = false;
	result = m_system->playSound(m_sounds[static_cast<int>(sound)], m_bgmChannelGroup, false, &m_bgmChannel);
	m_bgmChannel->setVolume(1.0f);
	if (result != FMOD_OK) { return; }
	m_isBGMPlaying = true;
}

void KSL::PlayBGMC(eSOUNDKIND sound)
{
	result = m_system->playSound(m_sounds[static_cast<int>(sound)], m_bgmChannelGroup, false, &m_bgmCChannel);
	m_bgmCChannel->setVolume(1.0f);
	if (result != FMOD_OK) { return; }
}

/// 3D채널에서 sfx를 플레이 함수
void KSL::Play3D(eSOUNDKIND sound)
{
	result = m_system->playSound(m_sounds[static_cast<int>(sound)], m_3dChannelGroup, false, &m_3dChannel);
	result = m_3dChannel->set3DAttributes(&pos, &vel);
	m_3dChannel->setVolume(m_fVolume);
	if (result != FMOD_OK) { return; }
	//m_isBGMPlaying = true;
}

/// 3D 사운드 중지
void KSL::Stop3D()
{
	result = m_3dChannel->stop();
	if (result != FMOD_OK) { return; }
}

/// BGM 중단 함수
void KSL::StopBGM()
{
	result = m_bgmChannel->stop();
	if (result != FMOD_OK) { return; }
	m_isBGMPlaying = false;
}



/// 지정한 채널을 중단
void KSL::StopChannel(Channel* channel)
{
	result = channel->stop();
	if (result != FMOD_OK) { return; }
	if (channel == m_bgmChannel)
		m_isBGMPlaying = false;
}

/// BGM 일시정지 함수
void KSL::PauseBGM()
{
	if (m_bgmChannel)
	{
		if (m_isBGMPaused)
		{
			m_bgmChannel->setPaused(false);		// 일시정지 해제
			m_isBGMPaused = false;
		}
		else
		{
			m_bgmChannel->setPaused(true);		// 일시정지
			m_isBGMPaused = true;
		}
	}
}

/// SFX 재생 함수
void KSL::PlaySFX(eSOUNDKIND sound)
{
	result = m_system->playSound(m_sounds[static_cast<int>(sound)], m_sfxChannelGroup, false, &m_sfxChannel);
	m_sfxChannel->setVolume(m_fVolume);
	if (result != FMOD_OK) { return; }
}

/// SFX 중단 함수
void KSL::StopSFX()
{
	result = m_sfxChannel->stop();
	if (result != FMOD_OK) { return; }
}

void KSL::PlaySFXR(eSOUNDKIND sound)
{
	result = m_system->playSound(m_sounds[static_cast<int>(sound)], m_sfxChannelGroup, false, &m_sfxRChannel);
	m_sfxRChannel->setVolume(m_fVolume);
	if (result != FMOD_OK) { return; }
}


//void KSL::PlayDoor1(eSOUNDKIND sound)
//{
//	result = m_system->playSound(m_sounds[static_cast<int>(sound)], m_3dChannelGroup, false, &m_door1Channel);
//	m_door1Channel->setVolume(m_fVolume);
//	result = m_door1Channel->set3DAttributes(&pos, &vel);
//	if (result != FMOD_OK) { return; }
//}
//
//
//
//void KSL::PlayDoor2(eSOUNDKIND sound)
//{
//	result = m_system->playSound(m_sounds[static_cast<int>(sound)], m_3dChannelGroup, false, &m_door2Channel);
//	m_door2Channel->setVolume(m_fVolume);
//	result = m_door2Channel->set3DAttributes(&pos, &vel);
//	if (result != FMOD_OK) { return; }
//}
//
//void KSL::PlayDoor3(eSOUNDKIND sound)
//{
//	result = m_system->playSound(m_sounds[static_cast<int>(sound)], m_3dChannelGroup, false, &m_door3Channel);
//	m_door3Channel->setVolume(m_fVolume);
//	result = m_door3Channel->set3DAttributes(&pos, &vel);
//	if (result != FMOD_OK) { return; }
//}
//
//void KSL::PlayDoor4(eSOUNDKIND sound)
//{
//	result = m_system->playSound(m_sounds[static_cast<int>(sound)], m_3dChannelGroup, false, &m_door4Channel);
//	m_door4Channel->setVolume(m_fVolume);
//	result = m_door4Channel->set3DAttributes(&pos, &vel);
//	if (result != FMOD_OK) { return; }
//}
//
//void KSL::PlayDoor5(eSOUNDKIND sound)
//{
//	result = m_system->playSound(m_sounds[static_cast<int>(sound)], m_3dChannelGroup, false, &m_door5Channel);
//	m_door5Channel->setVolume(m_fVolume);
//	result = m_door5Channel->set3DAttributes(&pos, &vel);
//	if (result != FMOD_OK) { return; }
//}
//
//void KSL::PlayDoor6(eSOUNDKIND sound)
//{
//	result = m_system->playSound(m_sounds[static_cast<int>(sound)], m_3dChannelGroup, false, &m_door6Channel);
//	m_door6Channel->setVolume(m_fVolume);
//	result = m_door6Channel->set3DAttributes(&pos, &vel);
//	if (result != FMOD_OK) { return; }
//}
//
//void KSL::PlayDoor7(eSOUNDKIND sound)
//{
//	result = m_system->playSound(m_sounds[static_cast<int>(sound)], m_3dChannelGroup, false, &m_door7Channel);
//	m_door7Channel->setVolume(m_fVolume);
//	result = m_door7Channel->set3DAttributes(&pos, &vel);
//	if (result != FMOD_OK) { return; }
//}
//
//void KSL::PlayDoor8(eSOUNDKIND sound)
//{
//	result = m_system->playSound(m_sounds[static_cast<int>(sound)], m_3dChannelGroup, false, &m_door8Channel);
//	m_door8Channel->setVolume(m_fVolume);
//	result = m_door8Channel->set3DAttributes(&pos, &vel);
//	if (result != FMOD_OK) { return; }
//}
//
//void KSL::PlayDoor9(eSOUNDKIND sound)
//{
//	result = m_system->playSound(m_sounds[static_cast<int>(sound)], m_3dChannelGroup, false, &m_door9Channel);
//	m_door9Channel->setVolume(m_fVolume);
//	result = m_door9Channel->set3DAttributes(&pos, &vel);
//	if (result != FMOD_OK) { return; }
//}
//
//void KSL::PlayDoor10(eSOUNDKIND sound)
//{
//	result = m_system->playSound(m_sounds[static_cast<int>(sound)], m_3dChannelGroup, false, &m_door10Channel);
//	m_door10Channel->setVolume(m_fVolume);
//	result = m_door10Channel->set3DAttributes(&pos, &vel);
//	if (result != FMOD_OK) { return; }
//}
//
/// 노력했지만 안된다
//void KSL::PlayDoor(int idx, eSOUNDKIND sound)
//{
//	if (idx < 1 || idx > 10) {
//		// 유효하지 않은 doorIndex 처리
//		return;
//	}
//
//	FMOD::Channel* doorChannel = nullptr;
//	switch (idx) {
//	case 1:
//		doorChannel = m_door1Channel;
//		break;
//	case 2:
//		doorChannel = m_door2Channel;
//		break;
//	case 3:
//		doorChannel = m_door1Channel;
//		break;
//	case 4:
//		doorChannel = m_door2Channel;
//		break;
//	case 5:
//		doorChannel = m_door1Channel;
//		break;
//	case 6:
//		doorChannel = m_door2Channel;
//		break;
//	case 7:
//		doorChannel = m_door1Channel;
//		break;
//	case 8:
//		doorChannel = m_door2Channel;
//		break;
//	case 9:
//		doorChannel = m_door2Channel;
//		break;
//	case 10:
//		doorChannel = m_door10Channel;
//		break;
//	default:
//		return;
//	}
//
//	result = m_system->playSound(m_sounds[static_cast<int>(sound)], m_3dChannelGroup, false, &doorChannel);
//	if (result != FMOD_OK) { return; }
//
//	doorChannel->setVolume(m_fVolume);
//	result = doorChannel->set3DAttributes(&pos, &vel);
//	if (result != FMOD_OK) { return; }
//}

void KSL::PlayDemon()
{
	result = m_system->playSound(GetSound("09.Summon_demon.wav"), m_3dChannelGroup, false, &m_demonChannel);
	m_demonChannel->setVolume(m_fVolume);
	result = m_demonChannel->set3DAttributes(&pos, &vel);
	if (result != FMOD_OK) { return; }
}

/// 사운드 포인터를 인자로 받아 그 사운드를 재생하는 함수
/// 사운드 데이터 맵을 찾아서 같은 이름의 데이터의 enum class의 사운드를 재생한다
void KSL::PlaybackBGM(Sound* sound)
{
	for (const auto& e : m_soundMap)
	{
		if (e.second.pSound == sound)
		{
			PlayBGM(e.first);
			return;
		}
	}
	return;
}

/// 사운드 포인터를 인자로 받아서 사운드를 재생하는 함수2
/// 얘는 직빵으로 소리를 재생한다
void KSL::PlayBGM2(Sound* sound)
{
	result = m_system->playSound(sound, m_bgmChannelGroup, false, &m_bgmChannel);
	if (result != FMOD_OK)
	{
		return;
	}
	m_bgmChannel->setVolume(m_bVolume);
}

void KSL::PlaybackBGMC(Sound* sound)
{
	for (const auto& e : m_soundMap)
	{
		if (e.second.pSound == sound)
		{
			PlayBGMC(e.first);
			return;
		}
	}
	return;
}

void KSL::PlayBGMC2(Sound* sound)
{
	result = m_system->playSound(sound, m_bgmChannelGroup, false, &m_bgmCChannel);
	if (result != FMOD_OK)
	{
		return;
	}
	m_bgmCChannel->setVolume(1.0f);
}

void KSL::PlaybackSFX(Sound* sound)
{
	for (const auto& e : m_soundMap)
	{
		if (e.second.pSound == sound)
		{
			PlaySFX(e.first);
			return;
		}
	}
	return;
}

void KSL::PlaySFX2(Sound* sound)
{
	result = m_system->playSound(sound, m_sfxChannelGroup, false, &m_sfxChannel);
	if (result != FMOD_OK)
	{
		return;
	}
	m_sfxChannel->setVolume(m_fVolume);

}

void KSL::PlaybackSFXR(Sound* sound)
{
	for (const auto& e : m_soundMap)
	{
		if (e.second.pSound == sound)
		{
			PlaySFXR(e.first);
			return;
		}
	}
	return;
}

void KSL::PlaySFXR2(Sound* sound)
{
	result = m_system->playSound(sound, m_sfxChannelGroup, false, &m_sfxRChannel);
	if (result != FMOD_OK)
	{
		return;
	}
	m_sfxRChannel->setVolume(m_fVolume);
}

void KSL::Playback3D(Sound* sound)
{
	for (const auto& e : m_soundMap)
	{
		if (e.second.pSound == sound)
		{
			Play3D(e.first);
			return;
		}
	}
	return;
}

void KSL::Play3D2(Sound* sound)
{
	result = m_system->playSound(sound, m_3dChannelGroup, false, &m_3dChannel);
	if (result != FMOD_OK)
	{
		return;
	}
	result = m_3dChannel->set3DAttributes(&pos, &vel);
	m_sfxChannel->setVolume(m_fVolume);
}

void KSL::PlayBlind(eSOUNDKIND sound)
{
	result = m_system->playSound(m_sounds[static_cast<int>(sound)], m_enemyChannelGroup, false, &m_BlindChannel);
	m_BlindChannel->setVolume(m_aVolume);
	if (result != FMOD_OK) { return; }
}

void KSL::PlayBlind2(Sound* sound)
{
	result = m_system->playSound(sound, m_enemyChannelGroup, false, &m_BlindChannel);
	if (result != FMOD_OK)
	{
		return;
	}
	result = m_3dChannel->set3DAttributes(&pos, &vel);
	m_BlindChannel->setVolume(m_aVolume);
}

void KSL::PlayJane(eSOUNDKIND sound)
{
	result = m_system->playSound(m_sounds[static_cast<int>(sound)], m_enemyChannelGroup, false, &m_JaneChannel);
	m_JaneChannel->setVolume(m_aVolume);
	if (result != FMOD_OK) { return; }
}

void KSL::PlayJane2(Sound* sound)
{
	result = m_system->playSound(sound, m_enemyChannelGroup, false, &m_JaneChannel);
	if (result != FMOD_OK)
	{
		return;
	}
	result = m_3dChannel->set3DAttributes(&pos, &vel);
	m_JaneChannel->setVolume(m_aVolume);
}


void KSL::PlayChaser(eSOUNDKIND sound)
{
	result = m_system->playSound(m_sounds[static_cast<int>(sound)], m_enemyChannelGroup, false, &m_ChaserChannel);
	m_ChaserChannel->setVolume(m_aVolume);
	if (result != FMOD_OK) { return; }
}

void KSL::PlayChaser2(Sound* sound)
{
	result = m_system->playSound(sound, m_enemyChannelGroup, false, &m_ChaserChannel);
	if (result != FMOD_OK)
	{
		return;
	}
	result = m_3dChannel->set3DAttributes(&pos, &vel);
	m_ChaserChannel->setVolume(m_aVolume);
}

void KSL::PlayGhost(eSOUNDKIND sound)
{
	result = m_system->playSound(m_sounds[static_cast<int>(sound)], m_enemyChannelGroup, false, &m_GhostChannel);
	m_GhostChannel->setVolume(m_aVolume);
	if (result != FMOD_OK) { return; }
}

void KSL::PlayGhost2(Sound* sound)
{
	result = m_system->playSound(sound, m_enemyChannelGroup, false, &m_GhostChannel);
	if (result != FMOD_OK)
	{
		return;
	}
	result = m_3dChannel->set3DAttributes(&pos, &vel);
	m_GhostChannel->setVolume(m_aVolume);
}

/// 혹시 모르니까, 파일 이름으로 재생하는 play함수도 만들어놓음
void KSL::PlayName(string filename)
{
	for (const auto& e : m_soundMap)
	{
		if (e.second.filename == filename)
		{
			PlaySFX(e.first);
			return;
		}
	}
	return;
}

/// 이러저런 이유로 발소리 함수와 채널을 분리하는 게 낫겠다
void KSL::PlayerWalk()
{
	// 만약 뛰는 중이었다면
	/*result = m_moveChannel->stop();
	if (result != FMOD_OK) { return; }*/

	result = m_system->playSound(m_sounds[static_cast<int>(eSOUNDKIND::lPlayerWalk)],
		m_sfxChannelGroup, false, &m_moveChannel);
	if (result != FMOD_OK)
	{
		return;
	}
}

void KSL::PlayerRun()
{
	// 만약 걷는 중이었다면
	/*result = m_moveChannel->stop();
	if (result != FMOD_OK) { return; }*/

	result = m_system->playSound(m_sounds[static_cast<int>(eSOUNDKIND::lPlayerRun)],
		m_sfxChannelGroup, false, &m_moveChannel);
	if (result != FMOD_OK)
	{
		return;
	}
}

/// 플레이어가 걷거나 뛰는걸 중단
void KSL::StopMove()
{
	result = m_moveChannel->stop();
	if (result != FMOD_OK) { return; }
}


// 여기저기서 자주 써먹을 것 같은 플레이 사운드 함수
// 재생할 사운드와 채널을 설정하면 거기서 바로 재생을 해줌
/// CreateChannel과 같이 쓰는게 좋다.
void KSL::PlaySound(Sound* sound, Channel** channel)
{
	result = m_system->playSound(sound, m_sfxChannelGroup, false, channel);
	if (result != FMOD_OK)
	{
		return;
	}
	result = (*channel)->set3DAttributes(&pos, &vel);
}

void KSL::PlaySound(Sound* sound)
{
	int count = 0;
	for (const auto& e : m_soundMap)
	{
		if (e.second.pSound == sound)
		{
			Channel* channel = GetChannel(count);
			result = m_system->playSound(sound, m_sfxChannelGroup, false, &channel);
		}
		count++;
	}
}

/// 지정한 채널을 중단
void KSL::StopSound(Channel* channel)
{
	result = channel->stop();
	if (result != FMOD_OK) { return; }
}

/// 리버브 함수
/// 일단 만들어놓음
void KSL::Reverb()
{
	// 리버브 객체를 생성하고
	result = m_system->createReverb3D(&m_reverb);
	FMOD_REVERB_PROPERTIES prop = FMOD_PRESET_CONCERTHALL;
	result = m_reverb->setProperties(&prop);
	if (result != FMOD_OK)
		return;

	// 3D 옵션을 설정함
	float mindist = 10.0f;		// min 내부라면 리버브를 감쇠없이 듣는다
	float maxdist = 20.0f;		// max 와 min사이라면 리버브를 거리에 따라 보간되어 듣는다
	result = m_reverb->set3DAttributes(&pos, mindist, maxdist);
	if (result != FMOD_OK)
		return;
}

/// 채널에 리버브를 추가
/// 리버브를 전역적으로 추가할 수는 없으니까
/// 리버브를 넣을거면 Play 후에 채널에 넣어줘야함
void KSL::AddReverb(Channel* channel)
{
	result = m_system->createDSPByType(FMOD_DSP_TYPE_SFXREVERB, &m_reverbDSP);
	if (result != FMOD_OK)
		return;

	// 리버브 수치 조정 (드라이)
	float param = 0.7f;

	m_reverbDSP->setParameterFloat(FMOD_DSP_SFXREVERB_DRYLEVEL, param);
	m_reverbDSP->setParameterFloat(FMOD_DSP_SFXREVERB_WETLEVEL, 1 - param);

	channel->addDSP(0, m_reverbDSP);
}

/// 채널에 리버브를 수치만큼 넣어주는 함수
void KSL::AddReverbParam(Channel* channel, float val)
{
	result = m_system->createDSPByType(FMOD_DSP_TYPE_SFXREVERB, &m_reverbDSP);
	if (result != FMOD_OK)
		return;

	// 리버브 수치 조정 (val만큼 리버브)
	m_reverbDSP->setParameterFloat(FMOD_DSP_SFXREVERB_DRYLEVEL, 1 - val);
	m_reverbDSP->setParameterFloat(FMOD_DSP_SFXREVERB_WETLEVEL, val);

	result = channel->addDSP(0, m_reverbDSP);
	if (result != FMOD_OK)
		return;
}

/// 채널에서 리버브를 제거
/// 인게임에서 로비로 돌아갈 때 제거
void KSL::RemoveReverb(Channel* channel)
{
	if (channel && m_reverbDSP)
	{
		channel->removeDSP(m_reverbDSP);
	}
}

void KSL::SetPriority(Channel* channel, float val)
{
	channel->setPriority(val);
}


/// 마스터 볼륨 조절 함수
/// 파라미터를 조정하는 데 사용되며, 실제 볼륨은 마스터볼륨 * 각채널 볼륨으로 재생됩니다
void KSL::AdjustMasterVolume(float amount)
{
	float& targetVolume = m_mVolume;

	targetVolume = amount;
	if (targetVolume > 1.0f) { targetVolume = 1.0f; }
	if (targetVolume < 0.0f) { targetVolume = 0.0f; }

	m_bChannelVolume = m_bVolume * m_mVolume;
	m_fChannelVolume = m_fVolume * m_mVolume;

	m_bgmChannel->setVolume(m_bChannelVolume);
	m_sfxChannel->setVolume(m_fChannelVolume);
}

/// 채널 볼륨 조절 함수
/// 파라미터를 조정하는 데 사용되며, 실제 볼륨은 마스터볼륨 * 각채널 볼륨으로 재생됩니다
void KSL::AdjustChannelVolume(eChannelType channelType, float amount)
{
	float& targetVolume = (channelType == eChannelType::BGM) ? m_bVolume : m_fVolume;

	targetVolume = amount;
	if (targetVolume > 1.0f) { targetVolume = 1.0f; }
	if (targetVolume < 0.0f) { targetVolume = 0.0f; }

	m_bChannelVolume = m_bVolume * m_mVolume;
	m_fChannelVolume = m_fVolume * m_mVolume;

	m_bgmChannel->setVolume(m_bChannelVolume);
	m_sfxChannel->setVolume(m_fChannelVolume);
}

/// 직접 볼륨 조정 함수
/// 특정 채널의 볼륨을 설정합니다. 이벤트 용도로 사용합니다.
void KSL::SetVolumeDirectly(Channel * channel, float amount)
{
	channel->setVolume(amount);
}

/// 파일 이름으로 받은 사운드의 
/// 3D 공간에서의 min거리와 max거리를 설정합니다.
/// min과 max 사이에서 선형-제곱 감쇠하며, max 밖에서는 무음이 됩니다.
void KSL::Set3DMinMaxDistance(string filename, float min, float max)
{
	GetSound(filename)->set3DMinMaxDistance(min, max);
}

void KSL::Set3DMinMaxDistance(eSOUNDKIND sound, float min, float max)
{
	GetSound(sound)->set3DMinMaxDistance(min, max);
}

void KSL::Set3DMinMaxDistance(Sound* sound, float min, float max)
{
	for (auto e : m_soundMap)
	{
		if (e.second.pSound == sound)
		{
			GetSound(e.first)->set3DMinMaxDistance(min, max);
		}
	}
}

/// 파일 이름을 받아 사운드 포인터를 반환하는 함수
/// 해시 맵에 저장된 파일명과 같은 enum class의 사운드 포인터를 반환합니다.
FMOD::Sound* KSL::GetSound(string filename)
{
	for (const auto& e : m_soundMap)
	{
		if (e.second.filename == filename)
		{
			return m_sounds[static_cast<int>(e.first)];
		}
	}
	return nullptr;
}

/// getSound를 enum으로도 하고싶다
FMOD::Sound* KSL::GetSound(eSOUNDKIND sound)
{
	for (const auto& e : m_soundMap)
	{
		if (e.first == sound)
		{
			return m_sounds[static_cast<int>(e.first)];
		}
	}
	return nullptr;
}

/// 해시 맵에 enum class에 저장된 파일명을 저장합니다.
/// 이 함수는 사운드를 Load할 때 같이 작동해야 합니다.
void KSL::SetSoundData(eSOUNDKIND soundkind, string filename, Sound* pSound)
{
	m_soundMap.insert({ soundkind, {filename, pSound} });
}

void KSL::PushDynamicSound(Sound*& sound)
{
	m_dSounds.push_back(sound);
}


// 리스너를 업데이트한다
// 이 버전은 사운드 소스는 움직이지 않고 리스너가 움직이는 구현
//void KSL::UpdateListener()
//{
//	static float t = 0;
//	static FMOD_VECTOR lastpos = { 0.0f, 0.0f, 0.0f };
//
//	if (listenerflag)
//	{
//		// left right 핑퐁
//		/*listenerpos.x = (float)sin(t * 0.000005f) * 1.0f * DISTANCEFACTOR;
//		listenerpos.z = (float)sin(t * 0.00001f) * 1.0f * DISTANCEFACTOR;*/
//		//PrintLPos();
//	}
//
//	// vel은 마지막 프레임에서 얼마나 멀리 움직였는가,
//	// 그리고 시간을 초 단위로 보정한다 (m/s)
//	vel.x = (listenerpos.x - lastpos.x) * (1000 / INTERFACE_UPDATETIME);
//	vel.y = (listenerpos.y - lastpos.y) * (1000 / INTERFACE_UPDATETIME);
//	vel.z = (listenerpos.z - lastpos.z) * (1000 / INTERFACE_UPDATETIME);
//
//	lastpos = listenerpos;
//
//	result = m_system->set3DListenerAttributes(0, &listenerpos, &vel, &forward, &up);
//
//	t += (30 * (1.0f / (float)INTERFACE_UPDATETIME));    // t is just a time value .. it increments in 30m/s steps in this example
//
//	if (t >= 16777216.0f)
//	{
//		t = 0;
//	}
//
//	//m_system->update();
//}

/// 진짜 이 버전을 사용한다
/// 이건 리스너를 업데이트 하지만 리스너는 가만히 있기만 함
/// 사실 아무것도 안하는 거 아닐까
void KSL::UpdateListener()
{
	{
		static float t = 0;
		static FMOD_VECTOR lastpos = { 0.0f, 0.0f, 0.0f };
		FMOD_VECTOR forward = { 0.0f, 0.0f, 1.0f };
		FMOD_VECTOR up = { 0.0f, 1.0f, 0.0f };
		FMOD_VECTOR vel;


		// ********* NOTE ******* READ NEXT COMMENT!!!!!
		// vel = how far we moved last FRAME (m/f), then time compensate it to SECONDS (m/s).
		vel.x = (listenerpos.x - lastpos.x) * (1000 / INTERFACE_UPDATETIME);
		vel.y = (listenerpos.y - lastpos.y) * (1000 / INTERFACE_UPDATETIME);
		vel.z = (listenerpos.z - lastpos.z) * (1000 / INTERFACE_UPDATETIME);

		// store pos for next time
		lastpos = listenerpos;

		result = m_system->set3DListenerAttributes(0, &listenerpos, &vel, &forward, &up);
		if (result != FMOD_OK)
			return;

		//t += (30 * (1.0f / (float)INTERFACE_UPDATETIME));    // t is just a time value .. it increments in 30m/s steps in this example
	}

	result = m_system->update();
}

// 이건 리스너는 가만히 있고 소스가 움직일 때의 구현
void KSL::UpdatePos()
{
	static float t = 0;
	static FMOD_VECTOR lastpos = { 0.0f, 0.0f, 0.0f };

	// pos가 움직인다는 가정
	// 나중에는 날려야됨
	if (listenerflag)
	{
		// left right 핑퐁
		pos.x = (float)sin(t * 0.000005f) * 1.0f * DISTANCEFACTOR;
		// front back 핑퐁
		pos.z = (float)sin(t * 0.000005f) * 3.0f * DISTANCEFACTOR;
		PrintPos();
	}

	// vel은 마지막 프레임에서 얼마나 멀리 움직였는가,
	// 그리고 시간을 초 단위로 보정한다 (m/s)
	vel.x = (pos.x - lastpos.x) * (1000 / INTERFACE_UPDATETIME);
	vel.y = (pos.y - lastpos.y) * (1000 / INTERFACE_UPDATETIME);
	vel.z = (pos.z - lastpos.z) * (1000 / INTERFACE_UPDATETIME);


	lastpos = pos;

	// 리스너 속성 설정

	result = m_system->set3DListenerAttributes(0, &pos, &vel, &forward, &up);
	if (result != FMOD_OK)
	{
		// Handle error
		return;
	}

	t += (30 * (1.0f / (float)INTERFACE_UPDATETIME));    // t is just a time value .. it increments in 30m/s steps in this example

	if (t >= 16777216.0f)
	{
		t = 0;
	}

	m_system->update();
}

/// 이 버전으로 사용한다
// 인자로 Vector3의 세 값을 받았을 경우
// pos값에 받은 인자를 넣어주며 업데이트
// 리스너는 가만히 있고, 플레이어를 기준으로 pos가 움직인다는 구현
void KSL::UpdatePos(float x, float y, float z)
{
	static FMOD_VECTOR lastpos = { 0.0f, 0.0f, 0.0f };

	// pos에 값 넣기
	pos.x = x;
	pos.y = y;
	pos.z = z;
	PrintPos();

	// vel은 마지막 프레임에서 얼마나 멀리 움직였는가,
	// 그리고 시간을 초 단위로 보정한다 (m/s)
	vel.x = (pos.x - lastpos.x) * (1000 / INTERFACE_UPDATETIME);
	vel.y = (pos.y - lastpos.y) * (1000 / INTERFACE_UPDATETIME);
	vel.z = (pos.z - lastpos.z) * (1000 / INTERFACE_UPDATETIME);

	lastpos = pos;

	// 리스너 속성 설정

	// 리스너의 pos인자에 음원의 위치를 넣으면 그에 맞춰 3D 사운드가 구현되지 않을까
	result = m_system->set3DListenerAttributes(0, &pos, &vel, &forward, &up);
	if (result != FMOD_OK)
	{
		// Handle error
		return;
	}

	m_system->update();
}



void KSL::PrintLPos()
{
	static int printCount = 0;
	constexpr int printFrequency = 100; // 출력 주기 설정

	if (printCount % printFrequency == 0) {
		cout << "x : " << listenerpos.x << " " << "z : " << listenerpos.z << endl;
	}
	printCount++;
}

void KSL::PrintPos()
{
	static int printCount = 0;
	constexpr int printFrequency = 100; // 출력 주기 설정

	if (printCount % printFrequency == 0) {
		cout << "pos x : " << pos.x << " " << "pos z : " << pos.z << endl;
	}
	printCount++;
}

FMOD_VECTOR KSL::PosIsMove()
{
	static float t = 0;
	FMOD_VECTOR temp = { 0.0f, 0.0f, 0.0f };

	// left right 핑퐁
	temp.x = (float)sin(t * 0.00005f) * 1.0f * DISTANCEFACTOR;
	// front back 핑퐁
	temp.z = (float)sin(t * 0.00005f) * 3.0f * DISTANCEFACTOR;

	t += (30 * (1.0f / (float)INTERFACE_UPDATETIME));    // t is just a time value .. it increments in 30m/s steps in this example

	if (t >= 16777216.0f)
	{
		t = 0;
	}

	cout << "pos x : " << temp.x << " " << "pos z : " << temp.z << endl;

	return temp;
}

FMOD_VECTOR KSL::PosIsMove2()
{
	static float t = 0;
	FMOD_VECTOR temp = { 0.0f, 0.0f, 0.0f };

	// left right 핑퐁
	temp.x = (float)sin(t * 0.0001f) * 3.0f * DISTANCEFACTOR;

	t += (30 * (1.0f / (float)INTERFACE_UPDATETIME));    // t is just a time value .. it increments in 30m/s steps in this example

	if (t >= 16777216.0f)
	{
		t = 0;
	}

	cout << "pos x : " << temp.x << " " << "pos z : " << temp.z << endl;

	return temp;
}

FMOD::Channel* KSL::GetChannel(int index)
{
	return m_channels[index];
}

FMOD::Channel* KSL::GetBGMChannel()
{
	return m_bgmChannel;
}

FMOD::Channel* KSL::GetBGMCChannel()
{
	return m_bgmCChannel;
}

FMOD::Channel* KSL::GetSFXChannel()
{
	return m_sfxChannel;
}

FMOD::Channel* KSL::GetSFXRChannel()
{
	return m_sfxRChannel;
}

FMOD::Channel* KSL::Get3DChannel()
{
	return m_3dChannel;
}

FMOD::Channel* KSL::GetMoveChannel()
{
	return m_moveChannel;
}

FMOD::Channel* KSL::GetUIChannel()
{
	return m_uiChannel;
}

#define PlayDoor(n) \
void KSL::PlayDoor##n##(eSOUNDKIND sound) \
{ \
	result = m_system->playSound(m_sounds[static_cast<int>(sound)], m_3dChannelGroup, false, &m_doorChannel[n]); \
	m_doorChannel[n]->setVolume(m_fVolume); \
	result = m_doorChannel[n]->set3DAttributes(&pos, &vel); \
	if (result != FMOD_OK) { return; } \
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

#define GetDoorChannel(n) \
FMOD::Channel* KSL::GetDoor##n##Channel() \
{ \
    return m_doorChannel[n]; \
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

//FMOD::Channel* KSL::GetDoor1Channel()
//{
//	return m_door1Channel;
//}
//
//FMOD::Channel* KSL::GetDoor2Channel()
//{
//	return m_door2Channel;
//}
//
//FMOD::Channel* KSL::GetDoor3Channel()
//{
//	return m_door3Channel;
//}
//
//FMOD::Channel* KSL::GetDoor4Channel()
//{
//	return m_door4Channel;
//}
//
//FMOD::Channel* KSL::GetDoor5Channel()
//{
//	return m_door5Channel;
//}
//
//FMOD::Channel* KSL::GetDoor6Channel()
//{
//	return m_door6Channel;
//}
//
//FMOD::Channel* KSL::GetDoor7Channel()
//{
//	return m_door7Channel;
//}
//
//FMOD::Channel* KSL::GetDoor8Channel()
//{
//	return m_door8Channel;
//}
//
//FMOD::Channel* KSL::GetDoor9Channel()
//{
//	return m_door9Channel;
//}
//
//FMOD::Channel* KSL::GetDoor10Channel()
//{
//	return m_door10Channel;
//}

FMOD::Channel* KSL::GetDemonChannel()
{
	return m_demonChannel;
}

FMOD::Channel* KSL::GetBlindChannel()
{
	return m_BlindChannel;
}

FMOD::Channel* KSL::GetJaneChannel()
{
	return m_JaneChannel;
}

FMOD::Channel* KSL::GetChaserChannel()
{
	return m_ChaserChannel;
}

FMOD::Channel* KSL::GetGhostChannel()
{
	return m_GhostChannel;
}

