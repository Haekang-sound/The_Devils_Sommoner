#pragma once

#pragma region RendererDef
using UINT = unsigned int;

struct Vector2 { float x{}, y{}; };
struct Vector3 { float x{}, y{}, z{}; };
struct Vector4 { float x{}, y{}, z{}, w{}; };

struct RenderTransform { Vector3 Position, Rotation, Scale; };
struct RenderMatrix44 { Vector4 m1, m2, m3, m4; };

struct Animations
{
	const char* AnimationName;
	UINT Duration;
	// �ִϸ��̼��� ����Ǵ� ��ü�ð�
	double AnimationFullTime = 0;
	// 1�����ӿ� �ɸ��� �ð�
	double TickPerFrame = 0;
};

struct AnimationInfo
{
	// Max Animation Size
	UINT AnimationNum;
	// �ϴ� ũ�� ��´�.
	Animations Animation[100];
};


#pragma endregion