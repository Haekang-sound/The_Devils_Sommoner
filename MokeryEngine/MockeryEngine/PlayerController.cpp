#include "pch.h"
#include "PlayerController.h"

#include "GameObject.h"
#include "InputManager.h"
#include "Transform.h"
#include "PlayerComponent.h"
#include "SoundManager.h"

#include <iostream>

PlayerController::PlayerController()
	: m_transform(nullptr),
	m_inputmanager(nullptr),
	speedX(0.f), speedY(0.f), speedZ(0.f), rotSpeed(0.5f)
{
	m_inputmanager = InputManager::GetInstance();

	hCursor = LoadCursor(NULL, IDC_HAND); // 여기서 IDC_HAND는 손가락 모양의 커서를 나타냅니다. 필요에 따라 다른 커서를 선택할 수 있습니다.

	// Set the cursor
	SetCursor(hCursor);
	ShowCursor(false);


}

PlayerController::~PlayerController()
{

}

void PlayerController::Start()
{
	// 컨트롤러가 포함된 오브젝트에서 transform을 가져온다.
	m_transform = GetOwner()->GetComponent<Transform>();

}


void PlayerController::FixedUpdate(float dTime)
{

}

void PlayerController::Update(float dTime)
{
	//std::cout << dTime << std::endl;
	m_transform->SetDirection();
	// 용준작성 수정 필요
	m_View = SimpleMath::Matrix::CreateLookAt(
		m_transform->GetPosition(), m_transform->GetPosition() + (-m_transform->m_Forward), m_transform->m_UP
	);

	memcpy(&m_RenderView, &m_View, sizeof(SimpleMath::Matrix));

	int width = m_inputmanager->windowRect.right - m_inputmanager->windowRect.left;
	int cwidth = m_inputmanager->clientRect.right - m_inputmanager->clientRect.left;
	int height = m_inputmanager->windowRect.bottom - m_inputmanager->windowRect.top;
	int cheight = m_inputmanager->clientRect.bottom - m_inputmanager->clientRect.top;
	int xPosition = m_inputmanager->windowRect.left;
	int yPosition = m_inputmanager->windowRect.top;

	int menuBarHeight = GetSystemMetrics(SM_CYMENU);
	int borderWidthX = GetSystemMetrics(SM_CXSIZEFRAME);
	int borderWidthY = GetSystemMetrics(SM_CYSIZEFRAME);
#pragma region OHKctrl
	m_moveSpeed = m_pOwner->GetComponent<PlayerComponent>()->GetMoveSpeed();

	
	if (isControl)
	{
		if (m_inputmanager->m_Keyboard.IsKeyHold('W') ||
			m_inputmanager->m_Keyboard.IsKeyHold('S') ||
			m_inputmanager->m_Keyboard.IsKeyHold('A') ||
			m_inputmanager->m_Keyboard.IsKeyHold('D'))
		{
			/// 달릴 때 (shift 키를 눌렀을 때)
			/// 이속이 두배로 되었을 때도 일로 들어옴
			if (!isRun && m_moveSpeed > 1.5f)
			{
				SoundManager::GetInstance().StopSound(SoundManager::GetInstance().GetMoveChannel());
				SoundManager::GetInstance().PlayerRun();
				isRun = true;
				isWalk = false;
			}
			/// 걸을 때
			else if (m_moveSpeed < 1.5f)
			{
				if (!isWalk)
				{
					SoundManager::GetInstance().StopSound(SoundManager::GetInstance().GetMoveChannel());
					SoundManager::GetInstance().PlayerWalk();
					isWalk = true;
					isRun = false;
				}
			}
		}
		/// 가만히 있을 때
		else
		{
			SoundManager::GetInstance().StopSound(SoundManager::GetInstance().GetMoveChannel());
			isWalk = false;
			isRun = false;
		}

		// player의 state에 따라, 가속과 maxspeed를 바꿔주자
		//m_moveSpeed = 6.f;
		//maxSpeed = 0.005f;



		// z축 이동
		if (m_inputmanager->m_Keyboard.IsKeyHold('S'))
		{
			speedZ = dTime * -m_moveSpeed;
			m_transform->m_MoveSpeed.z = speedZ;
		}
		else if (!m_inputmanager->m_Keyboard.IsKeyHold('W'))
		{
			m_transform->m_MoveSpeed.z = 0.f;
		}

		if (m_inputmanager->m_Keyboard.IsKeyHold('W'))
		{
			speedZ = dTime * m_moveSpeed;
			m_transform->m_MoveSpeed.z = speedZ;
		}
		else if (!m_inputmanager->m_Keyboard.IsKeyHold('S'))
		{
			m_transform->m_MoveSpeed.z = 0.f;
		}

		if (m_inputmanager->m_Keyboard.IsKeyHold('D'))
		{
			speedX = dTime * m_moveSpeed;
			m_transform->m_MoveSpeed.x = speedX;
		}
		else if (!m_inputmanager->m_Keyboard.IsKeyHold('A'))
		{
			m_transform->m_MoveSpeed.x = 0.f;
		}

		if (m_inputmanager->m_Keyboard.IsKeyHold('A'))
		{
			speedX = dTime * -m_moveSpeed;
			m_transform->m_MoveSpeed.x = speedX;
		}
		else if (!m_inputmanager->m_Keyboard.IsKeyHold('D'))
		{
			m_transform->m_MoveSpeed.x = 0.f;
		}

		// 
		// 		// 간이 점프
		// 		if (m_inputmanager->m_Keyboard.IsKeydown(DirectX::Keyboard::Keys::Space))
		// 		{
		// 			m_transform->SetLocalPosition({ m_transform->GetLocalPosition().x, m_transform->GetLocalPosition().y + 5,m_transform->GetLocalPosition().z, });
		// 		}
		// 		if (m_inputmanager->m_Keyboard.IsKeyUp(DirectX::Keyboard::Keys::Space))
		// 		{
		// 			m_transform->SetLocalPosition({ m_transform->GetLocalPosition().x, m_transform->GetLocalPosition().y - 5,m_transform->GetLocalPosition().z, });
		// 		}

				// 스케일
// 		if (m_inputmanager->m_Keyboard.IsKeyHold('R'))
// 		{
// 			m_transform->ScaleX(m_moveSpeed * dTime);
// 		}
// 		if (m_inputmanager->m_Keyboard.IsKeyHold('T'))
// 		{
// 			m_transform->ScaleX(-m_moveSpeed * dTime);
// 		}

		// 원위치
		if (m_inputmanager->m_Keyboard.IsKeyHold('X'))
		{
			m_transform->GoBack();
		}
		// 원위치
// 		if (m_inputmanager->m_Keyboard.IsKeyHold('Z'))
// 		{
// 			m_transform->GoBackPos();
// 		}
#pragma endregion OHKctrl


		// 마우스 이동의 따른 각도변화
		if (m_inputmanager->m_Mouse.isMove)
		{
			m_transform->Roll(m_inputmanager->m_Mouse.moveX * rotSpeed * dTime);
			m_transform->Pitch(m_inputmanager->m_Mouse.moveY * rotSpeed * dTime);

			// 모니터 상의 절대적인 위치값
			if (height % 2)
			{
				height += 1;
			}
			SetCursorPos(xPosition + width / 2, yPosition + height / 2);
			m_inputmanager->m_Mouse.isMouseCenter = true;
		}
	}

	// 컨트롤러 작동 여부를 결정한다
	if (m_inputmanager->m_Keyboard.IsKeydown('C'))
	{
		isControl = !isControl;
		// Show the cursor
		if (isControl)
		{
			ShowCursor(false);
		}
		else
		{
			ShowCursor(true);
		}
	}
}

