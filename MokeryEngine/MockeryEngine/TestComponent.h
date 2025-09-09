#pragma once
#include "Component.h"
#include "TestType.h"
class TestComponent :
    public Component
{
public:
    // IComponent을(를) 통해 상속됨
    virtual void Start() override;
    virtual void Update(float dTime) override;
    virtual void LateUpdate(float dTime) override;
    virtual void Render() override;
    virtual void Release() override;

    void SetTestComponent(std::string dd) {};

    TestType* m_test;

    // Component을(를) 통해 상속됨
    void FixedUpdate(float dTime) override;
};

