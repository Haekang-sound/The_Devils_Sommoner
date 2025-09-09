#pragma once

#include "../Libraries/DXTK/Inc/SpriteFont.h"
#include "../Libraries/DXTK/Inc/SpriteBatch.h"

class DXTKFont
{
public:
	DXTKFont();
	~DXTKFont();

	void Create(ID3D11Device* pDevice, ID3D11RasterizerState* rs, ID3D11DepthStencilState* ds);
	void DrawTextColor(int x, int y, DirectX::XMFLOAT4 color, const wchar_t* text, ...);

private:
	DirectX::SpriteBatch* m_pSpriteBatch;
	DirectX::SpriteFont* m_pSpriteFont;


	// �׳� ����ϸ� ���� ������ �����.
	ID3D11RasterizerState* m_RasterizerState;
	ID3D11DepthStencilState* m_DepthStencilState;
};

/*

�߰� �� ��
�ڰ�, ����, �� ���� ����� ��Ƽ���� �׸���

WriteFactory�� �̿��� â ��ȯ���� ����� ��Ʈ

*/