void PlayerController::LateUpdate(float dTime)
{
}

void PlayerController::Render()
{
}

void PlayerController::Release()
{
}

void PlayerController::Move(float dTime)
{
	//float velocity = 10.f;

	float speed = 18.f;

	bool isKeyDown = false;
	if (m_inputmanager->m_Keyboard.IsKeyHold('S'))
	{
		m_dir += m_pos.Forward;
		isKeyDown = true;
	}
	if (m_inputmanager->m_Keyboard.IsKeyHold('W'))
	{
		m_dir += m_pos.Forward * -1;
		isKeyDown = true;
	}
	if (m_inputmanager->m_Keyboard.IsKeyHold('A'))
	{
		m_dir += m_pos.Left;
		isKeyDown = true;
	}
	if (m_inputmanager->m_Keyboard.IsKeyHold('D'))
	{
		m_dir += m_pos.Left * -1;
		isKeyDown = true;
	}

	if (isKeyDown)
	{
		m_velocity += speed * dTime;
	}
	else
	{
		m_velocity -= speed * dTime;
	}
	if (m_velocity > 10.f) m_velocity = 10.f;
	if (m_velocity < 0.f) m_velocity = 0.f;

	m_dir.Normalize();

	SimpleMath::Vector3 nextPos = m_transform->GetPosition() + m_dir * m_velocity * dTime;
	m_transform->SetPosition(nextPos);
}