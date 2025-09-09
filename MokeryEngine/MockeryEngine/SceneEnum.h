#pragma once

// 리소스와 오브젝트 
// 생성/소멸 주기를 결정하는 레이어
enum SceneLayer
{
	TITLE = 0,	// Title,
	TEST,		// InGame
};

enum class SceneNumber
{
	Intro,

	Title,

	Test,
	Select,
	Stage01,
	Stage02,
	Stage03,

	Ending
};