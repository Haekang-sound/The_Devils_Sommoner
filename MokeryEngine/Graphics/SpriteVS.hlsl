#include <Header.hlsli>

Sprite_PS_Input main(Static_VS_Input input)
{
    Sprite_PS_Input output = (Sprite_PS_Input)0;
    
    float4 pos = input.Pos;
    pos.w = 1;
    
    output.Pos = mul(pos, WorldTransform);
    
    // DX�� NDC���̿� WinAPI�� NDC ���� ����ȭ
    output.Pos.xy /= 2;
    // ���� ��ȯ
    output.Pos = mul(output.Pos, SpriteProjection);
    
    output.Pos.x -= 1;
    output.Pos.y += 1;
    
    output.UVW = input.UVW;
    return output;
}