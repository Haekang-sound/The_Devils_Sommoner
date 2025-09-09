#pragma once
#include "Component.h"
#include "framework.h"

class Transform;

/// <summary>
///  UI에 필요한 sprite를 출력하는 친구
/// 버튼, 혹은 무언가에 의해 sprite가 변경되어야 할것
/// </summary>
class SpriteRenderer : public Component
{
public:
    SpriteRenderer();
    virtual ~SpriteRenderer() {};

    virtual void Start() override;
    virtual void FixedUpdate(float dTime) override;
    virtual void Update(float dTime) override;
    virtual void LateUpdate(float dTime) override;
    virtual void Render() override;
    virtual void Release() override;

public:
	void Trigger(unsigned int _flag);   // 에셋넘버를 받아서 그린다
	void Trigger(); // 그린다.

public:
	void SriteSwitch() {};  // 스프라이트가 상태? 상황의 따라 바뀌어야 함
    void SpriteToggle();  // 두개의 스프라이트가 교차 한다.
    void SetSpriteState(unsigned int _val) { m_state = _val; } // 상태변경을 통한 흑백? 반투명 연출이 존재함
	void DrawActive();      // 현재 오브젝트를 그린다
	void DrawInactive();    // 현재 오브젝트를 그리지 않는다... 여기서 하는게 맞을까?
	void DrawForCondition() {}; // 조건부로 그린다. 예상되는 조건-> hp, timeover, 아이템 획득

public:
    unsigned int GetLayer() const { return m_layer; }   // 레이어를 얻어가서 뭔가 하지 않을까
    void SetLayer(unsigned int val) { m_layer = val; }  // 그리는 순서를 정해주면 좋지않을까
	unsigned int* GetAssetNum() { return &m_assetNum; }
    SimpleMath::Matrix* GetWorldTM() { return &m_worldTM; }
    Vector2* GetSize() { return &m_size; }
    Vector2 GetSizeXY() { return m_size; }
    void SetSize(Vector2 _size) { m_size = _size; }
    void SetRect(RECT _rect);
    unsigned int* GetSate() { return &m_state; }
    void SetAssetNum(unsigned int assetNum) { m_assetNum = assetNum; };
	bool GetIsDraw() const { return isDraw; };

private:
    float m_layer = 0.f;   // 그리는 순서를 정하는 레이어 z값으로 하기로 했지만 일단 적는다.
    unsigned int m_assetNum;
    SimpleMath::Matrix m_worldTM = m_worldTM.Identity;
    Vector2 m_size = {100.f, 100.f};
    unsigned int m_state = 0;
    bool isDraw;

private:
    Transform* m_transform;
    RECT m_pos; // 위치, 사이즈
    
};

