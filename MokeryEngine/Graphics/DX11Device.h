#pragma once
#include "framework.h"
#include "DX11Define.h"

// comptr
enum class CB_Type
{
	CameraBuffer,
	ObjectBuffer,
	BoneBuffer,
	EngineBuffer,
	DirectionLightBuffer,

	END,
};
enum Shader_Type
{
	All,
	VertexShader,
	PixelShader,
	DefulatPS,
	StaticVS,
	SkeletalVS,

	END,
};

struct VSList
{
	ComPtr<ID3D11VertexShader> VS;
	ComPtr<ID3D11InputLayout> Layout;
};


namespace Device
{
	struct Vertex
	{
		SimpleMath::Vector3 m_Pos;
		SimpleMath::Vector3 m_UVW;
	};
}
/// <summary>
/// ������ �� Ŭ������ �׷��Ƚ����� �������� ���� Ŭ������ �ɰ�.
/// 
/// ����Ʈ �����ӿ�ũ�� ������.
/// </summary>
class DX11Device
{
public:
	DX11Device();
	~DX11Device();

public:
	HRESULT Create(HWND hWnd, int screenWidth, int screenHeight, float _GameScreenSize);

	void OnResize(int screenWidth, int screenHeight);

	// ����̽�
	ComPtr<ID3D11Device> GetDevice() const { return m_pDevice; }
	
	// ����̽� ���ؽ�Ʈ
	ComPtr<ID3D11DeviceContext> GetDeviceContext() const { return m_pDeviceContext; }

	// ����Ÿ�ٺ�
	ID3D11RenderTargetView* GetRenderTargetView() const { return m_RenderTargetView.Get(); }
	
	// �������ٽǺ�
	ID3D11DepthStencilView* GetDepthStencilView() const { return m_pScreenDepthView.Get(); }

	// ����������Ʈ

	void OnBeginRender();
	void RenderPipeline();
	void Draw();
	void OnEndRender();

	void ClearDepthView();

#pragma region CreateFunc
	// ���ؽ� ���̴��� �����մϴ�.
	void CreateVS(std::wstring _path, ComPtr<ID3D11VertexShader>* _VS,const std::vector<D3D11_INPUT_ELEMENT_DESC>& _layout, ComPtr<ID3D11InputLayout>* _inputLayout);
	// �ȼ� ���̴��� �����մϴ�.
	void CreatePS(std::wstring _path, ComPtr<ID3D11PixelShader>* _PS);

	template<typename T>
	void CreateConstantBuffer(UINT _type);

	void CreateVertexBuffer(UINT _ByteWidth, const void* _Data, ComPtr<ID3D11Buffer>* _VertexBuffer, bool _IsDynamic = false);
	void CreateIndexBuffer(UINT _IndexCount, const void* _Data, ComPtr<ID3D11Buffer>* _IndexBuffer);

	void CreateTexture(const std::string& _Path, ComPtr<ID3D11ShaderResourceView>* _SRV);
	void CreateTexture(const std::wstring& _Path, ComPtr<ID3D11ShaderResourceView>* _SRV);
#pragma endregion
#pragma region Setter
public:
	
	
	void SetTexture(UINT _StartSlot,UINT _NumViews,ComPtr<ID3D11ShaderResourceView> _SRV, Shader_Type _renderStage)
	{
		
		switch (_renderStage)
		{
		case Shader_Type::All:
			VSSetSRV(_StartSlot, _NumViews, _SRV);
			PSSetSRV(_StartSlot, _NumViews, _SRV);
			break;
		case Shader_Type::VertexShader:
			VSSetSRV(_StartSlot, _NumViews, _SRV);
			break;
		case Shader_Type::PixelShader:
			PSSetSRV(_StartSlot, _NumViews, _SRV);
			break;
		default:
			MessageBox(NULL, L"SetShaderResources ERROR", L"SetShaderResources ERROR", NULL);
			break;
		}
		;
	}
	


	/// <summary>
	/// 
	/// </summary>
	template<typename T>
	void SetConstantBuffer(CB_Type _type, T* _data, Shader_Type _renderStage);

