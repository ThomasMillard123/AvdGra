#pragma once

#include <windows.h>
#include <windowsx.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include <DirectXCollision.h>
#include <iostream>
#include <vector>

#include "Camera.h"
#include "InputControllor.h"
#include "DDSTextureLoader.h"
#include "resource.h"
#include "DrawableGameObject.h"
#include "structures.h"

#include"CameraController.h"
#include"Camera.h"

#include"ImGuiManager.h"

#include"ShaderController.h"
#include"LightControll.h"
#include"ShadowMap.h"
#include"RenderTargetTextureClass.h"
#include"BillboradObject.h"
using namespace std;

class Application
{
private:
	HINSTANCE               _hInst;
	HWND                    _hWnd;
	D3D_DRIVER_TYPE         _driverType;
	D3D_FEATURE_LEVEL       _featureLevel ;
	ID3D11Device* _pd3dDevice;
	ID3D11Device1* _pd3dDevice1;
	ID3D11DeviceContext* _pImmediateContext ;
	ID3D11DeviceContext1* _pImmediateContext1 ;
	IDXGISwapChain* _pSwapChain ;
	IDXGISwapChain1* _pSwapChain1 ;
	ID3D11RenderTargetView* _pRenderTargetView ;
	ID3D11Texture2D* _pDepthStencil = nullptr;
	ID3D11DepthStencilView* _pDepthStencilView = nullptr;
	ID3D11VertexShader* _pVertexShader;

	ID3D11PixelShader* _pPixelShader ;

	ID3D11InputLayout* _pVertexLayout ;

	ID3D11Buffer* _pConstantBuffer ;

	ID3D11Buffer* _pLightConstantBuffer;
	ID3D11Buffer* _pPostProcessingConstantBuffer;

	//post processing
	//--------------------------------------------------------
	PostProcessingCB postSettings;
	
	bool isRTT = false;


	//full screen quad
	struct SCREEN_VERTEX
	{
		XMFLOAT3 pos;
		XMFLOAT2 tex;
	};

	ID3D11Buffer* g_pScreenQuadVB = nullptr;
	
	ID3D11SamplerState* m_pPointrLinear;
	ID3D11SamplerState* m_pPointrClamp;

	RenderTargetTextureClass* RTT;
	RenderTargetTextureClass* Depth;
	ShadowMap* DepthLight;
	ShadowMap* DepthLight2;

	RenderTargetTextureClass* Fade;
	RenderTargetTextureClass* DepthOfField;
	RenderTargetTextureClass* DownSample;
	RenderTargetTextureClass* post1;
	RenderTargetTextureClass* post2;
	RenderTargetTextureClass* UpSample;
	RenderTargetTextureClass* alpha;
	//------------------------------------------------------

	BillboardObject* BillBoradObject;

	XMMATRIX                _View;
	XMMATRIX                _Projection;

	int	_viewWidth;
	int	_viewHeight;

	DrawableGameObject		_GameObject;
	DrawableGameObject		_GameObjectFloor;

	InputControllor* _controll;
	ShaderController* _Shader;
	CameraController* _pCamControll;
	ImGuiManager* DimGuiManager;
	LightControll* _pLightContol;

	Camera* _Camrea;


	

public:
	Application();
	~Application();

	LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	HRESULT Initialise(HINSTANCE hInstance, int nCmdShow);

	void Update();
	void Draw();



	bool InputControll(MSG msg);

private:

	float calculateDeltaTime();
	void setupLightForRender();
	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
	HRESULT InitDevice();
	void Cleanup();

	HRESULT		InitMesh();
	HRESULT		InitWorld(int width, int height);

	HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

};

