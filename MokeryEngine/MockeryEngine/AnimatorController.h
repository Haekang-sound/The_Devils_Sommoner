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

/// MK.1 : Animation을 컨트롤하기 위한 클래스


/// <summary>
/// AniamtionTransition이 다음 스테이트로 넘어갈 수 있게하는 조건
/// </summary>

template <typename Type>
struct AnimationCondition
{
	AnimationCondition() : value(nullptr) {}
	Type* value;
	// 비교할 대상의 값 // 굳이 포인터일 필요 없어도 될 듯
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
/// 각 애니메이션을 어떻게 연결할지를 관리 할 것이다.
/// 
/// </summary>
struct AnimationTransition
{
	AnimationTransition() : name(""), hasExitTime(false), nextAnimationState(nullptr) {}

	std::string name;

	// 현재 애니메이션이 끝나고 이 transition이 넘어갈 것인지를 결정한다.
	bool hasExitTime;

	/// 이스터 에그--------------------------------
	// 나는 강규석이다.
	// 나는 바보다.
	// 나는 일찐 강규석이다.
	// 나는 무섭게 생긴 게 맞다.
	// 나는 멍청이다
	// 나는 겁쟁이 전사다.
	// 나는 지능이 4다.
	// 나는 무계획이다. P 97%.
	// 나는 유치하다.

	AnimationStateNode* nextAnimationState;

	// variant를 이용하여 여러 type을 받을 수 있게한다.
	// -> 맞지 않는 구조인 것 같다.
	std::vector<std::variant<AnimationCondition<int>, AnimationCondition<float>, AnimationCondition<bool>>> conditions;
};

/// <summary>
/// 2024.01.23 - 강규석
/// Animator Controller에서 애니메이션을 관리하는 정보이다.
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

	// 현재 애니메이션
	Animation* animation;
	// 사실 아래 변수들은 될지 모르겠지만 만들어두었다. 사용안하면 지우도록 해야겠다.
	// 애니메이션 속도
	float speed;
	// 반대?
	bool mirror;

	std::vector<AnimationTransition*> transitions;
};

/// <summary>
/// 여러 Animation을 관리한다.
/// 2024.01.22 - 강규석
/// </summary>
class AnimatorController
{
	/// <summary>
	/// 현재 애니메이터가 무슨 역할을 하고 있는지. 렌더러?에게 무슨 역할을 받아와야 하는지를 결정한다.?
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

	// 현재 애니메이션을 통과할지 현재 스테이트의 transition을 통해 검사한다.
	bool CheckPassCurrentAnimState();

	// 만약 아무 스테이트도 없을 경우 현재 만드는 state를 default state로 바꾼다.
	// delete도 고려하고 만들었지만 사실 에디터도 안붙었기 때문에 Play도중 state를 delete할 경우는 없을 것 같다.
	bool CheckMakeDefaultState();

	// 새로운 스테이트를 만든다.
	void CreateState(const std::string& name);
	void CreateState(const std::string& name, Animation* animation);

	// State끼리 이어주는 Transition을 만들어 준다.
	void MakeTransition(const std::string& prevAnimState, const std::string& nextAnimState);
	// 어디에서나 조건만 만족하면 실행되는 AnyState에 만든다.
	void MakeTransitionAnyState(const std::string& nextAnimState);

	// 특정 State끼리 붙어있는 Transition을 수정하기 위해 만들었다. ex) 조건추가
	//void EditTransition(const std::string& prevAnimState, const std::string& nextAnimState);

	// 특정 Transition을 추가한다..?
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

		// 둘 사이를 연결하고 있는 transition을 찾는다.
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
		// 여기까지하다가 뭔가 이상해서 다시만들어야한다는 것을 깨달음. 일단 보류
		//animationCondition.value
		transition->conditions.push_back(animationCondition);
	}

/// Parameters : Transition에서 사용할 조건들을 만든다.
	void AddInt(const std::string& name, const int& value = 0);
	void AddFloat(const std::string& name, const float& value = 0.f);
	void AddBool(const std::string& name, const bool& value = false);

	void SetInt(const std::string& name, const int& value);
	void SetFloat(const std::string& name, const float& value);
	void SetBool(const std::string& name, const bool& value);

public:
	AnimationMode m_animationMode;

	// 현재 재생되고 있는 애니메이션 스테이트
	AnimationStateNode* m_currentAnimationState;

	// 애니메이션 스테이트가 처음 시작하는 곳
	AnimationStateNode* m_entryState;
	// 애니메이션 스테이트가 종료되면 들어오는 곳
	AnimationStateNode* m_exitState;
	std::unordered_map<std::string, AnimationStateNode*> m_animationStates;

	// Parameters
	std::unordered_map<std::string, int*> m_parameterIntegers;
	std::unordered_map<std::string, float*> m_parameterFloats;
	std::unordered_map<std::string, bool*> m_parameterBools;
};