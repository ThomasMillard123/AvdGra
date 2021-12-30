#pragma once

#include <d3d11_1.h>
#include <d3dcompiler.h>
#include<vector>
#include<string>
#include<cassert>
using namespace std;
/// <summary>
/// storage for a shader's data
/// </summary>
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



/// <summary>
/// controlls all the shaders in the appliaction
/// </summary>
class ShaderController
{
public:
	ShaderController();
	~ShaderController();
	//creat shader
	HRESULT NewShader(string Name,const WCHAR* szFileName, ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);
	HRESULT NewFullScreenShader(string Name, const WCHAR* szFileName, ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);
	HRESULT NewGeoShader(string Name, const WCHAR* szFileName, ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);

	//get shader
	vector<ShaderData> GetShaderList() { return _ShaderData; }
	ShaderData GetShaderData();
	ShaderData GetShaderByName(string Name);

	vector<ShaderData> GetFSShaderList() { return _FullScreenShaderData; }
	ShaderData GetFullScreenShaderByName(string Name);
	ShaderData GetFullScreenShaderByNumber(int No);

	ShaderData GetGeoShader() { return GeoShader; }
	//set shader
	void SetShaderData(UINT ShaderSet);
	
	


	
	
private:
	//shaders 
	vector<ShaderData>_ShaderData;
	vector<ShaderData>_FullScreenShaderData;
	ShaderData GeoShader;
	UINT CurrentShader;
	
	//Load shader flies
	HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
	//creat shader data
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

