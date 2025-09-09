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
    void SetSize(Vector2 _size);
    void SetRect(RECT _rect);
    void SetPos(int _X, int _Y);
    void SetPosX(int _X) { m_pos.left = _X; }
    void SetPosY(int _Y) { m_pos.top = _Y; }

    RECT& const GetRect() { return m_pos; };
    SimpleMath::Vector4 const GetNormalRect() const { return m_NormalPos; }
    unsigned int* GetSate() { return &m_state; }
    void SetAssetNum(unsigned int assetNum)
    {
        m_assetNum = assetNum;
#ifdef _DEBUG
        m_assetNumMin = min(m_assetNum, m_assetNumMin);
        m_assetNumMax = max(m_assetNum, m_assetNumMax);

        m_CurrAssetNum = m_assetNumMin;
#endif // _DEBUG
    };
	bool GetIsDraw() const { return isDraw; };

private:
    float m_layer = 0.f;   // �׸��� ������ ���ϴ� ���̾� z������ �ϱ�� ������ �ϴ� ���´�.
    unsigned int m_assetNum;

#ifdef _DEBUG
    static UINT m_assetNumMax;
    static UINT m_assetNumMin;
    static UINT m_CurrAssetNum;
#endif // _DEBUG


    SimpleMath::Matrix m_worldTM = m_worldTM.Identity;
    Vector2 m_size = {100.f, 100.f};
    unsigned int m_state = 0;
    bool isDraw;

private:
    Transform* m_transform;
    RECT m_pos; // ��ġ, ������
    SimpleMath::Vector4 m_NormalPos; // ����ȭ ��ġ, ������
    
};

