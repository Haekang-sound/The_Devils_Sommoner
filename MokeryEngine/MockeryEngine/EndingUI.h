#pragma once
#include "Component.h"
#include "framework.h"
class PlayerComponent;
class Timer;
class SpriteRenderer;
class Button;

class EndingUI : public Component
{
public:
    EndingUI();
    virtual ~EndingUI();
    // Component을(를) 통해 상속됨
    virtual void Start() override;
    virtual void FixedUpdate(float dTime) override;
    virtual void Update(float dTime) override;
    virtual void LateUpdate(float dTime) override;
    virtual void Render() override;
    virtual void Release() override;

private:
    bool m_isWin;

    public:
    PlayerComponent* m_player;
    Timer* m_timer;
    Button* m_button;
    SpriteRenderer* m_sprite;
    SpriteRenderer* m_spriteKnife;
};

