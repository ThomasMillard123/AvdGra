#pragma once
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>



using namespace DirectX;
class ShadowMap
{

public:
	ShadowMap(ID3D11Device* device, UINT width, UINT height);
	~ShadowMap();
	ID3D11ShaderResourceView* DepthMapSRV();
	void BindDsvAndSetNullRenderTarget(ID3D11DeviceContext* dc);

private:
	UINT mWidth;
	UINT mHeight;
	ID3D11ShaderResourceView* mDepthMapSRV;
	ID3D11DepthStencilView* mDepthMapDSV;
	D3D11_VIEWPORT mViewport;
	
	void CleanUp();

};

