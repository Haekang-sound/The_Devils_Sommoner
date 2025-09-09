#pragma once
#include <string>
class AnimationBuilder;

/// <summary>
/// 2024.01.22 - ���Լ�
/// Animation�� �����ϱ� ���� ���ҽ��̴�.
/// �̰͵��� �����ؼ� Animator���� �������ַ��� �Ѵ�.
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

