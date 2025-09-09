#pragma once
#include <string>
#include <unordered_map>
#include <vector>

#include <variant>
#include <cassert>

class ID3DRenderer;
class AnimatorControllerBuilder;
class Animation;
struct AnimationStateNode;

/// MK.1 : Animation�� ��Ʈ���ϱ� ���� Ŭ����


/// <summary>
/// AniamtionTransition�� ���� ������Ʈ�� �Ѿ �� �ְ��ϴ� ����
/// </summary>

template <typename Type>
struct AnimationCondition
{
	AnimationCondition() : value(nullptr) {}
	Type* value;
	// ���� ����� �� // ���� �������� �ʿ� ��� �� ��
	Type compValue;
};

template <>
struct AnimationCondition<int>
{
	enum class CompState
	{
		Greater,
		Less,
		Equals,
		NotEqual,
	};

	AnimationCondition(const std::string& name, CompState state, const int& compValue) : name(name), compState(CompState::Greater), value(nullptr), compValue(compValue) {}
	CompState compState;
	std::string name;
	int* value;
	int compValue;
};

template <>
struct AnimationCondition<float>
{
	enum class CompState
	{
		Greater,
		Less,
	};

	AnimationCondition(const std::string& name, CompState state, const float& value) : name(name), compState(CompState::Greater), value(nullptr), compValue(compValue) {}
	CompState compState;
	std::string name;
	float* value;
	float compValue;
};

template <>
struct AnimationCondition<bool>
{
	enum class CompState
	{
		True,
		False,
	};

	AnimationCondition(const std::string& name, CompState state) : name(name), compState(CompState::False), value(nullptr) {}
	CompState compState;
	std::string name;
	bool* value;
	//bool compValue;
};

/// <summary>
/// �� �ִϸ��̼��� ��� ���������� ���� �� ���̴�.
/// 
/// </summary>
struct AnimationTransition
{
	AnimationTransition() : name(""), hasExitTime(false), nextAnimationState(nullptr) {}

	std::string name;

	// ���� �ִϸ��̼��� ������ �� transition�� �Ѿ �������� �����Ѵ�.
	bool hasExitTime;

	/// �̽��� ����--------------------------------
	// ���� ���Լ��̴�.
	// ���� �ٺ���.
	// ���� ���� ���Լ��̴�.
	// ���� ������ ���� �� �´�.
	// ���� ��û�̴�
	// ���� ������ �����.
	// ���� ������ 4��.
	// ���� ����ȹ�̴�. P 97%.
	// ���� ��ġ�ϴ�.

	AnimationStateNode* nextAnimationState;

	// variant�� �̿��Ͽ� ���� type�� ���� �� �ְ��Ѵ�.
	// -> ���� �ʴ� ������ �� ����.
	std::vector<std::variant<AnimationCondition<int>, AnimationCondition<float>, AnimationCondition<bool>>> conditions;
};

/// <summary>
/// 2024.01.23 - ���Լ�
/// Animator Controller���� �ִϸ��̼��� �����ϴ� �����̴�.
/// </summary>
struct AnimationStateNode
{
	enum class StateType
	{
		Entry,
		DefaultState,
		State,
		Exit,
	};
	
	AnimationStateNode() : stateType(StateType::State), animation(nullptr), speed(1), mirror(false) {}
	~AnimationStateNode();

	StateType stateType;

	// ���� �ִϸ��̼�
	Animation* animation;
	// ��� �Ʒ� �������� ���� �𸣰����� �����ξ���. �����ϸ� ���쵵�� �ؾ߰ڴ�.
	// �ִϸ��̼� �ӵ�
	float speed;
	// �ݴ�?
	bool mirror;

	std::vector<AnimationTransition*> transitions;
};

