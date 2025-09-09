#include "pch.h"
#include "AnimatorController.h"
#include "Animation.h"
#include "../Graphics/ID3DRenderer.h"

//////////////////////// AnimationState ///////////////////////////

AnimationStateNode::~AnimationStateNode()
{
	for (auto& t : transitions)
	{
		delete t;
	}
	transitions.clear();
}

//////////////////////// AniamtionController ///////////////////////////

AnimatorControllerBuilder* AnimatorController::m_builder = nullptr;

AnimatorController::AnimatorController()
	: m_animationMode(AnimationMode::None),
	m_currentAnimationState(nullptr),
	m_entryState(nullptr),
	m_exitState(nullptr),
	m_animationStates()
{

}

AnimatorController::~AnimatorController()
{

}

void AnimatorController::Initialize(ID3DRenderer* renderer)
{
	m_entryState = new AnimationStateNode();
	m_entryState->stateType = AnimationStateNode::StateType::Entry;

	m_exitState = new AnimationStateNode();
	m_exitState->stateType = AnimationStateNode::StateType::Exit;

	// TODO : Animation을 Play하기 위한 Renderer을 가져온다? 일단 생각만 해두자.
}

void AnimatorController::Finalize()
{
	
}

void AnimatorController::UpdateData()
{
	// TODO : 뭔가 연동이 되어야 할 것 같은데.. Animation이 만들어지면 다시 봐야겠다.

	switch (m_animationMode)
	{
		case AnimationMode::None:
		{
			// 그냥 아무것도 아닌 상태. 아마 사용할 일이 있을까?
		}
			break;
		case AnimationMode::Play:
		{
			// 애니메이션을 재생시킨다. 그리고 wait으로 바꾸고
		}
			break;
		case AnimationMode::Wait:
		{
			// 애니메이션이 재생 중일 때 hasExitTime일 경우 종료 키 프레임이 될 때까지 기다린다.
		}
			break;
		case AnimationMode::Stop:
		{
			// 만약 루프가 체크되어 있을 경우 다시 반복
		}
			break;
		default:
			break;
	}
}

void AnimatorController::Play()
{
	// 애니메이션을 재생시키도록 조정
	// AddConditionToTransition<int>("a", "b", AnimationCondition<int>("a", AnimationCondition<int>::CompState::Greater));
}

void AnimatorController::Wait()
{

}

void AnimatorController::Stop()
{

}

bool AnimatorController::CheckPassCurrentAnimState()
{
	// 일단 hasExitTime 검사
	for (auto& transition : m_currentAnimationState->transitions)
	{
		if (transition->hasExitTime == true)
		{
			// TODO: 여기서 키프레임 검사 
			// 만약 마지막 키프레임 검사 후 무엇을 return 할 지 결정
			assert(false);
			return false;
		}

		// decay로 순수 형태만 남긴다.
		// https://cplusplus.com/reference/type_traits/decay/

		for (const auto& condition : transition->conditions)
		{
			// variant에 내장된 visit함수를 이용하여 람다식을 넣어 무언가를 한다.
			// 만약 조건을 하나라도 만족하지 못할 경우 다음 애니메이션 스테이트로 넘어가지 못한다.
			bool isPass =  std::visit([](const auto& c)->bool{
				// c의 타입에 대한 순수 정보를 알아오고 같은 value인지 비교한다. TODO: 여기 decay 삭제했을때와 안했을때 비교해서 해보기
				if constexpr (std::is_same_v<std::decay_t<decltype(c)>, AnimationCondition<int>>)
				{
					switch (c.compState)
					{
						case AnimationCondition<int>::CompState::Greater:
						{
							return *(c.value) > c.compValue;
						}
						break;
						case AnimationCondition<int>::CompState::Less:
						{
							return *(c.value) < c.compValue;
						}
						break;
						case AnimationCondition<int>::CompState::Equals:
						{
							return *(c.value) == c.compValue;
						}
						break;
						case AnimationCondition<int>::CompState::NotEqual:
						{
							return *(c.value) != c.compValue;
						}
						break;
					}
					return false;
				}
				else if constexpr (std::is_same_v<std::decay_t<decltype(c)>, AnimationCondition<float>>)
				{
					switch (c.compState)
					{
						case AnimationCondition<float>::CompState::Greater:
						{
							return *(c.value) > c.compValue;
						}
						break;
						case AnimationCondition<float>::CompState::Less:
						{
							return *(c.value) < c.compValue;
						}
						break;
					}
					return false;
				}
				else if constexpr (std::is_same_v<std::decay_t<decltype(c)>, AnimationCondition<bool>>)
				{
					switch (c.compState)
					{
						case AnimationCondition<bool>::CompState::True:
						{
							return *(c.value) == true;
						}
						break;
						case AnimationCondition<bool>::CompState::False:
						{
							return *(c.value) == false;
						}
						break;
					}
					return false;
				}
				else
				{
					assert(false);
					return false;
				}
			}, condition);

			if (!isPass)
			{
				// 만약 하나라도 통과하지 못하면 다시 검사할 필요가 없다.
				return false;
			}
		}
	}
	return true;
}

