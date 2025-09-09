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

	// TODO : Animation�� Play�ϱ� ���� Renderer�� �����´�? �ϴ� ������ �ص���.
}

void AnimatorController::Finalize()
{
	
}

void AnimatorController::UpdateData()
{
	// TODO : ���� ������ �Ǿ�� �� �� ������.. Animation�� ��������� �ٽ� ���߰ڴ�.

	switch (m_animationMode)
	{
		case AnimationMode::None:
		{
			// �׳� �ƹ��͵� �ƴ� ����. �Ƹ� ����� ���� ������?
		}
			break;
		case AnimationMode::Play:
		{
			// �ִϸ��̼��� �����Ų��. �׸��� wait���� �ٲٰ�
		}
			break;
		case AnimationMode::Wait:
		{
			// �ִϸ��̼��� ��� ���� �� hasExitTime�� ��� ���� Ű �������� �� ������ ��ٸ���.
		}
			break;
		case AnimationMode::Stop:
		{
			// ���� ������ üũ�Ǿ� ���� ��� �ٽ� �ݺ�
		}
			break;
		default:
			break;
	}
}

void AnimatorController::Play()
{
	// �ִϸ��̼��� �����Ű���� ����
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
	// �ϴ� hasExitTime �˻�
	for (auto& transition : m_currentAnimationState->transitions)
	{
		if (transition->hasExitTime == true)
		{
			// TODO: ���⼭ Ű������ �˻� 
			// ���� ������ Ű������ �˻� �� ������ return �� �� ����
			assert(false);
			return false;
		}

		// decay�� ���� ���¸� �����.
		// https://cplusplus.com/reference/type_traits/decay/

		for (const auto& condition : transition->conditions)
		{
			// variant�� ����� visit�Լ��� �̿��Ͽ� ���ٽ��� �־� ���𰡸� �Ѵ�.
			// ���� ������ �ϳ��� �������� ���� ��� ���� �ִϸ��̼� ������Ʈ�� �Ѿ�� ���Ѵ�.
			bool isPass =  std::visit([](const auto& c)->bool{
				// c�� Ÿ�Կ� ���� ���� ������ �˾ƿ��� ���� value���� ���Ѵ�. TODO: ���� decay ������������ �������� ���ؼ� �غ���
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
				// ���� �ϳ��� ������� ���ϸ� �ٽ� �˻��� �ʿ䰡 ����.
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
		// entry state���� defaultState�� transition�� ���������Ѵ�.
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

		// entry state���� defaultState�� transition�� ���������Ѵ�.
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
	// TODO : ����
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