	void SetVertexBuffer(ComPtr<ID3D11Buffer> _VertexBuffer, UINT _Stride, UINT _Offset)
	{
		m_pVertexBuffer = _VertexBuffer.Get();
		m_Stride = _Stride;
		m_Offset = _Offset;
	};
	void SetIndexBuffer(ComPtr<ID3D11Buffer> _IndexBuffer, UINT _IndexCount)
	{
		m_pIndexBuffer = _IndexBuffer.Get(); m_IndexCount = _IndexCount;
	};

	// �ð��� ���� ��
	void VSSetStatic()
	{
		m_RasterizerState = m_pDefaultRS.Get();
		SetVertexShader(m_pStaticVS);
	}
	void VSSetSkeletal()
	{
		m_RasterizerState = m_pDefaultRS.Get();
		SetVertexShader(m_pSkeletalVS);
	}
	void VSSetSprite()
	{
		m_RasterizerState = m_pSpriteRasterizerState.Get();
		SetVertexShader(m_pSpriteVS);

	}

	void PSSetModel()
	{
		//m_pDeviceContext->RSSetViewports(1, &m_ScreenViewport);
		//m_pDeviceContext->OMSetRenderTargets(1, m_pScreenTargetView.GetAddressOf(), m_pScreenDepthView.Get());
		m_pPixelShader = m_pDefaultPS.Get();
		m_IsPixelShader = true;
	}

	void PSSetSprite()
	{
		m_pDeviceContext->RSSetViewports(1, &m_UIViewport);
		m_pDeviceContext->OMSetRenderTargets(1, m_pUITargetView.GetAddressOf(), m_pUIDepthView.Get());
		m_pPixelShader = m_pSpritePS.Get();
		m_IsPixelShader = true;
	}

	void PSSetShadow()
	{
		m_pDeviceContext->RSSetViewports(1, &m_ShadowViewport);
		m_pDeviceContext->OMSetRenderTargets(1, m_pShadowTargetView.GetAddressOf(), m_pShadowDepthView.Get());
		m_pPixelShader = m_pDefaultPS.Get();
		m_IsPixelShader = false;
	}


#pragma endregion
private:
	inline void SetVertexShader(VSList _VS);
	inline void SetPixelShader(ComPtr<ID3D11PixelShader> _PS);

	void VSSetSRV(UINT _StartSlot, UINT _NumViews, ComPtr<ID3D11ShaderResourceView> _SRV);
	void PSSetSRV(UINT _StartSlot, UINT _NumViews, ComPtr<ID3D11ShaderResourceView> _SRV);
private:
	// ����ۿ� �� ������
	ComPtr<ID3D11Device> m_pDevice;						/// D3D11 ����̽�
	ComPtr<ID3D11Device> m_pDevice2;						/// D3D11 ����̽�
	ComPtr<ID3D11Device> m_pDevice3;						/// D3D11 ����̽�

	//ComPtr<ID3D11DeviceContext> m_pDeviceContext;		/// ����̽� ���ؽ�Ʈ
	ComPtr<ID3D11DeviceContext> m_pScreenDC;			/// ����̽� ���ؽ�Ʈ
	ComPtr<ID3D11DeviceContext> m_pUIDC;				/// ����̽� ���ؽ�Ʈ

	ID3D11DeviceContext* m_pDeviceContext;



	D3D_FEATURE_LEVEL m_FeatureLevel;				// ����� ���� ����
	ComPtr<IDXGISwapChain> m_pDrawSwapChain;					/// ����ü��





	ComPtr<ID3D11RenderTargetView> m_RenderTargetView;		// ���� Ÿ�� ��
	D3D11_VIEWPORT m_Viewport;

	ComPtr<ID3D11RenderTargetView> m_pScreenTargetView;
	ComPtr<ID3D11Texture2D> m_pScreenTargetBuffer;
	ComPtr<ID3D11DepthStencilView> m_pScreenDepthView;		// ����-���ٽ� ��
	ComPtr<ID3D11Texture2D> m_pScreenDepthBuffer;			// ����-���Ľ� ����
	D3D11_VIEWPORT m_ScreenViewport;				// ����Ʈ
	ComPtr<ID3D11ShaderResourceView> m_pScreenSRV;

