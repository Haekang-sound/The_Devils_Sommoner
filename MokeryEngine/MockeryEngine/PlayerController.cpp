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

	hCursor = LoadCursor(NULL, IDC_HAND); // ���⼭ IDC_HAND�� �հ��� ����� Ŀ���� ��Ÿ���ϴ�. �ʿ信 ���� �ٸ� Ŀ���� ������ �� �ֽ��ϴ�.

	// Set the cursor
	SetCursor(hCursor);
	ShowCursor(false);


}

PlayerController::~PlayerController()
{

}

void PlayerController::Start()
{
	// ��Ʈ�ѷ��� ���Ե� ������Ʈ���� transform�� �����´�.
	m_transform = GetOwner()->GetComponent<Transform>();

}


void PlayerController::FixedUpdate(float dTime)
{

}

void PlayerController::Update(float dTime)
{
	//std::cout << dTime << std::endl;
	m_transform->SetDirection();
	// �����ۼ� ���� �ʿ�
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
			/// �޸� �� (shift Ű�� ������ ��)
			/// �̼��� �ι�� �Ǿ��� ���� �Ϸ� ����
			if (!isRun && m_moveSpeed > 1.5f)
			{
				SoundManager::GetInstance().StopSound(SoundManager::GetInstance().GetMoveChannel());
				SoundManager::GetInstance().PlayerRun();
				isRun = true;
				isWalk = false;
			}
			/// ���� ��
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
		/// ������ ���� ��
		else
		{
			SoundManager::GetInstance().StopSound(SoundManager::GetInstance().GetMoveChannel());
			isWalk = false;
			isRun = false;
		}

		// player�� state�� ����, ���Ӱ� maxspeed�� �ٲ�����
		//m_moveSpeed = 6.f;
		//maxSpeed = 0.005f;



		// z�� �̵�
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
		// 		// ���� ����
		// 		if (m_inputmanager->m_Keyboard.IsKeydown(DirectX::Keyboard::Keys::Space))
		// 		{
		// 			m_transform->SetLocalPosition({ m_transform->GetLocalPosition().x, m_transform->GetLocalPosition().y + 5,m_transform->GetLocalPosition().z, });
		// 		}
		// 		if (m_inputmanager->m_Keyboard.IsKeyUp(DirectX::Keyboard::Keys::Space))
		// 		{
		// 			m_transform->SetLocalPosition({ m_transform->GetLocalPosition().x, m_transform->GetLocalPosition().y - 5,m_transform->GetLocalPosition().z, });
		// 		}

				// ������
// 		if (m_inputmanager->m_Keyboard.IsKeyHold('R'))
// 		{
// 			m_transform->ScaleX(m_moveSpeed * dTime);
// 		}
// 		if (m_inputmanager->m_Keyboard.IsKeyHold('T'))
// 		{
// 			m_transform->ScaleX(-m_moveSpeed * dTime);
// 		}

		// ����ġ
		if (m_inputmanager->m_Keyboard.IsKeyHold('X'))
		{
			m_transform->GoBack();
		}
		// ����ġ
// 		if (m_inputmanager->m_Keyboard.IsKeyHold('Z'))
// 		{
// 			m_transform->GoBackPos();
// 		}
#pragma endregion OHKctrl


		// ���콺 �̵��� ���� ������ȭ
		if (m_inputmanager->m_Mouse.isMove)
		{
			m_transform->Roll(m_inputmanager->m_Mouse.moveX * rotSpeed * dTime);
			m_transform->Pitch(m_inputmanager->m_Mouse.moveY * rotSpeed * dTime);

			// ����� ���� �������� ��ġ��
			if (height % 2)
			{
				height += 1;
			}
			SetCursorPos(xPosition + width / 2, yPosition + height / 2);
			m_inputmanager->m_Mouse.isMouseCenter = true;
		}
	}

	// ��Ʈ�ѷ� �۵� ���θ� �����Ѵ�
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