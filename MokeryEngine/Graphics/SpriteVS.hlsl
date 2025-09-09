#include <Header.hlsli>

Sprite_PS_Input main(Static_VS_Input input)
{
    Sprite_PS_Input output = (Sprite_PS_Input)0;
    
    float4 pos = input.Pos;
    pos.w = 1;
    
    output.Pos = mul(pos, WorldTransform);
    // 투영 전환
    output.Pos = mul(output.Pos, SpriteProjection);
    
    output.UVW = input.UVW;
    return output;
}