bool AnimatorController::CheckMakeDefaultState()
{
	if (m_entryState->transitions.size() == 0)
		return true;
	else
		return false;
}

void AnimatorController::CreateState(const std::string& name)
{
	AnimationStateNode* state = new AnimationStateNode();
	state->animation = nullptr;
	m_animationStates.insert({ name, state });

	if (CheckMakeDefaultState())
	{
		state->stateType = AnimationStateNode::StateType::DefaultState;

		// TEMP : 
		//m_currentAnimationState = state;
		// entry state에서 defaultState로 transition을 만들어줘야한다.
		AnimationTransition* transition = new AnimationTransition();
		transition->nextAnimationState = state;
		m_entryState->transitions.push_back(transition);
	}
	else
	{
		state->stateType = AnimationStateNode::StateType::State;
	}
}

void AnimatorController::CreateState(const std::string& name, Animation* animation)
{
	AnimationStateNode* state = new AnimationStateNode();
	state->animation = animation;	
	m_animationStates.insert({ name, state });

	if (CheckMakeDefaultState())
	{
		state->stateType = AnimationStateNode::StateType::DefaultState;

		// entry state에서 defaultState로 transition을 만들어줘야한다.
		AnimationTransition* transition = new AnimationTransition();
		transition->nextAnimationState = state;
		m_entryState->transitions.push_back(transition);
	}
	else
	{
		state->stateType = AnimationStateNode::StateType::State;
	}
}

void AnimatorController::MakeTransition(const std::string& prevAnimState, const std::string& nextAnimState)
{
	AnimationTransition* transition = new AnimationTransition();

	if (m_animationStates[nextAnimState] == nullptr)
	{
		assert(false);
		return;
	}
	else
	{
		transition->nextAnimationState = m_animationStates[nextAnimState];
		m_animationStates[prevAnimState]->transitions.push_back(transition);
	}
}

void AnimatorController::MakeTransitionAnyState(const std::string& nextAnimState)
{
	// TODO : 구현
}

void AnimatorController::AddInt(const std::string& name, const int& value /*= 0*/)
{
	int* newInt = new int(value);
	m_parameterIntegers.insert({ name, newInt });
}

void AnimatorController::AddFloat(const std::string& name, const float& value /*= 0.f*/)
{
	float* newFloat = new float(value);
	m_parameterFloats.insert({ name, newFloat });
}

void AnimatorController::AddBool(const std::string& name, const bool& value /*= false*/)
{
	bool* newBoolean = new bool(value);
	m_parameterBools.insert({ name, newBoolean });
}

void AnimatorController::SetInt(const std::string& name, const int& value)
{
	*m_parameterIntegers[name] = value;
}

void AnimatorController::SetFloat(const std::string& name, const float& value)
{
	*m_parameterFloats[name] = value;
}

void AnimatorController::SetBool(const std::string& name, const bool& value)
{
	*m_parameterBools[name] = value;
}
