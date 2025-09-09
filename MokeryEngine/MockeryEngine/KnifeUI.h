#pragma once
#include "Component.h"

class PlayerComponent;
class SpriteRenderer;

class KnifeUI : public Component
{
public:
    // Component을(를) 통해 상속됨
    KnifeUI();
    virtual ~KnifeUI();
    virtual void Start() override;
    virtual void FixedUpdate(float dTime) override;
    virtual void Update(float dTime) override;
    virtual void LateUpdate(float dTime) override;
    virtual void Render() override;
    virtual void Release() override;
private:
    PlayerComponent* m_player;
    SpriteRenderer* m_sprite;
};