	// shadow

	ComPtr<ID3D11RenderTargetView> m_pShadowTargetView;
	ComPtr<ID3D11DepthStencilView> m_pShadowDepthView;		// ����-���ٽ� ��
	ComPtr<ID3D11Texture2D> m_pShdowDepthBuffer;			// ����-���Ľ� ����
	D3D11_VIEWPORT m_ShadowViewport;						// ����Ʈ
	ComPtr<ID3D11ShaderResourceView> m_pShdowSRV;


	// UI
	ComPtr<ID3D11RenderTargetView> m_pUITargetView;		// ���� Ÿ�� ��
	ComPtr<ID3D11Texture2D> m_pUITargetBuffer;
	ComPtr<ID3D11DepthStencilView> m_pUIDepthView;		// ����-���ٽ� ��
	ComPtr<ID3D11Texture2D> m_pUIDepthBuffer;			// ����-���Ľ� ����
	D3D11_VIEWPORT m_UIViewport;
	ComPtr<ID3D11ShaderResourceView> m_pUISRV;

	// Combine
	std::vector<Device::Vertex> m_Vertex;
	std::vector<UINT> m_Indices;

	ComPtr<ID3D11Buffer> m_pCombineVertexBuffer;
	ComPtr<ID3D11Buffer> m_pCombineIndexBuffer;

#pragma region Variation
private:

#pragma region DEFUALT
	VSList m_pStaticVS;
	VSList m_pSkeletalVS;
	VSList m_pSpriteVS;
	VSList m_pCombine;
	ComPtr<ID3D11PixelShader> m_pDefaultPS;
	ComPtr<ID3D11PixelShader> m_pSpritePS;
	ComPtr<ID3D11PixelShader> m_pCombinePS;


	ComPtr<ID3D11SamplerState> m_pLinearSampler;
	ComPtr<ID3D11SamplerState> m_pClampSampler;
#pragma endregion

	// �������
	// �׸��� ���� ���۹� ���̴���

	ID3D11VertexShader* m_pVertexShader = nullptr;
	ID3D11PixelShader* m_pPixelShader = nullptr;
	ID3D11InputLayout* m_pInputLayout = nullptr;
	// �� �������� �� Ŭ�������� �����մϴ�.

	ID3D11Buffer* m_pVertexBuffer = nullptr;
	ID3D11Buffer* m_pIndexBuffer = nullptr;

	UINT m_Stride = 0;
	UINT m_Offset = 0;
	UINT m_IndexCount = 0;
public:


	// ��������� �⺻ ����.


	// ���� ������Ʈ��
	ID3D11BlendState* m_pBlendState;
	ID3D11RasterizerState* m_RasterizerState;
	ID3D11DepthStencilState* m_pDepthState;
	// m_pVertexBuffer = testobj.vb;

	// Render State
	ComPtr<ID3D11RasterizerState> m_pSpriteRasterizerState;
	ComPtr<ID3D11RasterizerState> m_pDefaultRS;
	ComPtr<ID3D11BlendState> m_pDefaultBlendState;


public:
	ComPtr<ID3D11DepthStencilState> m_pDefaultDepthState;
	ComPtr<ID3D11DepthStencilState> m_pCombineDepthState;


private:
	std::vector<ComPtr<ID3D11Buffer>> m_pConstantBuffer;

private:
	HWND m_hWnd;
	bool m_Enable4xMsaa;
	UINT m_4xMsaaQuality;
	D3D_DRIVER_TYPE m_D3DDriverType;

	bool m_isWireFrame;

	bool m_IsPixelShader = true;

	UINT m_ScreenWidth = 0;
	UINT m_ScreenHeight = 0;

#pragma endregion
};



