#pragma once
#include "Component.h"
#include "TestType.h"
class TestComponent :
    public Component
{
public:
    // IComponent��(��) ���� ��ӵ�
    virtual void Start() override;
    virtual void Update(float dTime) override;
    virtual void LateUpdate(float dTime) override;
    virtual void Render() override;
    virtual void Release() override;

    void SetTestComponent(std::string dd) {};

    TestType* m_test;

    // Component��(��) ���� ��ӵ�
    void FixedUpdate(float dTime) override;
};

