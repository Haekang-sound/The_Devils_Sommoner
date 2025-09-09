#pragma once
#include "Component.h"
#include "framework.h"

class Transform;

/// <summary>
///  UI�� �ʿ��� sprite�� ����ϴ� ģ��
/// ��ư, Ȥ�� ���𰡿� ���� sprite�� ����Ǿ�� �Ұ�
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
	void Trigger(unsigned int _flag);   // ���³ѹ��� �޾Ƽ� �׸���
	void Trigger(); // �׸���.

public:
	void SriteSwitch() {};  // ��������Ʈ�� ����? ��Ȳ�� ���� �ٲ��� ��
    void SpriteToggle();  // �ΰ��� ��������Ʈ�� ���� �Ѵ�.
    void SetSpriteState(unsigned int _val) { m_state = _val; } // ���º����� ���� ���? ������ ������ ������
	void DrawActive();      // ���� ������Ʈ�� �׸���
	void DrawInactive();    // ���� ������Ʈ�� �׸��� �ʴ´�... ���⼭ �ϴ°� ������?
	void DrawForCondition() {}; // ���Ǻη� �׸���. ����Ǵ� ����-> hp, timeover, ������ ȹ��

public:
    unsigned int GetLayer() const { return m_layer; }   // ���̾ ���� ���� ���� ������
    void SetLayer(unsigned int val) { m_layer = val; }  // �׸��� ������ �����ָ� ����������
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
    float m_layer = 0.f;   // �׸��� ������ ���ϴ� ���̾� z������ �ϱ�� ������ �ϴ� ���´�.
    unsigned int m_assetNum;
    SimpleMath::Matrix m_worldTM = m_worldTM.Identity;
    Vector2 m_size = {100.f, 100.f};
    unsigned int m_state = 0;
    bool isDraw;

private:
    Transform* m_transform;
    RECT m_pos; // ��ġ, ������
    
};

