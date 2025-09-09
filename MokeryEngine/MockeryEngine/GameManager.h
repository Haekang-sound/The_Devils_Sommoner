#pragma once
#include "SingleTon.h"


class GameObject;
class Timer;


// 싱글턴으로 만든 게임매니저
class GameManager : public SingleTon<GameManager>
{
public:
	void Init();
	void Update();
	void Finalize();

	void SetPlayerObject(GameObject* _player) { m_player = _player; }
	GameObject* GetPlayerObject() { return m_player; }

	void AddAltarObject(GameObject* _altar) { m_altar.push_back(_altar); }
	std::vector<GameObject*> GetAltarObject() { return m_altar; }

	void AddHeartChest(GameObject* heartChest) { m_heartChest.push_back(heartChest); }
	std::vector<GameObject*> GetHeartChest() { return m_heartChest; }

	void SetBlindObject(GameObject* enemy) { m_blind = enemy; }
	GameObject* GetBlindObject() { return m_blind; }

	void SetJaneDObject(GameObject* enemy) { m_janeD = enemy; }
	GameObject* GetJaneDObject() { return m_janeD; }

	void SetChaserObject(GameObject* enemy) { m_chaser = enemy; }
	GameObject* GetChaserObject() { return m_chaser; }

	void SetGhostObject(GameObject* enemy) { m_ghost = enemy; }
	GameObject* GetGhostObject() { return m_ghost; }

	void SetTimerComponent(Timer* timer) { m_timer = timer; }
	Timer* GetTimerComponent() { return m_timer; }

	void SetNextAltar(int count);

private:
	GameObject* m_player;
	GameObject* m_blind;
	GameObject* m_janeD;
	GameObject* m_chaser;
	GameObject* m_ghost;

	std::vector<GameObject*> m_altar;
	std::vector<GameObject*> m_heartChest;

	GameObject* m_currentAltar;

	Timer* m_timer;
	
	int m_altarCount;

public:
	// 목적지 재단을 바꿔주고 심장의 목적지도 바꿔준다.
	void SetCurrentAltarObject(GameObject* altar);
	GameObject* GetCurrentAltarObject() { return m_currentAltar; }

	void SetHeartObject(GameObject* _heart) { m_heart = _heart; }
	GameObject* GetHeartObject() { return m_heart; }

private:
	// 심장을 알고 있게 한다. 심장을 재단에 가져갈때마다 목적지를 바꿔줘야 한다.
	GameObject* m_heart;
};