void DX11Device::SetVertexShader(VSList _VS)
{
	//m_D3DDeviceContext->VSSetShader(_VS.VS.Get(),nullptr,0);
	//m_D3DDeviceContext->IASetInputLayout(_VS.Layout.Get());

	m_pVertexShader = _VS.VS.Get();
	m_pInputLayout = _VS.Layout.Get();
};

void DX11Device::SetPixelShader(ComPtr<ID3D11PixelShader> _PS)
{
	//m_D3DDeviceContext->PSSetShader(_PS.Get(), nullptr, 0);
	m_pPixelShader = _PS.Get();
}

inline void DX11Device::VSSetSRV(UINT _StartSlot, UINT _NumViews, ComPtr<ID3D11ShaderResourceView> _SRV)
{
	ID3D11ShaderResourceView* srv = nullptr;
	m_pDeviceContext->VSGetShaderResources(_StartSlot, _NumViews, &srv);
	if (&srv != _SRV.GetAddressOf())
	{
		m_pDeviceContext->VSSetShaderResources(_StartSlot, _NumViews, _SRV.GetAddressOf());

	}
}

inline void DX11Device::PSSetSRV(UINT _StartSlot, UINT _NumViews, ComPtr<ID3D11ShaderResourceView> _SRV)
{
	ID3D11ShaderResourceView* srv = nullptr;
	m_pDeviceContext->PSGetShaderResources(_StartSlot, _NumViews, &srv);
	if (&srv != _SRV.GetAddressOf())
	{
		m_pDeviceContext->PSSetShaderResources(_StartSlot, _NumViews, _SRV.GetAddressOf());

	}
}

template<typename T>
void DX11Device::CreateConstantBuffer(UINT _type)
{
	D3D11_BUFFER_DESC vbDesc = {};
	vbDesc.ByteWidth = (UINT)(sizeof(T));
	vbDesc.CPUAccessFlags = 0;
	vbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	vbDesc.Usage = D3D11_USAGE_DEFAULT;

	//  ������ ���ٰ� �����Ѵ�.. 
	m_pDevice->CreateBuffer(&vbDesc, nullptr, m_pConstantBuffer[(UINT)_type].GetAddressOf());
}

template<typename T>
void DX11Device::SetConstantBuffer(CB_Type _type, T* _data, Shader_Type _renderStage)
{
	m_pDeviceContext->UpdateSubresource(m_pConstantBuffer[(UINT)_type].Get(), 0, nullptr, _data, 0, 0);
	/*if ((Shader_Type::DefulatPS & _renderStage) == Shader_Type::DefulatPS)
	{
		
	}*/
	if (_renderStage == Shader_Type::All)
	{
		m_pDeviceContext->PSSetConstantBuffers((UINT)_type, 1, m_pConstantBuffer[(UINT)_type].GetAddressOf());
		m_pDeviceContext->VSSetConstantBuffers((UINT)_type, 1, m_pConstantBuffer[(UINT)_type].GetAddressOf());
		return;
	}
	// �ϴ� ����ġ ���̽������� �ذ��Ѵ�.
	switch (_renderStage)
	{
	case Shader_Type::VertexShader:
		m_pDeviceContext->VSSetConstantBuffers((UINT)_type, 1, m_pConstantBuffer[(UINT)_type].GetAddressOf());
		break;
	case Shader_Type::PixelShader:
		m_pDeviceContext->PSSetConstantBuffers((UINT)_type, 1, m_pConstantBuffer[(UINT)_type].GetAddressOf());
		break;

	case Shader_Type::DefulatPS:
		m_pDeviceContext->PSSetConstantBuffers((UINT)_type, 1, m_pConstantBuffer[(UINT)_type].GetAddressOf());
		break;
	case Shader_Type::StaticVS:
	case Shader_Type::SkeletalVS:
		m_pDeviceContext->VSSetConstantBuffers((UINT)_type, 1, m_pConstantBuffer[(UINT)_type].GetAddressOf());
		break;
	default:
		MessageBox(NULL, L"CB ERROR", L"CBERROR", NULL);
		break;
	}
	;
}
