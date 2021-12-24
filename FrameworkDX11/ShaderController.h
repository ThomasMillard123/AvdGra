#pragma once

#include <d3d11_1.h>
#include <d3dcompiler.h>
#include<vector>
#include<string>
#include<cassert>
using namespace std;

struct ShaderData
{
	string Name;
	ID3D11VertexShader* _pVertexShader;
	ID3D11GeometryShader* _pGeometryShader;
	ID3D11PixelShader* _pPixelShader;
	ID3D11InputLayout* _pVertexLayout;



	ShaderData() {
		_pVertexShader = nullptr;
		_pGeometryShader = nullptr;
		_pPixelShader = nullptr;
		_pVertexLayout = nullptr;
		Name = "A";
	}

	ShaderData(string _Name,ID3D11VertexShader* pVertexShader, ID3D11PixelShader* pPixelShader, ID3D11InputLayout* pVertexLayout , ID3D11GeometryShader* pGeometryShader = nullptr) {
		_pVertexShader = pVertexShader;
		_pGeometryShader = pGeometryShader;
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

		if (_pGeometryShader)
			_pGeometryShader->Release();
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
	ShaderData GetShaderByName(string Name);

	HRESULT NewFullScreenShader(string Name, const WCHAR* szFileName, ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);
	vector<ShaderData> GetFSShaderList() { return _FullScreenShaderData; }
	ShaderData GetFullScreenShaderByName(string Name);
	ShaderData GetFullScreenShaderByNumber(int No);


	HRESULT NewGeoShader(string Name, const WCHAR* szFileName, ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);
	ShaderData GetGeoShader() { return GeoShader; }
private:

	vector<ShaderData>_ShaderData;
	vector<ShaderData>_FullScreenShaderData;
	ShaderData GeoShader;
	UINT CurrentShader;
	
	
	HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
	HRESULT NewVertexShader(const WCHAR* szFileName,  ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext,bool instanced);
	HRESULT NewPixleShader(const WCHAR* szFileName, ID3D11Device* _pd3dDevice);
	HRESULT NewGeometryShader(const WCHAR* szFileName, ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);
	void CleanUp();

	ID3D11VertexShader* _pVertexShader = nullptr;
	ID3D11PixelShader* _pPixelShader = nullptr;
	ID3D11GeometryShader* _pGeometryShader=nullptr;
	ID3D11InputLayout* _pVertexLayout = nullptr;

	ID3D11InputLayout* g_pQuadLayout = nullptr;
	ID3D11VertexShader* g_pQuadVS = nullptr;
	ID3D11PixelShader* g_pQuadPS = nullptr;
};

