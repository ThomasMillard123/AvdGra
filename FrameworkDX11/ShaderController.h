#pragma once

#include <d3d11_1.h>
#include <d3dcompiler.h>
#include<vector>
#include<string>

using namespace std;

struct ShaderData
{
	string Name;
	ID3D11VertexShader* _pVertexShader;
	ID3D11PixelShader* _pPixelShader;
	ID3D11InputLayout* _pVertexLayout;

	ShaderData(string _Name,ID3D11VertexShader* pVertexShader, ID3D11PixelShader* pPixelShader, ID3D11InputLayout* pVertexLayout) {
		_pVertexShader = pVertexShader;
		_pPixelShader = pPixelShader;
		_pVertexLayout = pVertexLayout;
		Name = _Name;
	}

	void CleanUp() {

		if (_pVertexShader)
			_pVertexShader->Release();

		if (_pPixelShader)
			_pPixelShader->Release();

		if (_pVertexLayout)
			_pVertexLayout->Release();

	}

};




class ShaderController
{
public:
	ShaderController();
	~ShaderController();

	HRESULT NewShader(string Name,const WCHAR* szFileName, ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);

	vector<ShaderData> GetShaderList() { return _ShaderData; }
	ShaderData GetShaderData();
	void SetShaderData(UINT ShaderSet);


	HRESULT NewFullScreenShader(string Name, const WCHAR* szFileName, ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);
	vector<ShaderData> GetFSShaderList() { return _FullScreenShaderData; }
	

private:

	vector<ShaderData>_ShaderData;
	vector<ShaderData>_FullScreenShaderData;

	UINT CurrentShader;
	

	HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
	HRESULT NewVertexShader(const WCHAR* szFileName,  ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext );
	HRESULT NewPixleShader(const WCHAR* szFileName, ID3D11Device* _pd3dDevice);
	void CleanUp();

	ID3D11VertexShader* _pVertexShader = nullptr;
	ID3D11PixelShader* _pPixelShader = nullptr;
	ID3D11InputLayout* _pVertexLayout = nullptr;

	ID3D11InputLayout* g_pQuadLayout = nullptr;
	ID3D11VertexShader* g_pQuadVS = nullptr;
	ID3D11PixelShader* g_pQuadPS = nullptr;
};

