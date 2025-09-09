#pragma once
#include "Component.h"

class ID3DRenderer;

class MeshRenderer :
    public Component//, public Renderable
{
public:
    MeshRenderer();

    // IComponent��(��) ���� ��ӵ�
	void Start() override; 
	void FixedUpdate(float dTime) override;
    void Update(float dTime) override;
    void LateUpdate(float dTime) override;
    void Render() override;
    void Release() override;

    //get/set
public:
    void SetAssetNum(UINT _AssetID) { m_AssetID = _AssetID; };
    void CreateModel();
    void SetAnimationState(UINT idx);
    void PlayAnimation();
    void StopAnimation();
    void SetAnimationSpeed(float speed);
    void SetAnimationRepeat(bool value);

    bool IsFinishAnimation();

public:
    void PlayAnimationOnce(UINT state);
    void PlayAnimationOnce(UINT state, bool returnToBeforeState);
    void PlayAnimation(UINT state);

    void SetThisIsANIMATION();
private:
    UINT m_AssetID = 0;
    UINT m_animationState = 0;

private:
    bool m_animationRepeat;

    bool m_isPlayAnimation;
    // Play Animation Once�� ȣ���� �� ���� �ִϸ��̼����� �����ֱ� ���� ����
    UINT m_beforeAnimation;

    bool m_isReturnToBeforeState;
};

