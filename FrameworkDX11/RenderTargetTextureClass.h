#pragma once
#include <windows.h>
#include <windowsx.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>

using namespace DirectX;

class RenderTargetTextureClass
{
public:
	RenderTargetTextureClass();
	RenderTargetTextureClass(ID3D11Device* _pd3dDevice, UINT width, UINT height);
	~RenderTargetTextureClass();

	HRESULT Inizalize(ID3D11Device* _pd3dDevice, UINT width, UINT height);
	HRESULT SetRenderTarget(ID3D11DeviceContext* _pImmediateContext);


	ID3D11ShaderResourceView* GetTexture() { return _pShaderResourceView; }

private:
	// RTT front
	ID3D11Texture2D* _pRrenderTargetTexture;
	ID3D11RenderTargetView* _pRenderTargetView;
	//RTT Depth
	ID3D11Texture2D* _pDepthStencil = nullptr;
	ID3D11DepthStencilView* _pDepthStencilView;

	ID3D11ShaderResourceView* _pShaderResourceView;


	void CleanUp();
};

