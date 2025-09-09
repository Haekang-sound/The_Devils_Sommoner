#pragma once
#include <string>
class AnimationBuilder;

/// <summary>
/// 2024.01.22 - 강규석
/// Animation을 관리하기 위한 리소스이다.
/// 이것들을 조립해서 Animator에서 관리해주려고 한다.
/// </summary>
class Animation
{
public:
	Animation();
	~Animation();

private:
	static AnimationBuilder* m_builder;

public:
	void LoadAnimation(const std::string& path);

private:
	std::string m_path;
};