/// <summary>
/// ���� Animation�� �����Ѵ�.
/// 2024.01.22 - ���Լ�
/// </summary>
class AnimatorController
{
	/// <summary>
	/// ���� �ִϸ����Ͱ� ���� ������ �ϰ� �ִ���. ������?���� ���� ������ �޾ƿ;� �ϴ����� �����Ѵ�.?
	/// </summary>
	enum class AnimationMode
	{
		None,
		Play,
		Wait,
		Stop,
	};

public:
	AnimatorController();
	~AnimatorController();

public:
	void Initialize(ID3DRenderer* renderer);
	void Finalize();

private:
	static AnimatorControllerBuilder* m_builder;

public:
	void UpdateData();

	void Play();
	void Wait();
	void Stop();

	// ���� �ִϸ��̼��� ������� ���� ������Ʈ�� transition�� ���� �˻��Ѵ�.
	bool CheckPassCurrentAnimState();

	// ���� �ƹ� ������Ʈ�� ���� ��� ���� ����� state�� default state�� �ٲ۴�.
	// delete�� ����ϰ� ��������� ��� �����͵� �Ⱥپ��� ������ Play���� state�� delete�� ���� ���� �� ����.
	bool CheckMakeDefaultState();

	// ���ο� ������Ʈ�� �����.
	void CreateState(const std::string& name);
	void CreateState(const std::string& name, Animation* animation);

	// State���� �̾��ִ� Transition�� ����� �ش�.
	void MakeTransition(const std::string& prevAnimState, const std::string& nextAnimState);
	// ��𿡼��� ���Ǹ� �����ϸ� ����Ǵ� AnyState�� �����.
	void MakeTransitionAnyState(const std::string& nextAnimState);

	// Ư�� State���� �پ��ִ� Transition�� �����ϱ� ���� �������. ex) �����߰�
	//void EditTransition(const std::string& prevAnimState, const std::string& nextAnimState);

	// Ư�� Transition�� �߰��Ѵ�..?
	template <typename Type>
	void AddConditionToTransition(const std::string& prevAnimState, const std::string& nextAnimState, AnimationCondition<Type> animationCondition)
	{
		AnimationStateNode* prevState = m_animationStates[prevAnimState];
		AnimationStateNode* nextState = m_animationStates[nextAnimState];
		AnimationTransition* transition = nullptr;

		if (!prevState || !nextState)
		{
			assert(false);
			return;
		}

		// �� ���̸� �����ϰ� �ִ� transition�� ã�´�.
		for (auto t : prevState->transitions)
		{
			if (t->nextAnimationState == nextState)
			{
				transition = t;
				break;
			}
		}

		if (!transition)
		{
			assert(false);
			return;
		}

		//AnimationCondition<>
		// 
		// ��������ϴٰ� ���� �̻��ؼ� �ٽø������Ѵٴ� ���� ������. �ϴ� ����
		//animationCondition.value
		transition->conditions.push_back(animationCondition);
	}

/// Parameters : Transition���� ����� ���ǵ��� �����.
	void AddInt(const std::string& name, const int& value = 0);
	void AddFloat(const std::string& name, const float& value = 0.f);
	void AddBool(const std::string& name, const bool& value = false);

	void SetInt(const std::string& name, const int& value);
	void SetFloat(const std::string& name, const float& value);
	void SetBool(const std::string& name, const bool& value);

public:
	AnimationMode m_animationMode;

	// ���� ����ǰ� �ִ� �ִϸ��̼� ������Ʈ
	AnimationStateNode* m_currentAnimationState;

	// �ִϸ��̼� ������Ʈ�� ó�� �����ϴ� ��
	AnimationStateNode* m_entryState;
	// �ִϸ��̼� ������Ʈ�� ����Ǹ� ������ ��
	AnimationStateNode* m_exitState;
	std::unordered_map<std::string, AnimationStateNode*> m_animationStates;

	// Parameters
	std::unordered_map<std::string, int*> m_parameterIntegers;
	std::unordered_map<std::string, float*> m_parameterFloats;
	std::unordered_map<std::string, bool*> m_parameterBools;
};