#pragma once

#include <d3d11_1.h>
#include <d3dcompiler.h>
#include<vector>


using namespace std;



class ShaderController
{
public:
	ShaderController();
	~ShaderController();


	HRESULT NewVertexShader(const WCHAR* szFileName,  ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);
	HRESULT NewPixleShader(const WCHAR* szFileName, ID3D11Device* _pd3dDevice);

	ID3D11VertexShader* GetCurrentVertexShader();
	ID3D11PixelShader* GetCurrentPixleShader();


private:

	vector<ID3D11VertexShader*> _pVertexShader;
	vector<ID3D11PixelShader*> _pPixelShader;
	ID3D11InputLayout* _pVertexLayout;
	
	int currentVertexShader;
	int currentPixleShader;
	
	

	HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

};

