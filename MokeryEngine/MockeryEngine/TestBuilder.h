#pragma once
#include "IBuilder.h"
#include "TestType.h"
class TestBuilder :
    public IBuilder
{
public:
    // IBuilder을(를) 통해 상속됨
    void Initialize(ResourceCreator* creator) override;
    void CreateType(std::string fileName) override;
    void SetType(IResource* resource) override;

private:
    TestType* m_type;

};

